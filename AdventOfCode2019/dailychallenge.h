#pragma once

#include <fstream>
#include <string>

class DailyChallenge
{
public:
	virtual void Execute();

protected:
	virtual const char* GetInputSourceFile() const = 0;
	virtual void ChallengeA() = 0;
	virtual void ChallengeB() = 0;

protected:
	std::ifstream m_Input;
};