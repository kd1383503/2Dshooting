#include "Player.h"

void C_Player::Init()
{
	// ÉvÉåÉCÉÑÅ[ÇÃèâä˙ê›íË
	m_tex.Load("Asset/texture/GameScene/Chara/Player/player.png");
	m_pos = { 0,-300 };
	m_alive = true;

}

void C_Player::MatUpdate()
{

	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);

}

void C_Player::Update()
{

	ControlPlayer();

}

void C_Player::Draw()
{

	if (m_alive)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 64, 64), 1.0f);
	}

}

void C_Player::ControlPlayer()
{

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_pos.y += 5;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_pos.y -= 5;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pos.x += 5;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pos.x -= 5;
	}

}

void C_Player::Release()
{

	m_tex.Release();

}
