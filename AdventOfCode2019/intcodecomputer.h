#pragma once

#include <vector>
#include <string>

class IntcodeComputer
{
public:
	void LoadProgram(std::string input);

	int GetResult() const;
	void SetNounAndVerb(int noun, int verb);

	void ExecuteProgram();

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
};