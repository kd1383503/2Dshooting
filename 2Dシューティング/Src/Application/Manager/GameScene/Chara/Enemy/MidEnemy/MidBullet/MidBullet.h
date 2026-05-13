#pragma once

class C_GameScene;

class C_MidBullet
{
public:

	C_MidBullet(){}
	~C_MidBullet() { Release(); }

	enum bulletType
	{
		straight,
		cloth,
		charge
	};

	enum bulletSize
	{
		straightX = 1,
		straightY = 1,
		clothX = 1,
		clothY = 1,
		chargeX,
		chargeY
	};

	enum bulletRad
	{
		straightx,
		straighty,
		clothx,
		clothy,
		chargex,
		chargey,
		end
	};

	enum bulletDamage
	{
		str = 1,
		clo = 1
	};

	void Init();
	void Action();
	void MatUpdate();
	void Update();
	void Draw();


	//setter
	void SetPos(int i, Math::Vector2 pos) { m_pos[i] = pos; }
	void SetMove(int i, Math::Vector2 move) { m_move[i] = move; }
	void SetType(int i, bulletType type) { m_type[i] = type; }
	void SetAlive(int i, bool alive) { m_alive[i] = alive; }
	void SetBullet(int i, bulletType type, Math::Vector2 pos, Math::Vector2 move, Math::Vector2 size, Math::Vector2 rad, float angle);

	//getter
	int GetNum() { return buNum; }
	Math::Vector2 GetPos(int i) { return m_pos[i]; }
	bool GetAlive(int i) { return m_alive[i]; }
	float GetRad(bulletRad br) { return bRad[br]; }
	bulletType GetType(int i) { return m_type[i]; }

	//gameScene
	void SetGameScene(C_GameScene* _gameScene)
	{
		if (!_gameScene)return;
		m_gameScene = _gameScene;
	}


private:

	void Release();

	C_GameScene* m_gameScene;

	KdTexture m_strTex;
	KdTexture m_cloTex;
	KdTexture m_chaTex;

	static const int buNum = 100;
	Math::Matrix m_mat[buNum];
	Math::Vector2 m_size[buNum];
	Math::Vector2 m_pos[buNum];
	Math::Vector2 m_move[buNum];
	float m_angle[buNum];
	bool m_alive[buNum];
	bulletType m_type[buNum];

	Math::Vector2 m_rad[buNum] = {};

	
	float bRad[end] = { 16,16, 16,16, 0,0 };

};