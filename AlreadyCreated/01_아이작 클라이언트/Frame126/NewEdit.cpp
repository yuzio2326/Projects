#include "stdafx.h"
#include "NewEdit.h"
#include "KeyMgr.h"
#include "TempFunctor.h"
#include "ObjMgr.h"
#include "Obstacle.h";
#include "CObstacle.h";
#include "AbstracyFactory.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "ScrollMgr.h"
#include "BombFly.h"
#include "UFMonster.h"
#include "BossIsaac.h"
#include "Mushroom.h"
#include "BMonster.h"
#include "IObstacle.h";
#include "Flag.h"
#include "Ghost.h"

CNewEdit*		CNewEdit::m_pInstance = nullptr;

CNewEdit::CNewEdit():m_ePro(PRO_LINE),m_pRect(nullptr), m_eMode(EDIT_END)
{
	ZeroMemory(m_tLinePoint, sizeof(LINEPOINT) * 2);
	ZeroMemory(&m_tPoint, sizeof(POINT));
	m_fSpeed = 10.f;
}


CNewEdit::~CNewEdit()
{
	Release();
}

void CNewEdit::Initialize(void)
{
	ZeroMemory(m_tLinePoint, sizeof(LINEPOINT) * 2);
	for (auto& elem : CObjMgr::Get_Instance()->Get_ListRef(OBJ_OBSTACLE))
	{
		Safe_Delete(elem);
	}
	CObjMgr::Get_Instance()->Get_ListRef(OBJ_OBSTACLE).clear();
	list<CObj*>().swap(CObjMgr::Get_Instance()->Get_ListRef(OBJ_OBSTACLE));

	for (auto& elem : CObjMgr::Get_Instance()->Get_ListRef(OBJ_COBSTACLE))
	{
		Safe_Delete(elem);
	}
	CObjMgr::Get_Instance()->Get_ListRef(OBJ_COBSTACLE).clear();
	list<CObj*>().swap(CObjMgr::Get_Instance()->Get_ListRef(OBJ_COBSTACLE));

	// + 占쌩곤옙
	for (auto& elem : CObjMgr::Get_Instance()->Get_ListRef(OBJ_FYING_MONSTER))
	{
		Safe_Delete(elem);
	}
	CObjMgr::Get_Instance()->Get_ListRef(OBJ_FYING_MONSTER).clear();
	list<CObj*>().swap(CObjMgr::Get_Instance()->Get_ListRef(OBJ_FYING_MONSTER));

	for (auto& elem : CObjMgr::Get_Instance()->Get_ListRef(OBJ_UFMONSTER))
	{
		Safe_Delete(elem);
	}
	CObjMgr::Get_Instance()->Get_ListRef(OBJ_UFMONSTER).clear();
	list<CObj*>().swap(CObjMgr::Get_Instance()->Get_ListRef(OBJ_UFMONSTER));

	for (auto& elem : CObjMgr::Get_Instance()->Get_ListRef(OBJ_MUSHROOM))
	{
		Safe_Delete(elem);
	}
	CObjMgr::Get_Instance()->Get_ListRef(OBJ_MUSHROOM).clear();
	list<CObj*>().swap(CObjMgr::Get_Instance()->Get_ListRef(OBJ_MUSHROOM));

	for (auto& elem : CObjMgr::Get_Instance()->Get_ListRef(OBJ_BMONSTER))
	{
		Safe_Delete(elem);
	}
	CObjMgr::Get_Instance()->Get_ListRef(OBJ_BMONSTER).clear();
	list<CObj*>().swap(CObjMgr::Get_Instance()->Get_ListRef(OBJ_BMONSTER));

	for (auto& elem : CObjMgr::Get_Instance()->Get_ListRef(OBJ_IOBSTACLE))
	{
		Safe_Delete(elem);
	}
	CObjMgr::Get_Instance()->Get_ListRef(OBJ_IOBSTACLE).clear();
	list<CObj*>().swap(CObjMgr::Get_Instance()->Get_ListRef(OBJ_IOBSTACLE));

	for (auto& elem : CObjMgr::Get_Instance()->Get_ListRef(OBJ_BOSS))
	{
		Safe_Delete(elem);
	}
	CObjMgr::Get_Instance()->Get_ListRef(OBJ_BOSS).clear();
	list<CObj*>().swap(CObjMgr::Get_Instance()->Get_ListRef(OBJ_BOSS));

	for (auto& elem : CObjMgr::Get_Instance()->Get_ListRef(OBJ_FLAG))
	{
		Safe_Delete(elem);
	}
	CObjMgr::Get_Instance()->Get_ListRef(OBJ_FLAG).clear();
	list<CObj*>().swap(CObjMgr::Get_Instance()->Get_ListRef(OBJ_FLAG));

	for (auto& elem : CObjMgr::Get_Instance()->Get_ListRef(OBJ_GHOST))
	{
		Safe_Delete(elem);
	}
	CObjMgr::Get_Instance()->Get_ListRef(OBJ_GHOST).clear();
	list<CObj*>().swap(CObjMgr::Get_Instance()->Get_ListRef(OBJ_GHOST));
}

