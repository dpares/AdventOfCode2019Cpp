#include "pch.h"

#include "intcodecomputer.h"

void IntcodeComputer::LoadMemory(std::string input)
{
	std::istringstream inputStream{ input };
	int newElement;

	m_Memory.clear();

	while (inputStream >> newElement)
	{
		m_Memory.push_back(newElement);
		if (inputStream.peek() == ',')
		{
			inputStream.ignore();
		}
	}
}

int IntcodeComputer::GetValue(int pos) const
{
	return m_Memory[pos];
}

void IntcodeComputer::ReplaceValues(int noun, int verb)
{
	m_Memory[1] = noun;
	m_Memory[2] = verb;
}

void IntcodeComputer::ExecuteProgram(int startingPos)
{
	if (startingPos > m_Memory.size())
	{
		return;
	}

	const int opcode = m_Memory[startingPos];
	if (opcode == 1 || opcode == 2)
	{
		const int lhsPos = m_Memory[startingPos + 1];
		const int rhsPos = m_Memory[startingPos + 2];
		const int resultPos = m_Memory[startingPos + 3];

		if (opcode == 1)
		{
			m_Memory[resultPos] = m_Memory[lhsPos] + m_Memory[rhsPos];
		}
		else
		{
			m_Memory[resultPos] = m_Memory[lhsPos] * m_Memory[rhsPos];
		}

		ExecuteProgram(startingPos + 4);
	}
	else if (opcode == 99)
	{
		return;
	}
}