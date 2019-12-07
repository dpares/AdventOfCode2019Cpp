#pragma once

#include <vector>
#include <string>
#include <deque>

class IntcodeComputer
{
public:
	IntcodeComputer() = default;
	IntcodeComputer(std::deque<int>* pipe) : m_AmplifiersPipe(pipe) {}
	
	void LoadProgram(std::string input);

	int GetResult() const;
	void SetNounAndVerb(int noun, int verb);

	void ExecuteProgram();
	void OutputMemory();

	bool GetHasHalted() const { return m_HasHalted; }

private:
	enum class ParameterMode
	{
		Position,
		Immediate
	};

	using Parameter = std::pair<ParameterMode, int>;
	using ParameterList = std::vector<Parameter>;

	ParameterList GetNextInstructionParams(int numParams, int parameterModes);
	int& GetParamValue(Parameter param);

private:
	std::vector<int> m_Memory;
	unsigned int m_InstructionPointer = 0;
	
	std::deque<int>* m_AmplifiersPipe;

	int m_PausedInstructionPointer = -1;
	bool m_HasReceivedFirstInput = false;
	bool m_IsInFeedbackLoop = false;
	bool m_HasHalted = false;
};