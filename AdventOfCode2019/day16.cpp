#include "pch.h"

#include "day16.h"

void Day16::ParseInput()
{
	m_Signal.clear();

	char digit;
	while (m_Input >> digit)
	{
		m_Signal.push_back(digit - '0');
	}

	m_SignalSize = m_Signal.size();
}

Day16::DigitList Day16::BuildPatternListForOutput(int numOutput) const
{
	DigitList patternList;
	patternList.reserve(m_SignalSize);

	bool isFirstDigit = true;
	int patternArrayIndex = 0;
	size_t digitsAdded = 0;
	while (digitsAdded < m_SignalSize)
	{
		for (int i = 0; i < numOutput; ++i)
		{
			if (isFirstDigit)
			{
				isFirstDigit = false;
				continue;
			}

			patternList.push_back(PATTERN[patternArrayIndex]);
			++digitsAdded;
		}

		patternArrayIndex = (patternArrayIndex + 1) % PATTERN_SIZE;
	}

	return patternList;
}

void Day16::ExecuteFFTPhases(int numPhases)
{
	if (numPhases == 0)
	{
		return;
	}

	DigitList newSignal;
	newSignal.reserve(m_SignalSize);
	
	for (size_t outputIndex = 1; outputIndex <= m_SignalSize; ++outputIndex)
	{
		const DigitList patternList = BuildPatternListForOutput(outputIndex);
		DigitType newDigit = CalculateNextDigit(patternList);

		newSignal.push_back(newDigit);
	}

	std::swap(m_Signal, newSignal);

	ExecuteFFTPhases(numPhases - 1);
}

Day16::DigitType Day16::CalculateNextDigit(const DigitList& patternList) const
{
	DigitType dotProduct = 0;
	for (size_t i = 0; i < m_SignalSize; ++i)
	{
		dotProduct += m_Signal[i] * patternList[i];
	}

	return std::abs(dotProduct % 10);
}

void Day16::PrintSignalDigits(int lastDigit) const
{
	for (int i = 0; i < lastDigit; ++i)
	{
		std::cout << m_Signal[i];
	}

	std::cout << std::endl;
}

void Day16::ChallengeA()
{
	ParseInput();

	ExecuteFFTPhases(NUM_PHASES);

	std::cout << "Challenge A result: ";
	PrintSignalDigits(MESSAGE_LENGTH);
}

long long int Day16::GetMessageOffset() const
{
	long long int result = 0;

	for (int i = 0; i < OFFSET_LENGTH - 1; ++i)
	{
		result += m_Signal[i];
		result *= 10;
	}
	result += m_Signal[OFFSET_LENGTH - 1];

	return result;
}

void Day16::DecodeRealSignal(long long int offset)
{
	DigitList fullMessage;
	fullMessage.reserve(m_SignalSize * REAL_MESSAGE_REPEATS);

	for (int i = 0; i < REAL_MESSAGE_REPEATS; ++i)
	{
		fullMessage.insert(fullMessage.end(), m_Signal.begin(), m_Signal.end());
	}

	const size_t fullMessageSize = fullMessage.size();

	for (int i = 0; i < NUM_PHASES; ++i)
	{
		long long int totalSum = 0;
		for (size_t index = fullMessageSize - 1; index >= offset; --index)
		{
			DigitType& digit = fullMessage[index];
			totalSum += digit;
			if (totalSum < 0)
			{
				totalSum = std::abs(totalSum);
			}

			digit = totalSum % 10;
		}
	}

	m_Signal.clear();
	m_Signal.reserve(MESSAGE_LENGTH);
	m_Signal.insert(m_Signal.end(), fullMessage.begin() + offset, fullMessage.begin() + offset + MESSAGE_LENGTH);
}

void Day16::ChallengeB()
{
	ParseInput();

	const long long int offset = GetMessageOffset();
	DecodeRealSignal(offset);

	std::cout << "Challenge B result: ";
	PrintSignalDigits(MESSAGE_LENGTH);
}


