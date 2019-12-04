#include "pch.h"

void buildPath(std::string input, std::vector<std::pair<int, int>>& memory)
{
	std::istringstream inputStream{ input };

	std::pair<int, int> startingPoint{ 0,0 };

	char direction;
	while (inputStream.get(direction))
	{
		std::pair<int, int> nextDirection{ 0,0 };
		switch (direction)
		{
			case 'R':
			{
				nextDirection.first = 1;
				break;
			}
			case 'L':
			{
				nextDirection.first = -1;
				break;
			}
			case 'U':
			{
				nextDirection.second = 1;
				break;
			}
			case 'D':
			{
				nextDirection.second = -1;
				break;
			}
		}

		std::string numString;
		char nextChar;
		while (inputStream.get(nextChar) && nextChar != ',')
		{
			numString.push_back(nextChar);
		}
		numString.push_back('\0');

		int newCoordinate = std::stoi(numString);
		std::pair<int, int> newPoint = { 
			startingPoint.first + nextDirection.first * newCoordinate, 
			startingPoint.second + nextDirection.second * newCoordinate 
		};

		memory.push_back(newPoint);
		startingPoint = newPoint;
	}
}

bool isBetween(int value, int a, int b)
{
	return std::min(a, b) < value && value < std::max(a,b);
}

int findNearestCollision(const std::vector<std::pair<int, int>>& wirePath1, const std::vector<std::pair<int, int>>& wirePath2)
{
	unsigned int distanceToCollision = 0xFFFFFFFF;

	std::pair<int, int> prevPoint1{ 0,0 };

	for (const auto& newPoint1 : wirePath1)
	{
		std::pair<int, int> prevPoint2{ 0,0 };
		for (const auto& newPoint2 : wirePath2)
		{
			int collisionManhattanDistance = 0xFFFFFFFF;

			if (prevPoint1.first == newPoint1.first &&
				prevPoint2.second == newPoint2.second &&
				isBetween(prevPoint1.first, prevPoint2.first, newPoint2.first) &&
				isBetween(prevPoint2.second, prevPoint1.second, newPoint1.second))
			{
				collisionManhattanDistance = std::abs(prevPoint1.first) + std::abs(prevPoint2.second);
			}
			else if(prevPoint1.second == newPoint1.second &&
					prevPoint2.first == newPoint2.first &&
					isBetween(prevPoint1.second, prevPoint2.second, newPoint2.second) &&
					isBetween(prevPoint2.first, prevPoint1.first, newPoint1.first))
			{
				collisionManhattanDistance = std::abs(prevPoint1.second) + std::abs(prevPoint2.first);
			}

			if (collisionManhattanDistance < distanceToCollision)
			{
				distanceToCollision = collisionManhattanDistance;
			}

			prevPoint2 = newPoint2;
		}

		prevPoint1 = newPoint1;
	}

	return distanceToCollision;
}

int challengeC(std::ifstream& input)
{
	std::vector<std::pair<int, int>> wirePath1, wirePath2;
	std::string inputString;

	input >> inputString;
	buildPath(inputString, wirePath1);

	input >> inputString;
	buildPath(inputString, wirePath2);

	return findNearestCollision(wirePath1, wirePath2);
}

int findShortestCollisionPath(const std::vector<std::pair<int, int>>& wirePath1, const std::vector<std::pair<int, int>>& wirePath2)
{
	unsigned int minPathLength = 0xFFFFFFFF;

	int currentPathLength1 = 0;
	std::pair<int, int> prevPoint1{ 0,0 };
	for (const auto& newPoint1 : wirePath1)
	{
		int currentPathLength2 = 0;
		std::pair<int, int> prevPoint2{ 0,0 };
		for (const auto& newPoint2 : wirePath2)
		{
			int collisionPathLength = 0xFFFFFFFF;

			if (prevPoint1.first == newPoint1.first &&
				prevPoint2.second == newPoint2.second &&
				isBetween(prevPoint1.first, prevPoint2.first, newPoint2.first) &&
				isBetween(prevPoint2.second, prevPoint1.second, newPoint1.second))
			{
				collisionPathLength = (currentPathLength1 + std::abs(prevPoint1.second - prevPoint2.second)) + 
					(currentPathLength2 + std::abs(prevPoint2.first - prevPoint1.first));
			}
			else if (prevPoint1.second == newPoint1.second &&
					prevPoint2.first == newPoint2.first &&
					isBetween(prevPoint1.second, prevPoint2.second, newPoint2.second) &&
					isBetween(prevPoint2.first, prevPoint1.first, newPoint1.first))
			{
				collisionPathLength = (currentPathLength1 + std::abs(prevPoint2.first - prevPoint1.first)) +
					(currentPathLength2 + std::abs(prevPoint2.second - prevPoint1.second));
			}

			if (collisionPathLength < minPathLength)
			{
				minPathLength = collisionPathLength;
			}

			if (prevPoint2.first == newPoint2.first)
			{
				currentPathLength2 += std::abs(newPoint2.second - prevPoint2.second);
			}
			else if (prevPoint2.second == newPoint2.second)
			{
				currentPathLength2 += std::abs(newPoint2.first - prevPoint2.first);
			}

			prevPoint2 = newPoint2;
		}

		if (prevPoint1.first == newPoint1.first)
		{
			currentPathLength1 += std::abs(newPoint1.second - prevPoint1.second);
		}
		else if (prevPoint1.second == newPoint1.second)
		{
			currentPathLength1 += std::abs(newPoint1.first - prevPoint1.first);
		}

		prevPoint1 = newPoint1;
	}

	return minPathLength;
}

int challengeD(std::ifstream& input)
{
	std::vector<std::pair<int, int>> wirePath1, wirePath2;
	std::string inputString;

	input >> inputString;
	buildPath(inputString, wirePath1);

	input >> inputString;
	buildPath(inputString, wirePath2);

	return findShortestCollisionPath(wirePath1, wirePath2);
}

/*int main()
{
	std::ifstream input("input/day3.txt", std::ifstream::in);

	std::cout << "Challenge C result: " << challengeC(input) << std::endl;

	input.clear();
	input.seekg(0);

	std::cout << "Challenge D result: " << challengeD(input) << std::endl;
}*/
