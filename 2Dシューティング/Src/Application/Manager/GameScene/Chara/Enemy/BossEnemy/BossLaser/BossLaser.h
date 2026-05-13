#pragma once

class C_GameScene;

class C_BossLaser
{
public:

	C_BossLaser(){}
	~C_BossLaser() { Release(); }

	void Init();
	void Action();
	void MatUpdate();
	void Update();
	void Draw();


	//”­ŽË
	void SetLaser(Math::Vector2 pos, float angle);

	//getter
	float GetAngle() { return m_angle; }
	Math::Vector2 GetPos() { return m_pos; }
	float GetSize() { return m_size; }
	bool GetAlive() { return m_alive; }
	int GetDamage() { return m_damage; }
	bool GetJudge() { return m_hitjudge; }
	bool GetHit() { return m_hit; }

	//setter
	void SetJudge(bool flg) { m_hitjudge = flg; }
	void SetHit(bool flg) { m_hit = flg; }

	void SetGameScene(C_GameScene* _gameScene)
	{
		if (!_gameScene)return;
		m_gameScene = _gameScene;
	}

private:

	C_GameScene* m_gameScene;

	void Release();

	
	KdTexture m_tex;
	Math::Matrix m_mat;
	Math::Vector2 m_pos;
	float m_size;
	bool m_alive;
	const int m_damage = 10;
	float m_angle;
	static const int m_animMax = 19;
	int m_anim[m_animMax] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 13, 14, 13, 14 };
	float m_animCnt = 0.0f;

	bool m_hitjudge;
	bool m_hit;

};