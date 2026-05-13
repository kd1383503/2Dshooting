#pragma once

class C_GameScene;

class C_PlayerHp
{
public:

	C_PlayerHp(){}
	~C_PlayerHp() { Release(); }
	
	void Init();
	void Update();
	void MatUpdate();
	void Draw();




	//setgamescene
	void SetGameScene(C_GameScene* _gameScene)
	{
		if (!_gameScene)return;
		m_gameScene = _gameScene;
	}


private:

	C_GameScene* m_gameScene = nullptr;
	
	void Release();

	KdTexture m_iconTex;
	Math::Matrix m_iconMat;
	Math::Vector2 m_iconPos;

	static const int barNum = 10;
	KdTexture m_barTex;
	Math::Matrix m_barMat[barNum];
	Math::Vector2 m_barPos[barNum];
	
	KdTexture m_frameTex;
	Math::Matrix m_frameMat;
	Math::Vector2 m_framePos;
	
	
	float m_alpha;




};