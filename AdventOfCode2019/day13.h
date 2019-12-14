#pragma once

#include "dailychallenge.h"

#include "intcodecomputer.h"
#include <set>

class Day13 : public DailyChallenge
{
protected:
	virtual const char* GetInputSourceFile() const override { return "input/day13.txt"; }

	virtual void ChallengeA() override;
	virtual void ChallengeB() override;

private:
	enum class TileType
	{
		Empty = 0,
		Wall = 1,
		Block = 2,
		HorizontalPaddle = 3,
		Ball = 4
	};

	struct GameTile
	{
		int m_X = 0;
		int m_Y = 0;
		mutable TileType m_Type = TileType::Empty; // Defined mutable in order to allow changing an existing element of a std::set

		GameTile(int x, int y, TileType type) : m_X(x), m_Y(y), m_Type(type) {};

		bool operator<(const GameTile& other) const;
	};

	using GameTileList = std::set<GameTile>;

	void PrintGame();
private:
	GameTileList m_TileList;

	int m_MaxX = 0;
	int m_GameScore = 0;
};