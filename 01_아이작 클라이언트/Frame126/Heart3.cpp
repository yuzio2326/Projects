#include "stdafx.h"
#include "Heart3.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "Player.h"
#include "AbstactFactory.h"
CHeart3::CHeart3()
{
}


CHeart3::~CHeart3()
{
	Release();
}

void CHeart3::Initialize(void)
{
	m_tInfo.fX = 128.f;		// 중점 X
	m_tInfo.fY = 32.f;		// 중점 Y

	m_tInfo.fCX = 16.f;	//  가로 사이즈
	m_tInfo.fCY = 16.f;	//  세로 사이즈

	m_fSpeed = 100.f;

	m_iHP = CObjMgr::Get_Instance()->Get_Player()->Get_HP();
	m_iMaxHP = CObjMgr::Get_Instance()->Get_Player()->Get_MAXHP();
	m_eGroup = UI;

	Insert_Texture();

	First_State();

}

int CHeart3::Update(void)
{
	if (m_iMaxHP <= 8||m_iHP<=0)
		m_bDead = true;

	if (true == m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	//player hp 가져오기
	m_iMaxHP = CObjMgr::Get_Instance()->Get_Player()->Get_MAXHP();
	m_iHP = CObjMgr::Get_Instance()->Get_Player()->Get_HP();
	// hp status img change
	if (8 < m_iMaxHP)
	{
		if (m_iHP<=8)
		{
			m_pFrameKey = L"Heart";
			m_eState = EMPTY_HEART;
		}
		else if (8 < m_iHP&&m_iHP <=10 )
		{
			m_pFrameKey = L"Heart";
			m_eState = HALF_HEART;

		}
		else if (10 < m_iHP)
		{
			m_pFrameKey = L"Heart";
			m_eState = FULL_HEART;

		}

	}




	Motion_Change();
	Move_Frame();

	return OBJ_NOEVENT;
}

void CHeart3::Late_Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing('Q'))
		m_fAngle += 45.f;
}

void CHeart3::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Heart");



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

void CHeart3::Release(void)
{

}

void CHeart3::Motion_Change(void)
{
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{

		case FULL_HEART:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case HALF_HEART:
			m_tFrame.iFrameStart = 1;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		
		case EMPTY_HEART:
			m_tFrame.iFrameStart = 2;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		}

		m_ePreState = m_eState;
	}
}

void CHeart3::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/ui_hearts.bmp", L"Heart");

}

void CHeart3::First_State(void)
{
	//m_pFrameKey = L"Heart";
	//m_eState = FULL_HEART;
	//m_ePreState = FULL_HEART;

	//m_tFrame.iFrameStart = 0;
	//m_tFrame.iFrameEnd = 0;
	//m_tFrame.iFrameMotion = 0;
	//m_tFrame.dwFrameSpeed = 1000;
	//m_tFrame.dwFrameTime = GetTickCount();
}
