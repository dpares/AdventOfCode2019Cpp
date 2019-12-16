#pragma once

#include "dailychallenge.h"

class Day16 : public DailyChallenge
{
protected:
	virtual const char* GetInputSourceFile() const override { return "input/day16.txt"; }

	virtual void ChallengeA() override;
	virtual void ChallengeB() override;

private:
	using DigitType = int;
	using DigitList = std::vector<DigitType>;

	void ParseInput();
	DigitList BuildPatternListForOutput(int numOutput) const;
	void ExecuteFFTPhases(int numPhases);
	DigitType CalculateNextDigit(const DigitList& patternList) const;

	void PrintSignalDigits(int lastDigit) const;

	long long int GetMessageOffset() const;
	void DecodeRealSignal(long long int offset);

private:
	static constexpr int NUM_PHASES = 100;
	static constexpr int MESSAGE_LENGTH = 8;
	static constexpr int PATTERN_SIZE = 4;
	static constexpr int PATTERN[PATTERN_SIZE] = { 0, 1, 0, -1 };
	static constexpr int OFFSET_LENGTH = 7;
	static constexpr int REAL_MESSAGE_REPEATS = 10000;

	DigitList m_Signal;
	size_t m_SignalSize;
};