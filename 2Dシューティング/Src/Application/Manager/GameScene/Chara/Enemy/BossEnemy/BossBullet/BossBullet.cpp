#include "BossBullet.h"
#include "../../../../GameScene.h"


void C_BossBullet::Draw()
{

	for (int i = 0; i < buNum; i++)
	{
		if (!m_alive[i]) continue;

		
		SHADER.m_spriteShader.SetMatrix(m_mat[i]);
		SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 32 , 32), 1.0f);


	}

}



void C_BossBullet::Action()
{

	for (int i = 0; i < buNum; i++)
	{
		if (!m_alive[i]) continue;


	}

}

void C_BossBullet::Update()
{

	for (int i = 0; i < buNum; i++)
	{
		if (!m_alive[i]) continue;

		
			
		m_pos[i] += m_move[i];

		if (m_pos[i].x >= 640 + (m_rad[i].x * m_size[i].x)) m_alive[i] = false;
		if (m_pos[i].x <= -640 - (m_rad[i].x * m_size[i].x)) m_alive[i] = false;
		if (m_pos[i].y >= 360 + (m_rad[i].y * m_size[i].y)) m_alive[i] = false;
		if (m_pos[i].y <= -360 - (m_rad[i].y * m_size[i].y)) m_alive[i] = false;
			
		

	}

}

void C_BossBullet::MatUpdate()
{

	for (int i = 0; i < buNum; i++)
	{
		
		
		Math::Matrix rotate = Math::Matrix::CreateRotationZ(m_angle[i]);
		Math::Matrix scale = Math::Matrix::CreateScale(m_size[i].x, m_size[i].y, 0);
		Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos[i].x, m_pos[i].y, 0);
		m_mat[i] = scale * rotate * trans;
			
		
		
	}

}


void C_BossBullet::Init()
{

	m_tex.Load("Asset/texture/GameScene/Bullet/midBullet.png");
	

	for (int i = 0; i < buNum; i++)
	{
		m_pos[i] = {};
		m_move[i] = {};
		m_alive[i] = false;
		m_size[i] = {};
		m_rad[i] = {};
		m_angle[i] = {};
	}


}

void C_BossBullet::SetBullet(int i, Math::Vector2 pos, Math::Vector2 move,float angle)
{

	m_alive[i] = true;
	m_pos[i] = pos;
	m_move[i] = move;
	m_angle[i] = angle;
	m_size[i] = { 1,1 };
}

void C_BossBullet::Release()
{
	m_tex.Release();
}