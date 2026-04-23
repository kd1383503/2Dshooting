#pragma once

class C_GameScene; // 前方宣言

class C_PlayerBullet
{
public:

	C_PlayerBullet();
	~C_PlayerBullet() { Release(); }

	void Init();
	void BuInit();// 弾の初期化関数

	void MatUpdate();
	void Update();
	void Draw();


	//セッター
	void SetPressSpace(bool press) { m_pressSpace = press; }


private:

	void Release();

	C_GameScene* m_gameScene = nullptr; // ゲームシーンのポインタ


	KdTexture m_tex; // 弾のテクスチャ
	static const int m_buNum = 50; // 弾の最大数
	Math::Matrix m_mat[m_buNum]; // 弾の変換行列
	Math::Vector2 m_pos[m_buNum]; // 弾の位置
	bool m_alive[m_buNum]; // 弾が生きているかどうか
	int m_wait; // 弾を発射するまでの待ち時間
	


	bool m_pressSpace; // スペースキーが押されているかどうか


};