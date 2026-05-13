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

	Math::Color col = {};
	if (m_hit)
	{
		col = { 1.0f,0,0,m_alpha };
		m_cnt--;
		if (m_cnt <= 0) m_hit = false;
	}
	else
	{
		col = { 1,1,1,m_alpha };
	}

	//右腕
	SHADER.m_spriteShader.SetMatrix(m_rightArmMat);
	SHADER.m_spriteShader.DrawTex(&m_rightArmTex,Math::Rectangle(0, 0, 130, 393), &col);

	//左腕
	SHADER.m_spriteShader.SetMatrix(m_leftArmMat);
	SHADER.m_spriteShader.DrawTex(&m_leftArmTex,Math::Rectangle(0, 0, 130, 393), &col);

	//ボディー
	SHADER.m_spriteShader.SetMatrix(m_enMat);
	SHADER.m_spriteShader.DrawTex(&m_enTex, Math::Rectangle((int)m_anim * 48, 0, 48, 48), &col);
	
	//ボディー
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 800, 353), &col);

	if (m_danger)
	{
		col = { 1,1,1,m_dangerAlpha };
		//ボディー
		SHADER.m_spriteShader.SetMatrix(m_dangerMat);
		SHADER.m_spriteShader.DrawTex(&m_dangerTex, Math::Rectangle(0, 0, 1, 720), &col);
	}


}


void C_BossEnemy::Action()
{

	if (!m_defeat)
	{

		//出現
		if (!m_alive)
		{
			C_MidEnemy* me = m_gameScene->GetMidEnemy();
			if (me->GetKill() >= 2 && !m_warning && !m_start && !m_wait)
			{
				m_warningCnt = 180;
				m_wait = true;
			}

			if(m_wait)
			{
				m_warningCnt--;
				if (m_warningCnt <= 0) m_warning = true;
			}

			if (m_start)
			{
				m_alive = true;
				//初期化
				m_pos = { 0,360 + 300 };
				m_move = { 0,-3 };
				m_hp = 100;
				m_atk = false;

				
			}
		}

		if (!m_alive) return;

		if (!m_atk)
		{
			//出現処理
			m_move.y = -3;

		}
		else
		{
			//メイン
			
			C_Player* pl = m_gameScene->GetPlayer();
			if (m_pos.x > pl->GetPos().x) m_move.x = -1;
			else if (m_pos.x < pl->GetPos().x) m_move.x = 1;
			else m_move.x = 0;
	
			RotateArm();
			BulletATK();
			LaserATK();
			LushATK();

			if(!m_rush)
			{
				m_buAtkTime--;
				m_laserAtkTime--;
				m_rushAtkTime--;
			}

		}
	}
	if (m_hp <= 0)
	{
		m_move = {};
	}

}

void C_BossEnemy::Update()
{

	if (!m_alive) return;

	m_pos += m_move;
	m_rPos = { m_pos.x + 280 ,m_pos.y - 60 };
	m_lPos = { m_pos.x - 280 ,m_pos.y - 60 };
	m_laserPosY = m_pos.y - 150;

	if (m_pos.y < 240 && !m_atk)
	{
		m_atk = true;
		m_buAtkTime = 7;
		m_laserAtkTime = 360;
		m_rushAtkTime = 600;
		m_pos.y = 240;
		m_move.y = 0;
	}

	if (m_pos.x >= 300) m_pos.x = 300;
	if (m_pos.x <= -300) m_pos.x = -300;

	
	if (m_rPos.x >= 580) m_rPos.x = 580;
	if (m_rPos.x <= -20) m_rPos.x = -20;

	
	if (m_lPos.x >= 20) m_lPos.x = 20;
	if (m_lPos.x <= -580) m_lPos.x = -580;

	m_anim += 0.1f;
	if (m_anim >= 3.0f) m_anim = 0.0f;

	if (m_hp <= 0 && !m_defeat)
	{

		m_defeat = true;
		m_defeatCnt = 120;

		C_Explosion* ex = m_gameScene->GetExplosion();

		//スコアセット
		m_gameScene->SetScore(100000);

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

	trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y + 125, 0);
	scale = Math::Matrix::CreateScale(m_size.x * 2, -m_size.y * 2, 0);
	m_enMat = scale * trans;

	trans = Math::Matrix::CreateTranslation(m_pos.x, 0, 0);
	scale = Math::Matrix::CreateScale(660, 1, 0);
	m_dangerMat = scale * trans;

}

