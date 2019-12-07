#pragma once

#include "dailychallenge.h"

class Day7 : public DailyChallenge
{
protected:
	virtual const char* GetInputSourceFile() const override { return "input/day7.txt"; }

	virtual void ChallengeA() override;
	virtual void ChallengeB() override;

private:
	static std::vector<std::vector<int>> GetPermutations(std::vector<int>& vector);
};