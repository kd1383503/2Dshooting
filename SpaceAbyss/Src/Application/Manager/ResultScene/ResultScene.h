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



};