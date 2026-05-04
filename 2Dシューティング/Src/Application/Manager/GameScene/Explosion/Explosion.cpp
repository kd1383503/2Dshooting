#include "Explosion.h"

void C_Explosion::Draw()
{

	for (int i = 0; i < m_expNum; i++)
	{
		if (!m_alive[i])continue;
		SHADER.m_spriteShader.SetMatrix(m_mat[i]);
		SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(16 * (int)m_animCnt[i], 0, 16, 16), 1.0f);
	}

}

void C_Explosion::Update()
{

	for (int i = 0; i < m_expNum; i++)
	{
		if (!m_alive[i])continue;
		m_animCnt[i] += 0.1;
		if (m_animCnt[i] >= 6.0f)
		{
			m_alive[i] = false;
		}
	}

}

void C_Explosion::MatUpdate()
{

	for (int i = 0; i < m_expNum; i++)
	{
		Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos[i].x, m_pos[i].y, 0);
		Math::Matrix scale = Math::Matrix::CreateScale(m_size[i], m_size[i], 0);
		m_mat[i] = scale * trans;
	}

}

void C_Explosion::Init()
{

	m_tex.Load("Asset/texture/GameScene/Explosion/exp.png");

	for (int i = 0; i < m_expNum; i++)
	{
		m_alive[i] = false;
		m_pos[i] = {};
		m_anim[i] = 0;
		m_animCnt[i] = 0;
		m_size[i] = 0;

	}

}

void C_Explosion::Release()
{

	m_tex.Release();

}