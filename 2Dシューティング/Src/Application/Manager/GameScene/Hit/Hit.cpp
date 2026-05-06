#include "Hit.h"

#include "../GameScene.h"

#include "../Chara/Player/Player.h"//自機
#include "../Chara/Player/PlayerBullet/PlayerBullet.h"//自機の弾
#include "../Chara/Enemy/BasicEnemy/BasicEnemy.h"//雑魚敵
#include "../Explosion/Explosion.h"//爆発
#include "../Chara/Enemy/MidEnemy/MidEnemy.h"//敵２
#include "../Chara/Enemy/MidEnemy/MidBullet/MidBullet.h"//敵２弾
#include "../Chara/Enemy/BossEnemy/BossEnemy.h"
#include "../Chara/Enemy/BossEnemy/BossBullet/BossBullet.h"
#include "../Chara/Enemy/BossEnemy/BossLaser/BossLaser.h"


void C_Hit::Update()
{
	PlayerBulletToEnemy();
	PlayerEnemy();
	PlayerBulletToMidEnemy();
	StrBulletToPlayer();
	CloBulletToPlayer();
	PlayerMidEnemy();
	PlayerBulletToBossMain();
	PlayerBulletToRightArm();
	PlayerBulletToLeftArm();
	BossBulletToPlayer();
	BossLaserToPlayer();
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
			// 弾と敵の距離を計算する
			float x = pb->GetPos(i).x - be->GetPos(j).x;
			float y = (pb->GetPos(i).y + 14) - be->GetPos(j).y;
			float distance = sqrtf(x * x + y * y);

			// 当たり判定の半径は、弾の半径と敵の半径の合計とする
			if (distance < pb->GetRadius() + be->GetRadius())
			{
				//爆発処理
				ex->SetEx(pb->GetPos(i), ex->m_exSize::pb);
				
				// 当たり判定が成立した場合の処理
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
			// 当たり
			//爆発処理
			ex->SetEx(pb->GetPos(i), ex->m_exSize::pb);

			// 当たり判定が成立した場合の処理
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
			//爆発処理
			ex->SetEx(mb->GetPos(i), ex->m_exSize::mb);

			// 当たり判定が成立した場合の処理
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
			//爆発処理
			ex->SetEx(mb->GetPos(i), ex->m_exSize::mb);

			// 当たり判定が成立した場合の処理
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
		// 当たり
		//爆発処理
		ex->SetEx(pl->GetPos(), ex->m_exSize::pl);

		// 当たり判定が成立した場合の処理
		pl->SetAlive(false);

	}

}

void C_Hit::PlayerBulletToBossMain()
{

	C_PlayerBullet* pb = m_gameScene->GetPlayerBullet();
	C_BossEnemy* bs = m_gameScene->GetBoss();
	C_Explosion* ex = m_gameScene->GetExplosion();

	if (!bs->GetAlive())return;

	float top = bs->GetPos().y + (bs->GetRad().y * bs->GetSize().y);
	float bottom = bs->GetPos().y - (bs->GetRad().y * bs->GetSize().y) + 15;
	float right = bs->GetPos().x + (bs->GetRad().x * bs->GetSize().x);
	float left = bs->GetPos().x - (bs->GetRad().x * bs->GetSize().x);

	for (int i = 0; i < pb->GetBuNum(); i++)
	{
		if (!pb->GetAlive(i))continue;

		Math::Vector2 c = { pb->GetPos(i).x ,pb->GetPos(i).y + 14 };

		float clX = clamp(c.x, left, right);
		float clY = clamp(c.y, bottom, top);

		float dx = c.x - clX;
		float dy = c.y - clY;
		float distance = (dx * dx + dy * dy);
		if (distance <= pb->GetRadius() * pb->GetRadius())
		{
			// 当たり
			//爆発処理
			ex->SetEx(pb->GetPos(i), ex->m_exSize::pb);

			// 当たり判定が成立した場合の処理
			pb->SetAlive(i, false);
			bs->SetDamage(pb->GetDamage());
			break;

		}

	}

}

