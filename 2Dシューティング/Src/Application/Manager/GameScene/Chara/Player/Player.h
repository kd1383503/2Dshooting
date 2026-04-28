#pragma once
#include "../CharaBase.h"

class C_GameScene; // 前方宣言

class C_Player : public C_CharaBase
{
public:

	C_Player() {}
	~C_Player() { Release(); } // デストラクタでリソースを解放するようにする

	void Init() override;
	void Action() override;
	void MatUpdate() override;
	void Update() override;
	void Draw() override;

	void ControlPlayer(); // プレイヤーの操作を行う関数

	//ゲッター
	Math::Vector2 GetPos() { return m_pos; } // プレイヤーの位置を返す関数
	float GetRadius() { return m_radius; } // プレイヤーの半径を返す関数
	bool GetAlive() { return m_alive; } // プレイヤーが生きているかどうかを返す関数
	int GetHp() { return m_hp; }//プレイヤーの残り体力を返す関数

	//セッター
	void SetAlive(bool alive) { m_alive = alive; } // プレイヤーが生きているかどうかを設定する関数
	void SetHp(int hp) { m_hp = hp; }//hpをセットする関数
	void SetDamage(int damage) { m_hp -= damage; }//自機に与えられるダメージをHpに反映させる関数



	//ゲームシーンのアドレスセッター
	void SetGameScene(C_GameScene* gameScene)
	{
		if (!gameScene)return;
		m_gameScene = gameScene;
	}


private:


	void Release() override;


	C_GameScene* m_gameScene; // ゲームシーンのポインタ
	
	float m_radius = 32; // プレイヤーの半径


};