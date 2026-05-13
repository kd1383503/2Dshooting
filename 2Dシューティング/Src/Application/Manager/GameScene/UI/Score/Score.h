#pragma once

class C_GameScene;

class C_Score
{
public:

	C_Score(){}
	~C_Score() { Release(); }

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

	C_GameScene* m_gameScene;

	void Release();

	KdTexture m_tex;

	static const int maxDigit = 8;//桁数

	Math::Matrix m_mat[maxDigit];
	Math::Vector2 m_pos[maxDigit];
	unsigned long m_score = 0;		//現在のスコア
	int m_digit[maxDigit] = {};		//各桁を管理する配列


};