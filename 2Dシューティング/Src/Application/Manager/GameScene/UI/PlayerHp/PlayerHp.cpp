#include "PlayerHp.h"

#include "../../GameScene.h"
#include "../../Chara//Player/Player.h"

void C_PlayerHp::Draw()
{

	Math::Color col = { 1,1,1,1.0f };
	Math::Rectangle rec = { 0,0,20,20 };
	SHADER.m_spriteShader.SetMatrix(m_iconMat);
	SHADER.m_spriteShader.DrawTex(&m_iconTex, rec, &col);

	rec = { 0,0,54,12 };
	SHADER.m_spriteShader.SetMatrix(m_frameMat);
	SHADER.m_spriteShader.DrawTex(&m_frameTex, rec, &col);

	C_Player* pl = m_gameScene->GetPlayer();

	for (int i = 0;i < pl->GetHp();i++)
	{
		if (pl->GetHp() <= 3)
		{
			col = { 1,0,0,1 };
		}
		else if (pl->GetHp() <= 6)
		{
			col = { 1,1,0,1 };
		}
		else
		{
			col = { 0,1,0,1 };
		}

		rec = { 0,0,4,3 };
		SHADER.m_spriteShader.SetMatrix(m_barMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_barTex, rec, &col);

	}


}

void C_PlayerHp::Update()
{



}

void C_PlayerHp::MatUpdate()
{

	Math::Matrix scale = Math::Matrix::CreateScale(2, 2, 1);
	Math::Matrix trans = Math::Matrix::CreateTranslation(m_iconPos.x, m_iconPos.y, 0);
	m_iconMat = scale * trans;

	scale = Math::Matrix::CreateScale(4, 4, 1);
	trans = Math::Matrix::CreateTranslation(m_framePos.x, m_framePos.y, 0);
	m_frameMat = scale * trans;

	for (int i = 0; i < barNum; i++)
	{
		trans = Math::Matrix::CreateTranslation(m_barPos[i].x, m_barPos[i].y, 0);
		m_barMat[i] = scale * trans;
	}


}

void C_PlayerHp::Init()
{

	m_barTex.Load("Asset/texture/GameScene/UI/white.png");
	m_iconTex.Load("Asset/texture/GameScene/UI/hp_icon.png");
	m_frameTex.Load("Asset/texture/GameScene/UI/hp_frame.png");

	m_iconPos = { -610, -330 };
	m_framePos = { -475, -325 };

	for (int i = 0; i < barNum; i++)
	{
		m_barPos[i] = { -567.0f + (i * 20) ,-337};
	}

}

void C_PlayerHp::Release()
{

	m_barTex.Release();
	m_iconTex.Release();
	m_frameTex.Release();

}