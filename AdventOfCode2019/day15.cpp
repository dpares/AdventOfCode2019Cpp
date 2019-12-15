#include "pch.h"

#include "day15.h"

#define DEBUG_MAZE 0

namespace
{
	const std::string CLEAR_SCREEN = std::string(100, '\n');

	constexpr int INITIAL_COORD = 21;
	constexpr int MIN_COORD = 0;
	constexpr int MAX_COORD = 40;
}

bool Day15::MazeTile::operator<(const Day15::MazeTile& other) const
{
	bool result = false;

	if (m_Y == other.m_Y)
	{
		result = m_X < other.m_X;
	}
	else
	{
		result = m_Y < other.m_Y;
	}

	return result;
}

void Day15::PrintMaze(int x, int y) const
{
	std::cout << CLEAR_SCREEN;

	std::cout << "POSITION: (" << x << " , " << y << ")" << std::endl;

	int currentX = MIN_COORD;
	int currentY = MIN_COORD;
	for (const MazeTile& tile : m_TileList)
	{
		if (currentY < tile.m_Y)
		{
			currentX = MIN_COORD;
			while (currentY < tile.m_Y)
			{
				std::cout << std::endl;
				++currentY;
			}
		}

		while (currentX < tile.m_X)
		{
			std::cout << ' ';
			++currentX;
		}
		
		if (currentX == x && currentY == y)
		{
			std::cout << 'D';
		}
		else
		{
			switch (tile.m_Type)
			{
			case StatusCode::Empty:
				std::cout << '.';
				break;
			case StatusCode::Wall:
				std::cout << '#';
				break;
			case StatusCode::Destination:
				std::cout << '@';
				break;
			case StatusCode::Oxygen:
			default:
				std::cout << 'O';
			}
		}
	}

	std::cout << std::endl;
}

std::tuple<int, int> Day15::GetMovementVectorForCommand(Day15::MovementCommand direction) const
{
	switch (direction)
	{
		case MovementCommand::North: return { 0,-1 }; break;
		case MovementCommand::South: return { 0,1 }; break;
		case MovementCommand::West: return { -1, 0 }; break;
		case MovementCommand::East: default: return { 1, 0 }; break;
	}
}

Day15::MovementCommand Day15::GetBacktrackDirection(Day15::MovementCommand direction) const
{
	switch (direction)
	{
	case MovementCommand::North: return MovementCommand::South; break;
	case MovementCommand::South: return MovementCommand::North; break;
	case MovementCommand::West: return MovementCommand::East; break;
	case MovementCommand::East: default: return MovementCommand::West; break;
	}
}

Day15::StatusCode Day15::TryMoveDrone(Day15::MovementCommand direction, bool isBacktrack /* = false*/)
{
	m_MazePipe.push_back(static_cast<IntcodeComputer::Type>(direction));

	m_Computer.ExecuteProgram();

	const StatusCode visitedStatusCode = StatusCode(m_MazePipe.front());
	m_MazePipe.pop_front();

	auto[xDir, yDir] = GetMovementVectorForCommand(direction);
	const int visitedX = m_CurX + xDir;
	const int visitedY = m_CurY + yDir;

	if (visitedStatusCode != StatusCode::Wall)
	{
		m_CurX = visitedX;
		m_CurY = visitedY;
	}

	if (isBacktrack == false)
	{
		m_TileList.insert(MazeTile{ visitedX, visitedY, visitedStatusCode });
	}

	return visitedStatusCode;
}

std::tuple<bool, Day15::StatusCode> Day15::GetStatusAtPosition(int x, int y) const
{
	bool found = false;
	StatusCode status = StatusCode::Empty;

	const auto& tileIt = std::find_if(m_TileList.cbegin(), m_TileList.cend(),
		[x, y](const MazeTile& elem) { return x == elem.m_X && y == elem.m_Y; });

	if (tileIt != m_TileList.cend())
	{
		found = true;
		status = tileIt->m_Type;
	}

	return { found, status };

}

void Day15::SetStatusAtPosition(int x, int y, Day15::StatusCode newValue)
{
	const auto& tileIt = std::find_if(m_TileList.cbegin(), m_TileList.cend(),
		[x, y](const MazeTile& elem) { return x == elem.m_X && y == elem.m_Y; });

	if (tileIt != m_TileList.cend())
	{
		tileIt->m_Type = newValue;
	}

}