void CNewEdit::ProcessLine()
{
	POINT	pt{};

	float mfX = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fX;
	float mfY = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fY;
	mfX -= CScrollMgr::Get_Instance()->Get_ScrollX();
	mfY -= CScrollMgr::Get_Instance()->Get_ScrollY();

	m_pLine = nullptr;

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
			if (!m_bPress)
			{
				m_tLinePoint[0].fX = mfX;
				m_tLinePoint[0].fY = mfY;
				m_bPress = true;
			}
			else
			{
				float fX = Displacement<float>(m_tLinePoint[0].fX, mfX);
				float fY = Displacement<float>(mfY, m_tLinePoint[0].fY);
				float fR = Disatance<float>(fX, fY);

				float fRadian = acosf(fX / fR);

				if (m_tLinePoint[0].fY < mfY)
				{
					fRadian = 2 * PI - fRadian;
				}

				m_tLinePoint[1].fX = m_tLinePoint[0].fX
					+ (float)fR * cosf(PI / 180 * m_fAngle);
				m_tLinePoint[1].fY = m_tLinePoint[0].fY - (float)fR * sinf(PI / 180 * m_fAngle);

				LINE	tLine{ m_tLinePoint[0], m_tLinePoint[1] };

				m_LineList.push_back(new CLine(tLine));

				m_tLinePoint[0].fX = m_tLinePoint[1].fX;
				m_tLinePoint[0].fY = m_tLinePoint[1].fY;
				m_bPress = false;
				m_fAngle = 0;
				ZeroMemory(m_tLinePoint, sizeof(LINEPOINT) * 2);
		}
	}

	if (m_bPress)
	{
		float fX = Displacement<float>(m_tLinePoint[0].fX, mfX);
		float fY = Displacement<float>(mfY, m_tLinePoint[0].fY);
		float fR = Disatance<float>(fX, fY);

		float tempX = m_tLinePoint[0].fX + (float)fR * cosf(PI / 180 * m_fAngle);
		float tempY = m_tLinePoint[0].fY - (float)fR * sinf(PI / 180 * m_fAngle);

		m_pLine = new CLine(m_tLinePoint[0], LINEPOINT{ tempX, tempY });
	}
}

void CNewEdit::ProcessBlock()
{
	float mfX = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fX;
	float mfY = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fY;
	mfX -= CScrollMgr::Get_Instance()->Get_ScrollX();
	mfY -= CScrollMgr::Get_Instance()->Get_ScrollY();

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		LINE Line = {};
		CObj* pObj = CAbstracyFactory<CObstacle>::Create(mfX, mfY);

		CCollisionMgr::Collision_RectEx(pObj, &m_CObList);
		CCollisionMgr::Collision_RectEx(pObj, &m_ObList);
		CCollisionMgr::Collision_RectEx(pObj, &m_IObList);

		m_ObList.push_back(CAbstracyFactory<CObstacle>::Create(pObj->Get_Info().fX, pObj->Get_Info().fY));
		Line.tLPoint = LINEPOINT{ (float)(pObj->Get_Info().fX - BWIDTH * 0.5) , (float)(pObj->Get_Info().fY - BWIDTH  * 0.5) };
		Line.tRPoint = LINEPOINT{ (float)(pObj->Get_Info().fX + BWIDTH * 0.5) ,  (float)(pObj->Get_Info().fY - BWIDTH  * 0.5) };
		m_LineList.push_back(new CLine(Line));
	}
}

void CNewEdit::ProcessCBlock()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		float mfX = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fX;
		float mfY = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fY;
		mfX -= CScrollMgr::Get_Instance()->Get_ScrollX();
		mfY -= CScrollMgr::Get_Instance()->Get_ScrollY();
		LINE Line = {};
		CObj* pObj = CAbstracyFactory<CCObstacle>::Create(mfX, mfY);
		CCollisionMgr::Collision_RectEx(pObj, &m_CObList);
		CCollisionMgr::Collision_RectEx(pObj, &m_ObList);
		CCollisionMgr::Collision_RectEx(pObj, &m_IObList);
		m_CObList.push_back(CAbstracyFactory<CCObstacle>::Create(pObj->Get_Info().fX, pObj->Get_Info().fY));
		Line.tLPoint = LINEPOINT{ (float)(pObj->Get_Info().fX - BWIDTH * 0.5) ,(float)(pObj->Get_Info().fY - BWIDTH  * 0.5) };
		Line.tRPoint = LINEPOINT{ (float)(pObj->Get_Info().fX + BWIDTH * 0.5) , (float)(pObj->Get_Info().fY - BWIDTH  * 0.5) };
		m_LineList.push_back(new CLine(Line));
		Safe_Delete(pObj);
	}
}

void CNewEdit::ProcessFlower()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		float mfX = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fX;
		float mfY = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fY;
		mfX -= CScrollMgr::Get_Instance()->Get_ScrollX();
		mfY -= CScrollMgr::Get_Instance()->Get_ScrollY();
		CObj* pObj = CAbstracyFactory<CFlower>::Create(mfX, mfY);
		CCollisionMgr::Collision_RectEx(pObj, &m_CObList);
		m_FMonList.push_back(CAbstracyFactory<CFlower>::Create(pObj->Get_Info().fX, pObj->Get_Info().fY));
		Safe_Delete(pObj);
	}
}
void CNewEdit::ProcessUFMonster()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		float mfX = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fX;
		float mfY = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fY;
		mfX -= CScrollMgr::Get_Instance()->Get_ScrollX();
		mfY -= CScrollMgr::Get_Instance()->Get_ScrollY();
		CObj* pObj = CAbstracyFactory<CUFMonster>::Create(mfX, mfY);
		CCollisionMgr::Collision_RectEx(pObj, &m_CObList);
		m_UFMonList.push_back(CAbstracyFactory<CUFMonster>::Create(pObj->Get_Info().fX, pObj->Get_Info().fY));
		Safe_Delete(pObj);
	}
}

// 占쌩곤옙
void CNewEdit::ProcessMMonster()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		float mfX = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fX;
		float mfY = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fY;
		mfX -= CScrollMgr::Get_Instance()->Get_ScrollX();
		mfY -= CScrollMgr::Get_Instance()->Get_ScrollY();
		CObj* pObj = CAbstracyFactory<CMushroom>::Create(mfX, mfY);
		m_MMonList.push_back(CAbstracyFactory<CMushroom>::Create(pObj->Get_Info().fX, pObj->Get_Info().fY));
		Safe_Delete(pObj);
	}
}

