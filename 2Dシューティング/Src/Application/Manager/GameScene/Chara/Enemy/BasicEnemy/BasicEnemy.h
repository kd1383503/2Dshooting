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

	//ゲッター
	int GetEnemyNum() { return enemyNum; }
	Math::Vector2 GetPos(int i) { return m_pos[i]; }
	float GetRadius() { return m_radius; }
	bool GetAlive(int i) { return m_alive[i]; }

	//セッター
	void SetAlive(int i, bool alive) { m_alive[i] = alive; }
	void SetHp(int i, int hp) { m_hp[i] = hp; }
	void SetDamage(int i, int damage) { m_hp[i] -= damage; }

private:

	void Release() override;

	static const int enemyNum = 1; // 敵の数
	Math::Matrix m_mat[enemyNum]; // 敵の変換行列の配列
	Math::Vector2 m_pos[enemyNum]; // 敵の位置の配列
	Math::Vector2 m_move[enemyNum]; // 敵の移動量の配列
	float m_radius = 24; // 敵の半径の配列
	bool m_alive[enemyNum]; // 敵が生きているかどうかを表すフラグの配列
	int m_hp[enemyNum];//敵の体力



};