#include "stdafx.h"
#include "Tears.h"
#include "Bullet.h"
#include "Shield.h"
#include "AbstactFactory.h"
#include "ScrewBullet.h"
#include "ObjMgr.h"
#include "GuideBullet.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"



CTears::CTears()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CTears::~CTears()
{
	Release();
}

void CTears::Initialize(void)
{
	m_tInfo.fX = 100.f;		// 중점 X
	m_tInfo.fY = 100.f;		// 중점 Y

	m_tInfo.fCX = 64.f;	// 플레이어 가로 사이즈
	m_tInfo.fCY = 64.f;	// 플레이어 세로 사이즈

	m_fSpeed = 1.f;

	m_eGroup = GAMEOBJECT;

	Insert_Texture();
	First_State();

	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Success.wav", SOUND_EFFECT, g_fSound);
	
}

int CTears::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	Motion_Change();

	// 위쪽에서 중점 또는 사이즈의 변화를 끝낸 다음에 Update_Rect함수를 호출
	Move_Frame();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CTears::Late_Update(void)
{

}

void CTears::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX(); 
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = m_pBmpMgr->Find_Image(m_pFrameKey);
	HDC hStretchDC = m_pBmpMgr->Find_Image(L"Stretch");

	//BitBlt(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tInfo.fCX, m_tInfo.fCY, hMemDC, 0, 0, SRCCOPY);
	// 1인자 : 복사 받을 최종적으로 그림을 그릴 DC
	// 2, 3인자 : 복사 받을 위치의 좌표를 전달(L, T 좌표)
	// 4, 5인자 : 복사 받을 텍스처의 X, Y 사이즈
	// 6 인자 : 비트맵을 가지고 있는 DC
	// 7, 8인자 : 비트맵을 출력할 시작 좌표(L, T좌표)
	// 9인자 : 출력 효과를 설정 SRCCOPY : 그대로 출력
	if (m_bStretch)
	{

	GdiTransparentBlt(hDC,							// 1인자 : 복사 받을 최종적으로 그림을 그릴 DC
		(int)m_tRect.left + iScrollX-1.f,	// 2,3인자 : 2, 3인자 : 복사 받을 위치의 좌표를 전달(L, T 좌표)
		(int)m_tRect.top + iScrollY + 9.f,
		(int)m_tInfo.fCX,				// 4,5 인자 : 복사 받을 텍스처의 X, Y 사이즈
		(int)m_tInfo.fCY ,
		hMemDC,							// 6인자 : 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,			// 7, 8인자 : 비트맵을 출력할 시작 좌표
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9, 10인자 : 복사할 비트맵의 X,Y 사이즈	
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));
	}
	else
	{
		StretchBlt(hStretchDC,	// 출력할 이미지 핸들
			0,			// 2, 3인자 : 복사 받을 위치의 좌표를 전달(L, T 좌표)
			0,
			m_tInfo.fCX,	// 4, 5인자 : 출력할 이미지 사이즈
			m_tInfo.fCY,
			hMemDC,			// 6인자 : 반전해서 출력하고자 하는 텍스처 이미지 핸들
			m_tFrame.iFrameStart * (int)m_tInfo.fCX + m_tInfo.fCX, // 7,8인자 : 가져올 이미지의 시작점 x,y 좌표
			m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
			-m_tInfo.fCX,
			m_tInfo.fCY,
			SRCCOPY);

		GdiTransparentBlt(hDC,							// 1인자 : 복사 받을 최종적으로 그림을 그릴 DC
			(int)m_tRect.left + iScrollX-1.f,	// 2,3인자 : 2, 3인자 : 복사 받을 위치의 좌표를 전달(L, T 좌표)
			(int)m_tRect.top + iScrollY + 9.f,
			(int)m_tInfo.fCX,				// 4,5 인자 : 복사 받을 텍스처의 X, Y 사이즈	//크기 늘리기
			(int)m_tInfo.fCY,
			hStretchDC,							// 6인자 : 비트맵을 가지고 있는 DC
			0,						// 7, 8인자 : 비트맵을 출력할 시작 좌표
			0,
			(int)m_tInfo.fCX,		// 9, 10인자 : 복사할 비트맵의 X,Y 사이즈	
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));			// 11인자 : 제거하고자 하는 색상
	}
}

void CTears::Release(void)
{
	
}


void CTears::Motion_Change(void)
{		
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{
		case IDLE:
			m_tFrame.iFrameStart	= 0;
			m_tFrame.iFrameEnd		= 0;
			m_tFrame.iFrameMotion	= 0;
			m_tFrame.dwFrameSpeed	= 500;
			m_tFrame.dwFrameTime    = GetTickCount();
			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 500;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		}

		m_ePreState = m_eState;
	}
}

void CTears::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/poptears.bmp", L"Tears");
}

void CTears::First_State(void)
{
	m_pFrameKey = L"Tears";
	m_eState = IDLE;
	m_ePreState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 500;
	m_tFrame.dwFrameTime = GetTickCount();
}
