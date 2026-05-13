#include "Score.h"
#include "../../GameScene.h"

void C_Score::Draw()
{

	for (int i = 0; i < maxDigit; i++)
	{

		Math::Rectangle rec = { 32 * m_digit[i],0,32,46 };
		Math::Color col = { 1,1,1,0.6f };

		SHADER.m_spriteShader.SetMatrix(m_mat[i]);
		SHADER.m_spriteShader.DrawTex(&m_tex, rec, &col);

	}

}

void C_Score::Update()
{

	//配列に各桁の数値を格納
	m_score = m_gameScene->GetScore();
	for (int i = maxDigit - 1; i >= 0; --i)
	{
		//下位の桁から抽出し配列に格納していく
		m_digit[i] = m_score % 10;
		m_score /= 10;
	}


}

void C_Score::MatUpdate()
{

	for (int i = 0; i < maxDigit; i++)
	{
		Math::Matrix scale = Math::Matrix::CreateScale(1, 1, 1);
		Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos[i].x, m_pos[i].y, 0);
		m_mat[i] = scale * trans;
	}

}

void C_Score::Init()
{

	m_tex.Load("Asset/texture/GameScene/UI/num.png");

	m_score = 0;

	float x = -608;

	for (int i = 0; i < maxDigit; i++)
	{
		m_pos[i] = { x + i * 32 ,330};
		m_digit[i] = {};
	}

}

void C_Score::Release()
{

	m_tex.Release();

}