#include "Hit.h"

#include "../GameScene.h"

#include "../Chara/Player/Player.h"//é©ã@
#include "../Chara/Player/PlayerBullet/PlayerBullet.h"//é©ã@ÇÃíe
#include "../Chara/Enemy/BasicEnemy/BasicEnemy.h"//éGãõìG
#include "../Explosion/Explosion.h"//îöî≠
#include "../Chara/Enemy/MidEnemy/MidEnemy.h"//ìGÇQ
#include "../Chara/Enemy/MidEnemy/MidBullet/MidBullet.h"//ìGÇQíe


void C_Hit::Update()
{
	PlayerBulletToEnemy();
	PlayerEnemy();
	PlayerBulletToMidEnemy();
	StrBulletToPlayer();
	CloBulletToPlayer();
	PlayerMidEnemy();
}

void C_Hit::PlayerBulletToEnemy()
{

	C_PlayerBullet* pb = m_gameScene->GetPlayerBullet();
	C_BasicEnemy* be = m_gameScene->GetBasicEnemy();
	C_Explosion* ex = m_gameScene->GetExplosion();

	for(int i = 0;i <pb->GetBuNum(); i++)
	{
		if (!pb->GetAlive(i)) continue;
		for (int j = 0; j < be->GetEnemyNum(); j++)
		{
			if (!be->GetAlive(j)) continue;
			// íeÇ∆ìGÇÃãóó£ÇåvéZÇ∑ÇÈ
			float x = pb->GetPos(i).x - be->GetPos(j).x;
			float y = (pb->GetPos(i).y + 14) - be->GetPos(j).y;
			float distance = sqrtf(x * x + y * y);

			// ìñÇΩÇËîªíËÇÃîºåaÇÕÅAíeÇÃîºåaÇ∆ìGÇÃîºåaÇÃçáåvÇ∆Ç∑ÇÈ
			if (distance < pb->GetRadius() + be->GetRadius())
			{
				//îöî≠èàóù
				ex->SetEx(pb->GetPos(i), ex->m_exSize::pb);
				
				// ìñÇΩÇËîªíËÇ™ê¨óßÇµÇΩèÍçáÇÃèàóù
				pb->SetAlive(i, false);
				be->SetDamage(j, pb->GetDamage());
				break;
			}
		}
	}


}

void C_Hit::PlayerEnemy()
{

	C_Player* pl = m_gameScene->GetPlayer();
	C_BasicEnemy* pb = m_gameScene->GetBasicEnemy();

	for (int i = 0; i < pb->GetEnemyNum(); i++)
	{
		if (!pb->GetAlive(i))continue;

		float x = pl->GetPos().x - pb->GetPos(i).x;
		float y = pl->GetPos().y - pb->GetPos(i).y;
		float distance = sqrt(x * x + y * y);

		if (distance < pl->GetRadius() + pb->GetRadius())
		{
			pl->SetAlive(false);
			pb->SetAlive(i, false);
			break;
		}

	}

}

void C_Hit::PlayerBulletToMidEnemy()
{

	C_PlayerBullet* pb = m_gameScene->GetPlayerBullet();
	C_MidEnemy* me = m_gameScene->GetMidEnemy();
	C_Explosion* ex = m_gameScene->GetExplosion();

	float top = me->GetPos().y + me->GetRad().y;
	float bottom = me->GetPos().y - me->GetRad().y;
	float right = me->GetPos().x + me->GetRad().x;
	float left = me->GetPos().x - me->GetRad().x;

	if (!me->GetAlive())return;

	for (int i = 0; i < pb->GetBuNum(); i++)
	{
		if (!pb->GetAlive(i))continue;

		Math::Vector2 c = { pb->GetPos(i).x ,pb->GetPos(i).y + 14 };

		float clX = clamp(c.x, left, right);
		float clY = clamp(c.y, bottom, top);

		float dx = c.x - clX;
		float dy = c.y - clY;
		float distance = (dx * dx + dy * dy);
		if ( distance <= pb->GetRadius() * pb->GetRadius()) 
		{
			// ìñÇΩÇË
			//îöî≠èàóù
			ex->SetEx(pb->GetPos(i), ex->m_exSize::pb);

			// ìñÇΩÇËîªíËÇ™ê¨óßÇµÇΩèÍçáÇÃèàóù
			pb->SetAlive(i, false);
			me->SetDamage(pb->GetDamage());
			break;

		}

	}


}

