#include "PlayerBullet.h"
#include "../../../../SceneManager.h"
#include "../../../GameScene.h"
#include "../Player.h"


C_PlayerBullet::C_PlayerBullet()
{

	m_gameScene = static_cast<C_GameScene*>(SCENEMANAGER.GetCurrentState());
	

}


void C_PlayerBullet::Draw()
{

	for(int i = 0; i < m_buNum; i++)
	{
		if (!m_alive[i]) continue; // 生きていない弾はスキップする
		SHADER.m_spriteShader.SetMatrix(m_mat[i]); // 弾の変換行列をシェーダーにセットする
		SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 16, 16), 1.0f); // 弾のテクスチャを描画する
	}

}

void C_PlayerBullet::MatUpdate()
{
	
	for(int i = 0; i < m_buNum; i++)
	{
		if (!m_alive[i]) continue; // 生きていない弾はスキップする
		m_mat[i] = Math::Matrix::CreateTranslation(m_pos[i].x, m_pos[i].y, 0); // 弾の位置に変換行列を作成する
	}

}

void C_PlayerBullet::Update()
{
	
	m_wait++;
	for(int i = 0; i < m_buNum; i++)
	{
		if (!m_alive[i]) continue; // 生きていない弾はスキップする
		m_pos[i].y += 10; // 弾の移動速度を設定する
		if (m_pos[i].y > 360) // 画面外に出たら弾を消す
		{
			m_alive[i] = false;
		}

	}
	
}

void C_PlayerBullet::Init()
{

	m_tex.Load("Asset/texture/GameScene/Bullet/Bullet.png");
	m_wait = 0;
	for(int i = 0; i < m_buNum; i++)
	{
		m_alive[i] = false; // 最初はすべての弾を生きていない状態にする
		m_pos[i] = { 0.0f, 0.0f }; // 弾の位置を初期化する
	}

}

void C_PlayerBullet::BuInit()
{

	C_Player* m_pl = m_gameScene->GetPlayer();
	
	if (m_wait >= 5)
	{
		for (int i = 0; i < m_buNum; i++)
		{
			if (m_alive[i]) continue;		// すでに生きている弾はスキップする
			m_alive[i] = true;				// 弾を生きている状態にする
			m_pos[i] = m_pl->GetPos();		// 弾の位置をプレイヤーの位置に設定する
			m_wait = 0;						// 弾を発射したら待ち時間をリセットする
			break;							// 最初の空いている弾を初期化したらループを抜ける
		}
	}

}

void C_PlayerBullet::Release()
{

	m_tex.Release();

}