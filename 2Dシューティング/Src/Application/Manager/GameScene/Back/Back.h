#pragma once

class C_Back
{
	public:
	C_Back() {}
	~C_Back() { Release(); }
	void Init();
	void MatUpdate();
	void Update();
	void Draw();
private:
	
	void Release();

	KdTexture m_tex; // ”wŒi‚ÌƒeƒNƒXƒ`ƒƒ
	Math::Vector2 m_pos; // ”wŒi‚ÌˆÊ’u
	Math::Vector2 m_pos2; // ”wŒi2‚ÌˆÊ’u
	Math::Matrix m_mat; // ”wŒi‚Ì•ÏŠ·s—ñ
	Math::Matrix m_mat2; // ”wŒi2‚Ì•ÏŠ·s—ñ


	const float m_scroll = 3.0f; // ”wŒi‚ÌƒXƒNƒ[ƒ‹‘¬“x

};