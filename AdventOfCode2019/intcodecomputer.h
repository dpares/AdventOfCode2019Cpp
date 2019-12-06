#pragma once

#include <vector>
#include <string>

class IntcodeComputer
{
public:
	void LoadMemory(std::string input);

	int GetValue(int pos) const;
	void ReplaceValues(int noun, int verb);

	void ExecuteProgram(int startingPos);

private:
	std::vector<int> m_Memory;
};