void CNewEdit::ProcessBMonster()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		float mfX = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fX;
		float mfY = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fY;
		mfX -= CScrollMgr::Get_Instance()->Get_ScrollX();
		mfY -= CScrollMgr::Get_Instance()->Get_ScrollY();
		CObj* pObj = CAbstracyFactory<CBMonster>::Create(mfX, mfY);
		CCollisionMgr::Collision_RectEx(pObj, &m_CObList);
		CCollisionMgr::Collision_RectEx(pObj, &m_ObList);
		CCollisionMgr::Collision_RectEx(pObj, &m_IObList);
		m_BMonList.push_back(CAbstracyFactory<CBMonster>::Create(pObj->Get_Info().fX, pObj->Get_Info().fY));
		Safe_Delete(pObj);
	}
}
void CNewEdit::ProcessBoss()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		float mfX = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fX;
		float mfY = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fY;
		mfX -= CScrollMgr::Get_Instance()->Get_ScrollX();
		mfY -= CScrollMgr::Get_Instance()->Get_ScrollY();
		CObj* pObj = CAbstracyFactory<CBoss>::Create(mfX, mfY);
		CCollisionMgr::Collision_RectEx(pObj, &m_CObList);
		m_BossList.push_back(CAbstracyFactory<CBoss>::Create(pObj->Get_Info().fX, pObj->Get_Info().fY));
		Safe_Delete(pObj);
	}
}
void CNewEdit::ProcessIBlock()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		float mfX = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fX;
		float mfY = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fY;
		mfX -= CScrollMgr::Get_Instance()->Get_ScrollX();
		mfY -= CScrollMgr::Get_Instance()->Get_ScrollY();
		LINE Line = {};
		CObj* pObj = CAbstracyFactory<CIObstacle>::Create(mfX, mfY);
		CCollisionMgr::Collision_RectEx(pObj, &m_ObList);
		CCollisionMgr::Collision_RectEx(pObj, &m_CObList);
		CCollisionMgr::Collision_RectEx(pObj, &m_IObList);
		m_IObList.push_back(CAbstracyFactory<CIObstacle>::Create(pObj->Get_Info().fX, pObj->Get_Info().fY));
		Line.tLPoint = LINEPOINT{ (float)(pObj->Get_Info().fX - BWIDTH * 0.5) ,(float)(pObj->Get_Info().fY - BWIDTH  * 0.5) };
		Line.tRPoint = LINEPOINT{ (float)(pObj->Get_Info().fX + BWIDTH * 0.5) , (float)(pObj->Get_Info().fY - BWIDTH  * 0.5) };
		m_LineList.push_back(new CLine(Line));
		Safe_Delete(pObj);
	}
}

void CNewEdit::ProcessFlag()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		float mfX = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fX;
		float mfY = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fY;
		mfX -= CScrollMgr::Get_Instance()->Get_ScrollX();
		mfY -= CScrollMgr::Get_Instance()->Get_ScrollY();
		CObj* pObj = CAbstracyFactory<CFlag>::Create(mfX, mfY);
		m_FlagList.push_back(CAbstracyFactory<CFlag>::Create(pObj->Get_Info().fX, pObj->Get_Info().fY));
		Safe_Delete(pObj);
	}
}

void CNewEdit::ProcessGhost()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		float mfX = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fX;
		float mfY = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fY;
		mfX -= CScrollMgr::Get_Instance()->Get_ScrollX();
		mfY -= CScrollMgr::Get_Instance()->Get_ScrollY();
		CObj* pObj = CAbstracyFactory<CGhost>::Create(mfX, mfY);
		m_GhostList.push_back(CAbstracyFactory<CGhost>::Create(pObj->Get_Info().fX, pObj->Get_Info().fY));
		Safe_Delete(pObj);
	}
}

void CNewEdit::ProcessInitLine()
{
	ZeroMemory(m_tLinePoint, sizeof(LINEPOINT) * 2);
}

void CNewEdit::ProcessDrag()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
	{
		float mfX = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fX;
		float mfY = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fY;


		if (!m_bRPress)
		{
			if (!m_pRect)
				m_pRect = new RECT;

			m_pRect->left = mfX;
			m_pRect->top = mfY;
			m_bRPress = true;
		}
		else
		{
			m_pRect->right = mfX;
			m_pRect->bottom = mfY;
			m_bRPress = false;
			m_pRect->left -= CScrollMgr::Get_Instance()->Get_ScrollX();
			m_pRect->top -= CScrollMgr::Get_Instance()->Get_ScrollY();
			m_pRect->right -= CScrollMgr::Get_Instance()->Get_ScrollX();
			m_pRect->bottom -= CScrollMgr::Get_Instance()->Get_ScrollY();

			float fY = (m_pRect->top + m_pRect->bottom) *0.5;

			switch (m_ePro)
			{
			case PRO_LINE:
				ProcessLineY(fY, PRO_LINE);
				break;
			case PRO_BLOCK:
				ProcessLineY(fY, PRO_BLOCK);
				ProcessBLockLineY(fY);
				break;
			case PRO_CBLOCK:
				ProcessLineY(fY, PRO_CBLOCK);
				ProcessCBLockLineY(fY);
				break;
			case PRO_IBLOCK:
				ProcessLineY(fY, PRO_IBLOCK);
				ProcessIBLockLineY(fY);
				break;
			case PRO_FMONSTER:
				ProcessCFMonLineY(fY);
				break;
			case PRO_UFMONSTER:
				ProcessCUFMonLineY(fY);
				break;
			case PRO_MMONSTER:
				ProcessMMonLineY(fY);
				break;
			case PRO_BMONSTER:
				ProcessBMonLineY(fY);
				break;
			}
			Safe_Delete(m_pRect);
		}
	}
	if (m_bRPress)
	{
		float mfX = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fX;
		float mfY = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fY;
		m_pRect->right = mfX;
		m_pRect->bottom = mfY;
	}
}
void CNewEdit::ProcessCUFMonLineY(float _y)
{
	for (auto& elem : m_UFMonList)
	{
		if ((m_pRect->left <= elem->Get_Info().fX) &&
			(m_pRect->top <= elem->Get_Info().fY) &&
			(m_pRect->bottom >= elem->Get_Info().fY) &&
			m_pRect->right >= elem->Get_Info().fX)
		{
			elem->Get_Info().fY = _y;
			elem->Update_Rect();
		}
	}
}
void CNewEdit::ProcessCFMonLineY(float _y)
{
	for (auto& elem : m_FMonList)
	{
		if ((m_pRect->left <= elem->Get_Info().fX) &&
			(m_pRect->top <= elem->Get_Info().fY) &&
			(m_pRect->bottom >= elem->Get_Info().fY) &&
			m_pRect->right >= elem->Get_Info().fX)
		{
			elem->Get_Info().fY = _y;
			elem->Update_Rect();
		}
	}
}

