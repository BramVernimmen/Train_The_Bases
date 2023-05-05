#pragma once
#include "Texture.h"

class Sprite;
class InputNumber
{
public:
	enum class BaseTypes
	{
		binary,
		decimal,
		hexadecimal
	};
	enum class State
	{
		active,
		inactive,
		correct,
		incorrect
	};
	explicit InputNumber(InputNumber::BaseTypes inputBaseType, const Point2f& titleBottomLeftPosition);
	InputNumber(const InputNumber& other) = delete;
	InputNumber& operator=(const InputNumber& other) = delete;
	InputNumber(InputNumber&& other) = delete;
	InputNumber& operator=(InputNumber&& other) = delete;
	~InputNumber();

	void Draw() const;

	void SetActive();
	void SetInactive();

	bool IsActive();
	void CheckInputBoxHit(const Point2f& mousePos);
	void CheckClear(const Point2f& mousePos);
	bool CheckCorrect(const Point2f& mousePos);

	void Clear();

	void ConvertValue(int givenValue);
	void AddCharacter(char value);
private:
	void DrawNumbers(Sprite* pCorrectColor) const;
	InputNumber::BaseTypes m_CurrentBaseType;
	std::string m_InputString;
	State m_CurrentState;

	Rectf m_InputBox;

	Texture* m_pTypeTexture;
	const std::string m_FontPath;
	const int m_TextSize;
	const Color4f m_TextColor;

	const Point2f m_InputTypeTexturePosition;

	Texture* m_pBaseTypeTexture;
	const int m_TextSizeBaseType;
	const Point2f m_BaseTypeTexturePosition;

	Sprite* m_pGreenNumbersTexture;
	Sprite* m_pRedNumbersTexture;
	Sprite* m_pBlueNumbersTexture;
	Sprite* m_pWhiteNumbersTexture;
	const Point2f m_NumbersPosition;

	Texture* m_pClearButtonTexture;
	Rectf m_ClearButtonRectangle;

	Texture* m_pCheckCorrectButtonTexture;
	Rectf m_CheckCorrectButtonRectangle;

};

