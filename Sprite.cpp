#include "pch.h"
#include "Sprite.h"
#include <iostream>

Sprite::Sprite(const std::string& filename, int nrCols, int nrRows, const Point2f& drawPos)
	: m_Columns{ nrCols }
	, m_Rows{ nrRows }
	, m_TotalNrFrames{ nrRows * nrCols }
	//, m_pTexture{ new Texture{filename} }
	, m_FileName{filename}
	, m_DrawPos{ drawPos }
	, m_CurrentFrame{ 0 }
{

	m_pTexture = new Texture(filename);

	m_FrameWidth = m_pTexture->GetWidth() / m_Columns;
	m_FrameHeight = m_pTexture->GetHeight() / m_Rows;

}

Sprite::~Sprite()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void  Sprite::Draw() const
{
	
	Rectf sourceRect{};
	if (m_Rows == 1)
	{
		sourceRect.left = m_CurrentFrame * m_FrameWidth + 1.f;
	}
	else
	{
		sourceRect.left = (m_CurrentFrame % m_Columns) * m_FrameWidth;
	}
	sourceRect.bottom	= (m_CurrentFrame / m_Columns + 1) * m_FrameHeight;
	sourceRect.width	= m_FrameWidth;
	sourceRect.height	= m_FrameHeight;

	m_pTexture->Draw(m_DrawPos, sourceRect);
}



float Sprite::GetFrameWidth() const
{
	return m_FrameWidth;
}

float Sprite::GetFrameHeight() const
{
	return m_FrameHeight;
}

void Sprite::SetDrawPos(const Point2f& newDrawPos)
{
	m_DrawPos = newDrawPos;
}

int Sprite::GetCurrentFrame()
{
	return m_CurrentFrame;
}

int Sprite::GetTotalAmountOfFrames()
{
	return m_Columns * m_Rows;
}

void Sprite::SetCurrentFrame(int newFrame)
{
	m_CurrentFrame = newFrame;
}
