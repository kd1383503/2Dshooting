#include "MidEnemy.h"
#include "../../../GameScene.h"
#include "../BasicEnemy/BasicEnemy.h"

void C_MidEnemy::Draw()
{

	
	if (!m_alive)return;
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 400, 200), 1.0f);

	

}

void C_MidEnemy::Action()
{

	C_BasicEnemy* be = m_gameScene->GetBasicEnemy();
	
	if (be->GetKill() >= 5)//もしキルカウントが条件数を満たしたら
	{

		if (!m_alive)
		{

			m_alive = true;
			m_hp = m_enemyHp::mid;
			m_pos = { (float)Rand(600, 300) ,860 };
			m_move = { 0,0 };
			m_atk = false;
		}

	}

	if (!m_alive)return;
	if (!m_atk)
	{
		m_move.y = -5;
	}
	else
	{

		if (m_shake <= 0)
		{

			if (m_pos.x < -150)
			{
				if (Rand(100, 0) % 3 != 0)
				{
					m_move.x = 1;
				}
				else
				{
					m_move.x = -1;
				}
			}
			else if (m_pos.x > 150)
			{
				if (Rand(100, 0) % 2 != 0)
				{
					m_move.x = -1;
				}
				else
				{
					m_move.x = 1;
				}
			}
			else
			{
				if (Rand(100, 0) % 2 != 0)
				{
					m_move.x = 1;
				}
				else
				{
					m_move.x = -1;
				}
			}
			

			m_shake = Rand(60, 0) + 90;
		}


		m_shake--;
	}
	
	

}

void C_MidEnemy::Update()
{

	if (!m_alive)return;

	m_pos += m_move;


	if (m_pos.y <= 240)
	{
		m_pos.y = 240;
		m_move.y = 0.0f;
		m_atk = true;
	}

	if (m_pos.x > 440) m_pos.x = 440;
	if (m_pos.x < -440) m_pos.x = -440;


	C_BasicEnemy* be = m_gameScene->GetBasicEnemy();

	if (m_hp <= 0)
	{
		m_alive = false;
		be->SetKill(0);
	}
	

}

void C_MidEnemy::MatUpdate()
{

	
	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	Math::Matrix scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = scale * trans;

	

}

void C_MidEnemy::Init()
{

	m_tex.Load("Asset/texture/GameScene/Chara/Enemy/midBoss.png");

	
	m_pos = {};
	m_move = {};
	m_alive = false;
	m_size = { 1,1 };
	m_hp = 100;

	
	m_size = { 1,1 };

}

void C_MidEnemy::Release()
{

	m_tex.Release();

}
