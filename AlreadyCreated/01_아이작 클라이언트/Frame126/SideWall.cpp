#include "stdafx.h"
#include "SideWall.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
CSideWall::CSideWall()
{
}


CSideWall::~CSideWall()
{
	Release();
}

void CSideWall::Initialize(void)
{
	m_tInfo.fX = 32.f;		// 중점 X
	m_tInfo.fY = 32.f;		// 중점 Y

	m_tInfo.fCX = 64.f;	//  가로 사이즈
	m_tInfo.fCY = 64.f;	//  세로 사이즈

	m_fSpeed = 100.f;

	m_eGroup = GAMEOBJECT;

	Insert_Texture();




}

int CSideWall::Update(void)
{

	if (true == m_bDead)
		return OBJ_DEAD;

	if (m_fAngle == 0.f)
	{
		m_pFrameKey = L"Side_Wall1";
		m_eState = LEFT_TOP;
	}
	if (m_fAngle == 90.f)
	{
		m_pFrameKey = L"Side_Wall2";
		m_eState = LEFT_BOTTOM;
	}
	if (m_fAngle == 180.f)
	{
		m_pFrameKey = L"Side_Wall3";
		m_eState = RIGHT_BOTTOM;
	}
	if (m_fAngle == 270.f)
	{
		m_pFrameKey = L"Side_Wall4";
		m_eState = RIGHT_TOP;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CSideWall::Late_Update(void)
{

}

void CSideWall::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//BitBlt(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tInfo.fCX, m_tInfo.fCY, hMemDC, 0, 0, SRCCOPY);
	// 1인자 : 복사 받을 최종적으로 그림을 그릴 DC
	// 2, 3인자 : 복사 받을 위치의 좌표를 전달(L, T 좌표)
	// 4, 5인자 : 복사 받을 텍스처의 X, Y 사이즈
	// 6 인자 : 비트맵을 가지고 있는 DC
	// 7, 8인자 : 비트맵을 출력할 시작 좌표(L, T좌표)
	// 9인자 : 출력 효과를 설정 SRCCOPY : 그대로 출력
	GdiTransparentBlt(hDC,							// 1인자 : 복사 받을 최종적으로 그림을 그릴 DC
		(int)m_tRect.left + iScrollX,	// 2,3인자 : 2, 3인자 : 복사 받을 위치의 좌표를 전달(L, T 좌표)
		(int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,				// 4,5 인자 : 복사 받을 텍스처의 X, Y 사이즈	//크기 늘리기
		(int)m_tInfo.fCY,
		hMemDC,							// 6인자 : 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,			// 7, 8인자 : 비트맵을 출력할 시작 좌표
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9, 10인자 : 복사할 비트맵의 X,Y 사이즈	
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));			// 11인자 : 제거하고자 하는 색상



}

void CSideWall::Release(void)
{

}

void CSideWall::Motion_Change(void)
{

}

void CSideWall::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/side_wall1.bmp", L"Side_Wall1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/side_wall2.bmp", L"Side_Wall2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/side_wall3.bmp", L"Side_Wall3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/side_wall4.bmp", L"Side_Wall4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Plg.bmp", L"Rotation");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Reset.bmp", L"Reset");
}

void CSideWall::First_State(void)
{
}
