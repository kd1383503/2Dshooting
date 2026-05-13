#pragma once

class C_GameScene;

class C_Warning
{
public:

	C_Warning() {}
	~C_Warning() { Release(); }

	void Init();
	void Update();
	void MatUpdate();
	void Draw();

	//setgameScene
	void SetGameScene(C_GameScene* _gameScene)
	{
		if (!_gameScene)return;
		m_gameScene = _gameScene;
	}

private:

	void Release();

	C_GameScene* m_gameScene;

	KdTexture m_tex;
	KdTexture m_topTex;
	KdTexture m_btmTex;
	KdTexture m_backTex;

	Math::Matrix m_mat;
	Math::Vector2 m_pos;

	Math::Matrix m_topMat;
	Math::Vector2 m_topPos;
	Math::Matrix m_topMat2;
	Math::Vector2 m_topPos2;

	Math::Matrix m_btmMat;
	Math::Vector2 m_btmPos;
	Math::Matrix m_btmMat2;
	Math::Vector2 m_btmPos2;

	float m_scroll;

	int m_cnt;

	float m_alpha;
	float m_addAlpha;


};