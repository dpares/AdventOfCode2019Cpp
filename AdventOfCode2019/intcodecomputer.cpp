#include "pch.h"

#include "intcodecomputer.h"

#define LOG_INTCODE 0

void IntcodeComputer::LoadProgram(std::string input)
{
	std::istringstream stringStream{ input };
	Type newElement;

	m_Memory.clear();
	m_InstructionPointer = 0;
	m_RelativeBase = 0;

	while (stringStream >> newElement)
	{
		m_Memory.push_back(newElement);
		if (stringStream.peek() == ',')
		{
			stringStream.ignore();
		}
	}
}

IntcodeComputer::Type IntcodeComputer::GetResult() const
{
	return m_Memory[0];
}

void IntcodeComputer::SetNounAndVerb(Type noun, Type verb)
{
	m_Memory[1] = noun;
	m_Memory[2] = verb;
}

void IntcodeComputer::ExecuteProgram()
{
	if (m_PausedInstructionPointer != -1)
	{
		m_InstructionPointer = m_PausedInstructionPointer;
		m_PausedInstructionPointer = -1;
	}

	while (m_InstructionPointer < m_Memory.size())
	{
		const Type firstValue = m_Memory[m_InstructionPointer];
		const Type opcode = firstValue % 100;
		const Type paramModes = firstValue / 100;
		ParameterList params;

		switch (opcode)
		{
			case 1: // Add
			{
				params = GetNextInstructionParams(3, paramModes);
				const Type lhs = GetParamValue(params[0]);
				const Type rhs = GetParamValue(params[1]);
				Type& memPos = GetParamValue(params[2]);

#if LOG_INTCODE
				std::cout << "MEM[" << memPos << "] = " << lhs << " + " << rhs << std::endl;
#endif
				memPos = lhs + rhs;

				break;
			}
			case 2: // Multiply
			{
				params = GetNextInstructionParams(3, paramModes);
				const Type lhs = GetParamValue(params[0]);
				const Type rhs = GetParamValue(params[1]);
				Type& memPos = GetParamValue(params[2]);

#if LOG_INTCODE
				std::cout << "MEM[" << memPos << "] = " << lhs << " * " << rhs << std::endl;
#endif
				memPos = lhs * rhs;
				break;
			}
			case 3: // Get Input
			{
				params = GetNextInstructionParams(1, paramModes);
				Type& memPos = GetParamValue(params[0]);
				Type input;

				if (m_AmplifiersPipe != nullptr)
				{
					if (m_AmplifiersPipe->empty())
					{
						m_PausedInstructionPointer = m_InstructionPointer;
						m_WantsInput = true;
						return;
					}

					input = m_AmplifiersPipe->front();
					m_AmplifiersPipe->pop_front();

					if (m_HasReceivedFirstInput == false)
					{
						m_HasReceivedFirstInput = true;
						if (input >= 5 && input <= 9)
						{
							m_IsInFeedbackLoop = true;
						}
					}

					if (m_WantsInput)
					{
						m_WantsInput = false;
					}
				}
				else
				{
					std::cout << "Input: ";
					std::cin >> input;
				}

#if LOG_INTCODE
				std::cout << "MEM[" << memPos << "] = " << input << std::endl;
#endif
				memPos = input;
				break;
			}
			case 4: // Print Output
			{
				params = GetNextInstructionParams(1, paramModes);
				const Type value = GetParamValue(params[0]);

				if (m_AmplifiersPipe != nullptr)
				{
					m_AmplifiersPipe->push_back(value);
					if (m_IsInFeedbackLoop)
					{
						m_PausedInstructionPointer = m_InstructionPointer + 2;
						return;
					}
				}
				else
				{
					std::cout << "Output: " << value << std::endl;
				}

				break;
			}
			case 5: // Jump If True
			{
				params = GetNextInstructionParams(2, paramModes);
				const Type testVal = GetParamValue(params[0]);
				const Type newIPtr = GetParamValue(params[1]);

#if LOG_INTCODE
				std::cout << "IF " << testVal << " != 0 GOTO " << newIPtr << (testVal != 0 ? " (TRUE)" : " (FALSE)") << std::endl;

#endif

				if (testVal != 0)
				{
					m_InstructionPointer = newIPtr;
					continue;
				}
				break;
			}
			case 6: // Jump If False
			{
				params = GetNextInstructionParams(2, paramModes);
				const Type testVal = GetParamValue(params[0]);
				const Type newIPtr = GetParamValue(params[1]);

#if LOG_INTCODE
				std::cout << "IF " << testVal << " == 0 GOTO " << newIPtr << (testVal == 0 ? " (TRUE)" : " (FALSE)") << std::endl;
#endif

				if (testVal== 0)
				{
					m_InstructionPointer = newIPtr;
					continue;
				}
				break;
			}
			case 7: // Less Than
			{
				params = GetNextInstructionParams(3, paramModes);
				const Type lhs = GetParamValue(params[0]);
				const Type rhs = GetParamValue(params[1]);
				Type& memPos = GetParamValue(params[2]);

#if LOG_INTCODE
				std::cout << "MEM[" << memPos << "] = " << lhs << " < " << rhs << (lhs < rhs ? " (TRUE)" : " (FALSE)") << std::endl;
#endif

				memPos = lhs < rhs ? 1 : 0;
				break;
			}
			case 8: // Equals
			{
				params = GetNextInstructionParams(3, paramModes);
				const Type lhs = GetParamValue(params[0]);
				const Type rhs = GetParamValue(params[1]);
				Type& memPos = GetParamValue(params[2]);

#if LOG_INTCODE
				std::cout << "MEM[" << memPos << "] = " << lhs << " == " << rhs << (lhs == rhs ? " (TRUE)" : " (FALSE)") << std::endl;
#endif

				memPos = lhs == rhs ? 1 : 0;
				break;
			}
			case 9: // Adjust Relative Base
			{
				params = GetNextInstructionParams(1, paramModes);
				const Type val = GetParamValue(params[0]);

#if LOG_INTCODE
				std::cout << "RELATIVE_BASE += " << val << std::endl;
#endif

				m_RelativeBase += val;
				break;
			}
			case 99: // Halt And Catch Fire
			{
				if (m_AmplifiersPipe == nullptr)
				{
					std::cout << "**PROGRAM HALTED**" << std::endl;
				}
				m_HasHalted = true;
				return;
				break;
			}
		}

		m_InstructionPointer += params.size() + 1;
	}
}

