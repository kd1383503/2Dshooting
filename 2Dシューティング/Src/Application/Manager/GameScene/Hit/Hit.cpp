#include "Hit.h"

#include "../GameScene.h"

#include "../Chara/Player/Player.h"//©‹@
#include "../Chara/Player/PlayerBullet/PlayerBullet.h"//©‹@‚Ì’e
#include "../Chara/Enemy/BasicEnemy/BasicEnemy.h"//G‹›“G
#include "../Explosion/Explosion.h"//”š”­


void C_Hit::Update()
{
	PlayerBulletToEnemy();
	PlayerEnemy();
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
			// ’e‚Æ“G‚Ì‹——£‚ğŒvZ‚·‚é
			float x = pb->GetPos(i).x - be->GetPos(j).x;
			float y = pb->GetPos(i).y - be->GetPos(j).y;
			float distance = sqrtf(x * x + y * y);

			// “–‚½‚è”»’è‚Ì”¼Œa‚ÍA’e‚Ì”¼Œa‚Æ“G‚Ì”¼Œa‚Ì‡Œv‚Æ‚·‚é
			if (distance < pb->GetRadius() + be->GetRadius())
			{
				//”š”­ˆ—
				ex->SetEx(pb->GetPos(i), ex->m_exSize::pb);
				
				// “–‚½‚è”»’è‚ª¬—§‚µ‚½ê‡‚Ìˆ—
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
