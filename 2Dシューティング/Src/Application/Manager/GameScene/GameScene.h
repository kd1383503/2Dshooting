#pragma once
#include"../StateScene.h"

//前方宣言
class C_Player;

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


private:

	C_Player* m_player; // プレイヤーキャラクターのスマートポインタ


};