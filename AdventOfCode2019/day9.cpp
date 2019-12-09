#include "pch.h"

#include "day9.h"

void Day9::ChallengeA()
{
	std::string inputString;
	m_Input >> inputString;

	std::cout << "Challenge A:" << std::endl;

	m_Computer.LoadProgram(inputString);
	m_Computer.ExecuteProgram();
}

void Day9::ChallengeB()
{
	std::string inputString;
	m_Input >> inputString;

	std::cout << "Challenge B:" << std::endl;

	m_Computer.LoadProgram(inputString);
	m_Computer.ExecuteProgram();
}
