#include"GameScene.h"
#include"../SceneManager.h"
#include "../../Scene.h"

#include "Chara/Player/Player.h"// プレイヤーキャラクターのクラスのインクルード
#include "Chara/Player/PlayerBullet/PlayerBullet.h"// プレイヤーの弾のクラスのインクルード

#include "Chara/Enemy/BasicEnemy/BasicEnemy.h"//雑魚敵クラスのインクルード
#include "Chara/Enemy/MidEnemy/MidEnemy.h"//敵クラスのインクルード
#include "Chara/Enemy/MidEnemy/MidBullet/MidBullet.h"
#include "Chara/Enemy/BossEnemy/BossEnemy.h"
#include "Chara/Enemy/BossEnemy/BossBullet/BossBullet.h"
#include "Chara/Enemy/BossEnemy/BossLaser/BossLaser.h"

#include "Hit/Hit.h"//当たり判定クラスのインクルード
#include "Explosion/Explosion.h"//爆発処理クラスのインクルード

#include "Back/Back.h" // 背景のクラスのインクルード

#include "UI/PlayerHp/PlayerHp.h"//plHpUI
#include "UI/Score/Score.h"//scoreUI

#include "Warning/Warning.h"


void C_GameScene::Draw()
{
	m_back->Draw();//背景


	m_pBullet->Draw();//プレイヤーの弾
	m_player->Draw();//プレイヤー


	m_midBullet->Draw();
	m_basicEnemy->Draw();//敵
	m_midEnemy->Draw();//敵
	m_boss->Draw();
	m_bossBullet->Draw();
	m_laser->Draw();


	m_exp->Draw();//爆発

	m_hp->Draw();//hp
	m_scoreUI->Draw();//score

	m_warning->Draw();


}

void C_GameScene::Update()
{

	if (!m_stop)//ストップフラグがfalseならゲームを動かす
	{

		m_back->Update();

		m_player->Action();

		m_basicEnemy->Action();
		m_midEnemy->Action();
		m_midBullet->Action();
		m_boss->Action();
		m_bossBullet->Action();
		m_laser->Action();


		m_player->Update();
		m_pBullet->Update();

		m_basicEnemy->Update();
		m_midEnemy->Update();
		m_midBullet->Update();
		m_boss->Update();
		m_bossBullet->Update();
		m_laser->Update();

		m_hit->Update();//当たり判定を行う関数
		m_hp->Update();

		m_exp->Update();

		m_scoreUI->Update();

		m_warning->Update();



		//changeScene...シーンの切り替え処理を行う
		if (!m_player->GetAlive())
		{
			SCENE.SetResult(false);//敗北をセット
			SCENEMANAGER.ChangeState(new C_ResultScene());
			return;
		}
		if (!m_boss->GetAlive() && m_boss->GetDefeat())
		{
			SCENE.SetResult(true);//クリアをセット
			SCENE.SetScore(m_score);
			SCENEMANAGER.ChangeState(new C_ResultScene);
			return;
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
	m_midBullet->MatUpdate();
	m_boss->MatUpdate();
	m_bossBullet->MatUpdate();
	m_laser->MatUpdate();

	m_exp->MatUpdate();

	m_hp->MatUpdate();
	m_scoreUI->MatUpdate();


	m_warning->MatUpdate();


}

void C_GameScene::Init()
{

	//ゲームシーンのinit
	srand(time(0));
	m_stop = false;
	m_score = 0;
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
	
	//boss
	m_boss = new C_BossEnemy;
	m_boss->SetGameScene(this);
	m_boss->Init();
	
	//敵の弾
	m_midBullet = new C_MidBullet;
	m_midBullet->SetGameScene(this);
	m_midBullet->Init();

	m_bossBullet = new C_BossBullet;
	m_bossBullet->SetGameScene(this);
	m_bossBullet->Init();

	m_laser = new C_BossLaser;
	m_laser->SetGameScene(this);
	m_laser->Init();
	

	//当たり判定
	m_hit = new C_Hit;
	m_hit->SetGameScene(this);

	//爆発処理
	m_exp = new C_Explosion;
	m_exp->Init();

	//背景など
	m_back = new C_Back; // 背景のインスタンスを作成
	m_back->Init();

	//keikoku
	m_warning = new C_Warning;
	m_warning->SetGameScene(this);
	m_warning->Init();

	//ui
	m_hp = new C_PlayerHp;
	m_hp->SetGameScene(this);
	m_hp->Init();

	m_scoreUI = new C_Score;
	m_scoreUI->SetGameScene(this);
	m_scoreUI->Init();

}

void C_GameScene::Release()
{

	if(m_player != nullptr) delete m_player;
	m_player = nullptr;
	if (m_pBullet != nullptr) delete m_pBullet;
	m_pBullet = nullptr;

	if (m_basicEnemy != nullptr) delete m_basicEnemy;
	m_basicEnemy = nullptr;
	if (m_midEnemy != nullptr) delete m_midEnemy;
	m_midEnemy = nullptr;
	if (m_midBullet != nullptr) delete m_midBullet;
	m_midBullet = nullptr;
	if (m_boss != nullptr) delete m_boss;
	m_boss = nullptr;
	if (m_bossBullet != nullptr) delete m_bossBullet;
	m_bossBullet = nullptr;
	if (m_laser != nullptr) delete m_laser;
	m_laser = nullptr;

	if (m_hit != nullptr) delete m_hit;
	m_hit = nullptr;
	if (m_exp != nullptr) delete m_exp;
	m_exp = nullptr;
	if (m_back != nullptr) delete m_back;
	m_back = nullptr;

	if (m_hp != nullptr) delete m_hp;
	m_hp = nullptr;
	if (m_scoreUI != nullptr) delete m_scoreUI;
	m_scoreUI = nullptr;

}