IntcodeComputer::ParameterList IntcodeComputer::GetNextInstructionParams(Type numParams, Type parameterModes)
{
	ParameterList parameters;
	parameters.reserve(numParams);

	for (Type paramOffset = 1; paramOffset <= numParams; ++paramOffset)
	{
		const Type nextParamMode = parameterModes % 10;
		
		ParameterMode mode = ParameterMode::Position;
		if (nextParamMode == 1)
		{
			mode = ParameterMode::Immediate;
		}
		else if (nextParamMode == 2)
		{
			mode = ParameterMode::Relative;
		}

		const Type value = m_Memory[m_InstructionPointer + paramOffset];
		parameters.emplace_back(mode, value);

		parameterModes /= 10;
	}

	return parameters;
}

IntcodeComputer::Type& IntcodeComputer::GetParamValue(Parameter param)
{
	switch (param.first)
	{
		case (ParameterMode::Position):
		{
			if (param.second >= m_Memory.size())
			{
				m_Memory.resize(param.second + 1);
			}

			return m_Memory[param.second];
			break;
		}
		case (ParameterMode::Immediate):
		{
			return param.second;
			break;
		}
		case (ParameterMode::Relative):
		{
			const Type memPos = param.second + m_RelativeBase;
			if (memPos >= m_Memory.size())
			{
				m_Memory.resize(memPos + 1);
			}
			return m_Memory[memPos];
			break;
		}
	}
}

void IntcodeComputer::OutputMemory()
{
	for (const Type& value : m_Memory)
	{
		std::cout << value << ",";
	}
	std::cout << std::endl;
}