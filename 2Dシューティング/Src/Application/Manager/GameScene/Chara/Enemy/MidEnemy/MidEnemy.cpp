#include "MidEnemy.h"
#include "../../../GameScene.h"


void C_MidEnemy::Draw()
{

	for (int i = 0; i < m_enemyNum; i++)
	{
		if (!m_alive[i])continue;

		SHADER.m_spriteShader.SetMatrix(m_mat[i]);
		SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 0, 0), 1.0f);

	}

}

void C_MidEnemy::Action()
{

	for (int i = 0; i < m_enemyNum; i++)
	{
		if (!m_alive[i])continue;

		

	}

	if (0)//もしキルカウントが条件数を満たしたら
	{
		for (int i = 0; i < m_enemyNum; i++)
		{
			if (!m_alive[i])continue;

			m_alive[i] = true;
			m_hp[i] = m_enemyHp::mid;
			m_pos[i] = { 0,0 };
			m_move[i] = { 0,0 };

		}
	}

}

void C_MidEnemy::Update()
{

	for (int i = 0; i < m_enemyNum; i++)
	{

		m_pos[i] = m_move[i];




		if (m_hp[i] <= 0)
		{
			m_alive[i] = false;
		}

	}

}

void C_MidEnemy::MatUpdate()
{

	for (int i = 0; i < m_enemyNum; i++)
	{
		Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos[i].x, m_pos[i].y, 0);
		Math::Matrix scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
		m_mat[i] = scale * trans;

	}

}

void C_MidEnemy::Init()
{

	m_tex.Load("");

	for (int i = 0; i < m_enemyNum; i++)
	{
		m_pos[i] = {};
		m_move[i] = {};
		m_alive[i] = false;
		m_hp[i] = 100;

	}
	m_size = { 2,2 };

}

void C_MidEnemy::Release()
{

	m_tex.Release();

}