// 占쌩곤옙
void CNewEdit::ProcessMMonLineY(float _y)
{
	for (auto& elem : m_MMonList)
	{
		if ((m_pRect->left <= elem->Get_Info().fX) &&
			(m_pRect->top <= elem->Get_Info().fY) &&
			(m_pRect->bottom >= elem->Get_Info().fY) &&
			m_pRect->right >= elem->Get_Info().fX)
		{
			elem->Get_Info().fY = _y;
			elem->Update_Rect();
		}
	}
}

void CNewEdit::ProcessBMonLineY(float _y)
{
	for (auto& elem : m_BMonList)
	{
		if ((m_pRect->left <= elem->Get_Info().fX) &&
			(m_pRect->top <= elem->Get_Info().fY) &&
			(m_pRect->bottom >= elem->Get_Info().fY) &&
			m_pRect->right >= elem->Get_Info().fX)
		{
			elem->Get_Info().fY = _y;
			elem->Update_Rect();
		}
	}
}

void CNewEdit::ProcessIBLockLineY(float _y)
{
	for (auto& elem : m_IObList)
	{
		if ((m_pRect->left <= elem->Get_Info().fX) &&
			(m_pRect->top <= elem->Get_Info().fY) &&
			(m_pRect->bottom >= elem->Get_Info().fY) &&
			m_pRect->right >= elem->Get_Info().fX)
		{
			elem->Get_Info().fY = _y;
			elem->Update_Rect();
		}
	}
}

void CNewEdit::ProcessBLockLineY(float _y)
{
	for (auto& elem : m_ObList)
	{
		if ((m_pRect->left <= elem->Get_Info().fX) &&
			(m_pRect->top <= elem->Get_Info().fY) &&
			(m_pRect->bottom >= elem->Get_Info().fY) &&
			m_pRect->right >= elem->Get_Info().fX)
		{
			elem->Get_Info().fY = _y;
			elem->Update_Rect();
		}
	}
}

void CNewEdit::ProcessCBLockLineY(float _y)
{
	for (auto& elem : m_CObList)
	{
		if ((m_pRect->left <= elem->Get_Info().fX) &&
			(m_pRect->top <= elem->Get_Info().fY) &&
			(m_pRect->bottom >= elem->Get_Info().fY) &&
			m_pRect->right >= elem->Get_Info().fX)
		{
			elem->Get_Info().fY = _y;
			elem->Update_Rect();
		}
	}
}

void CNewEdit::ProcessLineY(float _y, ePRO _ePro)
{
	for (auto& elem : m_LineList)
	{
		if ((m_pRect->left <= elem->Get_Info().tLPoint.fX) &&
			(m_pRect->top <= elem->Get_Info().tLPoint.fY) &&
			(m_pRect->bottom >= elem->Get_Info().tLPoint.fY) &&
			(m_pRect->top <= elem->Get_Info().tRPoint.fY) &&
			(m_pRect->bottom >= elem->Get_Info().tRPoint.fY) &&
			m_pRect->right >= elem->Get_Info().tRPoint.fX)
		{
			switch (_ePro)
			{
			case PRO_LINE:
				elem->Get_Info().tLPoint.fY = _y;
				elem->Get_Info().tRPoint.fY = _y;
				break;
			case PRO_BLOCK:
				elem->Get_Info().tLPoint.fY = _y - m_ObList.front()->Get_Info().fCY * 0.5;
				elem->Get_Info().tRPoint.fY = _y - m_ObList.front()->Get_Info().fCY * 0.5;
				break;
			case PRO_CBLOCK:
				elem->Get_Info().tLPoint.fY = _y - m_CObList.front()->Get_Info().fCY * 0.5;
				elem->Get_Info().tRPoint.fY = _y - m_CObList.front()->Get_Info().fCY * 0.5;
				break;
			}
		}
	}
}

