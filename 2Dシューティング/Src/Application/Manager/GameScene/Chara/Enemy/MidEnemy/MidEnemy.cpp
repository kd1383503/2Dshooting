#include "MidEnemy.h"
#include "../../../GameScene.h"
#include "../BasicEnemy/BasicEnemy.h"
#include "MidBullet/MidBullet.h"
#include "../../../Explosion/Explosion.h"
#include "../BossEnemy/BossEnemy.h"

void C_MidEnemy::Draw()
{

	
	if (!m_alive)return;
	Math::Color col = {};
	if (m_hit)
	{
		col = { 1,0,0,1.0f };
		m_cnt--;
		if (m_cnt <= 0) m_hit = false;
	}
	else
	{
		col = { 1,1,1,1.0f };
	}

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 400, 200), &col);

	
	SHADER.m_spriteShader.SetMatrix(m_enMat);
	SHADER.m_spriteShader.DrawTex(&m_enTex, Math::Rectangle((int)m_anim * 48, 0, 48, 48), 1.0f);

	
	SHADER.m_spriteShader.SetMatrix(m_enMat2);
	SHADER.m_spriteShader.DrawTex(&m_enTex, Math::Rectangle((int)m_anim * 48, 0, 48, 48), 1.0f);

	

}

void C_MidEnemy::Action()
{

	C_BasicEnemy* be = m_gameScene->GetBasicEnemy();
	C_BossEnemy* bs = m_gameScene->GetBoss();

	if (!bs->GetAlive() && be->GetKill() >= 10)//もしキルカウントが条件数を満たしたら
	{

		if (!m_alive)
		{

			m_alive = true;
			m_hp = m_enemyHp::mid;
			m_pos = { (float)Rand(600, 300) ,860 };
			m_move = { 0,0 };
			m_strWait = 30;
			m_clothWait = 60;
			m_chargeWait = 120;
			m_atk = false;
		}

	}

	if (!m_alive)return;
	if (!m_atk)
	{
		m_move.y = -5;
	}
	else
	{

		if (m_shake <= 0)
		{

			if (m_pos.x < -150)
			{
				if (Rand(100, 0) % 3 != 0)
				{
					m_move.x = 1;
				}
				else
				{
					m_move.x = -1;
				}
			}
			else if (m_pos.x > 150)
			{
				if (Rand(100, 0) % 2 != 0)
				{
					m_move.x = -1;
				}
				else
				{
					m_move.x = 1;
				}
			}
			else
			{
				if (Rand(100, 0) % 2 != 0)
				{
					m_move.x = 1;
				}
				else
				{
					m_move.x = -1;
				}
			}
			

			m_shake = Rand(60, 0) + 90;
		}


		//攻撃系
		C_MidBullet* mb = m_gameScene->GetMidBullet();
		if (m_strWait <= 0)
		{

			for (int i = 0; i < mb->GetNum(); i++)
			{
				if (mb->GetAlive(i))continue;
				
				mb->SetBullet
				(i, mb->bulletType::straight, 
				{ m_pos.x, m_pos.y - 50 }, 
				{ 0,-5 },
				{ mb->bulletSize::straightX, mb->bulletSize::straightY }, 
				{ mb->GetRad(mb->bulletRad::straightx),mb->GetRad(mb->bulletRad::straighty) }, 0);
				
				

				break;
			}


			m_strWait = 30;
		}
		if (m_clothWait <= 0)
		{
			int loop = 2;
			for (int i = 0; i < mb->GetNum(); i++)
			{
				if (mb->GetAlive(i))continue;

				if (loop == 2)
				{
					mb->SetBullet
					(i, mb->bulletType::cloth,
					{ m_pos.x + 30, m_pos.y - 80 },
					{ -5,-5 },
					{ mb->bulletSize::clothX, mb->bulletSize::clothY },
					{ mb->GetRad(mb->bulletRad::clothx),mb->GetRad(mb->bulletRad::clothy) }, -45);
					
					loop--;
					continue;
				}
				

				if (loop == 1)
				{
					mb->SetBullet
					(i, mb->bulletType::cloth,
					{ m_pos.x - 30, m_pos.y - 80 },
					{ 5,-5 },
					{ mb->bulletSize::clothX, mb->bulletSize::clothY },
					{ mb->GetRad(mb->bulletRad::clothx),mb->GetRad(mb->bulletRad::clothy) }, 45);

					loop--;
				}


				if (loop > 0)continue;
				break;
			}

			m_clothWait = 60;
		}
		if (m_chargeWait <= 0)
		{

			for (int i = 0; i < mb->GetNum(); i++)
			{
				if (mb->GetAlive(i))continue;



				break;
			}

			m_chargeWait = 120;
		}




		//攻撃カウンタ
		m_strWait--;
		m_clothWait--;
		//m_chargeWait--;

		//揺れカウンタ
		m_shake--;
	}
	
	

}

void C_MidEnemy::Update()
{

	if (!m_alive)return;

	m_pos += m_move;


	if (m_pos.y <= 240)
	{
		m_pos.y = 240;
		m_move.y = 0.0f;
		m_atk = true;
	}

	if (m_pos.x > 440) m_pos.x = 440;
	if (m_pos.x < -440) m_pos.x = -440;

	m_anim += 0.1f;
	if (m_anim >= 3.0f)m_anim = 0.0f;

	C_BasicEnemy* be = m_gameScene->GetBasicEnemy();

	if (m_hp <= 0)
	{
		m_alive = false;
		be->SetKill(0);
		C_Explosion* ex = m_gameScene->GetExplosion();

		m_kill++;

		//スコアセット
		m_gameScene->SetScore(3000);

		ex->SetEx(m_pos, ex->m_exSize::me);
		ex->SetEx({m_pos.x + 100,m_pos.y + 50}, ex->m_exSize::me);
		ex->SetEx({m_pos.x + 100,m_pos.y - 50}, ex->m_exSize::me);
		ex->SetEx({m_pos.x - 100,m_pos.y + 50}, ex->m_exSize::me);
		ex->SetEx({m_pos.x - 100,m_pos.y - 50}, ex->m_exSize::me);

	}
	

}

void C_MidEnemy::MatUpdate()
{

	
	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	Math::Matrix scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = scale * trans;

	trans = Math::Matrix::CreateTranslation(m_pos.x + 65, m_pos.y + 103, 0);
	scale = Math::Matrix::CreateScale(m_size.x, -m_size.y, 0);
	m_enMat = scale * trans;

	trans = Math::Matrix::CreateTranslation(m_pos.x - 65, m_pos.y + 103, 0);
	scale = Math::Matrix::CreateScale(m_size.x, -m_size.y, 0);
	m_enMat2 = scale * trans;


}

void C_MidEnemy::Init()
{

	m_tex.Load("Asset/texture/GameScene/Chara/Enemy/midBoss.png");
	m_enTex.Load("Asset/texture/GameScene/Chara/Enemy/engine.png");
	

	m_pos = {};
	m_move = {};
	m_alive = false;
	m_size = { 1,1 };
	m_hp = 100;

	m_anim = 0;

	m_size = { 1,1 };

}

void C_MidEnemy::Release()
{

	m_tex.Release();
	m_enTex.Release();

}
