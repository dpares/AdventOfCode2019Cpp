#include "pch.h"

#include "day2.h"

void Day2::ChallengeA()
{
	std::string inputString;
	m_Input >> inputString;

	m_Computer.LoadProgram(inputString);
	m_Computer.SetNounAndVerb(12, 2);
	m_Computer.ExecuteProgram();

	std::cout << "Challenge A result: " << m_Computer.GetResult() << std::endl;
}

void Day2::ChallengeB()
{
	std::string inputString;
	m_Input >> inputString;

	int noun = 0;
	int verb = 0;

	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			m_Computer.LoadProgram(inputString);
			m_Computer.SetNounAndVerb(i, j);
			m_Computer.ExecuteProgram();

			if (m_Computer.GetResult() == 19690720)
			{
				noun = i;
				verb = j;
				break;
			}
		}
	}

	std::cout << "Challenge B result: " << 100 * noun + verb << std::endl;
}