int CNewEdit::Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);

	ProcessDrag();
	
	if (CKeyMgr::Get_Instance()->Key_Down('1'))
	{
		m_bPress = false;
		m_bRPress = false;
		m_ePro = PRO_LINE;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('2'))
	{
		m_bPress = false;
		m_bRPress = false;
		m_ePro = PRO_BLOCK;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('3'))
	{
		m_bPress = false;
		m_bRPress = false;
		m_ePro = PRO_CBLOCK;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('4'))
	{
		m_bPress = false;
		m_bRPress = false;
		m_ePro = PRO_FMONSTER;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('5'))
	{
		m_bPress = false;
		m_bRPress = false;
		m_ePro = PRO_UFMONSTER;
	}

	// 占쌩곤옙
	if (CKeyMgr::Get_Instance()->Key_Down('6'))
	{
		m_bPress = false;
		m_bRPress = false;
		m_ePro = PRO_MMONSTER;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('7'))
	{
		m_bPress = false;
		m_bRPress = false;
		m_ePro = PRO_BMONSTER;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('8'))
	{
		m_bPress = false;
		m_bRPress = false;
		m_ePro = PRO_IBLOCK;
	}


	if (CKeyMgr::Get_Instance()->Key_Down('9'))
	{
		m_bPress = false;
		m_bRPress = false;
		m_ePro = PRO_BOSS;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('G'))
	{
		m_bPress = false;
		m_bRPress = false;
		m_ePro = PRO_GHOST;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('F'))
	{
		m_bPress = false;
		m_bRPress = false;
		m_ePro = PRO_FLAG;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('I'))
	{
		ProcessInitLine();
	}

	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	{
		Save_File();
	}

	if (CKeyMgr::Get_Instance()->Key_Down('A'))
	{
		m_fAngle += 45;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('R'))
	{
		switch (m_ePro)
		{
		case PRO_LINE:
			if(!m_LineList.empty())
				m_LineList.pop_back();
			break;
		case PRO_BLOCK:
			if (!m_ObList.empty())
				m_ObList.pop_back();
			if (!m_LineList.empty())
				m_LineList.pop_back();
			break;
		case PRO_CBLOCK:
			if (!m_CObList.empty())
				m_CObList.pop_back();
			if (!m_LineList.empty())
				m_LineList.pop_back();
			break;
		case PRO_IBLOCK:
			if (!m_IObList.empty())
				m_IObList.pop_back();
			if (!m_LineList.empty())
				m_LineList.pop_back();
			break;
		case PRO_FMONSTER:
			if (!m_FMonList.empty())
				m_FMonList.pop_back();
			break;
		case PRO_UFMONSTER:
			if (!m_UFMonList.empty())
				m_UFMonList.pop_back();
			break;
		case PRO_MMONSTER:
			if (!m_MMonList.empty())
				m_MMonList.pop_back();
			break;
		case PRO_BMONSTER:
			if (!m_BMonList.empty())
				m_BMonList.pop_back();
			break;
		case PRO_BOSS:
			if (!m_BossList.empty())
				m_BossList.pop_back();
			break;
		case PRO_FLAG:
			if (!m_FlagList.empty())
				m_FlagList.pop_back();
			break;
		case PRO_GHOST:
			if (!m_GhostList.empty())
				m_GhostList.pop_back();
			break;
		}
	}

	switch (m_ePro)
	{
	case PRO_BLOCK:
		Safe_Delete(m_pLine);
		ProcessBlock();
		break;
	case PRO_LINE:
		ProcessLine();
		break;
	case PRO_CBLOCK:
		Safe_Delete(m_pLine);
		ProcessCBlock();
		break;
	case PRO_IBLOCK:
		Safe_Delete(m_pLine);
		ProcessIBlock();
		break;
	case PRO_FMONSTER:
		Safe_Delete(m_pLine);
		ProcessFlower();
		break;
	case PRO_UFMONSTER:
		Safe_Delete(m_pLine);
		ProcessUFMonster();
		break;
	case PRO_MMONSTER:
		Safe_Delete(m_pLine);
		ProcessMMonster();
		break;
	case PRO_BMONSTER:
		Safe_Delete(m_pLine);
		ProcessBMonster();
		break;
	case PRO_BOSS:
		Safe_Delete(m_pLine);
		ProcessBoss();
		break;
	case PRO_FLAG:
		Safe_Delete(m_pLine);
		ProcessFlag();
		break;
	case PRO_GHOST:
		Safe_Delete(m_pLine);
		ProcessGhost();
		break;
	}

	return 0;
}

void CNewEdit::Late_Update(void)
{
}

void CNewEdit::Render(HDC _DC)
{
	TextOut
	(_DC, 50, 10/*WINCY-100*/,
		L"[1]라인모드 [2]블록모드 [3]충돌블록모드 [4]꽃몬스터모드 [5]거북이몬스터모드 [6]버섯몬스터모드 [7]블록몬스터모드 [8]아이템블록모드 [9]보스모드 [F]플래그모드 [G]고스트몬스터 [A]라인각도조절 [L]모드교체 [Q]저장 [오른쪽드래그]Y값 라인정렬",
		lstrlen(L"[1]라인모드 [2]블록모드 [3]충돌블록모드 [4]꽃몬스터모드 [5]거북이몬스터모드 [6]버섯몬스터모드 [7]블록몬스터모드 [8]아이템블록모드 [9]보스모드 [F]플래그모드 [G]고스트몬스터 [A]라인각도조절 [L]모드교체 [Q]저장 [오른쪽드래그]Y값 라인정렬"));
	switch (m_ePro)
	{
	case CNewEdit::PRO_LINE:
		TextOut(_DC, 50, 50, L"현재 모드 라인모드", lstrlen(L"현재 모드 라인모드"));
		break;
	case CNewEdit::PRO_BLOCK:
		TextOut(_DC, 50, 50, L"현재 모드 블록", lstrlen(L"현재 모드 블록"));
		break;
	case CNewEdit::PRO_CBLOCK:
		TextOut(_DC, 50, 50, L"현재 모드 충돌 블록", lstrlen(L"현재 모드 충돌 블록"));
		break;
	case CNewEdit::PRO_IBLOCK:
		TextOut(_DC, 50, 50, L"현재 모드 아이템 블록", lstrlen(L"현재 모드 아이템 블록"));
		break;
	case CNewEdit::PRO_FMONSTER:
		TextOut(_DC, 50, 50, L"현재 꽃 몬스터 생성", lstrlen(L"현재 꽃 몬스터 생성"));
		break;
	case CNewEdit::PRO_UFMONSTER:
		TextOut(_DC, 50, 50, L"현재 거북 몬스터 생성", lstrlen(L"현재 거북 몬스터 생성"));
		break;
	case CNewEdit::PRO_MMONSTER:
		TextOut(_DC, 50, 50, L"현재 버섯 몬스터 생성", lstrlen(L"현재 버섯 몬스터 생성"));
		break;
	case CNewEdit::PRO_BMONSTER:
		TextOut(_DC, 50, 50, L"현재 블록 몬스터 생성", lstrlen(L"현재 버섯 몬스터 생성"));
		break;
	case CNewEdit::PRO_BOSS:
		TextOut(_DC, 50, 50, L"현재 보스 몬스터 생성", lstrlen(L"현재 보스 몬스터 생성"));
		break;
	case CNewEdit::PRO_FLAG:
		TextOut(_DC, 50, 50, L"현재 깃발 생성", lstrlen(L"현재 깃발 생성"));
		break;
	case CNewEdit::PRO_GHOST:
		TextOut(_DC, 50, 50, L"현재 유령 몬스터 생성", lstrlen(L"현재 유령 몬스터 생성"));
		break;
	default:
		break;
	}
	for (auto& iter : m_LineList)
	{
		iter->Render(_DC);
	}

	for (auto& iter : m_ObList)
	{
		iter->Render(_DC);
	}

	for (auto& iter : m_CObList)
	{
		iter->Render(_DC);
	}

	for (auto& iter : m_FMonList)
	{
		iter->Render(_DC);
	}

	for (auto& iter : m_UFMonList)
	{
		iter->Render(_DC);
	}

	// 占쌩곤옙
	for (auto& iter : m_MMonList)
	{
		iter->Render(_DC);
	}

	for (auto& iter : m_BMonList)
	{
		iter->Render(_DC);
	}

	for (auto& iter : m_IObList)
	{
		iter->Render(_DC);
	}
	for (auto& iter : m_BossList)
	{
		iter->Render(_DC);
	}

	for (auto& iter : m_FlagList)
	{
		iter->Render(_DC);
	}

	for (auto& iter : m_GhostList)
	{
		iter->Render(_DC);
	}

	if (m_pLine)
	{
		m_pLine->Render(_DC);
	}
	else if (m_pRect)
	{
		Rectangle(_DC, m_pRect->left, m_pRect->top, m_pRect->right, m_pRect->bottom);
	}


}

