#pragma once

class C_GameScene;

class C_Hit
{
public:



	C_Hit(){}
	~C_Hit(){}

	void Update();

	void PlayerBulletToEnemy();// プレイヤーの弾と敵の当たり判定を行う関数
	void PlayerEnemy();//プレイヤーと敵の当たり判定を行う関数
	
	void PlayerBulletToMidEnemy();
	void StrBulletToPlayer();
	void CloBulletToPlayer();
	void PlayerMidEnemy();

	void PlayerBulletToBossMain();
	void PlayerBulletToRightArm();
	void PlayerBulletToLeftArm();
	void BossBulletToPlayer();
	void BossLaserToPlayer();


	//便利関数
	float clamp(float v, float minV, float MaxV);

	//ゲームシーンのアドレスセッター
	void SetGameScene(C_GameScene* gameScene)
	{
		if (!gameScene)return;
		m_gameScene = gameScene;
	}

private:

	C_GameScene* m_gameScene = nullptr; // ゲームシーンのポインタ

};