void C_Hit::PlayerBulletToRightArm()
{

	C_PlayerBullet* pb = m_gameScene->GetPlayerBullet();
	C_BossEnemy* bs = m_gameScene->GetBoss();
	C_Explosion* ex = m_gameScene->GetExplosion();
	

	for (int i = 0; i < pb->GetBuNum(); i++)
	{
		if (!pb->GetAlive(i))continue;
		
		//レーザーの原点を(0,0)にした時のプレイヤーの位置
		Math::Vector2 rel = pb->GetPos(i) - bs->GetPosR();
		float halfW = 80 / 2.0f;
		float halfH = 300 / 2.0f;


		//float cosT = cos(DirectX::XMConvertToRadians(-(m_lastBoss->GetLaserAngle())));
		//float sinT = sin(DirectX::XMConvertToRadians(-(m_lastBoss->GetLaserAngle())));
		float cosT = cos(-(bs->GetRightAngle()));
		float sinT = sin(-(bs->GetRightAngle()));


		//レーザーの回転分を自機の座標に影響させる(回転行列を作成するときの式)
		//localとレーザーの当たり判定はレーザーの回転を無かったことにできる
		//(地面が傾いているので、自分も傾いて視点を合わせるイメージ)
		Math::Vector2 local;
		local.x = rel.x * cosT - rel.y * sinT;
		local.y = rel.x * sinT + rel.y * cosT;

		//もうレーザーの回転は考慮しなくていいので普通に当たり判定
		//レーザーの4頂点(座標は(0,0)で考える)
		float laserRight = halfW;
		float laserLeft = -halfW;
		float laserTop = halfH;
		float laserBottom = -halfH;

		//自機の4頂点(レーザー分の回転を影響させた座標localを使用)
		float myRight = local.x + pb->GetRadius();
		float myLeft = local.x - pb->GetRadius();
		float myTop = local.y + pb->GetRadius();
		float myBottom = local.y - pb->GetRadius();

		if ((myRight > laserLeft) && (myLeft < laserRight) && (myTop > laserBottom) && (myBottom < laserTop))
		{
			
			// 当たり
			//爆発処理
			ex->SetEx(pb->GetPos(i), ex->m_exSize::pb);

			// 当たり判定が成立した場合の処理
			pb->SetAlive(i, false);
			bs->SetDamage(pb->GetDamage());
			break;

		}
	

	}

}

void C_Hit::PlayerBulletToLeftArm()
{

	C_PlayerBullet* pb = m_gameScene->GetPlayerBullet();
	C_BossEnemy* bs = m_gameScene->GetBoss();
	C_Explosion* ex = m_gameScene->GetExplosion();


	for (int i = 0; i < pb->GetBuNum(); i++)
	{
		if (!pb->GetAlive(i))continue;

		//レーザーの原点を(0,0)にした時のプレイヤーの位置
		Math::Vector2 rel = pb->GetPos(i) - bs->GetPosL();
		float halfW = 80 / 2.0f;
		float halfH = 300 / 2.0f;


		//float cosT = cos(DirectX::XMConvertToRadians(-(m_lastBoss->GetLaserAngle())));
		//float sinT = sin(DirectX::XMConvertToRadians(-(m_lastBoss->GetLaserAngle())));
		float cosT = cos(-(bs->GetLeftAngle()));
		float sinT = sin(-(bs->GetLeftAngle()));


		//レーザーの回転分を自機の座標に影響させる(回転行列を作成するときの式)
		//localとレーザーの当たり判定はレーザーの回転を無かったことにできる
		//(地面が傾いているので、自分も傾いて視点を合わせるイメージ)
		Math::Vector2 local;
		local.x = rel.x * cosT - rel.y * sinT;
		local.y = rel.x * sinT + rel.y * cosT;

		//もうレーザーの回転は考慮しなくていいので普通に当たり判定
		//レーザーの4頂点(座標は(0,0)で考える)
		float laserRight = halfW;
		float laserLeft = -halfW;
		float laserTop = halfH;
		float laserBottom = -halfH;

		//自機の4頂点(レーザー分の回転を影響させた座標localを使用)
		float myRight = local.x + pb->GetRadius();
		float myLeft = local.x - pb->GetRadius();
		float myTop = local.y + pb->GetRadius();
		float myBottom = local.y - pb->GetRadius();

		if ((myRight > laserLeft) && (myLeft < laserRight) && (myTop > laserBottom) && (myBottom < laserTop))
		{

			// 当たり
			//爆発処理
			ex->SetEx(pb->GetPos(i), ex->m_exSize::pb);

			// 当たり判定が成立した場合の処理
			pb->SetAlive(i, false);
			bs->SetDamage(pb->GetDamage());
			break;

		}


	}
}

