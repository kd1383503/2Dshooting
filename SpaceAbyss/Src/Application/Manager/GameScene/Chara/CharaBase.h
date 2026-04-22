#pragma once

class C_CharaBase
{
public:

	C_CharaBase() {}
	~C_CharaBase() {}

	virtual void Init() = 0;
	virtual void MatUpdate() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	


protected:

	virtual void Release() = 0;
	
	KdTexture m_tex;// キャラクターのテクスチャ
	Math::Matrix m_mat;// キャラクターの変換行列
	Math::Vector2 m_pos; // キャラクターの位置を表すベクトル
	bool m_alive; // キャラクターが生きているかどうかを表すフラグ

};