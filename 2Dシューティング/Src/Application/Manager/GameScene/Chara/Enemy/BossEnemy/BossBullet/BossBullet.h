#pragma once

class C_GameScene;

class C_BossBullet
{
public:

	C_BossBullet(){}
	~C_BossBullet() { Release(); }

	void Init();
	void Action();
	void MatUpdate();
	void Update();
	void Draw();


	//setter
	void SetPos(int i, Math::Vector2 pos) { m_pos[i] = pos; }
	void SetMove(int i, Math::Vector2 move) { m_move[i] = move; }
	void SetAlive(int i, bool alive) { m_alive[i] = alive; }
	void SetBullet(int i, Math::Vector2 pos, Math::Vector2 move, float angle);

	//getter
	int GetNum() { return buNum; }
	Math::Vector2 GetPos(int i) { return m_pos[i]; }
	bool GetAlive(int i) { return m_alive[i]; }
	//float GetRad() { return bRad; }
	int GetDamage() { return m_damage; }
	

	//gameScene
	void SetGameScene(C_GameScene* _gameScene)
	{
		if (!_gameScene)return;
		m_gameScene = _gameScene;
	}


private:

	void Release();

	C_GameScene* m_gameScene;

	KdTexture m_tex;
	

	static const int buNum = 100;
	Math::Matrix m_mat[buNum];
	Math::Vector2 m_size[buNum];
	Math::Vector2 m_pos[buNum];
	Math::Vector2 m_move[buNum];
	float m_angle[buNum];
	bool m_alive[buNum];
	
	const int m_damage = 1;

	Math::Vector2 m_rad[buNum] = {};

};