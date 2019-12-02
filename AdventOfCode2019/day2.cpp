#include "pch.h"

void loadMemory(std::string input, std::vector<int>& memory)
{
	std::istringstream inputStream{ input };
	int newElement;

	memory.clear();

	while (inputStream >> newElement)
	{
		memory.push_back(newElement);
		if (inputStream.peek() == ',')
		{
			inputStream.ignore();
		}
	}
}

void replaceValues(std::vector<int>& memory, int noun, int verb)
{
	memory[1] = noun;
	memory[2] = verb;
}

void executeProgram(std::vector<int>& memory, int startingPos)
{
	if (startingPos > memory.size())
	{
		return;
	}

	const int opcode = memory[startingPos];
	if (opcode == 1 || opcode == 2)
	{
		const int lhsPos = memory[startingPos + 1];
		const int rhsPos = memory[startingPos + 2];
		const int resultPos = memory[startingPos + 3];

		if (opcode == 1)
		{
			memory[resultPos] = memory[lhsPos] + memory[rhsPos];
		}
		else
		{
			memory[resultPos] = memory[lhsPos] * memory[rhsPos];
		}

		executeProgram(memory, startingPos + 4);
	}
	else if (opcode == 99)
	{
		return;
	}
}

void challengeA(std::vector<int>& memory, std::ifstream& input)
{
	std::string inputString;
	input >> inputString;

	loadMemory(inputString, memory);
	replaceValues(memory, 12, 2);
	executeProgram(memory, 0);
}

void challengeB(std::vector<int>& memory, std::ifstream& input, int& noun, int& verb)
{
	std::string inputString;
	input >> inputString;

	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			loadMemory(inputString, memory);
			replaceValues(memory, i, j);
			executeProgram(memory, 0);

			if (memory[0] == 19690720)
			{
				noun = i;
				verb = j;

				return;
			}
		}
	}
}

int main()
{
	std::ifstream input("input/day2.txt", std::ifstream::in);
	std::vector<int> memory;

	challengeA(memory, input);
	std::cout << "Challenge A result: " << memory[0] << std::endl;

	input.clear();
	input.seekg(0);

	int noun = 0;
	int verb = 0;
	challengeB(memory, input, noun, verb);
	std::cout << "Challenge B result: " << 100 * noun + verb << std::endl;
}
