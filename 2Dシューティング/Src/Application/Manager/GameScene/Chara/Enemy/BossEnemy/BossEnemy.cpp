#include "BossEnemy.h"

#include "../../../../SceneManager.h"
#include "../../../GameScene.h"
#include "../MidEnemy/MidEnemy.h"
#include "../../Player/Player.h"
#include "BossBullet/BossBullet.h"
#include "BossLaser/BossLaser.h"
#include "../../../Explosion/Explosion.h"

void C_BossEnemy::Draw()
{

	if (!m_alive) return;
	//右腕
	SHADER.m_spriteShader.SetMatrix(m_rightArmMat);
	SHADER.m_spriteShader.DrawTex(&m_rightArmTex,Math::Rectangle(0, 0, 130, 393), m_alpha);

	//左腕
	SHADER.m_spriteShader.SetMatrix(m_leftArmMat);
	SHADER.m_spriteShader.DrawTex(&m_leftArmTex,Math::Rectangle(0, 0, 130, 393), m_alpha);

	//ボディー
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 800, 353), m_alpha);

}

void C_BossEnemy::Action()
{

	//出現
	if(!m_alive)
	{
		C_MidEnemy* me = m_gameScene->GetMidEnemy();
		if (me->GetKill() >= 1)
		{
			m_alive = true;
			//初期化
			m_pos = { 0,360 + 180 };
			m_move = { 0,-5 };
			m_hp = 10;
			m_atk = false;

			m_rPos = { m_pos.x + 280 ,m_pos.y - 60 };
			m_lPos = { m_pos.x - 280 ,m_pos.y - 60 };
		}
	}

	if (!m_alive) return;

	if (!m_atk)
	{
		//出現処理
		m_move.y = -5;

	}
	else
	{
		//メイン
		//腕の回転制御
		m_targetAngleR = RightArmAngle();
		m_targetAngleL = LeftArmAngle();

		// ② targetAngleR が可動範囲外なら追従しない
		if (m_targetAngleR < m_rArmMin || m_targetAngleR > m_rArmMax)
		{

		}
		else
		{

			// ③ 差分
			float diffR = m_targetAngleR - m_rightArmAngle;

			// ④ -π〜+π に正規化
			while (diffR > DirectX::XM_PI) diffR -= DirectX::XM_2PI;
			while (diffR < -DirectX::XM_PI) diffR += DirectX::XM_2PI;

			// ⑤ 少しずつ寄せる
			m_rightArmAngle += diffR * 3 * 0.016;


		}
		// ② targetAngleL が可動範囲外なら追従しない
		if (m_targetAngleL < m_lArmMin || m_targetAngleL > m_lArmMax)
		{

		}
		else
		{

			// ③ 差分
			float diffL = m_targetAngleL - m_leftArmAngle;

			// ④ -π〜+π に正規化
			while (diffL > DirectX::XM_PI) diffL -= DirectX::XM_2PI;
			while (diffL < -DirectX::XM_PI) diffL += DirectX::XM_2PI;

			// ⑤ 少しずつ寄せる
			m_leftArmAngle += diffL * 3 * 0.016;


		}
		//腕の回転幅
		m_rightArmAngle = Clamp(m_rightArmAngle, m_rArmMin, m_rArmMax);
		m_leftArmAngle = Clamp(m_leftArmAngle, m_lArmMin, m_lArmMax);
		//↑腕の回転制御

		//弾発射制御
		if (m_buAtkTime <= 0)//0なったら弾発射
		{
			C_BossBullet* bb = m_gameScene->GetBossBullet();
			
			
			//右腕
			Math::Vector2 pos = m_rPos + Rotate({0, -150}, m_rightArmAngle);
			float angle = m_rightArmAngle - DirectX::XM_PIDIV2;
			Math::Vector2 move = { cos(angle) * 5, sin(angle) * 5};

			for(int i = 0; i < bb->GetNum(); i++)
			{
				if (bb->GetAlive(i))continue;
				bb->SetBullet(i, pos, move,m_rightArmAngle);
				break;
			}
			//左腕
			pos = m_lPos + Rotate({0, -150}, m_leftArmAngle) ;
			angle = m_leftArmAngle - DirectX::XM_PIDIV2;
			move = { cos(angle) * 5, sin(angle) * 5};

			for(int i = 0; i < bb->GetNum(); i++)
			{
				if (bb->GetAlive(i))continue;
				bb->SetBullet(i, pos, move, m_leftArmAngle);
				break;
			}

			m_buAtkTime = 30;
		}

		m_buAtkTime--;


		//laser
		
		if (m_laserAtkTime <= 0)
		{

			C_BossLaser* bl = m_gameScene->GetLaser();
			Math::Vector2 pos;
			pos.x = m_pos.x;
			pos.y = m_laserPosY;
			bl->SetLaser(pos, GetBossPlayerAngle());

			m_laserAtkTime = 200;
		}

		m_laserAtkTime--;
	}


}

