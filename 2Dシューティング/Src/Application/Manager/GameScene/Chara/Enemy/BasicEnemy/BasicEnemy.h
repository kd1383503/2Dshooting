#pragma once
#include "../../CharaBase.h"

//前方宣言
class C_GameScene;

class C_BasicEnemy : public C_CharaBase
{
public:

	C_BasicEnemy(){}
	~C_BasicEnemy() { Release(); }

	//C_CharaBaseクラスの純粋仮想関数をオーバーライド
	void Init() override;
	void Action() override;
	void MatUpdate() override;
	void Update() override;
	void Draw() override;


private:

	void Release() override;

	static const int enemyNum = 1; // 敵の数
	Math::Matrix m_mat[enemyNum]; // 敵の変換行列の配列
	Math::Vector2 m_pos[enemyNum]; // 敵の位置の配列
	Math::Vector2 m_move[enemyNum]; // 敵の移動量の配列
	float m_radius[enemyNum]; // 敵の半径の配列
	bool m_alive[enemyNum]; // 敵が生きているかどうかを表すフラグの配列




};