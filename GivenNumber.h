#pragma once
#include "InputNumber.h"
#include "Texture.h"
class Sprite;

class GivenNumber
{
public:
	explicit GivenNumber(InputNumber::BaseTypes givenBaseType, const Point2f& titleBottomLeftPosition);
	GivenNumber(const GivenNumber& other) = delete;
	GivenNumber& operator=(const GivenNumber& other) = delete;
	GivenNumber(GivenNumber&& other) = delete;
	GivenNumber& operator=(GivenNumber&& other) = delete;
	~GivenNumber();

	void Draw() const;
	void HandleClick(const Point2f& mousePos);

	void InputCharacter(char value);
private:
	std::string ConvertValueToString(int decimalValue) const;
	InputNumber* m_pFirstInputNumber;
	InputNumber* m_pSecondInputNumber;

	InputNumber::BaseTypes m_CurrentBaseType;

	bool m_HasOneActive;

	Texture* m_pGivenTypeTexture;
	const std::string m_FontPath;
	const int m_TextSize;
	const Color4f m_TextColor;

	const Point2f m_GivenTypeTexturePosition;
	
	
	Texture* m_pGivenBaseTypeTexture;
	const int m_TextSizeBaseType;
	const Point2f m_BaseTypeTexturePosition;

	Sprite* m_pGreenNumbersTexture;
	const Point2f m_GreenNumbersPosition;


	int m_GivenDecimalValue;

	Texture* m_pRefreshTexture;
	Rectf m_RefreshRectangle;

};

