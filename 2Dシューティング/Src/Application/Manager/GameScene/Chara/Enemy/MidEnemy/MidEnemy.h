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
	Math::Vector2 GetPos() { return m_pos; }
	Math::Vector2 GetRad() { return m_radius; }
	bool GetAlive() { return m_alive; }
	int GetKill() { return m_kill; }

	//セッター
	void SetHp(int hp) { m_hp = hp; }
	void SetDamage(int damage) { m_hp -= damage; }
	void SetAlive(bool alive) { m_alive = alive; }

	//ゲームシーンセッター
	void SetGameScene(C_GameScene* gameScene)
	{
		if (!gameScene)return;
		m_gameScene = gameScene;
	}

	
private:

	void Release() override;

	C_GameScene* m_gameScene = nullptr;

	
	Math::Matrix m_mat; // 敵の変換行列の配列
	Math::Vector2 m_pos; // 敵の位置の配列
	Math::Vector2 m_move; // 敵の移動量の配列
	Math::Vector2 m_radius = { 200 - 40 ,100 - 30 }; // 敵の半径の配列
	Math::Vector2 m_size;
	bool m_alive; // 敵が生きているかどうかを表すフラグの配列
	int m_hp;//敵の体力

	bool m_atk = false;//攻撃許可
	int m_shake = 0;
	
	int m_strWait = 0;
	int m_clothWait = 0;
	int m_chargeWait = 0;

	//ボス出現
	int m_kill = 1;

};