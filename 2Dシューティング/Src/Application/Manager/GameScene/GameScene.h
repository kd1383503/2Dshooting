#pragma once
#include"../StateScene.h"

//前方宣言
class C_Player;	// プレイヤーキャラクターのクラスの前方宣言
class C_PlayerBullet; // プレイヤーの弾のクラスの前方宣言
class C_Back;	// 背景のクラスの前方宣言

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

	//各クラスのインスタンスを渡すためのゲッター関数
	C_Player* GetPlayer() { return m_player; } // プレイヤーキャラクターのポインタを返す関数
	C_PlayerBullet* GetPlayerBullet() { return m_pBullet; } // プレイヤーの弾のポインタを返す関数

private:

	C_Player* m_player = nullptr; // プレイヤーキャラクターのポインタ
	C_PlayerBullet* m_pBullet = nullptr; // プレイヤーの弾のポインタ
	C_Back* m_back = nullptr; // 背景のポインタ
	

	


};