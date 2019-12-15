#pragma once

#include "dailychallenge.h"

#include "intcodecomputer.h"
#include <set>

class Day15 : public DailyChallenge
{
public:
	Day15() : m_Computer(&m_MazePipe) {};

protected:
	virtual const char* GetInputSourceFile() const override { return "input/day15.txt"; }

	virtual void ChallengeA() override;
	virtual void ChallengeB() override;

private:
	enum class MovementCommand
	{
		North = 1,
		South = 2,
		West = 3,
		East = 4
	};

	enum class StatusCode
	{
		Wall = 0,
		Empty = 1,
		Destination = 2,
		Oxygen = 3
	};

	struct MazeTile
	{
		int m_X = 0;
		int m_Y = 0;
		mutable StatusCode m_Type = StatusCode::Empty; // Defined mutable in order to allow changing an existing element of a std::set

		MazeTile(int x, int y, StatusCode type) : m_X(x), m_Y(y), m_Type(type) {};

		bool operator<(const MazeTile& other) const;
	};

	using GameTileList = std::set<MazeTile>;

	void PrintMaze(int x, int y) const;

	std::tuple<int, int> GetMovementVectorForCommand(MovementCommand direction) const;
	MovementCommand GetBacktrackDirection(MovementCommand direction) const;
	std::tuple<bool, StatusCode> GetStatusAtPosition(int x, int y) const;
	void SetStatusAtPosition(int x, int y, StatusCode newStatus);

	StatusCode TryMoveDrone(MovementCommand direction, bool isBacktrack = false);
	void FindShortestPathToDestination(MovementCommand backtrackDir, int stepsTaken);

	int FillMazeWithOxygen();

private:
	GameTileList m_TileList;
	IntcodeComputer m_Computer;
	std::deque<IntcodeComputer::Type> m_MazePipe;

	int m_CurX = 0;
	int m_CurY = 0;

	int m_ShortestPath = 0;

	int m_DestinationX = 0;
	int m_DestinationY = 0;
};