void C_BossEnemy::Update()
{

	if (!m_alive) return;

	m_pos += m_move;
	m_rPos += m_move;
	m_lPos += m_move;
	m_laserPosY = m_pos.y - 150;

	if (m_pos.y < 240)
	{
		m_atk = true;
		m_buAtkTime = 10;
		m_laserAtkTime = 200;
		m_pos.y = 240;
		m_move.y = 0;
	}


	
	if (m_hp <= 0 && !m_defeat)
	{

		m_defeat = true;
		m_defeatCnt = 120;

		C_Explosion* ex = m_gameScene->GetExplosion();



		ex->SetEx(m_pos, ex->m_exSize::bs);
		ex->SetEx({ m_pos.x + 200,m_pos.y + 100 }, ex->m_exSize::bs);
		ex->SetEx({ m_pos.x + 200,m_pos.y - 100 }, ex->m_exSize::bs);
		ex->SetEx({ m_pos.x - 200,m_pos.y + 100 }, ex->m_exSize::bs);
		ex->SetEx({ m_pos.x - 200,m_pos.y - 100 }, ex->m_exSize::bs);

	}
	if (m_defeat)
	{
		if (m_defeatCnt <= 60)
		{
			C_Explosion* ex = m_gameScene->GetExplosion();

			ex->SetEx(m_pos, ex->m_exSize::bs);
			ex->SetEx({ m_pos.x + 200,m_pos.y + 100 }, ex->m_exSize::bs);
			ex->SetEx({ m_pos.x + 200,m_pos.y - 100 }, ex->m_exSize::bs);
			ex->SetEx({ m_pos.x - 200,m_pos.y + 100 }, ex->m_exSize::bs);
			ex->SetEx({ m_pos.x - 200,m_pos.y - 100 }, ex->m_exSize::bs);
		}


		if (m_defeatCnt <= 0)
		{
			m_alive = false;
		}

		m_alpha *= 0.95;
		m_defeatCnt--;
	}


}

void C_BossEnemy::MatUpdate()
{

	Math::Matrix scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = scale * trans;

	Math::Matrix rotate = Math::Matrix::CreateRotationZ(m_rightArmAngle);
	scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	trans = Math::Matrix::CreateTranslation(m_rPos.x, m_lPos.y, 0);
	m_rightArmMat = scale * rotate * trans;

	rotate = Math::Matrix::CreateRotationZ(m_leftArmAngle);
	scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	trans = Math::Matrix::CreateTranslation(m_lPos.x, m_lPos.y, 0);
	m_leftArmMat = scale * rotate * trans;

}

void C_BossEnemy::Init()
{

	m_tex.Load("Asset/texture/GameScene/Chara/Enemy/BossBody.png");
	m_rightArmTex.Load("Asset/texture/GameScene/Chara/Enemy/rightArm.png");
	m_leftArmTex.Load("Asset/texture/GameScene/Chara/Enemy/leftArm.png");

	m_pos = {};
	m_move = {};
	m_alive = false;
	m_hp = 1000;

	m_rPos = {};
	m_lPos = {};
	m_laserPosY = 0;

	m_rightArmAngle = DirectX::XMConvertToRadians(0);
	m_leftArmAngle = DirectX::XMConvertToRadians(0);

	m_defeat = false;
	m_defeatCnt = 120;
	m_alpha = 1.0f;
}

void C_BossEnemy::Release()
{
	
	m_tex.Release();
	m_rightArmTex.Release();
	m_leftArmTex.Release();

}

float C_BossEnemy::RightArmAngle()
{
	float rangle = 0;

	C_Player* pl = m_gameScene->GetPlayer();

	rangle = atan2((pl->GetPos().y) - (m_rPos.y), (pl->GetPos().x) - (m_rPos.x));
	rangle += DirectX::XMConvertToRadians(90);

	return rangle;
}

float C_BossEnemy::LeftArmAngle()
{
	float langle = 0;

	C_Player* pl = m_gameScene->GetPlayer();

	langle = atan2((pl->GetPos().y) - (m_lPos.y), (pl->GetPos().x) - (m_lPos.x));
	langle += DirectX::XMConvertToRadians(90);


	return langle;
}

float C_BossEnemy::Clamp(float v, float minV, float maxV)
{

	if (v < minV) return minV;
	if (v > maxV) return maxV;
	return v;
}

Math::Vector2 C_BossEnemy::Rotate(Math::Vector2 v, float angle)
{
	Math::Vector2 rotate = {};
	
	float c = cos(angle);
	float s = sin(angle);

	rotate.x = v.x * c - v.y * s;
	rotate.y = v.x * s + v.y * c;

	return rotate;
}

float C_BossEnemy::GetBossPlayerAngle()
{

	float angle;

	C_Player* pl = m_gameScene->GetPlayer();

	angle = atan2((pl->GetPos().y) - (m_laserPosY), (pl->GetPos().x) - (m_pos.x));
	//補正
	angle += DirectX::XMConvertToRadians(90);
		

	return angle;
}