void C_BossEnemy::Init()
{

	m_tex.Load("Asset/texture/GameScene/Chara/Enemy/BossBody.png");
	m_rightArmTex.Load("Asset/texture/GameScene/Chara/Enemy/rightArm.png");
	m_leftArmTex.Load("Asset/texture/GameScene/Chara/Enemy/leftArm.png");
	m_enTex.Load("Asset/texture/GameScene/Chara/Enemy/engine.png");
	m_dangerTex.Load("Asset/texture/GameScene/warning/danger.png");

	m_anim = 0;

	m_pos = {};
	m_move = {};
	m_alive = false;
	m_hp = 1000;

	m_rPos = {};
	m_lPos = {};
	m_laserPosY = 0;
	m_laserFlg = false;

	m_rightArmAngle = DirectX::XMConvertToRadians(0);
	m_leftArmAngle = DirectX::XMConvertToRadians(0);

	m_defeat = false;
	m_defeatCnt = 120;
	m_alpha = 1.0f;

	m_warning = false;
	m_start = false;

	m_rush = false;
	
	m_dangerAlpha = 0;
	m_addDanger = 0.05f;


}

void C_BossEnemy::Release()
{
	
	m_tex.Release();
	m_rightArmTex.Release();
	m_leftArmTex.Release();
	m_enTex.Release();
	m_dangerTex.Release();

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

void C_BossEnemy::RotateArm()
{
	//腕の回転制御
	m_targetAngleR = RightArmAngle();
	m_targetAngleL = LeftArmAngle();

	if (m_rush)
	{
		m_targetAngleL = DirectX::XMConvertToRadians(0);
		m_targetAngleR = DirectX::XMConvertToRadians(0);
	}

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
}

void C_BossEnemy::BulletATK()
{

	//弾発射制御
	if (m_buAtkTime <= 0)//0なったら弾発射
	{
		C_BossBullet* bb = m_gameScene->GetBossBullet();


		//右腕
		Math::Vector2 pos = m_rPos + Rotate({ 0, -150 }, m_rightArmAngle);
		float angle = m_rightArmAngle - DirectX::XM_PIDIV2;
		Math::Vector2 move = { cos(angle) * 7, sin(angle) * 7 };

		for (int i = 0; i < bb->GetNum(); i++)
		{
			if (bb->GetAlive(i))continue;
			bb->SetBullet(i, pos, move, m_rightArmAngle);
			break;
		}
		//左腕
		pos = m_lPos + Rotate({ 0, -150 }, m_leftArmAngle);
		angle = m_leftArmAngle - DirectX::XM_PIDIV2;
		move = { cos(angle) * 7, sin(angle) * 7 };

		for (int i = 0; i < bb->GetNum(); i++)
		{
			if (bb->GetAlive(i))continue;
			bb->SetBullet(i, pos, move, m_leftArmAngle);
			break;
		}

		m_buAtkTime = 30;
	}

}

void C_BossEnemy::LaserATK()
{

	//laser
	if (m_laserFlg || m_hp <= 0)
	{
		m_move.x = 0;
	}

	if (m_laserAtkTime <= 0 && !m_rush)
	{
		m_laserFlg = true;
		C_BossLaser* bl = m_gameScene->GetLaser();
		Math::Vector2 pos;
		pos.x = m_pos.x;
		pos.y = m_laserPosY;
		bl->SetLaser(pos, GetBossPlayerAngle());
		m_laserAtkTime = 360;
	}


}

void C_BossEnemy::LushATK()
{

	if (m_rushAtkTime <= 0 && !m_laserFlg && !m_rush)
	{
		m_rush = true;
		m_rushCnt = 0;
		m_move.y = 5;

		
	}

	if (m_rush)
	{

		if (m_pos.y >= 800 && !m_danger && !m_nowRush)
		{
			m_danger = true;
			m_dangerCnt = 120;
			m_pos.y = 800;
			m_dangerAlpha = 0.3f;
			m_addDanger = 0.1f;
			
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_int_distribution<int> dist(-300, 300);
			m_pos.x = dist(mt);
		}

		if (m_danger) 
		{

			m_dangerAlpha += m_addDanger;
			if (m_dangerAlpha >= 0.8f)
			{
				m_dangerAlpha = 0.8f;
				m_addDanger = -0.03f;
			}
			if (m_dangerAlpha <= 0.3f)
			{
				m_dangerAlpha = 0.3f;
				m_addDanger = 0.03f;
			}

			if(m_dangerCnt <= 0)//赤で注意終了
			{
				m_danger = false;
				m_dangerCnt = 0;
				m_nowRush = true;
				m_move.y = -20;
			}
		}
		

		if (m_nowRush)//降下中
		{


			if (m_pos.y <= -1000)
			{
				m_pos.y = 1000;
				m_atk = false;
				m_nowRush = false;
				m_rush = false;
			}
		}




		m_dangerCnt--;
		m_move.x = 0;
	}


}
