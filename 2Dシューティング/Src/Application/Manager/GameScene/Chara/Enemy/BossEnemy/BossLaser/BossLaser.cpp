#include"BossLaser.h"

void C_BossLaser::Draw() 
{

	if (!m_alive)return;
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTexReferencePoint(&m_tex, Math::Rectangle(m_anim[(int)m_animCnt]* 64, 0, 64, 1000), 1.0f);

}

void C_BossLaser::Action() 
{
	if (!m_alive)return;


}

void C_BossLaser::Update()
{
	if (!m_alive)return;

	m_animCnt += 0.2f;
	if (m_animCnt >= 9) m_hitjudge = true;
	if (m_animCnt >= m_animMax)
	{
		m_animCnt = 0;
		m_alive = false;
		m_hitjudge = false;
		m_hit = false;
	}

}

void C_BossLaser::MatUpdate()
{

	float h = 1000.0f;
	float w = 64.0f;

	
	Math::Matrix rotate = Math::Matrix::CreateRotationZ(m_angle);
	Math::Matrix scale = Math::Matrix::CreateScale(m_size, m_size, 1);
	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);

	m_mat = scale * rotate * trans;

}

void C_BossLaser::Init()
{

	m_tex.Load("Asset/texture/GameScene/Bullet/2laser.png");

	m_pos = {};
	m_size = 2;
	m_alive = false;
	m_angle = 0;
	m_hitjudge = false;
	m_hit = false;

}

void C_BossLaser::Release()
{
	m_tex.Release();
}


void C_BossLaser::SetLaser(Math::Vector2 pos, float angle)
{

	m_alive = true;
	m_angle = angle;
	m_pos = pos;
	m_animCnt = 0;

}