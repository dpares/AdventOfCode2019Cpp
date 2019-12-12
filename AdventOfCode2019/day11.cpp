#include "pch.h"

#include "day11.h"

#include "intcodecomputer.h"

bool Day11::HullPosition::operator<(const HullPosition& other) const
{
	bool isLesser = false;

	if (m_Y == other.m_Y)
	{
		isLesser = m_X < other.m_X;
	}
	else
	{
		// Order of Ys is inverted in order to see a legible message in PrintHull()
		isLesser = m_Y > other.m_Y;
	}

	return isLesser;
}

void Day11::PaintHull(bool isInitialPositionWhite)
{
	std::string inputString;
	m_Input >> inputString;

	std::deque<IntcodeComputer::Type> mapPipe;
	m_PaintedPositions.clear();

	int currentX = 0;
	int currentY = 0;
	int directionX = 0;
	int directionY = 1;

	IntcodeComputer amplifierComputer(&mapPipe);
	amplifierComputer.LoadProgram(inputString);
	amplifierComputer.SetFeedbackLoopMode(true);

	bool isFirstLoop = true;
	mapPipe.push_back(isInitialPositionWhite ? 1 : 0);

	while (!amplifierComputer.GetHasHalted())
	{
		const HullPositionListIt& hullIt = std::find_if(m_PaintedPositions.begin(), m_PaintedPositions.end(),
			[currentX, currentY](const HullPosition& pos) { return currentX == pos.m_X && currentY == pos.m_Y; });

		if (isFirstLoop)
		{
			isFirstLoop = false;
		}
		else
		{
			int inputParam = 0;
			if (hullIt != m_PaintedPositions.end() && hullIt->m_IsWhite)
			{
				inputParam = 1;
			}
			mapPipe.push_back(inputParam);
		}

		amplifierComputer.ExecuteProgram();
		if (!amplifierComputer.GetHasHalted())
		{
			const int newColor = mapPipe.front();
			mapPipe.pop_front();

			if (hullIt == m_PaintedPositions.end())
			{
				HullPosition newPaintedPosition;
				newPaintedPosition.m_X = currentX;
				newPaintedPosition.m_Y = currentY;
				newPaintedPosition.m_IsWhite = newColor != 0;

				m_PaintedPositions.push_back(newPaintedPosition);
			}
			else
			{
				hullIt->m_IsWhite = newColor != 0;
			}

			amplifierComputer.ExecuteProgram();

			const int newDirection = mapPipe.front();
			mapPipe.pop_front();

			// Turn left
			if (newDirection == 0)
			{
				directionY *= -1;
			}
			// Turn right
			else
			{
				directionX *= -1;
			}

			std::swap(directionX, directionY);

			currentX += directionX;
			currentY += directionY;
		}
	}
}

void Day11::ChallengeA()
{
	PaintHull(false);

	std::cout << "Challenge A result: " << m_PaintedPositions.size() << std::endl;
}

void Day11::PrintHull()
{
	std::sort(m_PaintedPositions.begin(), m_PaintedPositions.end());

	int previousY = 0xFFFFFFFF;
	for (const auto& hullPos : m_PaintedPositions)
	{
		if (previousY != hullPos.m_Y)
		{
			previousY = hullPos.m_Y;
			std::cout << std::endl;

			int nextX = 0;
			while (nextX < hullPos.m_X)
			{
				std::cout << '.';
				++nextX;
			}
		}

		std::cout << (hullPos.m_IsWhite ? '#' : '.');
	}
}

void Day11::ChallengeB()
{
	PaintHull(true);

	std::cout << "Challenge B result:" << std::endl;

	PrintHull();
}
