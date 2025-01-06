#include "stdafx.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "PlayerBody.h"

CObjMgr*	CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

CObj* CObjMgr::Get_Target(OBJID eID, CObj* pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj* pTarget = nullptr;

	float	fDistance = 0.f;

	for (auto& iter : m_ObjList[eID])
	{
		if(iter->Get_Dead())
			continue;

		float	fWidth = fabs(pObj->Get_Info().fX - iter->Get_Info().fX);
		float	fHeight = fabs(pObj->Get_Info().fY - iter->Get_Info().fY);

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if (!pTarget || fDistance > fDiagonal)
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}
	}

	return pTarget;
}

CObj * CObjMgr::Get_Status(OBJID eID, CObj * pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj* pTarget = nullptr;

	int		iHP = 0;
	float	fATKDMG = 0.f;



	for (auto& iter : m_ObjList[eID])
	{
		if (iter->Get_Dead())
			continue;

		fATKDMG = pObj->Get_ATKDMG();
		iHP = pObj->Get_HP();
		
	}
}

list<CObj*>* CObjMgr::Get_List(OBJID eID)
{

	return &m_ObjList[eID];
}

list<CObj*>& CObjMgr::Get_ListRef(OBJID eID)
{
	return m_ObjList[eID];
}


void CObjMgr::AddObject(OBJID eID, CObj * pObj)
{
	if (nullptr == pObj)
		return;

	m_ObjList[eID].push_back(pObj);
}

int CObjMgr::Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		auto& iter = m_ObjList[i].begin();

		for (; iter != m_ObjList[i].end(); )
		{
			int iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return 0;
}

