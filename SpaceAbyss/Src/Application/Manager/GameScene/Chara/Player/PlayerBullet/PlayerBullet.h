#pragma once

class C_PlayerBullet
{
public:

	C_PlayerBullet() {}
	~C_PlayerBullet() { Release(); }

	void Init();
	void MatUpdate();
	void Update();
	void Draw();


	//セッター
	void SetPressSpace(bool press) { m_pressSpace = press; }


private:

	void Release();

	Math::Vector2 m_pos; // 弾の位置
	bool m_alive; // 弾が生きているかどうか



	bool m_pressSpace; // スペースキーが押されているかどうか


};