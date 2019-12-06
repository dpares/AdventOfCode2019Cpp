#include "pch.h"

#include "dailychallenge.h"

void DailyChallenge::Execute()
{
	m_Input.open(GetInputSourceFile());

	ChallengeA();

	m_Input.clear();
	m_Input.seekg(0);

	ChallengeB();

	m_Input.close();
}