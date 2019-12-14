#pragma once

#include <vector>
#include <string>
#include <deque>

class IntcodeComputer
{
public:
	using Type = long long int;

	IntcodeComputer() = default;
	IntcodeComputer(std::deque<Type>* pipe) : m_AmplifiersPipe(pipe) {}
	
	void LoadProgram(std::string input);

	Type GetResult() const;
	void SetMemoryAtPos(size_t index, Type value) { m_Memory[index] = value; }
	void SetNounAndVerb(Type noun, Type verb);

	void ExecuteProgram();
	void OutputMemory();

	bool GetHasHalted() const { return m_HasHalted; }
	bool GetWantsInput() const { return m_WantsInput; }
	void SetFeedbackLoopMode(bool value) { m_IsInFeedbackLoop = value; }

private:
	enum class ParameterMode
	{
		Position,
		Immediate,
		Relative,
	};

	using Parameter = std::pair<ParameterMode, Type>;
	using ParameterList = std::vector<Parameter>;

	ParameterList GetNextInstructionParams(Type numParams, Type parameterModes);
	Type& GetParamValue(Parameter param);

private:
	std::vector<Type> m_Memory;
	Type m_InstructionPointer = 0;
	
	std::deque<Type>* m_AmplifiersPipe;

	Type m_PausedInstructionPointer = -1;
	bool m_HasReceivedFirstInput = false;
	bool m_IsInFeedbackLoop = false;
	bool m_HasHalted = false;
	bool m_WantsInput = false;

	Type m_RelativeBase = 0;
};