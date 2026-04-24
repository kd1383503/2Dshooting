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

	//セッター
	void SetAlive(bool alive) { m_alive = alive; } // プレイヤーが生きているかどうかを設定する関数

private:


	void Release() override;


	C_GameScene* m_gameScene; // ゲームシーンのポインタ
	
	float m_radius = 64; // プレイヤーの半径


};