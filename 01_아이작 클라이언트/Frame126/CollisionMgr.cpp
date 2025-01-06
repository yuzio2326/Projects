#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
			{
				Dest->Set_Dead();
				Sour->Set_Dead();
			}
		}
	}

}

void CCollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			float	fX = 0.f, fY = 0.f;

			if (Check_Rect(Dest, Sour, &fX, &fY))
			{
				if (fX > fY)	// 상하 충돌의 경우
				{
					// 상 충돌
					if (Dest->Get_Info().fY < Sour->Get_Info().fY)
					{
						Dest->Set_PosY(-fY);
					}
					else // 하 충돌
					{
						Dest->Set_PosY(fY);
					}
				}
				else			// 좌우 충돌의 경우
				{
					// 상 충돌
					if (Dest->Get_Info().fX < Sour->Get_Info().fX)
					{
						Dest->Set_PosX(-fX);
					}
					else // 하 충돌
					{
						Dest->Set_PosX(fX);
					}
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{
				Dest->Set_Dead();
				Sour->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collsion_Monster(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{
				Dest->Set_Dead();
				int DMG = Dest->Get_ATKDMG();
				Sour->Set_HP(-(DMG));
			}
		}
	}
}

void CCollisionMgr::Collsion_Boss(list<CObj*> _Dest, list<CObj*> _Sour)
{
}

void CCollisionMgr::Collsion_Player_Monster(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{
				
				float	fWidth = Sour->Get_Info().fX - Dest->Get_Info().fX;
				float	fHeight = Sour->Get_Info().fY - Dest->Get_Info().fY;

				float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

				float m_fAngle = acosf(fWidth / fDiagonal);


				if (Dest->Get_Info().fY < Sour->Get_Info().fY)
					m_fAngle *= -1.f;

				Dest->Set_PosX(-cosf(m_fAngle) * 50.f);
				Dest->Set_PosY(sinf(m_fAngle ) * 50.f);

				Dest->Set_HP(-2);
				

			}
		}
	}
}

void CCollisionMgr::Collsion_Meterial(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{
				Sour->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collsion_Explosoin(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{

				float	fWidth = Sour->Get_Info().fX - Dest->Get_Info().fX;
				float	fHeight = Sour->Get_Info().fY - Dest->Get_Info().fY;

				float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

				float m_fAngle = acosf(fWidth / fDiagonal);


				if (Dest->Get_Info().fY < Sour->Get_Info().fY)
					m_fAngle *= -1.f;

				Dest->Set_PosX(-cosf(m_fAngle) * 50.f);
				Dest->Set_PosY(sinf(m_fAngle) * 50.f);

				Dest->Set_HP(-15);

			}
		}
	}
}

void CCollisionMgr::Collsion_Player(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{
				//float	fWidth = Sour->Get_Info().fX - Dest->Get_Info().fX;
				//float	fHeight = Sour->Get_Info().fY - Dest->Get_Info().fY;

				//float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

				//float m_fAngle = acosf(fWidth / fDiagonal);


				//if (Dest->Get_Info().fY < Sour->Get_Info().fY)
				//	m_fAngle *= -1.f;

				//Dest->Set_PosX(-cosf(m_fAngle) * 50.f);
				//Dest->Set_PosY(sinf(m_fAngle) * 50.f);


				Dest->Set_Dead();
 				Sour->Set_HP(-2);
			}
		}
	}
}

void CCollisionMgr::Collsion_PlayerHit(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{
				Dest->Set_HP(-2);
				Dest->Set_Check_Hit(true);
			}
		}
	}
}

void CCollisionMgr::Collision_HitArmor(list<CObj*> _Dest )
{
	for (auto& Dest : _Dest)
	{
		Dest->Get_HP();
		

	}

}

bool CCollisionMgr::Check_Sphere(CObj* pDest, CObj* pSour)
{
	float		fWidth = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);		// abs 는 절대 값을 구해주는 함수
	float		fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);
	
	float		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);			// 루트를 씌워 값을 구해주는 함수

	//float		fRadius = pDest->Get_Info().fCX / 2.f + pSour->Get_Info().fCX / 2.f;

	float		fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;


	return fRadius >= fDiagonal;
}

bool CCollisionMgr::Check_Rect(CObj* pDest, CObj* pSour, float* _fX, float* _fY)
{
	float		fWidth = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float		fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	float		fCX = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;
	float		fCY = (pDest->Get_Info().fCY + pSour->Get_Info().fCY) * 0.5f;

	if ((fCX > fWidth) && (fCY > fHeight))
	{
		*_fX = fCX - fWidth;
		*_fY = fCY - fHeight;

		return true;
	}

	return false;
}



/*
// player 데미지 처리
for (auto& Player : m_ObjList[OBJ_PLAYER])
{
for (auto& MobBullet : m_ObjList[OBJ_MONSTER_BULLET])
{
if (CCollisionMgr::Check_Sphere(Player, MobBullet))
{
MobBullet->Set_Dead();
Player->Set_HP(-1);
}
}

for (auto& Monster : m_ObjList[OBJ_MONSTER])
{
if (CCollisionMgr::Check_Sphere(Player, Monster))
{
Player->Set_HP(-1);
}
}

for (auto& Item : m_ObjList[OBJ_ITEM])
{
if (CCollisionMgr::Check_Rect(Item, Player, nullptr, nullptr))
{
Item->Set_Dead();
}
}
//add bomb
}

//monster 데미지 처리
for (auto& Monster : m_ObjList[OBJ_MONSTER])
{
for (auto& Bullet : m_ObjList[OBJ_BULLET])
{
if (CCollisionMgr::Check_Sphere(Monster, Bullet))
{

Bullet->Set_Dead();
Monster->Set_HP(-1);
}
}

//폭탄 추가


}

*/
