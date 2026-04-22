#pragma once

class C_StateScene
{
public:

	C_StateScene() {}
	~C_StateScene() {}

	virtual void Init() = 0;
	virtual void MatUpdate() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;


};