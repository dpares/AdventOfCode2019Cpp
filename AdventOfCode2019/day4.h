#pragma once

#include "dailychallenge.h"

class Day4 : public DailyChallenge
{
protected:
	virtual const char* GetInputSourceFile() const override { return "input/day4.txt"; }

	virtual void ChallengeA() override;
	virtual void ChallengeB() override;
};