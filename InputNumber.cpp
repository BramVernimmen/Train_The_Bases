#include "pch.h"
#include "InputNumber.h"
#include "utils.h"
#include "Sprite.h"
#include <iostream>

InputNumber::InputNumber(InputNumber::BaseTypes inputBaseType, const Point2f& titleBottomLeftPosition)
	: m_CurrentBaseType{inputBaseType}
	, m_CurrentState{State::inactive}
	, m_InputString{"0"}
	, m_InputTypeTexturePosition{titleBottomLeftPosition}
	, m_FontPath{ "Resources/Baloo.ttf" }
	, m_TextSize{ 42 }
	, m_TextColor{ Color4f{98.f / 255.f, 146.f / 255.f, 99.f / 255.f, 1.f} }
	, m_BaseTypeTexturePosition{ Point2f{titleBottomLeftPosition.x + 370.f, titleBottomLeftPosition.y - 50.f} }
	, m_NumbersPosition{ Point2f{titleBottomLeftPosition.x + 340.f, titleBottomLeftPosition.y - 30.f} }
	, m_TextSizeBaseType{ 28 }
	, m_pTypeTexture{nullptr}
	, m_pBaseTypeTexture{nullptr}
	, m_pClearButtonTexture{nullptr}
	, m_pCheckCorrectButtonTexture{nullptr}
{
	switch (m_CurrentBaseType)
	{
	case InputNumber::BaseTypes::binary:
		m_pTypeTexture = new Texture("Binary", m_FontPath, m_TextSize, m_TextColor);
		m_pBaseTypeTexture = new Texture("2", m_FontPath, m_TextSizeBaseType, m_TextColor);
		break;
	case InputNumber::BaseTypes::decimal:
		m_pTypeTexture = new Texture("Decimal", m_FontPath, m_TextSize, m_TextColor);
		m_pBaseTypeTexture = new Texture("10", m_FontPath, m_TextSizeBaseType, m_TextColor);
		break;
	case InputNumber::BaseTypes::hexadecimal:
		m_pTypeTexture = new Texture("Hexadecimal", m_FontPath, m_TextSize, m_TextColor);
		m_pBaseTypeTexture = new Texture("16", m_FontPath, m_TextSizeBaseType, m_TextColor);
		break;
	}

	m_pGreenNumbersTexture = new Sprite("Resources/green.png", 16, 1, Point2f{ 0.f, 0.f });
	m_pRedNumbersTexture = new Sprite("Resources/red.png", 16, 1, Point2f{ 0.f, 0.f });
	m_pBlueNumbersTexture = new Sprite("Resources/blue.png", 16, 1, Point2f{ 0.f, 0.f });
	m_pWhiteNumbersTexture = new Sprite("Resources/white.png", 16, 1, Point2f{ 0.f, 0.f });

	m_pCheckCorrectButtonTexture = new Texture("Resources/Check.png");
	m_CheckCorrectButtonRectangle.left = titleBottomLeftPosition.x + 400.f;
	m_CheckCorrectButtonRectangle.bottom = titleBottomLeftPosition.y + 15.f;
	m_CheckCorrectButtonRectangle.width = m_pCheckCorrectButtonTexture->GetWidth();
	m_CheckCorrectButtonRectangle.height = m_pCheckCorrectButtonTexture->GetHeight();

	m_pClearButtonTexture = new Texture("Resources/Delete.png");
	m_ClearButtonRectangle.bottom = titleBottomLeftPosition.y + 15.f;
	m_ClearButtonRectangle.width = m_pClearButtonTexture->GetWidth();
	m_ClearButtonRectangle.left = m_CheckCorrectButtonRectangle.left - m_ClearButtonRectangle.width * 1.5f;
	m_ClearButtonRectangle.height = m_pClearButtonTexture->GetHeight();

	m_InputBox.left = titleBottomLeftPosition.x;
	m_InputBox.bottom = titleBottomLeftPosition.y - 35.f;
	m_InputBox.width = 370.f;
	m_InputBox.height = 50.f;
}

InputNumber::~InputNumber()
{
	delete m_pTypeTexture;
	m_pTypeTexture = nullptr;
	delete m_pBaseTypeTexture;
	m_pBaseTypeTexture = nullptr;
	delete m_pGreenNumbersTexture;
	m_pGreenNumbersTexture = nullptr;
	delete m_pRedNumbersTexture;
	m_pRedNumbersTexture = nullptr;
	delete m_pBlueNumbersTexture;
	m_pBlueNumbersTexture = nullptr;
	delete m_pWhiteNumbersTexture;
	m_pWhiteNumbersTexture = nullptr;
	delete m_pClearButtonTexture;
	m_pClearButtonTexture = nullptr;
	delete m_pCheckCorrectButtonTexture;
	m_pCheckCorrectButtonTexture = nullptr;
}

