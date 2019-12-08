#pragma once

#include "dailychallenge.h"

class Day8 : public DailyChallenge
{
protected:
	virtual const char* GetInputSourceFile() const override { return "input/day8.txt"; }

	virtual void ChallengeA() override;
	virtual void ChallengeB() override;

private:
	struct LayerArity
	{
		unsigned int m_Zeroes = 0;
		unsigned int m_Ones = 0;
		unsigned int m_Twos = 0;

		bool operator<(LayerArity& other) { return m_Zeroes < other.m_Zeroes; }
		int GetOnesAndTwosProduct() const { return m_Ones * m_Twos; }
	};

	LayerArity GetLayerArity(const char* layerData) const;
	void PrintImage(const char* imageData) const;
};