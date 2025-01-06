#include "stdafx.h"
#include "Tile.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"


CTile::CTile()
{
}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize(void)
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_iDrawID = 0;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/lbasementfloorTile.bmp", L"Tile");
}

int CTile::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CTile::Late_Update(void)
{
	
}

void CTile::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Tile");

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	
	BitBlt(hDC, 
		m_tRect.left + iScrollX, 
		m_tRect.top + iScrollY, 
		TILECX, TILECY, 
		hMemDC, 
		TILECX * m_iDrawID,
		0, 
		SRCCOPY);
}

void CTile::Release(void)
{
	
}
