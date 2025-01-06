#include "stdafx.h"
#include "PickupCoin.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "AbstactFactory.h"
#include "SoundMgr.h"

CPickupCoin::CPickupCoin()
{
}


CPickupCoin::~CPickupCoin()
{
	Release();
}

void CPickupCoin::Initialize(void)
{
	m_tInfo.fX = 200.f;		// 중점 X
	m_tInfo.fY = 300.f;		// 중점 Y

	m_tInfo.fCX = 32.f;	//  가로 사이즈
	m_tInfo.fCY = 16.f;	//  세로 사이즈

	m_fSpeed = 100.f;

	m_eGroup = GAMEOBJECT;

	dw_Tincle = GetTickCount();
	
	Insert_Texture();
	First_State();

	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Item/boss explosions 0.wav", SOUND_EFFECT, g_fSound);

}

int CPickupCoin::Update(void)
{

	if (true == m_bDead)
	{
		CObjMgr::Get_Instance()->Get_Player()->Set_Coin(1);
		CSoundMgr::Get_Instance()->PlaySound(L"penny pickup 1.wav", SOUND_COIN, g_fSound);
		CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_COIN, g_fSound);

		return OBJ_DEAD;
	}

	if (dw_Tincle + 100 < GetTickCount())
	{
		m_pFrameKey = L"PickupCoin";
		m_eState = IDLE;
	}
	if (dw_Tincle + 300 < GetTickCount())
	{
		m_pFrameKey = L"PickupCoin";
		m_eState = TINCLE;
	}
	if (dw_Tincle + 500 < GetTickCount())
	{
		m_pFrameKey = L"PickupCoin";
		m_eState = TINCLE2;
	}
	if (dw_Tincle + 600 < GetTickCount())
	{
		m_pFrameKey = L"PickupCoin";
		m_eState = TINCLE_END;
	}
	if (dw_Tincle + 3000 < GetTickCount())
		dw_Tincle = GetTickCount();

	Motion_Change();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPickupCoin::Late_Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing('Q'))
		m_fAngle += 45.f;
}

void CPickupCoin::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PickupCoin");

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
		RGB(195, 195, 195));			// 11인자 : 제거하고자 하는 색상



}

void CPickupCoin::Release(void)
{

}

void CPickupCoin::Motion_Change(void)
{
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{

		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case TINCLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameMotion = 1;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case TINCLE2:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameMotion = 2;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case TINCLE_END:
			m_tFrame.iFrameStart = 1;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameMotion = 2;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		}
	}

}

void CPickupCoin::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/pickup_002_coin.bmp", L"PickupCoin");

}

void CPickupCoin::First_State(void)
{
	m_pFrameKey = L"PickupCoin";
	m_eState = IDLE;
	m_ePreState = IDLE;

	m_tFrame.iFrameStart = 1;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iFrameMotion = 2;
	m_tFrame.dwFrameSpeed = 20;
	m_tFrame.dwFrameTime = GetTickCount();
}
