#include "pch.h"

#include "day8.h"

namespace
{
	constexpr int WIDTH = 25;
	constexpr int HEIGHT = 6;
	constexpr int LAYER_SIZE = WIDTH * HEIGHT;
}

Day8::LayerArity Day8::GetLayerArity(const char* layerData) const
{
	LayerArity arity;
	const char* dataPtr = layerData;
	while (dataPtr != nullptr && *dataPtr != '\0')
	{
		switch (*dataPtr)
		{
			case ('0'):
			{
				++arity.m_Zeroes;
				break;
			}
			case ('1'):
			{
				++arity.m_Ones;
				break;
			}
			case ('2'):
			{
				++arity.m_Twos;
				break;
			}
		}
		++dataPtr;
	}

	return arity;
}

void Day8::PrintImage(const char* layerData) const
{
	const char* dataPtr = layerData;
	int currentPixel = 0;
	while (dataPtr != nullptr && *dataPtr != '\0')
	{
		switch (*dataPtr)
		{
			case ('0'):
			{
				std::cout << '.';
				break;
			}
			case ('1'):
			{
				std::cout << '#';
				break;
			}
			case ('2'):
			{
				std::cout << '?';
				break;
			}
		}
		++dataPtr;

		if (currentPixel == WIDTH - 1)
		{
			std::cout << std::endl;
			currentPixel = 0;
		}
		else
		{
			++currentPixel;
		}
	}
}
void Day8::ChallengeA()
{
	char layerData[LAYER_SIZE];
	LayerArity minZeroesLayer;
	minZeroesLayer.m_Zeroes = -1;

	while (m_Input.read(layerData, LAYER_SIZE))
	{
		LayerArity newLayer = GetLayerArity(layerData);
		if (newLayer < minZeroesLayer)
		{
			minZeroesLayer = newLayer;
		}
	}

	std::cout << "Challenge A result: " << minZeroesLayer.GetOnesAndTwosProduct() << std::endl;
}

void Day8::ChallengeB()
{
	char imageData[LAYER_SIZE];
	m_Input.read(imageData, LAYER_SIZE);

	char pixelData = 0;
	int pixelIdx = 0;
	while (m_Input.get(pixelData))
	{
		char imagePixel = imageData[pixelIdx];
		if (imagePixel == '2' && pixelData != '2')
		{
			imageData[pixelIdx] = pixelData;
		}

		if (pixelIdx == LAYER_SIZE - 1)
		{
			pixelIdx = 0;
		}
		else
		{
			++pixelIdx;
		}
	}

	std::cout << "Challenge B result:" << std::endl;
	PrintImage(imageData);
}


