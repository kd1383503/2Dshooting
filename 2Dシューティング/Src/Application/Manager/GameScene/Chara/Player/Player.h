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

	Math::Vector2 GetPos() { return m_pos; } // プレイヤーの位置を返す関数


private:


	void Release() override;


	C_GameScene* m_gameScene; // ゲームシーンのポインタ


};