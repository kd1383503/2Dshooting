#include "Back.h"

void C_Back::Draw()
{
		
	//”wŒi‚Ì•`‰æ
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 1280, 720), 1.0f);
	//”wŒi2‚Ì•`‰æ
	SHADER.m_spriteShader.SetMatrix(m_mat2);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 1280, 720), 1.0f);

}

void C_Back::MatUpdate()
{
	
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat2 = Math::Matrix::CreateTranslation(m_pos2.x, m_pos2.y, 0);

}

void C_Back::Update()
{

	m_pos.y -= m_scroll;
	m_pos2.y -= m_scroll;

	if(m_pos.y <= -720.0f)
	{
		m_pos.y = 0.0f;
		m_pos2.y = 720.0f;
	}

}

void C_Back::Init()
{
	
	m_pos = { 0.0f, 0.0f };
	m_pos2 = { 0.0f, 720.0f };
	m_tex.Load("Asset/texture/GameScene/Back/Back.png");
	


}

void C_Back::Release()
{
	
	m_tex.Release();

}