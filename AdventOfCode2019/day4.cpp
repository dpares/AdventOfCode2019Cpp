#include "pch.h"

#include "day4.h"

int getValidCombinationsA(const std::vector<int>& lower, const std::vector<int>& upper, int prevDigit, int curDigitIdx, bool consecutiveDigits, bool arePrevDigitsUpper, bool arePrevDigitsLower)
{
	if (curDigitIdx == lower.size())
	{
		return consecutiveDigits ? 1 : 0;
	}

	int numCombinations = 0;

	const int lowerBound = arePrevDigitsLower ? std::max(lower[curDigitIdx], prevDigit) : prevDigit;
	const int upperBound = arePrevDigitsUpper ? upper[curDigitIdx] : 9;
	for (int digit = lowerBound; digit <= upperBound; ++digit)
	{
		bool newConsecutiveDigits = consecutiveDigits;
		bool newAreDigitsUpper = arePrevDigitsUpper;
		bool newAreDigitsLower = arePrevDigitsLower;

		if (prevDigit == digit)
		{
			newConsecutiveDigits = true;
		}

		if (arePrevDigitsUpper && digit < upperBound)
		{
			newAreDigitsUpper = false;
		}

		if (arePrevDigitsLower && digit > lowerBound)
		{
			newAreDigitsLower = false;
		}

		numCombinations += getValidCombinationsA(lower, upper, digit, curDigitIdx + 1, newConsecutiveDigits, newAreDigitsUpper, newAreDigitsLower);
	}

	return numCombinations;
}

int getValidCombinationsB(const std::vector<int>& lower, const std::vector<int>& upper, int prevDigit, int curDigitIdx, int numConsecutiveDigits, bool pairFound, bool arePrevDigitsUpper, bool arePrevDigitsLower)
{
	if (curDigitIdx == lower.size())
	{
		return (pairFound || numConsecutiveDigits == 2) ? 1 : 0;
	}

	int numCombinations = 0;

	const int lowerBound = arePrevDigitsLower ? std::max(lower[curDigitIdx], prevDigit) : prevDigit;
	const int upperBound = arePrevDigitsUpper ? upper[curDigitIdx] : 9;
	for (int digit = lowerBound; digit <= upperBound; ++digit)
	{
		int newNumConsecutiveDigits = numConsecutiveDigits;
		bool newPairFound = pairFound;
		bool newAreDigitsUpper = arePrevDigitsUpper;
		bool newAreDigitsLower = arePrevDigitsLower;

		if (prevDigit == digit)
		{
			++newNumConsecutiveDigits;
		}
		else
		{
			if (numConsecutiveDigits == 2)
			{
				newPairFound = true;
			}

			newNumConsecutiveDigits = 1;
		}

		if (arePrevDigitsUpper && digit < upperBound)
		{
			newAreDigitsUpper = false;
		}

		if (arePrevDigitsLower && digit > lowerBound)
		{
			newAreDigitsLower = false;
		}

		numCombinations += getValidCombinationsB(lower, upper, digit, curDigitIdx + 1, newNumConsecutiveDigits, newPairFound, newAreDigitsUpper, newAreDigitsLower);
	}

	return numCombinations;
}

void parseVector(std::ifstream& input, std::vector<int>& vector)
{
	char nextLetter;
	int arrayIdx = 0;

	while (input.get(nextLetter) && nextLetter != '-')
	{
		vector.push_back(nextLetter - '0');
	}
}

void Day4::ChallengeA()
{
	int numPasswords = 0;
	std::vector<int> lowerLimit, upperLimit;
	
	parseVector(m_Input, lowerLimit);
	parseVector(m_Input, upperLimit);

	std::cout << "Result for Challenge A: " << getValidCombinationsA(lowerLimit, upperLimit, -1, 0, false, true, true) << std::endl;
}

void Day4::ChallengeB()
{
	int numPasswords = 0;
	std::vector<int> lowerLimit, upperLimit;

	parseVector(m_Input, lowerLimit);
	parseVector(m_Input, upperLimit);

	std::cout << "Result for Challenge B: " << getValidCombinationsB(lowerLimit, upperLimit, -1, 0, 0, false, true, true) << std::endl;
}