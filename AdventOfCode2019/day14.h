#pragma once

#include "dailychallenge.h"

#include <unordered_map>

class Day14 : public DailyChallenge
{
protected:
	virtual const char* GetInputSourceFile() const override { return "input/day14.txt"; }

	virtual void ChallengeA() override;
	virtual void ChallengeB() override;

private:
	struct Chemical
	{
		int m_Amount;
		std::string m_Name;

		Chemical(int amount, std::string name) :m_Amount(amount), m_Name(name) {};
		bool operator==(const Chemical& other) const { return m_Amount == other.m_Amount && m_Name == other.m_Name; }
	};

	struct ChemicalHash
	{
		std::size_t operator()(const Chemical& elem) const
		{
			return std::hash<std::string>{}(elem.m_Name) ^ std::hash<int>{}(elem.m_Amount);
		}
	};

	using ChemicalList = std::vector<Chemical>;
	using ChemicalMap = std::unordered_map<Chemical, ChemicalList, ChemicalHash>;

	void ParseInput();

	const Chemical* FindChemicalByName(const std::string& name) const;

	void CalculateOreRequiredToGenerateChemical(int parentsAmount, const Chemical& chemical, ChemicalList& productList);
	int CalculateOreRequiredToGenerateChemical(const std::string& name);


private:
	ChemicalMap m_ChemicalMap;
};