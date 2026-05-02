#pragma once
#include "../../CharaBase.h"

class C_BossEnemy : public C_CharaBase
{
public:

	C_BossEnemy(){}
	~C_BossEnemy() { Release(); }

	void Init()override;
	void Action()override;
	void MatUpdate()override;
	void Update()override;
	void Draw()override;


private:

	void Release()override;


};