void CNewEdit::Release(void)
{
	Safe_Delete(m_pLine);
	Safe_Delete(m_pRect);

	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();
	list<CLine*>().swap(m_LineList);

	for_each(m_ObList.begin(), m_ObList.end(), CDeleteObj());
	m_ObList.clear();
	list<CObj*>().swap(m_ObList);

	for_each(m_CObList.begin(), m_CObList.end(), CDeleteObj());
	m_CObList.clear();
	list<CObj*>().swap(m_CObList);

	for_each(m_FMonList.begin(), m_FMonList.end(), CDeleteObj());
	m_FMonList.clear();
	list<CObj*>().swap(m_FMonList);

	for_each(m_UFMonList.begin(), m_UFMonList.end(), CDeleteObj());
	m_UFMonList.clear();
	list<CObj*>().swap(m_UFMonList);

	for_each(m_MMonList.begin(), m_MMonList.end(), CDeleteObj());
	m_MMonList.clear();
	list<CObj*>().swap(m_MMonList);

	for_each(m_BMonList.begin(), m_BMonList.end(), CDeleteObj());
	m_BMonList.clear();
	list<CObj*>().swap(m_BMonList);

	for_each(m_IObList.begin(), m_IObList.end(), CDeleteObj());
	m_IObList.clear();
	list<CObj*>().swap(m_IObList);

	for_each(m_BossList.begin(), m_BossList.end(), CDeleteObj());
	m_BossList.clear();
	list<CObj*>().swap(m_BossList);

	for_each(m_FlagList.begin(), m_FlagList.end(), CDeleteObj());
	m_FlagList.clear();
	list<CObj*>().swap(m_FlagList);

	for_each(m_GhostList.begin(), m_GhostList.end(), CDeleteObj());
	m_GhostList.clear();
	list<CObj*>().swap(m_GhostList);
}

