#include"GameScene.h"
#include"../SceneManager.h"
#include "../../Scene.h"

#include "Chara/Player/Player.h"// プレイヤーキャラクターのクラスのインクルード
#include "Chara/Player/PlayerBullet/PlayerBullet.h"// プレイヤーの弾のクラスのインクルード

#include "Chara/Enemy/BasicEnemy/BasicEnemy.h"

#include "Hit/Hit.h"

#include "Back/Back.h" // 背景のクラスのインクルード


void C_GameScene::Draw()
{
	m_back->Draw();//背景

	m_player->Draw();//プレイヤー
	m_pBullet->Draw();//プレイヤーの弾

	m_basicEnemy->Draw();//敵

}

void C_GameScene::Update()
{

	m_back->Update();

	m_player->Action();
	
	m_basicEnemy->Action();


	m_player->Update();
	m_pBullet->Update();

	m_basicEnemy->Update();

	m_hit->PlayerBulletToEnemy();// プレイヤーの弾と敵の当たり判定を行う関数
	m_hit->PlayerEnemy();//プレイヤーと敵







	//changeScene
	if (!m_player->GetAlive())
	{
		SCENE.SetResult(false);//敗北をセット
		SCENEMANAGER.ChangeState(new C_ResultScene());
	}

}

void C_GameScene::MatUpdate()
{

	m_back->MatUpdate();

	m_player->MatUpdate();
	m_pBullet->MatUpdate();

	m_basicEnemy->MatUpdate();

}

void C_GameScene::Init()
{

	//プレイヤー
	m_player = new C_Player; // プレイヤーキャラクターのインスタンスを作成
	m_player->Init();

	m_pBullet = new C_PlayerBullet; // プレイヤーの弾のインスタンスを作成
	m_pBullet->Init();

	//敵
	m_basicEnemy = new C_BasicEnemy; // 敵のインスタンスを作成
	m_basicEnemy->Init();

	//当たり判定
	m_hit = new C_Hit;

	//背景など
	m_back = new C_Back; // 背景のインスタンスを作成
	m_back->Init();

}

void C_GameScene::Release()
{

	if(m_player != nullptr) delete m_player;
	if (m_pBullet != nullptr) delete m_pBullet;

	if (m_basicEnemy != nullptr) delete m_basicEnemy;

	if (m_hit != nullptr) delete m_hit;

	if (m_back != nullptr) delete m_back;


}
