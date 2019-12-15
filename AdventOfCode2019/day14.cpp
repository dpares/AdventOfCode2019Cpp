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

const Day14::Chemical* Day14::FindChemicalByName(const std::string& name) const
{
	const Chemical* chemicalPtr = nullptr;

	const auto& chemicalIt = std::find_if(m_ChemicalMap.cbegin(), m_ChemicalMap.cend(),
		[name](const auto& elem) { return name == elem.first.m_Name; });

	if (chemicalIt != m_ChemicalMap.cend())
	{
		chemicalPtr = &chemicalIt->first;
	}

	return chemicalPtr;
}


// DOES NOT WORK FOR SAMPLES 4, FIVE NOR TEST
void Day14::CalculateOreRequiredToGenerateChemical(int amountNeeded, const Chemical& chemical, ChemicalList& productList)
{
	const Chemical* parentPtr = FindChemicalByName(chemical.m_Name);
	ChemicalList& inputs = m_ChemicalMap[*parentPtr];

	if (inputs[0].m_Name == ORE_STRING)
	{
		const auto& productIt = std::find_if(productList.begin(), productList.end(),
			[&chemical](const Chemical& elem) { return chemical.m_Name == elem.m_Name; });
		if (productIt == productList.end())
		{
			productList.emplace_back(amountNeeded, chemical.m_Name);
		}
		else
		{
			productIt->m_Amount += amountNeeded;
		}

		return;
	}

	for (const Chemical& input : inputs)
	{
		const int amountPerReaction = parentPtr->m_Amount;
		const int parentAmountNeeded = chemical.m_Amount;
		const int newAmountNeeded= static_cast<int>(std::ceilf(amountNeeded / (float)amountPerReaction)) * input.m_Amount;

		CalculateOreRequiredToGenerateChemical(newAmountNeeded, input, productList);
	}
}

void Day14::ChallengeA()
{
	ParseInput();

	const Chemical* fuelPtr = FindChemicalByName(FUEL_STRING);
	ChemicalList productList;

	CalculateOreRequiredToGenerateChemical(1, *fuelPtr, productList);

	int oreAmount = 0;
	for (const Chemical& product : productList)
	{
		const Chemical* productPtr = FindChemicalByName(product.m_Name);
		Chemical oreNode = m_ChemicalMap[*productPtr][0];

		oreAmount += static_cast<int>(std::ceilf(product.m_Amount / (float)productPtr->m_Amount)) * oreNode.m_Amount;
	}

	std::cout << "Challenge A result: " << oreAmount << std::endl;
}

void Day14::ChallengeB()
{
}


