#pragma once
#include "../../CharaBase.h"

class C_GameScene;

class C_MidEnemy : public C_CharaBase
{
public:

	C_MidEnemy(){}
	~C_MidEnemy() { Release(); }

	void Init() override;
	void Action() override;
	void MatUpdate() override;
	void Update() override;
	void Draw() override;
	

	//ゲッター
	int GetEnemyNum() { return m_enemyNum; }
	Math::Vector2 GetPos(int i) { return m_pos[i]; }

	//セッター
	void SetHp(int i, int hp) { m_hp[i] = hp; }
	void SetDamage(int i, int damage) { m_hp[i] -= damage; }
	void SetAlive(int i, bool alive) { m_alive[i] = alive; }

	//ゲームシーンセッター
	void SetGameScene(C_GameScene* gameScene)
	{
		if (!gameScene)return;
		m_gameScene = gameScene;
	}

	
private:

	void Release() override;

	C_GameScene* m_gameScene = nullptr;

	static const int m_enemyNum = 10; // 敵の数
	Math::Matrix m_mat[m_enemyNum]; // 敵の変換行列の配列
	Math::Vector2 m_pos[m_enemyNum]; // 敵の位置の配列
	Math::Vector2 m_move[m_enemyNum]; // 敵の移動量の配列
	Math::Vector2 m_radius = {}; // 敵の半径の配列
	Math::Vector2 m_size;
	bool m_alive[m_enemyNum]; // 敵が生きているかどうかを表すフラグの配列
	int m_hp[m_enemyNum];//敵の体力

};