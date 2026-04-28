#pragma once
#include"../StateScene.h"

//前方宣言
class C_Player;	// プレイヤーキャラクターのクラスの前方宣言
class C_PlayerBullet; // プレイヤーの弾のクラスの前方宣言

class C_BasicEnemy; // 敵のクラスの前方宣言

class C_Hit; // 当たり判定のクラスの前方宣言
class C_Explosion;//爆発エフェクトクラスの前方宣言

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

	//ゲームシーンの関数
	bool m_stop;//ゲームの進行を一時中断する変数
	

	//ゲームシーンの関数
	bool GetStop() { return m_stop; }
	void SetStop(bool stop) { m_stop = stop; }//他クラスからゲームの一時中断をさせるための関数


	//各クラスのインスタンスを渡すためのゲッター関数
	C_Player* GetPlayer() { return m_player; } // プレイヤーキャラクターのポインタを返す関数
	C_PlayerBullet* GetPlayerBullet() { return m_pBullet; } // プレイヤーの弾のポインタを返す関数
	
	C_BasicEnemy* GetBasicEnemy() { return m_basicEnemy; } // 敵のポインタを返す関数

	C_Explosion* GetExplosion() { return m_exp; }//爆発クラスのポインタを返す関数

private:

	// 各クラスのインスタンスを保持するためのメンバ変数
	C_Player* m_player = nullptr; // プレイヤーキャラクターのポインタ
	C_PlayerBullet* m_pBullet = nullptr; // プレイヤーの弾のポインタ
	
	C_BasicEnemy* m_basicEnemy = nullptr; // 敵のポインタ
	
	C_Hit* m_hit = nullptr; // 当たり判定のポインタ
	C_Explosion* m_exp = nullptr; //爆発処理のポインタ

	C_Back* m_back = nullptr; // 背景のポインタ
	

	


};