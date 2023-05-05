#include "pch.h"
#include "GivenNumber.h"
#include "Sprite.h"
#include <iostream>
#include <vector>
#include "utils.h"

GivenNumber::GivenNumber(InputNumber::BaseTypes givenBaseType, const Point2f& titleBottomLeftPosition)
	: m_CurrentBaseType{givenBaseType}
	, m_HasOneActive{false}
	, m_pFirstInputNumber{nullptr}
	, m_pSecondInputNumber{nullptr}
	, m_pGivenTypeTexture{nullptr}
	, m_pGivenBaseTypeTexture{nullptr}
	, m_pGreenNumbersTexture{nullptr}
	, m_FontPath{"Resources/Baloo.ttf"}
	, m_TextSize{42}
	, m_TextColor{Color4f{98.f / 255.f, 146.f / 255.f, 99.f / 255.f, 1.f}}
	, m_GivenTypeTexturePosition{titleBottomLeftPosition}
	, m_BaseTypeTexturePosition{ Point2f{titleBottomLeftPosition.x + 370.f, titleBottomLeftPosition.y - 50.f} }
	, m_GreenNumbersPosition{ Point2f{titleBottomLeftPosition.x + 340.f, titleBottomLeftPosition.y - 30.f} }
	, m_TextSizeBaseType{28}

{

	Point2f tempPos1{ titleBottomLeftPosition.x, titleBottomLeftPosition.y - 100.f };
	Point2f tempPos2{ titleBottomLeftPosition.x, titleBottomLeftPosition.y - 240.f };
	switch (m_CurrentBaseType)
	{
	case InputNumber::BaseTypes::binary:
		m_pFirstInputNumber = new InputNumber(InputNumber::BaseTypes::decimal, tempPos1);
		m_pSecondInputNumber = new InputNumber(InputNumber::BaseTypes::hexadecimal, tempPos2);
		m_pGivenTypeTexture = new Texture("Binary", m_FontPath, m_TextSize, m_TextColor);
		m_pGivenBaseTypeTexture = new Texture("2", m_FontPath, m_TextSizeBaseType, m_TextColor);
		break;
	case InputNumber::BaseTypes::decimal:
		m_pFirstInputNumber = new InputNumber(InputNumber::BaseTypes::binary, tempPos1);
		m_pSecondInputNumber = new InputNumber(InputNumber::BaseTypes::hexadecimal, tempPos2);
		m_pGivenTypeTexture = new Texture("Decimal", m_FontPath, m_TextSize, m_TextColor);
		m_pGivenBaseTypeTexture = new Texture("10", m_FontPath, m_TextSizeBaseType, m_TextColor);
		break;
	case InputNumber::BaseTypes::hexadecimal:
		m_pFirstInputNumber = new InputNumber(InputNumber::BaseTypes::decimal, tempPos1);
		m_pSecondInputNumber = new InputNumber(InputNumber::BaseTypes::binary, tempPos2);
		m_pGivenTypeTexture = new Texture("Hexadecimal", m_FontPath, m_TextSize, m_TextColor);
		m_pGivenBaseTypeTexture = new Texture("16", m_FontPath, m_TextSizeBaseType, m_TextColor);
		break;
	}

	m_pGreenNumbersTexture = new Sprite("Resources/green.png", 16, 1, Point2f{0.f, 0.f});

	m_pRefreshTexture = new Texture("Resources/Refresh.png");
	m_RefreshRectangle.bottom = titleBottomLeftPosition.y + 15.f;
	m_RefreshRectangle.left = titleBottomLeftPosition.x + 400.f;
	m_RefreshRectangle.height = m_pRefreshTexture->GetHeight();
	m_RefreshRectangle.width = m_pRefreshTexture->GetWidth();


	m_GivenDecimalValue = rand() % 4095 + 1;
	// rand value between 0 - 111111111111  (0-4095)
}

GivenNumber::~GivenNumber()
{
	delete m_pFirstInputNumber;
	m_pFirstInputNumber = nullptr;
	delete m_pSecondInputNumber;
	m_pSecondInputNumber = nullptr;
	delete m_pGivenTypeTexture;
	m_pGivenTypeTexture = nullptr;
	delete m_pGivenBaseTypeTexture;
	m_pGivenBaseTypeTexture = nullptr;
	delete m_pGreenNumbersTexture;
	m_pGreenNumbersTexture = nullptr;
	delete m_pRefreshTexture;
	m_pRefreshTexture = nullptr;
}