void CNewEdit::Save_File(void)
{
	switch (m_eMode)
	{
	case EDIT1:
		DeleteFileA("../Data/Line.dat");
		DeleteFileA("../Data/Obstacle.dat");
		DeleteFileA("../Data/CObstacle.dat");
		DeleteFileA("../Data/CFlower.dat");
		DeleteFileA("../Data/CUFMonster.dat");
		DeleteFileA("../Data/CMushroom.dat");
		DeleteFileA("../Data/CBMonster.dat");
		DeleteFileA("../Data/IObstacle.dat");
		DeleteFileA("../Data/CBoss.dat");
		DeleteFileA("../Data/CFlag.dat");
		DeleteFileA("../Data/CGhost.dat");
		break;
	case EDIT2:
		break;
	}

	HANDLE		hFile;
	DWORD		dwByte = 0;
	for (int i = 0; i < 11; ++i)
	{
		hFile = CreateFile(FILEPATH[i],		// 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙恝占?占싱몌옙
			GENERIC_WRITE,			// 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占?(GENERIC_WRITE 占쏙옙占쏙옙 占쏙옙占? GENERIC_READ 占쏙옙占쏙옙 占쌉뤄옙)
			NULL,					// 占쏙옙占쏙옙占쏙옙占? 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쌍댐옙 占쏙옙占승울옙占쏙옙 占쌕몌옙 占쏙옙占싸그뤄옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙 占썬가 占쏙옙 占쏙옙占싸곤옙(null占쏙옙 占쏙옙占?占쏙옙占쏙옙占쏙옙占쏙옙 占십는댐옙)
			NULL,					// 占쏙옙占싫속쇽옙, null占쏙옙 占썩본占쏙옙占쏙옙占쏙옙 占쏙옙占싫삼옙占승몌옙 占쏙옙占쏙옙
			CREATE_ALWAYS,			// 占쏙옙占쏙옙占쏙옙占? 占쌔댐옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏘서 占쌜억옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙占쏙옙占?占쏙옙占쏙옙, CREATE_ALWAYS 占쏙옙占쏙옙占쏙옙 占쏙옙占쌕몌옙 占쏙옙占쏙옙, 占쌍다몌옙 占쏙옙占쏘쓰占쏙옙, OPEN_EXISITING 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙荑∽옙占?占쏙옙占쏙옙 占심쇽옙)
			FILE_ATTRIBUTE_NORMAL,	// 占쏙옙占쏙옙 占쌈쇽옙占쏙옙占쏙옙(占싻깍옙 占쏙옙占쏙옙, 占쏙옙占쏙옙 占쏙옙占?占쏙옙占? FILE_ATTRIBUTE_NORMAL 占싣뱄옙占쏙옙 占쌈쇽옙占쏙옙 占쏙옙占쏙옙 占싹뱄옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙
			NULL);					// 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쌈쇽옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占시몌옙 占쏙옙占쏙옙, 占쎌리占쏙옙 占쏙옙占쏙옙占쏙옙占?占쏙옙占쏙옙 占쏙옙占싱깍옙 占쏙옙占쏙옙占쏙옙 null

		if (INVALID_HANDLE_VALUE == hFile)
		{
			// _T : 占싣쏙옙키占쌘듸옙 占쏙옙占쌘울옙占쏙옙 占쏙옙占쏙옙占쌘듸옙占?占쏙옙환占쏙옙占쏙옙占쌍댐옙 占쏙옙크占쏙옙
			MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
			// 2占쏙옙占쏙옙 : 占싯억옙 창占쏙옙 占쏙옙占쏙옙占쏙옙 占싹댐옙 占쌨쇽옙占쏙옙
			// 3占쏙옙占쏙옙 : 占싯억옙 창占쏙옙 占싱몌옙
		}

		switch (i)
		{
		case 0:
			for (auto& iter : m_LineList)
			{
				WriteFile(hFile, &iter->Get_Info(), sizeof(LINE), &dwByte, nullptr);
			}
			break;
		case 1:
			for (auto& iter : m_ObList)
			{
				WriteFile(hFile, static_cast<CObstacle*>(iter), sizeof(CObstacle), &dwByte, nullptr);
			}
			break;
		case 2:
			for (auto& iter : m_CObList)
			{
				WriteFile(hFile, static_cast<CCObstacle*>(iter), sizeof(CCObstacle), &dwByte, nullptr);
			}
			break;
		case 3:
			for (auto& iter : m_FMonList)
			{
				WriteFile(hFile, static_cast<CFlower*>(iter), sizeof(CFlower), &dwByte, nullptr);
			}
			break;
		case 4:
			for (auto& iter : m_UFMonList)
			{
				WriteFile(hFile, static_cast<CUFMonster*>(iter), sizeof(CUFMonster), &dwByte, nullptr);
			}
			break;
		case 5:
			for (auto& iter : m_MMonList)
			{
				WriteFile(hFile, static_cast<CMushroom*>(iter), sizeof(CMushroom), &dwByte, nullptr);
			}
			break;
		case 6:
			for (auto& iter : m_BMonList)
			{
				WriteFile(hFile, static_cast<CBMonster*>(iter), sizeof(CBMonster), &dwByte, nullptr);
			}
			break;
		case 7:
			for (auto& iter : m_IObList)
			{
				WriteFile(hFile, static_cast<CIObstacle*>(iter), sizeof(CIObstacle), &dwByte, nullptr);
			}
			break;
		case 8:
			for (auto& iter : m_BossList)
			{
				WriteFile(hFile, static_cast<CBoss*>(iter), sizeof(CBoss), &dwByte, nullptr);
			}
			break;
		case 9:
			for (auto& iter : m_FlagList)
			{
				WriteFile(hFile, static_cast<CFlag*>(iter), sizeof(CFlag), &dwByte, nullptr);
			}
			break;
		case 10:
			for (auto& iter : m_GhostList)
			{
				WriteFile(hFile, static_cast<CGhost*>(iter), sizeof(CGhost), &dwByte, nullptr);
			}
			MessageBox(g_hWnd, _T("Save 성공"), _T("성공"), MB_OK);
			break;
		}
		dwByte = 0;
		CloseHandle(hFile);
	}
}