void C_Hit::StrBulletToPlayer()
{

	C_Player* pl = m_gameScene->GetPlayer();
	C_MidBullet* mb = m_gameScene->GetMidBullet();
	C_Explosion* ex = m_gameScene->GetExplosion();

	for (int i = 0; i < mb->GetNum(); i++)
	{
		if (!mb->GetAlive(i))continue;
		if (mb->GetType(i) != mb->bulletType::straight)continue;

		float x = pl->GetPos().x - mb->GetPos(i).x;
		float y = pl->GetPos().y - mb->GetPos(i).y;
		float distance = sqrt(x * x + y * y);

		if (distance < pl->GetRadius() + ((mb->GetRad(mb->bulletRad::straightx) - 6) * mb->bulletSize::straightX))
		{
			//îöî≠èàóù
			ex->SetEx(mb->GetPos(i), ex->m_exSize::mb);

			// ìñÇΩÇËîªíËÇ™ê¨óßÇµÇΩèÍçáÇÃèàóù
			mb->SetAlive(i, false);
			pl->SetDamage(mb->bulletDamage::str);
			break;
		}

	}

}

void C_Hit::CloBulletToPlayer()
{

	C_Player* pl = m_gameScene->GetPlayer();
	C_MidBullet* mb = m_gameScene->GetMidBullet();
	C_Explosion* ex = m_gameScene->GetExplosion();

	for (int i = 0; i < mb->GetNum(); i++)
	{
		if (!mb->GetAlive(i))continue;
		if (mb->GetType(i) != mb->bulletType::cloth)continue;

		float x = pl->GetPos().x - mb->GetPos(i).x;
		float y = pl->GetPos().y - mb->GetPos(i).y;
		float distance = sqrt(x * x + y * y);

		if (distance < pl->GetRadius() + ((mb->GetRad(mb->bulletRad::clothx) - 6) * mb->bulletSize::clothX))
		{
			//îöî≠èàóù
			ex->SetEx(mb->GetPos(i), ex->m_exSize::mb);

			// ìñÇΩÇËîªíËÇ™ê¨óßÇµÇΩèÍçáÇÃèàóù
			mb->SetAlive(i, false);
			pl->SetDamage(mb->bulletDamage::clo);
			break;
		}
	}
}

void C_Hit::PlayerMidEnemy()
{
	
	C_Player* pl = m_gameScene->GetPlayer();
	C_MidEnemy* me = m_gameScene->GetMidEnemy();
	C_Explosion* ex = m_gameScene->GetExplosion();

	float top = me->GetPos().y + me->GetRad().y;
	float bottom = me->GetPos().y - me->GetRad().y;
	float right = me->GetPos().x + me->GetRad().x;
	float left = me->GetPos().x - me->GetRad().x;

	if (!me->GetAlive())return;

	Math::Vector2 c = { pl->GetPos().x ,pl->GetPos().y};

	float clX = clamp(c.x, left, right);
	float clY = clamp(c.y, bottom, top);

	float dx = c.x - clX;
	float dy = c.y - clY;
	float distance = (dx * dx + dy * dy);
	if (distance <= pl->GetRadius() * pl->GetRadius())
	{
		// ìñÇΩÇË
		//îöî≠èàóù
		ex->SetEx(pl->GetPos(), ex->m_exSize::pl);

		// ìñÇΩÇËîªíËÇ™ê¨óßÇµÇΩèÍçáÇÃèàóù
		pl->SetAlive(false);

	}

}



float C_Hit::clamp(float v, float minV, float maxV)
{
	if (v < minV) return minV;
	if (v > maxV) return maxV;
	return v;
}
