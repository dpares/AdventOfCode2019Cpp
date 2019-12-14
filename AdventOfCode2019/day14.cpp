#include "pch.h"

#include "day14.h"

namespace
{
	constexpr const char* ORE_STRING = "ORE";
	constexpr const char* FUEL_STRING = "FUEL";
}

void Day14::ParseInput()
{
	while (m_Input.good())
	{
		ChemicalList inputs;

		while (true)
		{
			int amount = 0;
			std::string name;
			m_Input >> amount;
			m_Input >> name;

			if (name[name.size() - 1] == ',')
			{
				name.erase(name.end() - 1);
			}

			inputs.emplace_back(amount, name);

			m_Input.ignore();
			if (m_Input.peek() == '=')
			{
				m_Input >> name; // Consume "=>";
				break;
			}
		}

		int amount = 0;
		std::string name;

		m_Input >> amount;
		m_Input >> name;

		Chemical result{ amount,name };
		m_ChemicalMap[result] = inputs;
	}


}

int Day14::CalculateOreRequiredToGetFuel() const
{
	// TODO
	return 0;
}

void Day14::ChallengeA()
{
	ParseInput();

	std::cout << "Challenge A result: " << CalculateOreRequiredToGetFuel() << std::endl;
}

void Day14::ChallengeB()
{
}