void C_Hit::BossBulletToPlayer()
{

	C_Player* pl = m_gameScene->GetPlayer();
	C_BossBullet* bb = m_gameScene->GetBossBullet();
	C_Explosion* ex = m_gameScene->GetExplosion();

	for (int i = 0; i < bb->GetNum(); i++)
	{
		if (!bb->GetAlive(i))continue;


		float x = pl->GetPos().x - bb->GetPos(i).x;
		float y = pl->GetPos().y - bb->GetPos(i).y;
		float distance = sqrt(x * x + y * y);

		if (distance < pl->GetRadius() + 8)
		{
			//爆発処理
			ex->SetEx(bb->GetPos(i), ex->m_exSize::mb);

			// 当たり判定が成立した場合の処理
			bb->SetAlive(i, false);
			pl->SetDamage(bb->GetDamage());
			break;
		}

	}
}

void C_Hit::BossLaserToPlayer()
{

	C_Player* pl = m_gameScene->GetPlayer();
	C_BossLaser* bl = m_gameScene->GetLaser();
	C_BossEnemy* bs = m_gameScene->GetBoss();
	C_Explosion* ex = m_gameScene->GetExplosion();


	
	if (!bl->GetAlive()) return;
	if (!bl->GetJudge()) return;
	if (bl->GetHit())return;

	//レーザーの原点を(0,0)にした時のプレイヤーの位置
	Math::Vector2 rel = bl->GetPos() - pl->GetPos();
	float halfW = 128 / 2.0f;
	float laserH = 2000;


	//float cosT = cos(DirectX::XMConvertToRadians(-(m_lastBoss->GetLaserAngle())));
	//float sinT = sin(DirectX::XMConvertToRadians(-(m_lastBoss->GetLaserAngle())));
	float cosT = cos(-(bl->GetAngle()));
	float sinT = sin(-(bl->GetAngle()));


	//レーザーの回転分を自機の座標に影響させる(回転行列を作成するときの式)
	//localとレーザーの当たり判定はレーザーの回転を無かったことにできる
	//(地面が傾いているので、自分も傾いて視点を合わせるイメージ)
	Math::Vector2 local;
	local.x = rel.x * cosT - rel.y * sinT;
	local.y = rel.x * sinT + rel.y * cosT;

	//もうレーザーの回転は考慮しなくていいので普通に当たり判定
	//レーザーの4頂点(座標は(0,0)で考える)
	float laserRight = halfW;
	float laserLeft = -halfW;
	float laserTop = laserH;
	float laserBottom = 0;

	//自機の4頂点(レーザー分の回転を影響させた座標localを使用)
	float myRight = local.x + pl->GetRadius();
	float myLeft = local.x - pl->GetRadius();
	float myTop = local.y + pl->GetRadius();
	float myBottom = local.y - pl->GetRadius();

	if ((myRight > laserLeft) && (myLeft < laserRight) && (myTop > laserBottom) && (myBottom < laserTop))
	{

		// 当たり
		//爆発処理
		ex->SetEx(pl->GetPos(), ex->m_exSize::pl);

		// 当たり判定が成立した場合の処理
		pl->SetDamage(bl->GetDamage());
		bl->SetHit(true);

	}


}







float C_Hit::clamp(float v, float minV, float maxV)
{
	if (v < minV) return minV;
	if (v > maxV) return maxV;
	return v;
}
