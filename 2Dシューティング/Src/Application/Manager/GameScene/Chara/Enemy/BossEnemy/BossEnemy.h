#pragma once
#include "../../CharaBase.h"

class C_GameScene;

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

	void RotateArm();
	void BulletATK();
	void LaserATK();
	void LushATK();

	float RightArmAngle();
	float LeftArmAngle();
	float Clamp(float v, float minV, float maxV);
	Math::Vector2 Rotate(Math::Vector2 v, float angle);
	float GetBossPlayerAngle();



	//ÉQÉbÉ^Å[
	Math::Vector2 GetPos() { return m_pos; }
	Math::Vector2 GetRad() { return m_radius; }
	bool GetAlive() { return m_alive; }
	Math::Vector2 GetSize() { return m_size; }
	bool GetDefeat() { return m_defeat; }

	//âEòr
	Math::Vector2 GetPosR() { return m_rPos; }
	float GetRightAngle() { return m_rightArmAngle; }

	//ç∂òr
	Math::Vector2 GetPosL() { return m_lPos; }
	float GetLeftAngle() { return m_leftArmAngle; }

	//ÉZÉbÉ^Å[
	void SetHp(int hp) { m_hp = hp; }
	void SetDamage(int damage) { m_hp -= damage; }
	void SetAlive(bool alive) { m_alive = alive; }
	void SetLaserFlg(bool flg) { m_laserFlg = flg; }
	void SetHit(bool flg)
	{
		m_hit = flg;
		m_cnt = 4;
	}

	//warning
	void SetStart() { m_start = true; }
	void SetWarning() { m_warning = false; }
	bool GetWarning() { return m_warning; }
	bool GetWait() { return m_wait; }

	//gamesceneSet
	void SetGameScene(C_GameScene* _gameScene)
	{
		if (!_gameScene)return;
		m_gameScene = _gameScene;
	}

private:

	C_GameScene* m_gameScene;

	void Release()override;

	Math::Vector2 m_radius = {400 , 177};
	Math::Vector2 m_size = { 0.75, 0.75};
	
	KdTexture m_enTex;
	Math::Matrix m_enMat;
	float m_anim;

	//arm
	KdTexture m_rightArmTex;
	Math::Matrix m_rightArmMat;
	Math::Vector2 m_rPos;
	float m_rightArmAngle;
	const float m_rArmMax = DirectX::XMConvertToRadians(80);
	const float m_rArmMin = DirectX::XMConvertToRadians(-55);
	float m_targetAngleR = 0;


	KdTexture m_leftArmTex;
	Math::Matrix m_leftArmMat;
	Math::Vector2 m_lPos;
	float m_leftArmAngle;
	const float m_lArmMax = DirectX::XMConvertToRadians(55);
	const float m_lArmMin = DirectX::XMConvertToRadians(-80);
	float m_targetAngleL = 0;

	float m_laserPosY;
	bool m_laserFlg;

	int m_buAtkTime = 0;
	int m_laserAtkTime = 0;

	bool m_atk = false;//çUåÇãñâ¬

	bool m_alive;
	int m_hp;

	bool m_defeat;
	int m_defeatCnt;
	float m_alpha;


	bool m_warning;
	bool m_start;

	bool m_hit = {};
	int m_cnt = 0;

	int m_warningCnt = 0;
	bool m_wait = false;


	bool m_rush;
	int m_rushAtkTime = 0;
	int m_rushCnt;
	bool m_danger = false;
	int m_dangerCnt = 0;
	bool m_nowRush = false;

	KdTexture m_dangerTex;
	Math::Matrix m_dangerMat;
	float m_dangerAlpha;
	float m_addDanger;

};