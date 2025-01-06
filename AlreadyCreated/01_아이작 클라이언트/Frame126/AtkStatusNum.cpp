#include "stdafx.h"
#include "AtkStatusNum.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "Player.h"
CAtkStatusNum::CAtkStatusNum()
{
}


CAtkStatusNum::~CAtkStatusNum()
{
	Release();
}

void CAtkStatusNum::Initialize(void)
{
	m_tInfo.fX = 60.f;		// 중점 X
	m_tInfo.fY = 305.f;		// 중점 Y

	m_tInfo.fCX = 14.f;	//  가로 사이즈
	m_tInfo.fCY = 14.f;	//  세로 사이즈

	m_fSpeed = 100.f;

	m_iHP = CObjMgr::Get_Instance()->Get_Player()->Get_HP();
	m_iMaxHP = CObjMgr::Get_Instance()->Get_Player()->Get_MAXHP();
	m_eGroup = UI;

	m_fATKDMG = CObjMgr::Get_Instance()->Get_Player()->Get_ATKDMG();
	m_iBomb = CObjMgr::Get_Instance()->Get_Player()->Get_Bomb();
	Insert_Texture();

	//First_State();

}

int CAtkStatusNum::Update(void)
{
	m_iBomb = CObjMgr::Get_Instance()->Get_Player()->Get_Bomb();
	m_fATKDMG = CObjMgr::Get_Instance()->Get_Player()->Get_ATKDMG();

	if (m_iHP <= 0)
		m_bDead = true;


	if (true == m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	//get bomb
	//m_iHP = CObjMgr::Get_Instance()->Get_Player()->Get_HP();

	CountAtk();
	Motion_Change();
	Move_Frame();

	return OBJ_NOEVENT;
}

void CAtkStatusNum::Late_Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing('Q'))
		m_fAngle += 45.f;
}

void CAtkStatusNum::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Number");

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
		(int)m_tInfo.fCX+5.f,				// 4,5 인자 : 복사 받을 텍스처의 X, Y 사이즈	//크기 늘리기
		(int)m_tInfo.fCY+5.f,
		hMemDC,							// 6인자 : 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,			// 7, 8인자 : 비트맵을 출력할 시작 좌표
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9, 10인자 : 복사할 비트맵의 X,Y 사이즈	
		(int)m_tInfo.fCY,
		RGB(153, 217, 234));			// 11인자 : 제거하고자 하는 색상



}

void CAtkStatusNum::Release(void)
{

}

void CAtkStatusNum::Motion_Change(void)
{
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{

		case ONE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case ZERO:
			m_tFrame.iFrameStart = 1;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount() + 100000;
			break;
		case TWO:
			m_tFrame.iFrameStart = 2;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount() + 100000;
			break;
		case THREE:
			m_tFrame.iFrameStart = 3;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount() + 100000;
			break;
		case FOUR:
			m_tFrame.iFrameStart = 4;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount()+100000;
			break;
		case FIVE:
			m_tFrame.iFrameStart = 5;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount() + 100000;
			break;
		case SIX:
			m_tFrame.iFrameStart = 6;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount() + 100000;
			break;
		case SEVEN:
			m_tFrame.iFrameStart = 7;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case EIGHT:
			m_tFrame.iFrameStart = 8;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case NINE:
			m_tFrame.iFrameStart = 9;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		}

		m_ePreState = m_eState;
	}
}

void CAtkStatusNum::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Number1.bmp", L"Number");

}

void CAtkStatusNum::First_State(void)
{
	m_pFrameKey = L"Number";
	m_eState = ZERO;
	m_ePreState = ZERO;


	m_tFrame.iFrameStart = 1;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 10000000;
	m_tFrame.dwFrameTime = GetTickCount();

}

void CAtkStatusNum::CountAtk(void)
{
	float		fAtkCount = m_fATKDMG;

	if (fAtkCount == 0.f)
	{
		m_pFrameKey = L"Number";
		m_eState = ZERO;
	}
	else if (fAtkCount == 1.f)
	{
		m_pFrameKey = L"Number";
		m_eState = ONE;
	}
	else if (fAtkCount == 2.f)
	{
		m_pFrameKey = L"Number";
		m_eState = TWO;
	}
	else if (fAtkCount == 3.f)
	{
		m_pFrameKey = L"Number";
		m_eState = THREE;
	}
	else if (fAtkCount == 4.f)
	{
		m_pFrameKey = L"Number";
		m_eState = FOUR;
	}
	else if (fAtkCount == 5.f)
	{
		m_pFrameKey = L"Number";
		m_eState = FIVE;
	}
	else if (fAtkCount == 6.f)
	{
		m_pFrameKey = L"Number";
		m_eState = SIX;
	}
	else if (fAtkCount == 7.f)
	{
		m_pFrameKey = L"Number";
		m_eState = SEVEN;
	}
	else if (fAtkCount == 8.f)
	{
		m_pFrameKey = L"Number";
		m_eState = EIGHT;
	}
	else if (fAtkCount == 9.f)
	{
		m_pFrameKey = L"Number";
		m_eState = NINE;
	}
	else
	{
		return;
	}


}
