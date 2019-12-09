#include "pch.h"

#include "day7.h"

#include "intcodecomputer.h"

namespace
{
	constexpr size_t NUM_AMPLIFIERS = 5;

	void GetPermutationsInternal(size_t pos, std::vector<int>& vector, std::vector<std::vector<int>>& permutationsList)
	{
		if (pos > vector.size() - 1)
		{
			permutationsList.push_back(vector);
			return;
		}

		for (size_t swapPos = pos; swapPos < vector.size(); ++swapPos)
		{
			std::swap(vector[pos], vector[swapPos]);
			GetPermutationsInternal(pos + 1, vector, permutationsList);
			std::swap(vector[pos], vector[swapPos]);
		}
		
	}
}

std::vector<std::vector<int>> Day7::GetPermutations(std::vector<int>& vector)
{
	std::vector<std::vector<int>> result;

	GetPermutationsInternal(0, vector, result);
	return result;
}

void Day7::ChallengeA()
{
	std::string inputString;
	m_Input >> inputString;

	std::deque<IntcodeComputer::Type> amplifiersPipe;
	std::vector<int> possibleSettings{ 0,1,2,3,4 };
	std::vector<std::vector<int>> settingsPermutations = GetPermutations(possibleSettings);
	int maxValue = 0;

	for (const auto& permutation : settingsPermutations)
	{
		IntcodeComputer::Type lastAmplifierOutput = 0;
		for (int ampIdx = 0; ampIdx < NUM_AMPLIFIERS; ++ampIdx)
		{
			IntcodeComputer amplifierComputer(&amplifiersPipe);
			amplifiersPipe.push_back(permutation[ampIdx]);
			amplifiersPipe.push_back(lastAmplifierOutput);

			amplifierComputer.LoadProgram(inputString);
			amplifierComputer.ExecuteProgram();

			lastAmplifierOutput = amplifiersPipe.front();
			amplifiersPipe.pop_front();

			if (lastAmplifierOutput > maxValue)
			{
				maxValue = lastAmplifierOutput;
			}
		}
	}

	std::cout << "Challenge A result: " << maxValue << std::endl;
}

void Day7::ChallengeB()
{
	std::string inputString;
	m_Input >> inputString;

	std::vector<int> possibleSettings{ 9,8,7,6,5 };
	std::vector<std::vector<int>> settingsPermutations = GetPermutations(possibleSettings);
	int maxValue = 0;

	for (const auto& permutation : settingsPermutations)
	{
		std::vector<IntcodeComputer> amplifiers;
		amplifiers.reserve(5);
		std::deque<IntcodeComputer::Type> amplifiersPipe;

		IntcodeComputer::Type lastAmplifierOutput = 0;
		
		for (int ampIdx = 0; ampIdx < NUM_AMPLIFIERS; ++ampIdx)
		{
			IntcodeComputer amplifierComputer(&amplifiersPipe);

			amplifierComputer.LoadProgram(inputString);
			amplifiers.push_back(amplifierComputer);
		}

		bool hasHalted = false;
		bool isFirstLoop = true;
		while (!hasHalted)
		{
			for (int ampIdx = 0; ampIdx < NUM_AMPLIFIERS; ++ampIdx)
			{
				if (isFirstLoop)
				{
					amplifiersPipe.push_back(permutation[ampIdx]);
				}
				amplifiersPipe.push_back(lastAmplifierOutput);

				amplifiers[ampIdx].ExecuteProgram();

				lastAmplifierOutput = amplifiersPipe.front();
				amplifiersPipe.pop_front();
			}

			isFirstLoop = false;
			hasHalted = amplifiers[amplifiers.size() - 1].GetHasHalted();
		}

		if (lastAmplifierOutput > maxValue)
		{
			maxValue = lastAmplifierOutput;
		}
	}

	std::cout << "Challenge B result: " << maxValue << std::endl;
}
