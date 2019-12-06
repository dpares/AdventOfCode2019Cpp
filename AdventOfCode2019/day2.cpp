#include "pch.h"

#include "day2.h"

void Day2::ChallengeA()
{
	std::string inputString;
	m_Input >> inputString;

	m_Computer.LoadMemory(inputString);
	m_Computer.ReplaceValues(12, 2);
	m_Computer.ExecuteProgram(0);

	std::cout << "Challenge A result: " << m_Computer.GetValue(0) << std::endl;
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
			m_Computer.LoadMemory(inputString);
			m_Computer.ReplaceValues(i, j);
			m_Computer.ExecuteProgram(0);

			if (m_Computer.GetValue(0) == 19690720)
			{
				noun = i;
				verb = j;
				break;
			}
		}
	}

	std::cout << "Challenge B result: " << 100 * noun + verb << std::endl;
}
