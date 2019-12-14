#include "pch.h"

#include "day13.h"

#define DEBUG_GAME 0

namespace
{
	const std::string CLEAR_SCREEN = std::string(100, '\n');
}

bool Day13::GameTile::operator<(const Day13::GameTile& other) const
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

void Day13::ChallengeA()
{
	std::string inputString;
	m_Input >> inputString;

	std::deque<IntcodeComputer::Type> gamePipe;
	m_TileList.clear();

	IntcodeComputer amplifierComputer(&gamePipe);
	amplifierComputer.LoadProgram(inputString);
	amplifierComputer.SetFeedbackLoopMode(true);

	int numBlocks = 0;
	while (!amplifierComputer.GetHasHalted())
	{
		amplifierComputer.ExecuteProgram();
		if (!amplifierComputer.GetHasHalted())
		{
			const int newX = static_cast<int>(gamePipe.front());
			gamePipe.pop_front();

			if (newX > m_MaxX)
			{
				m_MaxX = newX;
			}

			amplifierComputer.ExecuteProgram();

			const int newY = static_cast<int>(gamePipe.front());
			gamePipe.pop_front();

			amplifierComputer.ExecuteProgram();

			const TileType newTileType = TileType(gamePipe.front());
			gamePipe.pop_front();
			if (newTileType == TileType::Block)
			{
				++numBlocks;
			}

			m_TileList.insert(GameTile{ newX, newY, newTileType });
		}
	}

#if DEBUG_GAME
	PrintGame();
#endif

	std::cout << "Challenge A result: " << numBlocks << std::endl;
}

void Day13::PrintGame()
{
	std::cout << CLEAR_SCREEN;
	std::cout << m_GameScore << std::endl;

	int currentX = 0;
	int currentY = 0;
	for (const GameTile& tile : m_TileList)
	{
		if (currentY < tile.m_Y)
		{
			currentX = 0;
			while (currentY < tile.m_Y)
			{
				std::cout << std::endl;
				++currentY;
			}
		}

		while (currentX < tile.m_X)
		{
			std::cout << '.';
			++currentX;
		}

		switch (tile.m_Type)
		{
		case TileType::Empty:
			std::cout << '.';
			break;
		case TileType::Wall:
			std::cout << "#";
			break;
		case TileType::Block:
			std::cout << "X";
			break;
		case TileType::Ball:
			std::cout << "@";
			break;
		case TileType::HorizontalPaddle:
			std::cout << "=";
			break;
		}
	}

	std::cout << std::endl;
}

void Day13::ChallengeB()
{
	std::string inputString;
	m_Input >> inputString;

	std::deque<IntcodeComputer::Type> gamePipe;
	m_TileList.clear();

	IntcodeComputer amplifierComputer(&gamePipe);
	amplifierComputer.LoadProgram(inputString);
	amplifierComputer.SetFeedbackLoopMode(true);
	amplifierComputer.SetMemoryAtPos(0, 2);

	int ballX = 0;
	int ballY = 0;
	int paddleX = 0;

	while (!amplifierComputer.GetHasHalted())
	{
		amplifierComputer.ExecuteProgram();
		
		if (amplifierComputer.GetWantsInput())
		{
#if DEBUG_GAME
			PrintGame();

			char c;
			std::cin >> c;
#endif

			// Give new Paddle direction
			int paddleDir = 0;
			if (paddleX < ballX)
			{
				paddleDir = 1;
			}
			else if (paddleX > ballX)
			{
				paddleDir = -1;
			}
			paddleX += paddleDir;

			gamePipe.push_back(paddleDir);
			amplifierComputer.ExecuteProgram();
		}

		if (!amplifierComputer.GetHasHalted())
		{
			const int newX = static_cast<int>(gamePipe.front());
			gamePipe.pop_front();

			bool isScoreUpdate = newX == -1;
			if (newX > m_MaxX)
			{
				m_MaxX = newX;
			}

			amplifierComputer.ExecuteProgram();

			const int newY = static_cast<int>(gamePipe.front());
			gamePipe.pop_front();

			if (isScoreUpdate && newY != 0)
			{
				isScoreUpdate = false;
			}

			amplifierComputer.ExecuteProgram();

			const int thirdOutput = static_cast<int>(gamePipe.front());
			gamePipe.pop_front();

			if (isScoreUpdate)
			{
				m_GameScore = thirdOutput;
			}
			else
			{
				const TileType newTileType = TileType(thirdOutput);

				const auto& tileIt = std::find_if(m_TileList.begin(), m_TileList.end(),
					[newX, newY](const GameTile& elem) { return newX == elem.m_X && newY == elem.m_Y; });

				if (tileIt == m_TileList.cend())
				{
					m_TileList.insert(GameTile{ newX, newY, newTileType });
				}
				else
				{
					tileIt->m_Type = newTileType;
				}

				if (newTileType == TileType::Ball)
				{
					ballX = newX;
					ballY = newY;
				}
				else if (newTileType == TileType::HorizontalPaddle)
				{
					paddleX = newX;
				}
			}
		}
	}

	std::cout << "Challenge B result: " << m_GameScore << std::endl;
}
