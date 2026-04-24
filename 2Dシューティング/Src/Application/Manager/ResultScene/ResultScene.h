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
	KdTexture m_gameoverTex;

	Math::Matrix m_clearMat;
	Math::Matrix m_gameoverMat;



};