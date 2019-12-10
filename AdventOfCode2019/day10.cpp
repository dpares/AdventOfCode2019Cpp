#include "pch.h"

#include "day10.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <unordered_map>
#include <set>

namespace
{
	constexpr char ASTEROID = '#';
}

bool Day10::DestructionInfo::operator<(const Day10::DestructionInfo& other) const
{
	bool result = false;
	if (m_Angle == other.m_Angle)
	{
		result = m_Distance < other.m_Distance;
	}
	else
	{
		result = m_Angle < other.m_Angle;
	}

	return result;
}

bool Day10::DestructionInfo::operator==(const Day10::DestructionInfo& other) const
{
	return m_Angle == other.m_Angle && m_Distance == other.m_Distance;
}

void Day10::ParseAsteroidMap()
{
	AsteroidMapRow newRow;
	char nextChar = '\0';
	while (m_Input.get(nextChar))
	{
		newRow.push_back(nextChar);
		
		char peekChar = m_Input.peek();
		if (peekChar == '\n' || peekChar == EOF)
		{
			m_Map.emplace_back(newRow);
			newRow.clear();
			m_Input.ignore();
		}
	}
}

int Day10::GreatestCommonDivisor(int x, int y) const
{
	return y == 0 ? x : GreatestCommonDivisor(y, x % y);
}

float Day10::GetAngleBetweenPoints(Coordinates lhs, Coordinates rhs) const
{
	const float distanceX = rhs.first - lhs.first;
	const float distanceY = rhs.second - lhs.second;

	const float rads = -1 * std::atan2(distanceY, distanceX);
	float degs = rads * 180.f / M_PI;
	if (degs < 0)
	{
		degs += 360.0f;
	}

	return degs;
}

int Day10::GetSquaredDistanceBetweenPoints(Coordinates lhs, Coordinates rhs) const
{
	Coordinates distVector = { lhs.first - rhs.first, lhs.second - rhs.second };
	
	return distVector.first * distVector.first + distVector.second * distVector.second;
}

int Day10::GetAsteroidsInLOS(int originX, int originY)
{
	int numAsteroids = 0;

	for (int x = 0; x < m_Map.size(); ++x)
	{
		for (int y = 0; y < m_Map[0].size(); ++y)
		{
			if (x == originX && y == originY)
			{
				continue;
			}

			if (m_Map[x][y] == ASTEROID)
			{
				const int distX = std::abs(x - originX);
				const int distY = std::abs(y - originY);
				const int gcd = GreatestCommonDivisor(distX, distY);

				bool foundCollision = false;
				if (gcd > 1)
				{
					const int incX = originX == x ? 0 : distX / gcd;
					const int incY = originY == y ? 0 : distY / gcd;
					const bool shouldAddX = x < originX;
					const bool shouldAddY = y < originY;

					int testCoordX = shouldAddX ? x + incX : x - incX;
					int testCoordY = shouldAddY ? y + incY : y - incY;

					while (foundCollision == false && 
						testCoordX >= 0 && testCoordX < m_Map.size() &&
						testCoordY >= 0 && testCoordY < m_Map[0].size() && 
						(testCoordX != originX || testCoordY != originY) && (testCoordX != x || testCoordY != y))
					{
						if (m_Map[testCoordX][testCoordY] == ASTEROID)
						{
							foundCollision = true;
							break;
						}

						testCoordX = shouldAddX ? testCoordX + incX : testCoordX - incX;
						testCoordY = shouldAddY ? testCoordY + incY : testCoordY - incY;
					}
				}

				if (foundCollision == false)
				{
					++numAsteroids;
				}
			}
		}
	}

	return numAsteroids;
}

void Day10::ChallengeA()
{
	ParseAsteroidMap();

	int maxDetectedAsteroids = 0;

	for (int x = 0; x < m_Map.size(); ++x)
	{
		for (int y = 0; y < m_Map[0].size(); ++y)
		{
			if (m_Map[x][y] == ASTEROID)
			{
				const int numDetectedAsteroids = GetAsteroidsInLOS(x, y);
				if (numDetectedAsteroids > maxDetectedAsteroids)
				{
					maxDetectedAsteroids = numDetectedAsteroids;
					m_BestLocation = { x, y };
				}
			}
		}
	}

	std::cout << "Challenge A result: " << maxDetectedAsteroids << std::endl;
}

Day10::Coordinates Day10::GetNthDestroyedAsteroidPosition(int n) const
{
	std::vector<DestructionInfo> destructionInfoList;
	std::unordered_map<float, std::set<int>> anglesSeen;
	destructionInfoList.reserve(m_Map.size() * m_Map[0].size());

	for (int x = 0; x < m_Map.size(); ++x)
	{
		for (int y = 0; y < m_Map[0].size(); ++y)
		{
			if (m_Map[x][y] != ASTEROID || (x == m_BestLocation.first && y == m_BestLocation.second))
			{
				continue;
			}

			DestructionInfo newInfo;
			newInfo.m_Coordinates = { x,y };
			newInfo.m_Angle = GetAngleBetweenPoints(newInfo.m_Coordinates, m_BestLocation);
			newInfo.m_Distance = GetSquaredDistanceBetweenPoints(newInfo.m_Coordinates, m_BestLocation);

			anglesSeen[newInfo.m_Angle].insert(newInfo.m_Distance);

			destructionInfoList.push_back(newInfo);
		}
	}

	std::sort(destructionInfoList.begin(), destructionInfoList.end(), 
		[&](const DestructionInfo& lhs, const DestructionInfo& rhs)
		{
			float lhsAngle = lhs.m_Angle + 360.f * std::distance(anglesSeen[lhs.m_Angle].begin(), anglesSeen[lhs.m_Angle].find(lhs.m_Distance));
			float rhsAngle = rhs.m_Angle + 360.f * std::distance(anglesSeen[rhs.m_Angle].begin(), anglesSeen[rhs.m_Angle].find(rhs.m_Distance));

			return lhsAngle < rhsAngle;
		});

	return destructionInfoList[n - 1].m_Coordinates;
}

void Day10::ChallengeB()
{
	Coordinates resultLocation = GetNthDestroyedAsteroidPosition(200);
	std::cout << "Challenge B result: " << resultLocation.second * 100 + resultLocation.first << std::endl;
}