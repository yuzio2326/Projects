#include "stdafx.h"
#include "Room1.h"

#include "AbstactFactory.h"
#include "ObjMgr.h"

#include "Wall.h"
#include "SideWall.h"
#include "Door.h"
//#include "Treasurebox.h"

CRoom1::CRoom1()
	:m_pObj1(nullptr), m_pObj2(nullptr), m_pObj3(nullptr)
{
}


CRoom1::~CRoom1()
{
	Release();
}

void CRoom1::Initialize(float _fX, float _fY)
{
	m_tRect.left = 32;
	m_tRect.top = 32;
	m_tRect.right = 32 * 22;
	m_tRect.bottom = 32 * 16;

	Set_Pos(_fX, _fY);

	CObjMgr::Get_Instance()->AddObject(OBJ_METERIAL, CAbstactFactory<CWall>::Create(m_tRect.left, m_tRect.top));
	CObjMgr::Get_Instance()->AddObject(OBJ_METERIAL, CAbstactFactory<CWall>::Create(m_tRect.left, m_tRect.bottom));
	CObjMgr::Get_Instance()->AddObject(OBJ_METERIAL, CAbstactFactory<CWall>::Create(m_tRect.right, m_tRect.top));
	CObjMgr::Get_Instance()->AddObject(OBJ_METERIAL, CAbstactFactory<CWall>::Create(m_tRect.right, m_tRect.bottom));

	CObjMgr::Get_Instance()->AddObject(OBJ_METERIAL, CAbstactFactory<CSideWall>::Create(m_tRect.left, m_tRect.top));
	CObjMgr::Get_Instance()->AddObject(OBJ_METERIAL, CAbstactFactory<CSideWall>::Create(m_tRect.right, m_tRect.top));
	CObjMgr::Get_Instance()->AddObject(OBJ_METERIAL, CAbstactFactory<CSideWall>::Create(m_tRect.left, m_tRect.bottom));
	CObjMgr::Get_Instance()->AddObject(OBJ_METERIAL, CAbstactFactory<CSideWall>::Create(m_tRect.right, m_tRect.bottom));

	for(int i = 0; i < 5; i++)
	{
		CObjMgr::Get_Instance()->AddObject(OBJ_METERIAL, CAbstactFactory<CWall>::Create(m_tRect.left + 32 * (i + 1.5f), m_tRect.top));
	}

	for (int i = 0; i < 5; i++)
	{
		CObjMgr::Get_Instance()->AddObject(OBJ_METERIAL, CAbstactFactory<CWall>::Create(m_tRect.left, m_tRect.top + 32 * (i + 1.5f)));
	}

	for (int i = 0; i < 5; i++)
	{
		CObjMgr::Get_Instance()->AddObject(OBJ_METERIAL, CAbstactFactory<CWall>::Create(m_tRect.right, m_tRect.top + 32 * (i + 1.5f)));
	}

	CObjMgr::Get_Instance()->AddObject(OBJ_METERIAL, CAbstactFactory<CWall>::Create(m_tRect.left + 32 * 1.5f, m_tRect.bottom,180.f));
	CObjMgr::Get_Instance()->AddObject(OBJ_METERIAL, CAbstactFactory<CWall>::Create(m_tRect.right - 32 * 1.5f, m_tRect.bottom,180.f));


}

int CRoom1::Update(void)
{
	return OBJ_NOEVENT;
}

void CRoom1::Release(void)
{
	m_pObj1 = nullptr;
	m_pObj2 = nullptr;
	m_pObj3 = nullptr;
}
