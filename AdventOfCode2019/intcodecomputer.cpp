#include "pch.h"

#include "intcodecomputer.h"

#define LOG_INTCODE 0

void IntcodeComputer::LoadProgram(std::string input)
{
	std::istringstream stringStream{ input };
	int newElement;

	m_Memory.clear();
	m_InstructionPointer = 0;

	while (stringStream >> newElement)
	{
		m_Memory.push_back(newElement);
		if (stringStream.peek() == ',')
		{
			stringStream.ignore();
		}
	}
}

int IntcodeComputer::GetResult() const
{
	return m_Memory[0];
}

void IntcodeComputer::SetNounAndVerb(int noun, int verb)
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
		const int firstValue = m_Memory[m_InstructionPointer];
		const int opcode = firstValue % 100;
		const int paramModes = firstValue / 100;
		ParameterList params;

		switch (opcode)
		{
			case 1: // Add
			{
				params = GetNextInstructionParams(3, paramModes);
				const int lhs = GetParamValue(params[0]);
				const int rhs = GetParamValue(params[1]);
				int& memPos = GetParamValue(params[2]);

#if LOG_INTCODE
				std::cout << "MEM[" << memPos << "] = " << lhs << " + " << rhs << std::endl;
#endif
				memPos = lhs + rhs;

				break;
			}
			case 2: // Multiply
			{
				params = GetNextInstructionParams(3, paramModes);
				const int lhs = GetParamValue(params[0]);
				const int rhs = GetParamValue(params[1]);
				int& memPos = GetParamValue(params[2]);

#if LOG_INTCODE
				std::cout << "MEM[" << memPos << "] = " << lhs << " * " << rhs << std::endl;
#endif
				memPos = lhs * rhs;
				break;
			}
			case 3: // Get Input
			{
				params = GetNextInstructionParams(1, paramModes);
				int& memPos = GetParamValue(params[0]);
				int input;

				if (m_AmplifiersPipe != nullptr)
				{
					if (m_AmplifiersPipe->empty())
					{
						m_PausedInstructionPointer = m_InstructionPointer;
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
				const int value = GetParamValue(params[0]);

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
				const int testVal = GetParamValue(params[0]);
				const int newIPtr = GetParamValue(params[1]);

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
				const int testVal = GetParamValue(params[0]);
				const int newIPtr = GetParamValue(params[1]);

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
				const int lhs = GetParamValue(params[0]);
				const int rhs = GetParamValue(params[1]);
				int& memPos = GetParamValue(params[2]);

#if LOG_INTCODE
				std::cout << "MEM[" << memPos << "] = " << lhs << " < " << rhs << (lhs < rhs ? " (TRUE)" : " (FALSE)") << std::endl;
#endif

				memPos = lhs < rhs ? 1 : 0;
				break;
			}
			case 8: // Equals
			{
				params = GetNextInstructionParams(3, paramModes);
				const int lhs = GetParamValue(params[0]);
				const int rhs = GetParamValue(params[1]);
				int& memPos = GetParamValue(params[2]);

#if LOG_INTCODE
				std::cout << "MEM[" << memPos << "] = " << lhs << " == " << rhs << (lhs == rhs ? " (TRUE)" : " (FALSE)") << std::endl;
#endif

				memPos = lhs == rhs ? 1 : 0;
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

IntcodeComputer::ParameterList IntcodeComputer::GetNextInstructionParams(int numParams, int parameterModes)
{
	ParameterList parameters;
	parameters.reserve(numParams);

	for (int paramOffset = 1; paramOffset <= numParams; ++paramOffset)
	{
		const int nextParamMode = parameterModes % 10;
		
		const ParameterMode mode = nextParamMode == 0 ? ParameterMode::Position : ParameterMode::Immediate;
		const int value = m_Memory[m_InstructionPointer + paramOffset];
		parameters.emplace_back(mode, value);

		parameterModes /= 10;
	}

	return parameters;
}

int& IntcodeComputer::GetParamValue(Parameter param)
{
	return param.first == ParameterMode::Position ? m_Memory[param.second] : param.second;
}

void IntcodeComputer::OutputMemory()
{
	for (const int& value : m_Memory)
	{
		std::cout << value << ",";
	}
	std::cout << std::endl;
}