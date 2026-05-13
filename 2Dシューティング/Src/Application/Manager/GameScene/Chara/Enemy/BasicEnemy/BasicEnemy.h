#pragma once
#include "../../CharaBase.h"

class C_GameScene;

class C_BasicEnemy : public C_CharaBase
{
public:

	C_BasicEnemy() {}
	~C_BasicEnemy() { Release(); }

	//C_CharaBaseクラスの純粋仮想関数をオーバーライド
	void Init() override;
	void EnemyInit(int i, int type);
	void Action() override;
	void MatUpdate() override;
	void Update() override;
	void Draw() override;

	

	//ゲッター
	int GetEnemyNum() { return enemyNum; }
	Math::Vector2 GetPos(int i) { return m_pos[i]; }
	float GetRadius() { return m_radius; }
	bool GetAlive(int i) { return m_alive[i]; }
	int GetKill() { return m_killCnt; }//ベーシックエネミーを倒した数を他クラスに渡す

	//セッター
	void SetAlive(int i, bool alive) { m_alive[i] = alive; }
	void SetHp(int i, int hp) { m_hp[i] = hp; }
	void SetDamage(int i, int damage) { m_hp[i] -= damage; }
	void SetKill(int i) { m_killCnt = i; }
	void SetHit(int i, bool flg)
	{
		m_hit[i] = flg;
		m_cnt[i] = 3;
	}

	//gamescene setter
	void SetGameScene(C_GameScene* gameScene)
	{
		if (!gameScene)return;
		m_gameScene = gameScene;
	}

private:

	void Release() override;

	enum enemyType
	{
		basic = 0,
		shake,
		uni
	};

	C_GameScene* m_gameScene = nullptr;

	KdTexture m_tex2;

	static const int enemyNum = 10; // 敵の数
	Math::Matrix m_mat[enemyNum]; // 敵の変換行列の配列
	Math::Vector2 m_pos[enemyNum]; // 敵の位置の配列
	Math::Vector2 m_move[enemyNum]; // 敵の移動量の配列
	float m_radius = 24; // 敵の半径の配列
	bool m_alive[enemyNum]; // 敵が生きているかどうかを表すフラグの配列
	int m_hp[enemyNum];//敵の体力
	int m_enemyType[enemyNum];//タイプごとに画像と動きを変える
	float m_anim[enemyNum];

	int m_shakeCnt[enemyNum] = {};//

	bool m_hit[enemyNum] = {};
	int m_cnt[enemyNum] = {};


	int m_killCnt = 0; //ベーシックエネミーが倒されたら１カウント

	

};