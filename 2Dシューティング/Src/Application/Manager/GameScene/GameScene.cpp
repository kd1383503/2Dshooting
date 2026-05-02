#include"GameScene.h"
#include"../SceneManager.h"
#include "../../Scene.h"

#include "Chara/Player/Player.h"// プレイヤーキャラクターのクラスのインクルード
#include "Chara/Player/PlayerBullet/PlayerBullet.h"// プレイヤーの弾のクラスのインクルード

#include "Chara/Enemy/BasicEnemy/BasicEnemy.h"//雑魚敵クラスのインクルード
#include "Chara/Enemy/MidEnemy/MidEnemy.h"//敵クラスのインクルード

#include "Hit/Hit.h"//当たり判定クラスのインクルード
#include "Explosion/Explosion.h"//爆発処理クラスのインクルード

#include "Back/Back.h" // 背景のクラスのインクルード


void C_GameScene::Draw()
{
	m_back->Draw();//背景

	m_player->Draw();//プレイヤー
	m_pBullet->Draw();//プレイヤーの弾

	m_basicEnemy->Draw();//敵
	m_midEnemy->Draw();//敵

	m_exp->Draw();//爆発

}

void C_GameScene::Update()
{

	if (!m_stop)//ストップフラグがfalseならゲームを動かす
	{

		m_back->Update();

		m_player->Action();

		m_basicEnemy->Action();
		m_midEnemy->Action();


		m_player->Update();
		m_pBullet->Update();

		m_basicEnemy->Update();
		m_midEnemy->Update();

		m_hit->Update();//当たり判定を行う関数

		m_exp->Update();





		//changeScene...シーンの切り替え処理を行う
		if (!m_player->GetAlive())
		{
			SCENE.SetResult(false);//敗北をセット
			SCENEMANAGER.ChangeState(new C_ResultScene());
		}

	}//ゲームのメイン部分はこの中に書く

	
	 //オプション部分は下に



}

void C_GameScene::MatUpdate()
{

	m_back->MatUpdate();

	m_player->MatUpdate();
	m_pBullet->MatUpdate();

	m_basicEnemy->MatUpdate();
	m_midEnemy->MatUpdate();

	m_exp->MatUpdate();

}

void C_GameScene::Init()
{

	//ゲームシーンのinit
	srand(time(0));
	m_stop = false;

	//===================

	//プレイヤー
	m_player = new C_Player; // プレイヤーキャラクターのインスタンスを作成
	m_player->Init();
	m_player->SetGameScene(this);

	m_pBullet = new C_PlayerBullet; // プレイヤーの弾のインスタンスを作成
	m_pBullet->Init();
	m_pBullet->SetGameScene(this);


	//敵
	m_basicEnemy = new C_BasicEnemy; // 敵のインスタンスを作成
	m_basicEnemy->SetGameScene(this);
	m_basicEnemy->Init();

	m_midEnemy = new C_MidEnemy;
	m_midEnemy->SetGameScene(this);
	m_midEnemy->Init();


	//当たり判定
	m_hit = new C_Hit;
	m_hit->SetGameScene(this);

	//爆発処理
	m_exp = new C_Explosion;
	m_exp->Init();

	//背景など
	m_back = new C_Back; // 背景のインスタンスを作成
	m_back->Init();

}

void C_GameScene::Release()
{

	if(m_player != nullptr) delete m_player;
	if (m_pBullet != nullptr) delete m_pBullet;

	if (m_basicEnemy != nullptr) delete m_basicEnemy;
	if (m_midEnemy != nullptr) delete m_midEnemy;

	if (m_hit != nullptr) delete m_hit;
	if (m_exp != nullptr) delete m_exp;

	if (m_back != nullptr) delete m_back;


}
