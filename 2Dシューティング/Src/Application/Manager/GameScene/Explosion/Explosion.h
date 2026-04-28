#pragma once

class C_GameScene;

class C_Explosion
{
public:

	enum m_exSize
	{
		pb = 1,		//自機弾
		be = 2,		//雑魚敵
		pl = 4		//自機
	};


	C_Explosion() {}
	~C_Explosion() { Release(); }

	void Init();
	void MatUpdate();
	void Update();
	void Draw();

	//getter
	int GetExNum() { return m_expNum; }

	//setter
	void SetEx(Math::Vector2 pos, float size)
	{
		for(int i = 0;i < m_expNum;i++)
		{
			if (m_alive[i])continue;
			m_pos[i] = pos;
			m_size[i] = size;
			m_alive[i] = true;
			m_animCnt[i] = 0;
			break;
		}
	}
	
	//ゲームシーンのアドレスセッター
	void SetGameScene(C_GameScene* gameScene)
	{
		if (!gameScene) return;
		m_gameScene = gameScene;
	}

private:

	void Release();

	C_GameScene* m_gameScene;

	KdTexture m_tex;
	static const int m_expNum = 30;//同時爆発可能数
	int m_anim[m_expNum];//爆発アニメーション
	float m_animCnt[m_expNum];//爆発アニメーションのカウンタ
	bool m_ex[m_expNum];//爆発を起こす
	Math::Matrix m_mat[m_expNum];//爆発の行列
	Math::Vector2 m_pos[m_expNum];//爆発の位置
	float m_size[m_expNum];//爆発の大きさ
	bool m_alive[m_expNum];//その爆発が使われてるか

};