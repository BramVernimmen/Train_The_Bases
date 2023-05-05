#pragma once
#include "Texture.h"
class Sprite final
{
public:
	Sprite(const std::string& filename, int nrCols, int nrRows, const Point2f& drawPos);
	~Sprite();
	Sprite(const Sprite& other) = delete;
	Sprite& operator=(const Sprite& rhs) = delete;
	Sprite(Sprite&& other) = delete;
	Sprite& operator=(Sprite&& rhs) = delete;

	void  Draw() const;
	float GetFrameWidth() const;
	float GetFrameHeight() const;
	void SetDrawPos(const Point2f& newDrawPos);

	int GetCurrentFrame();
	int GetTotalAmountOfFrames();
	void SetCurrentFrame(int newFrame);


private:
	Texture* m_pTexture;
	std::string m_FileName;
	const int m_Columns;
	const int m_Rows;

	const int m_TotalNrFrames;
	int m_CurrentFrame;

	float m_FrameWidth;
	float m_FrameHeight;

	Point2f m_DrawPos;
};