void CObjMgr::Late_Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Late_Update();

			if (m_ObjList[i].empty())
				break;

			RENDERID	eGroup = iter->Get_RenderID();
			m_RenderSort[eGroup].push_back(iter);
		}
	}

	//CCollisionMgr::Collision_Rect(m_ObjList[OBJ_MOUSE], m_ObjList[OBJ_MONSTER]);
	//monster관련 충돌
	CCollisionMgr::Collsion_Monster(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::Collsion_Monster(m_ObjList[OBJ_ITEM_BULLET], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);// 총알로 만드는 몬스터 히트백
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_ITEM_BULLET]);// 총알로 만드는 몬스터 히트백
	CCollisionMgr::Collsion_Monster(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_FYING_MONSTER]);
	CCollisionMgr::Collsion_Monster(m_ObjList[OBJ_ITEM_BULLET], m_ObjList[OBJ_FYING_MONSTER]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_FYING_MONSTER], m_ObjList[OBJ_BULLET]);// 총알로 만드는 몬스터 히트백
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_FYING_MONSTER], m_ObjList[OBJ_ITEM_BULLET]);// 총알로 만드는 몬스터 히트백
	//CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);//히트백 monster


	//player 충돌 밀처내기 
	//CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]);//b가 밀면 a가 밀림
	//CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_FYING_MONSTER]);//b가 밀면 a가 밀림

	//player 데미지 관련 충돌
	CCollisionMgr::Collsion_Player_Monster(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]);	//player 몬스터 충돌시 플레이어 데미지
	CCollisionMgr::Collsion_Player_Monster(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_FYING_MONSTER]);	//player 몬스터 충돌시 플레이어 데미지
	CCollisionMgr::Collsion_Player(m_ObjList[OBJ_MONSTER_BULLET], m_ObjList[OBJ_PLAYER]);

	//충돌전 항상 처리
	//if (hit == false)
	//{
	//	if (dwCheckTime <= GetTickCount())
	//	{
	//		CCollisionMgr::Collsion_PlayerHit(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]);	//player 몬스터 충돌시 플레이어 데미지
	//		CCollisionMgr::Collsion_PlayerHit(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_FYING_MONSTER]);	//player 몬스터 충돌시 플레이어 데미지
	//		CCollisionMgr::Collsion_Player(m_ObjList[OBJ_MONSTER_BULLET], m_ObjList[OBJ_PLAYER]);
	//		if ((CObjMgr::Get_Instance()->Get_Player()->Get_HP())<(CObjMgr::Get_Instance()->Get_Player()->Get_CheckHP()))
	//		{
	//			CObjMgr::Get_Instance()->Get_Player()->Set_HP(CObjMgr::Get_Instance()->Get_Player()->Get_CheckHP());
	//			hit = true;
	//		}
	//		//dwCheckTime = GetTickCount();
	//	}

	//}
	//if (hit == true)
	//{
	//	if (dwCheckTime <= GetTickCount())
	//		return;
	//	if (dwCheckTime + 2000 <= GetTickCount())
	//	{
	//		dwCheckTime = GetTickCount();
	//		hit = false;
	//	}
	//}



	/*if (dwCheckTime <= GetTickCount())
	{

		CCollisionMgr::Collsion_PlayerHit(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]);	//player 몬스터 충돌시 플레이어 데미지
		CCollisionMgr::Collsion_PlayerHit(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_FYING_MONSTER]);	//player 몬스터 충돌시 플레이어 데미지
		CCollisionMgr::Collsion_Player(m_ObjList[OBJ_MONSTER_BULLET], m_ObjList[OBJ_PLAYER]);
		//player hp 가 체크보다 작으면 실행
		if (CObjMgr::Get_Instance()->Get_Player()->Get_HP()<CObjMgr::Get_Instance()->Get_Player()->Get_CheckHP())
		{
			CObjMgr::Get_Instance()->Get_Player()->Set_HP(CObjMgr::Get_Instance()->Get_Player()->Get_CheckHP());
			dwCheckTime = GetTickCount() - 2000;
		}
	}
	if (dwCheckTime + 2000 <= GetTickCount())
	{
		//return;
	}
	if (dwCheckTime + 4000 <= GetTickCount())
	{
		dwCheckTime = GetTickCount();
	}
	*/
	//2초가 지난 후에 충돌시 데미지가 입음
	//if (dwCheckTime + 2000 <= GetTickCount())
	//{
	//	CCollisionMgr::Collsion_PlayerHit(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]);	//player 몬스터 충돌시 플레이어 데미지
	//	CCollisionMgr::Collsion_PlayerHit(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_FYING_MONSTER]);	//player 몬스터 충돌시 플레이어 데미지
	//	CCollisionMgr::Collsion_Player(m_ObjList[OBJ_MONSTER_BULLET], m_ObjList[OBJ_PLAYER]);
	//	dwCheckTime = GetTickCount();
	//}



	//meterial place	방해물
	CCollisionMgr::Collsion_Meterial(m_ObjList[OBJ_METERIAL], m_ObjList[OBJ_BULLET]);//총알 삭제
	CCollisionMgr::Collsion_Meterial(m_ObjList[OBJ_METERIAL], m_ObjList[OBJ_MONSTER_BULLET]);//총알 삭제
	CCollisionMgr::Collsion_Meterial(m_ObjList[OBJ_METERIAL], m_ObjList[OBJ_ITEM_BULLET]);//총알 삭제		
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_METERIAL]);//b가 밀면 a가 밀림
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_METERIAL]);//b가 밀면 a가 밀림
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_BOMB], m_ObjList[OBJ_METERIAL]);//b가 밀면 a가 밀림
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_METERIAL_MOVE], m_ObjList[OBJ_PLAYER]);//b가 밀면 a가 밀림


	//bomb place
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_BOMB], m_ObjList[OBJ_PLAYER]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_BOMB], m_ObjList[OBJ_BULLET]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_BOMB], m_ObjList[OBJ_ITEM_BULLET]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_BOMB], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_BOMB], m_ObjList[OBJ_FYING_MONSTER]);

	//explosion
	CCollisionMgr::Collsion_Meterial(m_ObjList[OBJ_EXPLOSION], m_ObjList[OBJ_METERIAL]); //폭발이 바위 삭제
	CCollisionMgr::Collsion_Player_Monster(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_EXPLOSION]);
	CCollisionMgr::Collsion_Explosoin(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_EXPLOSION]);
	CCollisionMgr::Collsion_Explosoin(m_ObjList[OBJ_FYING_MONSTER], m_ObjList[OBJ_EXPLOSION]);

	// wall
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_BOMB], m_ObjList[OBJ_WALL]);//b가 밀면 a가 밀림
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_WALL]);//b가 밀면 a가 밀림
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_WALL]);//b가 밀면 a가 밀림
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_FYING_MONSTER], m_ObjList[OBJ_WALL]);//b가 밀면 a가 밀림
	CCollisionMgr::Collsion_Meterial(m_ObjList[OBJ_WALL], m_ObjList[OBJ_BULLET]);//총알 삭제
	CCollisionMgr::Collsion_Meterial(m_ObjList[OBJ_WALL], m_ObjList[OBJ_MONSTER_BULLET]);//총알 삭제		
	CCollisionMgr::Collsion_Meterial(m_ObjList[OBJ_WALL], m_ObjList[OBJ_ITEM_BULLET]);//총알 삭제

	// item
	CCollisionMgr::Collsion_Meterial(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_ITEM]);//아이템 삭제		
	CCollisionMgr::Collsion_Meterial(m_ObjList[OBJ_SHIELD], m_ObjList[OBJ_MONSTER_BULLET]);//총알 삭제		


	//	door


}

template<typename T>
bool		CompareY(T Dest, T Sour)
{
	return Dest->Get_Info().fY < Sour->Get_Info().fY;
}

void CObjMgr::Render(HDC hDC)
{
	/*for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(hDC);
	}*/

	for (int i = 0; i < RENDER_END; ++i)
	{
		m_RenderSort[i].sort(CompareY<CObj*>);
		
		for (auto& iter : m_RenderSort[i])
			iter->Render(hDC);

		m_RenderSort[i].clear();
	}


}

void CObjMgr::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), CDeleteObj());
		m_ObjList[i].clear();
	}
}

void CObjMgr::Delete_ID(OBJID eID)
{
	for (auto& iter : m_ObjList[eID])
		Safe_Delete(iter);

	m_ObjList[eID].clear();
}
