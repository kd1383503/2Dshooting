#include"GameScene.h"
#include"../SceneManager.h"
#include "Chara/Player/Player.h"// プレイヤーキャラクターのクラスのインクルード
#include "Chara/Player/PlayerBullet/PlayerBullet.h"// プレイヤーの弾のクラスのインクルード
#include "Back/Back.h" // 背景のクラスのインクルード


void C_GameScene::Draw()
{
	m_back->Draw();//背景

	m_player->Draw();//プレイヤー
	m_pBullet->Draw();//プレイヤーの弾
}

void C_GameScene::Update()
{

	m_back->Update();

	m_player->Action();

	m_player->Update();
	m_pBullet->Update();
}

void C_GameScene::MatUpdate()
{

	m_back->MatUpdate();
	m_player->MatUpdate();
	m_pBullet->MatUpdate();
}

void C_GameScene::Init()
{

	m_player = new C_Player; // プレイヤーキャラクターのインスタンスを作成
	m_player->Init();

	m_back = new C_Back; // 背景のインスタンスを作成
	m_back->Init();

	m_pBullet = new C_PlayerBullet; // プレイヤーの弾のインスタンスを作成
	m_pBullet->Init();

}

void C_GameScene::Release()
{

	if(m_player != nullptr) delete m_player;
	if (m_back != nullptr) delete m_back;
	if (m_pBullet != nullptr) delete m_pBullet;
}
