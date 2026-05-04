#include "MidBullet.h"
#include "../../../../GameScene.h"

#include "../MidEnemy.h"

void C_MidBullet::Draw()
{

	for (int i = 0; i < buNum; i++)
	{
		if (!m_alive[i]) continue;

		switch (m_type[i])
		{
			case bulletType::straight:
			{
				SHADER.m_spriteShader.SetMatrix(m_mat[i]);
				SHADER.m_spriteShader.DrawTex(&m_strTex, Math::Rectangle(0, 0, bRad[bulletRad::straightx] * 2, bRad[bulletRad::straighty] * 2), 1.0f);
				break;
			}
			case bulletType::cloth:
			{
				SHADER.m_spriteShader.SetMatrix(m_mat[i]);
				SHADER.m_spriteShader.DrawTex(&m_cloTex, Math::Rectangle(0, 0, bRad[bulletRad::clothx] * 2, bRad[bulletRad::clothy] * 2), 1.0f);
				break;
			}
			case bulletType::charge:
			{
				SHADER.m_spriteShader.SetMatrix(m_mat[i]);
				SHADER.m_spriteShader.DrawTex(&m_chaTex, Math::Rectangle(0, 0, bRad[bulletRad::chargex], bRad[bulletRad::chargey]), 1.0f);
				break;
			}
		}

	}

}



void C_MidBullet::Action()
{

	for (int i = 0; i < buNum; i++)
	{
		if (!m_alive[i]) continue;

		switch (m_type[i])
		{
			case bulletType::straight:
			{
				break;

			}
			case bulletType::cloth:
			{
				break;

			}
			case bulletType::charge:
			{
				break;

			}
		}

	}

}

void C_MidBullet::Update()
{

	for (int i = 0; i < buNum; i++)
	{
		if (!m_alive[i]) continue;

		switch (m_type[i])
		{
			case bulletType::straight:
			{
				m_pos[i] += m_move[i];

				if (m_pos[i].x >= 640 + (m_rad[i].x * m_size[i].x)) m_alive[i] = false;
				if (m_pos[i].x <= -640 - (m_rad[i].x * m_size[i].x)) m_alive[i] = false;
				if (m_pos[i].y >= 360 + (m_rad[i].y * m_size[i].y)) m_alive[i] = false;
				if (m_pos[i].y <= -360 - (m_rad[i].y * m_size[i].y)) m_alive[i] = false;
				break;
			}
			case bulletType::cloth:
			{
				m_pos[i] += m_move[i];

				if (m_pos[i].x >= 640 + (m_rad[i].x * m_size[i].x)) m_alive[i] = false;
				if (m_pos[i].x <= -640 - (m_rad[i].x * m_size[i].x)) m_alive[i] = false;
				if (m_pos[i].y >= 360 + (m_rad[i].y * m_size[i].y)) m_alive[i] = false;
				if (m_pos[i].y <= -360 - (m_rad[i].y * m_size[i].y)) m_alive[i] = false;
				break;

			}
			case bulletType::charge:
			{
				m_pos[i] += m_move[i];

				if (m_pos[i].x >= 640 + (m_rad[i].x * m_size[i].x)) m_alive[i] = false;
				if (m_pos[i].x <= -640 - (m_rad[i].x * m_size[i].x)) m_alive[i] = false;
				if (m_pos[i].y >= 360 + (m_rad[i].y * m_size[i].y)) m_alive[i] = false;
				if (m_pos[i].y <= -360 - (m_rad[i].y * m_size[i].y)) m_alive[i] = false;
				break;
			}
		}

	}

}

void C_MidBullet::MatUpdate()
{

	for (int i = 0; i < buNum; i++)
	{
		switch (m_type[i])
		{
			case bulletType::straight:
			{
				Math::Matrix scale = Math::Matrix::CreateScale(m_size[i].x, m_size[i].y, 0);
				Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos[i].x, m_pos[i].y, 0);
				m_mat[i] = scale * trans;
				break;
			}
			case bulletType::cloth:
			{
				Math::Matrix scale = Math::Matrix::CreateScale(m_size[i].x, m_size[i].y, 0);
				Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos[i].x, m_pos[i].y, 0);
				Math::Matrix rotate = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_angle[i]));
				m_mat[i] = scale * rotate * trans;
				break;
			}
			case bulletType::charge:
			{
				Math::Matrix scale = Math::Matrix::CreateScale(m_size[i].x, m_size[i].y, 0);
				Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos[i].x, m_pos[i].y, 0);
				m_mat[i] = scale * trans;
				break;
			}
		}
	}

}


void C_MidBullet::Init()
{

	m_strTex.Load("Asset/texture/GameScene/Bullet/midBullet.png");
	m_cloTex.Load("Asset/texture/GameScene/Bullet/midBullet2.png");

	for (int i = 0; i < buNum; i++)
	{
		m_pos[i] = {};
		m_move[i] = {};
		m_alive[i] = false;
		m_type[i] = bulletType::straight;
		m_size[i] = {};
		m_rad[i] = {};
		m_angle[i] = {};
	}


}

void C_MidBullet::SetBullet(int i, bulletType type, Math::Vector2 pos, Math::Vector2 move, Math::Vector2 size, Math::Vector2 rad, float angle)
{

	m_alive[i] = true;
	m_pos[i] = pos;
	m_move[i] = move;
	m_type[i] = type;
	m_size[i] = size;
	m_rad[i] = rad;
	m_angle[i] = angle;
}

void C_MidBullet::Release()
{
	m_strTex.Release();
}