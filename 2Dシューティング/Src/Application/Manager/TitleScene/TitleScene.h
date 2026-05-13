#pragma once
#include"../StateScene.h"

class C_Back;

class C_TitleScene : public C_StateScene
{
public:

	C_TitleScene(){}
	~C_TitleScene(){}

	void Init() override;
	void MatUpdate() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:

	KdTexture m_tex;				// タイトルの背景テクスチャ
	KdTexture m_pressEnterTex;		// Press Enterのテクスチャ

	Math::Matrix m_mat;				// タイトルの行列
	Math::Matrix m_matS;
	Math::Vector2 m_pos;			// タイトルの位置


	Math::Matrix m_pressEnterMat;	// Press Enterの行列
	Math::Vector2 m_pressEnterPos;	// Press Enterの位置
	float m_pressEnterAlpha;		// Press Enterのアルファ値
	float m_addAlpha;				// Press Enterのアルファ値の増減量

	C_Back* m_back = nullptr;


};