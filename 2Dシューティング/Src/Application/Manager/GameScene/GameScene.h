#pragma once
#include"../StateScene.h"

//前方宣言
class C_Player;	// プレイヤーキャラクターのクラスの前方宣言
class C_PlayerBullet; // プレイヤーの弾のクラスの前方宣言

class C_BasicEnemy; // 敵のクラスの前方宣言
class C_MidEnemy; //敵クラス2の前方宣言
class C_MidBullet;//midenemyの弾クラスの前方宣言
class C_BossEnemy;//ボスクラスの前方宣言
class C_BossBullet;
class C_BossLaser;

class C_Hit; // 当たり判定のクラスの前方宣言
class C_Explosion;//爆発エフェクトクラスの前方宣言

class C_Back;	// 背景のクラスの前方宣言

class C_PlayerHp;//hpUI
class C_Score;//score

class C_Warning;

class C_GameScene : public C_StateScene
{
public:

	C_GameScene() {}
	~C_GameScene() {}

	void Init() override;
	void MatUpdate() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void Debug();

	//ゲームシーンの関数
	bool m_stop;//ゲームの進行を一時中断する変数
	int m_frame;//ゲーム実行中の時間を調べるため
	int m_score;


	//ゲームシーンの関数
	bool GetStop() { return m_stop; }
	void SetStop(bool stop) { m_stop = stop; }//他クラスからゲームの一時中断をさせるための関数
	int GetScore() { return m_score; }
	void SetScore(int s) { m_score += s; }


	//各クラスのインスタンスを渡すためのゲッター関数
	C_Player* GetPlayer() { return m_player; } // プレイヤーキャラクターのポインタを返す関数
	C_PlayerBullet* GetPlayerBullet() { return m_pBullet; } // プレイヤーの弾のポインタを返す関数

	C_BasicEnemy* GetBasicEnemy() { return m_basicEnemy; } // 敵のポインタを返す関数
	C_MidEnemy* GetMidEnemy() { return m_midEnemy; }
	C_MidBullet* GetMidBullet() { return m_midBullet; }
	C_BossEnemy* GetBoss() { return m_boss; }
	C_BossBullet* GetBossBullet() { return m_bossBullet; }
	C_BossLaser* GetLaser() { return m_laser; }

	C_Explosion* GetExplosion() { return m_exp; }//爆発クラスのポインタを返す関数

private:

	// 各クラスのインスタンスを保持するためのメンバ変数
	C_Player* m_player = nullptr; // プレイヤーキャラクターのポインタ
	C_PlayerBullet* m_pBullet = nullptr; // プレイヤーの弾のポインタ
	
	C_BasicEnemy* m_basicEnemy = nullptr; // 敵のポインタ
	C_MidEnemy* m_midEnemy = nullptr;//敵ポインタ２
	C_MidBullet* m_midBullet = nullptr;//midenemyの弾ポインタ
	C_BossEnemy* m_boss = nullptr;//bossポインタ
	C_BossBullet* m_bossBullet = nullptr;//ボスの弾ポインタ
	C_BossLaser* m_laser = nullptr;

	C_Hit* m_hit = nullptr; // 当たり判定のポインタ
	C_Explosion* m_exp = nullptr; //爆発処理のポインタ

	C_Back* m_back = nullptr; // 背景のポインタ
	
	C_PlayerHp* m_hp = nullptr;
	C_Score* m_scoreUI = nullptr;

	C_Warning* m_warning = nullptr;

};