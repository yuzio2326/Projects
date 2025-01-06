#include "stdafx.h"
#include "RangeStatus.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "Player.h"
CRangeStatus::CRangeStatus()
{
}


CRangeStatus::~CRangeStatus()
{
	Release();
}

void CRangeStatus::Initialize(void)
{
	m_tInfo.fX = 16.f;		// 중점 X
	m_tInfo.fY = 370.f;		// 중점 Y

	m_tInfo.fCX = 16.f;	//  가로 사이즈
	m_tInfo.fCY = 16.f;	//  세로 사이즈


	m_iHP = CObjMgr::Get_Instance()->Get_Player()->Get_HP();
	m_iMaxHP = CObjMgr::Get_Instance()->Get_Player()->Get_MAXHP();
	m_eGroup = UI;

	Insert_Texture();

	First_State();

}

int CRangeStatus::Update(void)
{

	if (m_iHP <= 0)
		m_bDead = true;


	if (true == m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	//get bomb
	//m_iHP = CObjMgr::Get_Instance()->Get_Player()->Get_HP();

	Motion_Change();
	Move_Frame();

	return OBJ_NOEVENT;
}

void CRangeStatus::Late_Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing('Q'))
		m_fAngle += 45.f;
}

void CRangeStatus::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Status");

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
		(int)m_tRect.left,	// 2,3인자 : 2, 3인자 : 복사 받을 위치의 좌표를 전달(L, T 좌표)
		(int)m_tRect.top,
		(int)m_tInfo.fCX+16.f,				// 4,5 인자 : 복사 받을 텍스처의 X, Y 사이즈	//크기 늘리기
		(int)m_tInfo.fCY+16.f,
		hMemDC,							// 6인자 : 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,			// 7, 8인자 : 비트맵을 출력할 시작 좌표
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9, 10인자 : 복사할 비트맵의 X,Y 사이즈	
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));			// 11인자 : 제거하고자 하는 색상



}

void CRangeStatus::Release(void)
{

}

void CRangeStatus::Motion_Change(void)
{

}

void CRangeStatus::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/hudstats.bmp", L"Status");

}

void CRangeStatus::First_State(void)
{
	m_pFrameKey = L"OwnItem";
	m_eState = BOMB;
	m_ePreState = BOMB;


	m_tFrame.iFrameStart = 3;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 10000000;
	m_tFrame.dwFrameTime = GetTickCount();

}
