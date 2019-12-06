#pragma once

#include "dailychallenge.h"

class Day3 : public DailyChallenge
{
protected:
	virtual const char* GetInputSourceFile() const override { return "input/day3.txt"; }

	virtual void ChallengeA() override;
	virtual void ChallengeB() override;
};