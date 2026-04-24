#include "BasicEnemy.h"

void C_BasicEnemy::Draw()
{

	for(int i = 0; i < enemyNum; i++)
	{
		if (!m_alive[i]) continue;
		SHADER.m_spriteShader.SetMatrix(m_mat[i]);
		SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 48, 48), 1.0f);
	}

}

void C_BasicEnemy::Action()
{
	for (int i = 0; i < enemyNum; i++)
	{

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
	
	
	for (int i = 0; i < enemyNum; i++)
	{
		if (!m_alive[i]) continue;

		m_pos[i] += m_move[i];
		
		if (m_pos[i].y < -360 - 32) m_pos[i].y = 360 + 32;

		if (m_hp[i] <= 0)m_alive[i] = false;

	}


}

void C_BasicEnemy::Init()
{

	m_tex.Load("Asset/texture/GameScene/Chara/Enemy/enemy.png");
	
	srand(time(0));

	for(int i = 0; i < enemyNum; i++)
	{
		m_pos[i] = { (float)(rand() % 1281 - 640),360 + 32};
		m_move[i] = { 0,-2 };
		m_alive[i] = true;
		m_hp[i] = 10;
	}

}

void C_BasicEnemy::Release()
{
	m_tex.Release();
}
