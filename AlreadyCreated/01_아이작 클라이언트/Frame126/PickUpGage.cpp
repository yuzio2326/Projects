#include "stdafx.h"
#include "PickUpGage.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "Player.h"
#include "AbstactFactory.h"
CPickUpGage::CPickUpGage()
{
}


CPickUpGage::~CPickUpGage()
{
	Release();
}

void CPickUpGage::Initialize(void)
{
	m_tInfo.fX = 32.f;		// 중점 X
	m_tInfo.fY = 32.f;		// 중점 Y

	m_tInfo.fCX = 16.f;	//  가로 사이즈
	m_tInfo.fCY = 16.f;	//  세로 사이즈

	m_fSpeed = 100.f;

	m_iCoin = CObjMgr::Get_Instance()->Get_Player()->Get_Coin();
	m_eGroup = UI;

	m_iGage = 1;

	Insert_Texture();

	First_State();

}

int CPickUpGage::Update(void)
{

	if (true == m_bDead)
		return OBJ_DEAD;

	m_iCoin = CObjMgr::Get_Instance()->Get_Player()->Get_Coin();

	Update_Rect();

	//player hp 가져오기
	Key_input();
	

	Motion_Change();
	Move_Frame();

	return OBJ_NOEVENT;
}

void CPickUpGage::Late_Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing('Q'))
		m_fAngle += 45.f;
}

void CPickUpGage::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ChargeBar");



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

void CPickUpGage::Release(void)
{

}

void CPickUpGage::Motion_Change(void)
{
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{

		case FULL:
			m_tFrame.iFrameStart = 1;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 1000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		
		case EMPTY:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 1000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		}

		m_ePreState = m_eState;
	}
}

void CPickUpGage::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/ui_chargebar.bmp", L"ChargeBar");

}

void CPickUpGage::First_State(void)
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

void CPickUpGage::Key_input(void)
{

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE) )
	{
		if (m_iGage==1)
		{

			m_iGage = 0;
		}
		else
		{
			return;
		}

	}
}
