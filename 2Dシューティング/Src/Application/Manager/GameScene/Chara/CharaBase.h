#pragma once

class C_CharaBase
{
public:

	C_CharaBase() {}
	~C_CharaBase() {}

	virtual void Init() = 0;
	virtual void Action() = 0;
	virtual void MatUpdate() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	


protected:

	virtual void Release() = 0;
	
	KdTexture m_tex;// キャラクターのテクスチャ
	Math::Matrix m_mat;// キャラクターの変換行列
	Math::Vector2 m_pos; // キャラクターの位置を表すベクトル
	Math::Vector2 m_move; // キャラクターの移動量を表すベクトル
	float m_radius; // キャラクターの半径
	bool m_alive; // キャラクターが生きているかどうかを表すフラグ
	int m_hp;//キャラクターの体力

};