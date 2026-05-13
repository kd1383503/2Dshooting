#include "Warning.h"
#include "../GameScene.h"
#include "../Chara/Enemy/BossEnemy/BossEnemy.h"

void C_Warning::Draw()
{

	C_BossEnemy* bs = m_gameScene->GetBoss();
	if (!bs->GetWarning())return;

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_backTex, Math::Rectangle(0, 0, 1280, 720), 0.5f * m_alpha);

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 1280, 720), m_alpha);

	SHADER.m_spriteShader.SetMatrix(m_topMat);
	SHADER.m_spriteShader.DrawTex(&m_topTex, Math::Rectangle(40, 0, 1220, 720), m_alpha);

	SHADER.m_spriteShader.SetMatrix(m_topMat2);
	SHADER.m_spriteShader.DrawTex(&m_topTex, Math::Rectangle(40, 0, 1218, 720), m_alpha);

	SHADER.m_spriteShader.SetMatrix(m_btmMat);
	SHADER.m_spriteShader.DrawTex(&m_btmTex, Math::Rectangle(0, 0, 1220, 720), m_alpha);

	SHADER.m_spriteShader.SetMatrix(m_btmMat2);
	SHADER.m_spriteShader.DrawTex(&m_btmTex, Math::Rectangle(0, 0, 1280, 720), m_alpha);

}

void C_Warning::Update()
{

	C_BossEnemy* bs = m_gameScene->GetBoss();
	if (!bs->GetWarning())return;


	m_topPos.x += m_scroll;
	m_topPos2.x += m_scroll;
	m_btmPos.x -= m_scroll;
	m_btmPos2.x -= m_scroll;
	if (m_topPos.x >= 1280) 
	{
		m_topPos.x = 0;
		m_topPos2.x = -1280;
	}
	if (m_btmPos.x <= -1280) 
	{
		m_btmPos.x = 0;
		m_btmPos2.x = 1280;
	}

	m_alpha += m_addAlpha;
	if (m_alpha <= 0.3)
	{
		m_alpha = 0.3f;
		m_addAlpha = 0.02f;
	}
	if (m_alpha >= 1.0f)
	{
		m_alpha = 1.0f;
		m_addAlpha = -0.02f;
	}

	m_cnt--;
	if (m_cnt <= 0)
	{
		bs->SetWarning();
		bs->SetStart();
	}

}

void C_Warning::MatUpdate()
{

	
	m_mat = Math::Matrix::CreateTranslation(0, 0, 0);
	m_topMat = Math::Matrix::CreateTranslation(m_topPos.x, m_topPos.y, 0);
	m_topMat2 = Math::Matrix::CreateTranslation(m_topPos2.x, m_topPos2.y, 0);
	m_btmMat = Math::Matrix::CreateTranslation(m_btmPos.x, m_btmPos.y, 0);
	m_btmMat2 = Math::Matrix::CreateTranslation(m_btmPos2.x, m_btmPos2.y, 0);

}

void C_Warning::Init()
{

	m_tex.Load("Asset/texture/GameScene/warning/warning.png");
	m_topTex.Load("Asset/texture/GameScene/warning/warning2.png");
	m_btmTex.Load("Asset/texture/GameScene/warning/warning3.png");
	m_backTex.Load("Asset/texture/GameScene/warning/back.png");


	m_topPos = { 20,0 };
	m_topPos2 = { -1160,0 };
	m_btmPos = { -20,0 };
	m_btmPos2 = { 1228,0 };

	m_scroll = 3.0f;
	m_cnt = 180;
	m_alpha = 0.0f;
	m_addAlpha = 0.05;

}


void C_Warning::Release()
{

	m_tex.Release();
	m_topTex.Release();
	m_btmTex.Release();
	m_backTex.Release();

}
