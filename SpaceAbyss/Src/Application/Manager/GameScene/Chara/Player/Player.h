#pragma once
#include "../CharaBase.h"

class C_Player : public C_CharaBase
{
public:

	C_Player() {}
	~C_Player() { Release(); } // デストラクタでリソースを解放するようにする

	void Init() override;
	void MatUpdate() override;
	void Update() override;
	void Draw() override;

	//void SetTex(KdTexture* tex) { m_tex = tex; } // テクスチャをセットする関数
	void ControlPlayer(); // プレイヤーの操作を行う関数

private:


	void Release() override;



};