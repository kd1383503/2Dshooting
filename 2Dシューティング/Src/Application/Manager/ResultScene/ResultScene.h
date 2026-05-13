#pragma once
#include"../StateScene.h"

class C_ResultScene : public C_StateScene
{
public:

	C_ResultScene() {}
	~C_ResultScene() {}

	void Init() override;
	void MatUpdate() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:

	KdTexture m_clearTex;
	Math::Matrix m_clearMat;
	Math::Vector2 m_clearPos;

	KdTexture m_scoreTex;
	

	KdTexture m_scTex;
	Math::Matrix m_scMat;

	static const int maxDigit = 8;//桁数


	Math::Matrix m_scoreMat[maxDigit];
	Math::Vector2 m_scorePos[maxDigit];
	unsigned long m_score = 0;		//現在のスコア
	int m_digit[maxDigit] = {};		//各桁を管理する配列
	float m_size;
	bool m_sizeFlg;
	int m_cnt;

	//
	KdTexture m_backTex;
	Math::Matrix m_backMat;
	
	KdTexture m_gameoverTex;
	KdTexture m_blackTex;
	
	Math::Matrix m_gameoverMat;
	Math::Matrix m_blackMat;
	Math::Vector2 m_gameoverPos;
	float m_goAlpha;
	float m_peAlpha;
	float m_peAnim;
	bool m_peFlg;

	KdTexture m_peTex;
	Math::Matrix m_peMat;



};