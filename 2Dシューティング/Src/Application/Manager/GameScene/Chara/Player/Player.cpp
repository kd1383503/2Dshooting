#include "Player.h"
#include "../../GameScene.h"
#include "PlayerBullet/PlayerBullet.h"
#include "../../Explosion/Explosion.h"

void C_Player::Init()
{

	// プレイヤーの初期設定
	m_tex.Load("Asset/texture/GameScene/Chara/Player/player.png");
	m_pos = { 0,-300 };
	m_move = { 0,0 };
	m_hp = 10;
	m_alive = true;
	m_scale = { 1.33f, 1.33f };

	m_alpha = 1.0f;

	m_lose = false;
	m_loseCnt = 0;

	m_hit = false;
	m_addAlpha = 0.05;
	m_hitCnt = 0;

}

void C_Player::Action()
{
	if (!m_lose)
	{
		ControlPlayer();
	}
}

void C_Player::MatUpdate()
{
	if (!m_alive) return;
	Math::Matrix scale = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);
	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = scale * trans;

}

void C_Player::Update()
{

	if (!m_alive)return;

	m_pos += m_move;


	//画面内固定
	if (m_pos.x > 640 - 32) m_pos.x = 640 - 32;
	if (m_pos.x < -640 + 32) m_pos.x = -640 + 32;
	if (m_pos.y > 360 - 32) m_pos.y = 360 - 32;
	if (m_pos.y < -360 + 32) m_pos.y = -360 + 32;

	//アニメーション
	m_anim.x += 0.2;
	if (m_anim.x >= 3.0f)
	{
		m_anim.x = 0.0f;
	}


	if (m_hit)
	{
		m_alpha += m_addAlpha;
		if (m_alpha >= 1.0f)
		{
			m_alpha = 1.0f;
			m_addAlpha = -0.1f;
		}
		if (m_alpha <= 0.0f)
		{
			m_alpha = 0.0f;
			m_addAlpha = 0.1f;
		}
		m_hitCnt--;
		if (m_hitCnt <= 0)
		{
			m_hit = false;
		}
	}


	if (m_hp <= 0) m_hp = 1;

	if (GetAsyncKeyState('O') & 0x8000) m_hp = 0;

	if (m_hp <= 0 && !m_lose)
	{
		m_lose = true;
		m_loseCnt = 60;
		C_Explosion* ex = m_gameScene->GetExplosion();
		ex->SetEx(m_pos, ex->m_exSize::pl);

		m_move = {};
	}

	if (m_lose)
	{
		if (m_loseCnt <= 0)
		{
			m_alive = false;
		}
		m_loseCnt--;
		m_alpha *= 0.9;
	}

}

void C_Player::Draw()
{

	if (m_alive)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle((int)m_anim.x * 48, (int)m_anim.y * 58, 48, 58), m_alpha);
	}

}

void C_Player::ControlPlayer()
{

	// キーが押されたときに移動量を設定する
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			m_move.y = 8;
		}
		else
		{
			m_move.y = 5;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			m_move.y = -8;
		}
		else
		{
			m_move.y = -5;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			m_move.x = 8;
			m_anim.y = 2.0f;
		}
		else
		{
			m_move.x = 5;
			m_anim.y = 1.0f;
		}
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			m_move.x = -8;
			m_anim.y = 4.0f;
		}
		else
		{
			m_move.x = -5;
			m_anim.y = 3.0f;
		}
	}

	// キーが離されたときに移動量を0にする
	if(!(GetAsyncKeyState(VK_RIGHT) & 0x8000) && !(GetAsyncKeyState(VK_LEFT) & 0x8000))
	{
		m_move.x = 0;
		m_anim.y = 0.0f;
	}
	if(!(GetAsyncKeyState(VK_UP) & 0x8000) && !(GetAsyncKeyState(VK_DOWN) & 0x8000))
	{
		m_move.y = 0;
	}

	// スペースキーが押されたときに弾を発射する
	C_PlayerBullet* m_pb = m_gameScene->GetPlayerBullet();
	if(GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_pb->SetPressSpace(true);// スペースキーが押されていることをプレイヤーの弾クラスに伝える
		m_pb->BuInit();
	}
	else
	{
		m_pb->SetPressSpace(false);
	}



}

void C_Player::Release()
{

	m_tex.Release();

}
