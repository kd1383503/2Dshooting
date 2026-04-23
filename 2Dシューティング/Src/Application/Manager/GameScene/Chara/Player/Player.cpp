#include "Player.h"
#include "../../../SceneManager.h"
#include "PlayerBullet/PlayerBullet.h"

void C_Player::Init()
{

	m_gameScene = static_cast<C_GameScene*>(SCENEMANAGER.GetCurrentState());

	// プレイヤーの初期設定
	m_tex.Load("Asset/texture/GameScene/Chara/Player/player.png");
	m_pos = { 0,-300 };
	m_move = { 0,0 };
	m_alive = true;

}

void C_Player::Action()
{
	ControlPlayer();
}

void C_Player::MatUpdate()
{
	
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);

}

void C_Player::Update()
{

	m_pos += m_move;

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

	// キーが押されたときに移動量を設定する
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_move.y = 5;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_move.y = - 5;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_move.x = 5;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_move.x = -5;
	}

	// キーが離されたときに移動量を0にする
	if(!(GetAsyncKeyState(VK_RIGHT) & 0x8000) && !(GetAsyncKeyState(VK_LEFT) & 0x8000))
	{
		m_move.x = 0;
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
