#include"GameScene.h"
#include"../SceneManager.h"
#include "Chara/Player/Player.h"


void C_GameScene::Draw()
{

	m_player->Draw();

}

void C_GameScene::Update()
{

	m_player->Update();

}

void C_GameScene::MatUpdate()
{

	m_player->MatUpdate();

}

void C_GameScene::Init()
{

	m_player = new C_Player; // プレイヤーキャラクターのインスタンスを作成
	m_player->Init();

}

void C_GameScene::Release()
{

	if(m_player != nullptr) delete m_player;

}