void Day15::FindShortestPathToDestination(Day15::MovementCommand backtrackDir, int stepsTaken)
{
	const std::vector<MovementCommand> availableDirections = { MovementCommand::West,
		MovementCommand::South, MovementCommand::East, MovementCommand::North };

	m_Computer.ExecuteProgram();
	if (m_Computer.GetHasHalted())
	{
		return;
	}

	// Select next direction
	bool foundDestination = false;
	for (const MovementCommand& direction : availableDirections)
	{
		auto[xDir, yDir] = GetMovementVectorForCommand(direction);

		const int newX = m_CurX + xDir;
		const int newY = m_CurY + yDir;

		auto[visited, status] = GetStatusAtPosition(newX, newY);

		static bool onePathFound = false;
		if (visited == false)
		{
			status = TryMoveDrone(direction);
			MovementCommand newBacktrackDir = GetBacktrackDirection(direction);

			switch (status)
			{
			case Day15::StatusCode::Wall:
				continue;
				break;
			case Day15::StatusCode::Empty:
				FindShortestPathToDestination(newBacktrackDir, stepsTaken + 1);
				break;
			case Day15::StatusCode::Destination:
			default:
				m_ShortestPath = stepsTaken + 1;
				m_DestinationX = m_CurX;
				m_DestinationY = m_CurY;
				foundDestination = true;
				break;
			}

			if (foundDestination)
			{
				break;
			}
		}
	}

	// Backtrack
	if (m_CurX != INITIAL_COORD || m_CurY != INITIAL_COORD)
	{
		TryMoveDrone(backtrackDir, true);
	}
}

void Day15::ChallengeA()
{
	std::string inputString;
	m_Input >> inputString;

	m_TileList.clear();
	m_TileList.insert({ INITIAL_COORD, INITIAL_COORD, StatusCode::Empty });

	m_Computer.LoadProgram(inputString);
	m_Computer.SetFeedbackLoopMode(true);

	m_CurX = INITIAL_COORD;
	m_CurY = INITIAL_COORD;

	FindShortestPathToDestination(MovementCommand::North, 0);

#if DEBUG_MAZE
	PrintMaze(INITIAL_COORD, INITIAL_COORD);
#endif

	std::cout << "Challenge A result: " << m_ShortestPath << std::endl;
}

int Day15::FillMazeWithOxygen()
{
	int stepsTaken = 0;

	const std::vector<MovementCommand> availableDirections = { MovementCommand::West,
		MovementCommand::South, MovementCommand::East, MovementCommand::North };

	using Coordinates = std::pair<int, int>;
	std::deque<Coordinates> nextPointsToVisit;
	nextPointsToVisit.emplace_back(m_DestinationX, m_DestinationY);

	while (nextPointsToVisit.empty() == false)
	{
		const size_t numPointsInCurrentStep = nextPointsToVisit.size();

		for (size_t i = 0; i < numPointsInCurrentStep; ++i)
		{
			const Coordinates coords = nextPointsToVisit.front();
			nextPointsToVisit.pop_front();

			SetStatusAtPosition(coords.first, coords.second, StatusCode::Oxygen);

			for (const MovementCommand& direction : availableDirections)
			{
				auto[xDir, yDir] = GetMovementVectorForCommand(direction);

				const int newX = coords.first + xDir;
				const int newY = coords.second + yDir;

				Coordinates newCoords{ newX, newY };
				if (std::find(nextPointsToVisit.cbegin(), nextPointsToVisit.cend(), newCoords) != nextPointsToVisit.cend())
				{
					continue;
				}

				auto[visited, status] = GetStatusAtPosition(newX, newY);
				if (visited && status == StatusCode::Empty)
				{
					nextPointsToVisit.emplace_back(newCoords);
				}
			}
		}
		++stepsTaken;
	}

	return stepsTaken - 1;
}

void Day15::ChallengeB()
{
	std::string inputString;
	m_Input >> inputString;

	m_Computer.LoadProgram(inputString);
	m_Computer.SetFeedbackLoopMode(true);

	const int steps = FillMazeWithOxygen();

	std::cout << "Challenge B result: " << steps << std::endl;
}