void GivenNumber::Draw() const
{
	m_pGivenTypeTexture->Draw(m_GivenTypeTexturePosition);
	m_pGivenBaseTypeTexture->Draw(m_BaseTypeTexturePosition);


	//int testNumber{ 2222222222 };
	//size_t testNumber{ 222222222222 };
	float pixelBuffer{ 5.f };
	
	// draw correctString
	{
		std::string valueString{ ConvertValueToString(m_GivenDecimalValue)};
		//valueString = std::to_string(testNumber);
		
		for (size_t index{ 1 }; index < valueString.size() + 1; ++index)
		{
			m_pGreenNumbersTexture->SetDrawPos(Point2f{ m_GreenNumbersPosition.x - (m_pGreenNumbersTexture->GetFrameWidth() * (index - 1)) - (pixelBuffer * (index - 1)), m_GreenNumbersPosition.y });
			char charValue{ valueString[valueString.size() - index] };
			int correctValue{ int(charValue) - 48 };
			if (correctValue > 9)
			{
				correctValue = correctValue - 7; // ascii values for letters are 7 higher than numbers
			}
			m_pGreenNumbersTexture->SetCurrentFrame(correctValue);
			m_pGreenNumbersTexture->Draw();
			
		}
	
	}


	m_pFirstInputNumber->Draw();
	m_pSecondInputNumber->Draw();

	m_pRefreshTexture->Draw(Point2f{m_RefreshRectangle.left, m_RefreshRectangle.bottom});
}

void GivenNumber::HandleClick(const Point2f& mousePos)
{
	if (utils::IsPointInRect(mousePos, m_RefreshRectangle) == true)
	{
		m_GivenDecimalValue = rand() % 4095 + 1;
		m_pFirstInputNumber->Clear();
		m_pSecondInputNumber->Clear();
	}
	m_pFirstInputNumber->CheckInputBoxHit(mousePos);
	m_pSecondInputNumber->CheckInputBoxHit(mousePos);

	m_pFirstInputNumber->CheckClear(mousePos);
	m_pSecondInputNumber->CheckClear(mousePos);

	if (m_pFirstInputNumber->CheckCorrect(mousePos) == true)
	{
		m_pFirstInputNumber->ConvertValue(m_GivenDecimalValue);
	}
	if (m_pSecondInputNumber->CheckCorrect(mousePos) == true)
	{
		m_pSecondInputNumber->ConvertValue(m_GivenDecimalValue);
	}
}

void GivenNumber::InputCharacter(char value)
{
	m_pFirstInputNumber->AddCharacter(value);
	m_pSecondInputNumber->AddCharacter(value);
}


std::string GivenNumber::ConvertValueToString(int decimalValue) const
{
	std::string convertedValue{};
	//std::cout << decimalValue << std::endl;
	switch (m_CurrentBaseType)
	{
	case InputNumber::BaseTypes::binary:

		for (size_t powerValue{12}; powerValue > 0; --powerValue)
		{
			int powerSolution{ int(pow(2, powerValue - 1)) };
			if (decimalValue >= powerSolution)
			{
				decimalValue -= powerSolution;
				convertedValue += "1";
			}
			else
			{
				if (convertedValue.size() > 0)
				{
					convertedValue += "0";
				}
			}
			//std::cout << powerSolution << std::endl;
		}
		break;
	case InputNumber::BaseTypes::decimal:
		convertedValue = std::to_string(decimalValue);
		break;
	case InputNumber::BaseTypes::hexadecimal:
		std::vector<int> remainderArray{};
		while (decimalValue > 0)
		{
			remainderArray.push_back(decimalValue % 16);
			int tempValue{ decimalValue / 16 };
			decimalValue = tempValue;
		}

		for (size_t index{remainderArray.size()}; index > 0; --index)
		{
			//test
			if (remainderArray[index - 1] > 9)
			{
				if (remainderArray[index - 1] == 10)
				{
					convertedValue += "A";
				}
				else if (remainderArray[index - 1] == 11)
				{
					convertedValue += "B";
				}
				else if (remainderArray[index - 1] == 12)
				{
					convertedValue += "C";
				}
				else if (remainderArray[index - 1] == 13)
				{
					convertedValue += "D";
				}
				else if (remainderArray[index - 1] == 14)
				{
					convertedValue += "E";
				}
				else if (remainderArray[index - 1] == 15)
				{
					convertedValue += "F";
				}
			}
			else
			{
				convertedValue += std::to_string(remainderArray[index - 1]);
			}
			//std::cout << "Test " << remainderArray[index - 1] << std::endl;
		}
		break;
	}
	return convertedValue;
}