void InputNumber::Draw() const
{
	m_pTypeTexture->Draw(m_InputTypeTexturePosition);
	m_pBaseTypeTexture->Draw(m_BaseTypeTexturePosition);
	utils::SetColor(Color4f{0.1f, 0.1f, 0.1f, 1.f});
	utils::FillRect(m_InputBox);

	if (m_CurrentState != State::correct)
	{
		m_pClearButtonTexture->Draw(Point2f{m_ClearButtonRectangle.left, m_ClearButtonRectangle.bottom});
		m_pCheckCorrectButtonTexture->Draw(Point2f{ m_CheckCorrectButtonRectangle.left, m_CheckCorrectButtonRectangle.bottom});
	}


	switch (m_CurrentState)
	{
	case InputNumber::State::active:
		DrawNumbers(m_pBlueNumbersTexture);
		break;
	case InputNumber::State::inactive:
		DrawNumbers(m_pWhiteNumbersTexture);
		break;
	case InputNumber::State::correct:
		DrawNumbers(m_pGreenNumbersTexture);
		break;
	case InputNumber::State::incorrect:
		DrawNumbers(m_pRedNumbersTexture);
		break;
	}
}

void InputNumber::SetActive()
{
	m_CurrentState = State::active;
}

void InputNumber::SetInactive()
{
	m_CurrentState = State::inactive;
}

bool InputNumber::IsActive()
{
	if (m_CurrentState == State::active)
	{
		return true;
	}
	return false;
}

void InputNumber::CheckInputBoxHit(const Point2f& mousePos)
{
	if (utils::IsPointInRect(mousePos, m_InputBox) == true && m_CurrentState != State::correct)
	{
		m_CurrentState = State::active;
	}
	else if (utils::IsPointInRect(mousePos, m_InputBox) == false && m_CurrentState != State::correct && m_CurrentState != State::incorrect)
	{
		m_CurrentState = State::inactive;
	}
}

void InputNumber::CheckClear(const Point2f& mousePos)
{
	if (utils::IsPointInRect(mousePos, m_ClearButtonRectangle) == true && m_CurrentState != State::correct)
	{
		Clear();
	}
}

bool InputNumber::CheckCorrect(const Point2f& mousePos)
{
	if (utils::IsPointInRect(mousePos, m_CheckCorrectButtonRectangle) == true && m_CurrentState != State::correct)
	{
		return true;
	}
	return false;
}

void InputNumber::Clear()
{
	SetInactive();
	m_InputString = "0";
}

void InputNumber::ConvertValue(int givenValue)
{
	// convert current string to int
	switch (m_CurrentBaseType)
	{
	case InputNumber::BaseTypes::binary:
		//std::cout << m_InputString << std::endl;
		// you can specify std::stoi to convert different bases; default is 10
		//std::cout << std::stoi(m_InputString, nullptr, 2) << std::endl;
		
		if (std::stoi(m_InputString, nullptr, 2) == givenValue)
		{
			m_CurrentState = State::correct;
		}
		else
		{
			m_CurrentState = State::incorrect;
		}
		break;
	case InputNumber::BaseTypes::decimal:
		if (std::stoi(m_InputString) == givenValue)
		{
			m_CurrentState = State::correct;
		}
		else
		{
			m_CurrentState = State::incorrect;
		}
		break;
	case InputNumber::BaseTypes::hexadecimal:
		if (std::stoi(m_InputString, nullptr, 16) == givenValue)
		{
			m_CurrentState = State::correct;
		}
		else
		{
			m_CurrentState = State::incorrect;
		}
		break;
	}
}

void InputNumber::AddCharacter(char value)
{
	if (m_CurrentState == State::active)
	{
		switch (m_CurrentBaseType)
		{
		case InputNumber::BaseTypes::binary:
			if (value == '0' || value == '1' && m_InputString.size() < 12)
			{
				if (m_InputString[0] == '0')
				{
					m_InputString[0] = value;
				}
				else
				{
					m_InputString += value;
				}
			}
			break;
		case InputNumber::BaseTypes::decimal:
			if (value != 'a' && value != 'b' && value != 'c' && value != 'd' && value != 'e' && value != 'f' && m_InputString.size() < 4)
			{
				if (m_InputString[0] == '0')
				{
					m_InputString[0] = value;
				}
				else
				{
					m_InputString += value;
				}
			}
			break;
		case InputNumber::BaseTypes::hexadecimal:
			if (m_InputString.size() < 3)
			{
				if (m_InputString[0] == '0')
				{
					m_InputString[0] = value;
				}
				else
				{
					m_InputString += value;
				}
			}
			
			break;
		}
		

		
	}
}

void InputNumber::DrawNumbers(Sprite* pCorrectColor) const
{
	float pixelBuffer{ 5.f };
	
	{
		for (size_t index{ 1 }; index < m_InputString.size() + 1; ++index)
		{
			pCorrectColor->SetDrawPos(Point2f{ m_NumbersPosition.x - (pCorrectColor->GetFrameWidth() * (index - 1)) - (pixelBuffer * (index - 1)), m_NumbersPosition.y });
			char charValue{ m_InputString[m_InputString.size() - index] };
			int correctValue{ int(charValue) - 48 };
			if (correctValue > 9)
			{
				correctValue = correctValue - 7; // ascii values for letters are 7 higher than numbers
			}
			pCorrectColor->SetCurrentFrame(correctValue);
			pCorrectColor->Draw();

		}

	}
}
