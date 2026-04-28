#pragma once

class C_GameScene; // 前方宣言

class C_PlayerBullet
{
public:

	C_PlayerBullet(){}
	~C_PlayerBullet() { Release(); }

	void Init();
	void BuInit();// 弾の初期化関数

	void MatUpdate();
	void Update();
	void Draw();


	//ゲッター
	int GetBuNum() { return m_buNum; } // 弾の最大数を返す関数
	Math::Vector2 GetPos(int i) { return m_pos[i]; } // 弾の位置を返す関数
	bool GetAlive(int i) { return m_alive[i]; } // 弾が生きているかどうかを返す関数
	float GetRadius() { return m_radius; } // 弾の半径を返す関数
	int GetDamage() { return m_buDamage; }//弾の火力を返す関数

	//セッター
	void SetPressSpace(bool press) { m_pressSpace = press; }
	void SetAlive(int i, bool alive) { m_alive[i] = alive; } // 弾が生きているかどうかを設定する関数

	//ゲームシーンのアドレスセッター
	void SetGameScene(C_GameScene* gameScene)
	{
		if (!gameScene)return;
		m_gameScene = gameScene;
	}

private:

	void Release();

	C_GameScene* m_gameScene = nullptr; // ゲームシーンのポインタ


	KdTexture m_tex; // 弾のテクスチャ
	static const int m_buNum = 50; // 弾の最大数
	Math::Matrix m_mat[m_buNum]; // 弾の変換行列
	Math::Vector2 m_pos[m_buNum]; // 弾の位置
	bool m_alive[m_buNum]; // 弾が生きているかどうか
	int m_wait; // 弾を発射するまでの待ち時間
	float m_radius = 8; // 弾の半径
	const int m_buDamage = 2; //弾の攻撃力

	bool m_pressSpace; // スペースキーが押されているかどうか


};