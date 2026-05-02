#include<random>
#include "BasicEnemy.h"

#include "../../../GameScene.h"
#include "../../../Explosion/Explosion.h"

void C_BasicEnemy::Draw()
{

	for(int i = 0; i < enemyNum; i++)
	{
		if (!m_alive[i]) continue;
		switch (m_enemyType[i])
		{
		case enemyType::basic:
			
			SHADER.m_spriteShader.SetMatrix(m_mat[i]);
			SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 48, 48), 1.0f);
			
			break;
		case enemyType::shake:
			
			SHADER.m_spriteShader.SetMatrix(m_mat[i]);
			SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 48, 48), 1.0f);
			
			break;

		case enemyType::uni:
			

			
			break;

		}
	}

}



void C_BasicEnemy::Action()
{
	for (int i = 0; i < enemyNum; i++)
	{
		switch (m_enemyType[i])
		{
		case enemyType::basic:

			m_move[i] = { 0,-3 };

			break;

		case enemyType::shake:

			m_shakeCnt[i]--;

			if (m_shakeCnt[i] <= 0)
			{
				m_move[i].x *= -1;
				m_shakeCnt[i] = Rand(20, 0) + 50;
			}

			break;

		case enemyType::uni:

			break;

		}
	}
}

void C_BasicEnemy::MatUpdate()
{
	for (int i = 0; i < enemyNum; i++)
	{
		m_mat[i] = Math::Matrix::CreateTranslation(m_pos[i].x, m_pos[i].y, 0.0f);

	}

}

void C_BasicEnemy::Update()
{
	
	int cnt = 0;
	for (int i = 0; i < enemyNum; i++)
	{
		if (!m_alive[i])continue;
		cnt++;//現在生きてるベーシックエネミーの数を数える
	}

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(1, 100);

	if (dist(mt) <= 10) {
		// 20% の確率
		for (int i = 0; i < enemyNum; i++)
		{
			if (m_alive[i])continue;//生きてたらスルー
			
			std::mt19937 mt(rd());
			std::uniform_int_distribution<int> dist(1, 2);

			switch (dist(mt))
			{
			case 1:
				EnemyInit(i, enemyType::basic);
				break;
			case 2:
				EnemyInit(i, enemyType::shake);
				break;
			case 3:
				EnemyInit(i, enemyType::uni);
				break;
			}
			break;

		}
	}

	
	
	for (int i = 0; i < enemyNum; i++)
	{
		if (!m_alive[i]) continue;


		switch (m_enemyType[i])
		{
			case enemyType::basic:
			{
				m_pos[i] += m_move[i];

				if (m_pos[i].y < -360 - 32) m_pos[i].y = 360 + 32;

				if (m_hp[i] <= 0)
				{

					C_Explosion* ex = m_gameScene->GetExplosion();

					ex->SetEx(m_pos[i], ex->m_exSize::be);
					m_killCnt++;
					m_alive[i] = false;
				}

				break;
			}
			case enemyType::shake:
			{

				m_pos[i] += m_move[i];

				if (640 - 32 < m_pos[i].x)m_pos[i].x = 640 - 32;
				if (-640 + 32 > m_pos[i].x)m_pos[i].x = -640 + 32;
				if (m_pos[i].y < -360 - 32) m_pos[i].y = 360 + 32;

				if (m_hp[i] <= 0)
				{

					C_Explosion* ex = m_gameScene->GetExplosion();

					ex->SetEx(m_pos[i], ex->m_exSize::be);
					m_killCnt++;
					m_alive[i] = false;
				}
				break;
			}
			case enemyType::uni:
			{
				m_pos[i] += m_move[i];


				if (m_hp[i] <= 0)
				{

					C_Explosion* ex = m_gameScene->GetExplosion();

					ex->SetEx(m_pos[i], ex->m_exSize::be);
					m_killCnt++;
					m_alive[i] = false;
				}
				break;
			}
		}
		

	}


}

void C_BasicEnemy::Init()
{

	m_tex.Load("Asset/texture/GameScene/Chara/Enemy/enemy.png");
	
	srand(time(0));

	for(int i = 0; i < enemyNum; i++)
	{
		m_pos[i] = { 0,0 };
		m_move[i] = { 0,-2 };
		m_alive[i] = false;
		m_hp[i] = m_enemyHp::basic;
		m_enemyType[i] = enemyType::basic;
	}

	m_killCnt = 0;

}

void C_BasicEnemy::EnemyInit(int i, int type)
{

	switch (type)
	{
	case enemyType::basic:
		m_pos[i] = { (float)Rand(1280 - 64, 640 - 32),360 + 32 };
		m_move[i] = { 0,-2 };
		m_alive[i] = true;
		m_hp[i] = m_enemyHp::basic;
		m_enemyType[i] = type;
		break;

	case enemyType::shake:
		m_pos[i] = { (float)Rand(1280 - 64, 640 - 32),360 + 32 };
		m_move[i] = { 1.0f ,-2};
		m_alive[i] = true;
		m_hp[i] = m_enemyHp::basic;
		m_shakeCnt[i] = Rand(20,0) + 50;
		m_enemyType[i] = type;
		break;

	case enemyType::uni:
		m_pos[i] = { (float)Rand(1280 - 64, 640 - 32),360 + 32 };
		m_move[i] = { 0,-2 };
		m_alive[i] = true;
		m_hp[i] = m_enemyHp::basic;
		m_enemyType[i] = type;
		break;

	}
	

}

void C_BasicEnemy::Release()
{
	m_tex.Release();
}