void CNewEdit::Load_File(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();

	HANDLE		hFile;
	DWORD		dwByte = 0;
	LINE		tInfo{};
	CObstacle	tCObj{};
	CCObstacle	tCCObj{};
	CFlower	    tCFlower{};
	CUFMonster	tCUFMoster{};
	CMushroom	tCMushroom{};
	CBMonster	tCBMonster{};
	CIObstacle	tCIObj{};
	CBoss		tBossMonster{};
	CFlag		tCFlag{};
	CGhost		tCGhost{};

	for (int i = 0; i < 11; ++i)
	{
		hFile = CreateFile(FILEPATH[i],		// 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙恝占?占싱몌옙
			GENERIC_READ,			// 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占?(GENERIC_WRITE 占쏙옙占쏙옙 占쏙옙占? GENERIC_READ 占쏙옙占쏙옙 占쌉뤄옙)
			NULL,					// 占쏙옙占쏙옙占쏙옙占? 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쌍댐옙 占쏙옙占승울옙占쏙옙 占쌕몌옙 占쏙옙占싸그뤄옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙 占썬가 占쏙옙 占쏙옙占싸곤옙(null占쏙옙 占쏙옙占?占쏙옙占쏙옙占쏙옙占쏙옙 占십는댐옙)
			NULL,					// 占쏙옙占싫속쇽옙, null占쏙옙 占썩본占쏙옙占쏙옙占쏙옙 占쏙옙占싫삼옙占승몌옙 占쏙옙占쏙옙
			OPEN_EXISTING,			// 占쏙옙占쏙옙占쏙옙占? 占쌔댐옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏘서 占쌜억옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙占쏙옙占?占쏙옙占쏙옙, CREATE_ALWAYS 占쏙옙占쏙옙占쏙옙 占쏙옙占쌕몌옙 占쏙옙占쏙옙, 占쌍다몌옙 占쏙옙占쏘쓰占쏙옙, OPEN_EXISITING 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙荑∽옙占?占쏙옙占쏙옙 占심쇽옙)
			FILE_ATTRIBUTE_NORMAL,	// 占쏙옙占쏙옙 占쌈쇽옙占쏙옙占쏙옙(占싻깍옙 占쏙옙占쏙옙, 占쏙옙占쏙옙 占쏙옙占?占쏙옙占? FILE_ATTRIBUTE_NORMAL 占싣뱄옙占쏙옙 占쌈쇽옙占쏙옙 占쏙옙占쏙옙 占싹뱄옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙
			NULL);					// 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쌈쇽옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占시몌옙 占쏙옙占쏙옙, 占쎌리占쏙옙 占쏙옙占쏙옙占쏙옙占?占쏙옙占쏙옙 占쏙옙占싱깍옙 占쏙옙占쏙옙占쏙옙 null

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, _T("Line Load File"), _T("Fail"), MB_OK);
		}

		switch (i)
		{
		case 0:
			while (true)
			{
				ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

				if (0 == dwByte)
					break;

				m_LineList.push_back(new CLine(tInfo));
			}
			break;
		case 1:
			while (true)
			{
				ReadFile(hFile, &tCObj, sizeof(CObstacle), &dwByte, nullptr);
				if (0 == dwByte)
					break;

				CObjMgr::Get_Instance()->AddObject(OBJ_OBSTACLE, CAbstracyFactory<CObstacle>::Create(tCObj));
			}
			break;
		case 2:
			while (true)
			{
				ReadFile(hFile, &tCCObj, sizeof(CCObstacle), &dwByte, nullptr);

				if (0 == dwByte)
					break;

				CObjMgr::Get_Instance()->AddObject(OBJ_COBSTACLE, CAbstracyFactory<CCObstacle>::Create(tCCObj));
			}
			break;
		case 3:
			while (true)
			{
				ReadFile(hFile, &tCFlower, sizeof(CFlower), &dwByte, nullptr);

				if (0 == dwByte)
					break;

				CObjMgr::Get_Instance()->AddObject(OBJ_FLOWER, CAbstracyFactory<CFlower>::Create(tCFlower.Get_Info().fX
				, tCFlower.Get_Info().fY));
			}
			break;
		case 4:
			while (true)
			{
				ReadFile(hFile, &tCUFMoster, sizeof(CUFMonster), &dwByte, nullptr);

				if (0 == dwByte)
					break;

				CObjMgr::Get_Instance()->AddObject(OBJ_UFMONSTER, CAbstracyFactory<CUFMonster>::Create(tCUFMoster.Get_Info().fX
					, tCUFMoster.Get_Info().fY));
			}
			break;
		case 5:
			while (true)
			{
				ReadFile(hFile, &tCMushroom, sizeof(CMushroom), &dwByte, nullptr);

				if (0 == dwByte)
					break;

				CObjMgr::Get_Instance()->AddObject(OBJ_MUSHROOM, CAbstracyFactory<CMushroom>::Create(tCMushroom.Get_Info().fX
					, tCMushroom.Get_Info().fY));
			}
			break;
		case 6:
			while (true)
			{
				ReadFile(hFile, &tCBMonster, sizeof(CBMonster), &dwByte, nullptr);

				if (0 == dwByte)
					break;

				CObjMgr::Get_Instance()->AddObject(OBJ_BMONSTER, CAbstracyFactory<CBMonster>::Create(tCBMonster.Get_Info().fX
					, tCBMonster.Get_Info().fY));
			}
			break;
		case 7:
			while (true)
			{
				ReadFile(hFile, &tCIObj, sizeof(CIObstacle), &dwByte, nullptr);

				if (0 == dwByte)
					break;

				CObjMgr::Get_Instance()->AddObject(OBJ_IOBSTACLE, CAbstracyFactory<CIObstacle>::Create(tCIObj));
			}
			break;
		case 8:
			while (true)
			{
				ReadFile(hFile, &tBossMonster, sizeof(CBoss), &dwByte, nullptr);

				if (0 == dwByte)
					break;

				CObjMgr::Get_Instance()->AddObject(OBJ_BOSS, CAbstracyFactory<CBoss>::Create(tBossMonster.Get_Info().fX
					, tBossMonster.Get_Info().fY));
			}
			break;
		case 9:
			while (true)
			{
				ReadFile(hFile, &tCFlag, sizeof(CFlag), &dwByte, nullptr);

				if (0 == dwByte)
					break;

				CObjMgr::Get_Instance()->AddObject(OBJ_FLAG, CAbstracyFactory<CFlag>::Create(tCFlag.Get_Info().fX
					, tCFlag.Get_Info().fY));
			}

			break;
		case 10:
			while (true)
			{
				ReadFile(hFile, &tCGhost, sizeof(CGhost), &dwByte, nullptr);

				if (0 == dwByte)
					break;

				CObjMgr::Get_Instance()->AddObject(OBJ_GHOST, CAbstracyFactory<CGhost>::Create(tCGhost.Get_Info().fX
					, tCGhost.Get_Info().fY));
			}
			MessageBox(g_hWnd, _T("Load 성공"), _T("성공"), MB_OK);
			break;
		}
		dwByte = 0;
		CloseHandle(hFile);
	}

	switch (m_eMode)
	{
	case EDIT_MODE::EDIT2:
			m_ObList.swap(CObjMgr::Get_Instance()->Get_ListRef(OBJ_OBSTACLE));
			m_CObList.swap(CObjMgr::Get_Instance()->Get_ListRef(OBJ_COBSTACLE));
			m_FMonList.swap(CObjMgr::Get_Instance()->Get_ListRef(OBJ_FLOWER));
			m_UFMonList.swap(CObjMgr::Get_Instance()->Get_ListRef(OBJ_UFMONSTER));
			m_MMonList.swap(CObjMgr::Get_Instance()->Get_ListRef(OBJ_MUSHROOM));
			m_BMonList.swap(CObjMgr::Get_Instance()->Get_ListRef(OBJ_BMONSTER));
			m_IObList.swap(CObjMgr::Get_Instance()->Get_ListRef(OBJ_IOBSTACLE));
			m_BossList.swap(CObjMgr::Get_Instance()->Get_ListRef(OBJ_BOSS));
			m_FlagList.swap(CObjMgr::Get_Instance()->Get_ListRef(OBJ_FLAG));
			m_GhostList.swap(CObjMgr::Get_Instance()->Get_ListRef(OBJ_GHOST));
			break;
	}
}
