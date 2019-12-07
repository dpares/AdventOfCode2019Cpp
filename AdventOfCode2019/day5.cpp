#include "pch.h"

#include "day5.h"

void Day5::ChallengeA()
{
	std::string inputString;
	m_Input >> inputString;

	std::cout << "Challenge A:" << std::endl;

	m_Computer.LoadProgram(inputString);
	m_Computer.ExecuteProgram();
}

void Day5::ChallengeB()
{
	std::string inputString;
	m_Input >> inputString;

	std::cout << "Challenge B:" << std::endl;

	m_Computer.LoadProgram(inputString);
	m_Computer.ExecuteProgram();
}
