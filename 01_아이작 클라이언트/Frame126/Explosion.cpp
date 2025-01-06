#include "stdafx.h"
#include "Explosion.h"
#include "Shield.h"
#include "AbstactFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"


CExplosion::CExplosion()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CExplosion::~CExplosion()
{
	Release();
}

void CExplosion::Initialize(void)
{
	m_tInfo.fX = 200.f;		// 중점 X
	m_tInfo.fY = 100.f;		// 중점 Y

	m_tInfo.fCX = 98.f;	//  가로 사이즈
	m_tInfo.fCY = 100.f;	//  세로 사이즈

	m_fSpeed = 1.f;

	dwLifeTime = GetTickCount();

	m_eGroup = EFFECT;

	Insert_Texture();
	First_State();

	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Item/boss explosions 0.wav", SOUND_EFFECT, g_fSound);
}

int CExplosion::Update(void)
{



	if (true == m_bDead)
	{
		//CObjMgr::Get_Instance()->AddObject(OBJ_EXPLOSION, CAbstactFactory<CExplosion>::Create(m_tInfo.fX, m_tInfo.fY, 0));
		return OBJ_DEAD;
	}


	//update sound
	CSoundMgr::Get_Instance()->PlaySoundW(L"boss explosions 0.wav", SOUND_EFFECT, g_fSound);
	CSoundMgr::Get_Instance()->PlaySound(L"boss explosions 0.wav", SOUND_ITEM_EFFECT, g_fSound);
	CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_ITEM_EFFECT, g_fSound);


	Run_Time();

	Motion_Change();

	// 위쪽에서 중점 또는 사이즈의 변화를 끝낸 다음에 Update_Rect함수를 호출
	Move_Frame();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CExplosion::Late_Update(void)
{

}

void CExplosion::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = m_pBmpMgr->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,							// 1인자 : 복사 받을 최종적으로 그림을 그릴 DC
		(int)m_tRect.left + iScrollX,	// 2,3인자 : 2, 3인자 : 복사 받을 위치의 좌표를 전달(L, T 좌표)
		(int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,				// 4,5 인자 : 복사 받을 텍스처의 X, Y 사이즈
		(int)m_tInfo.fCY,
		hMemDC,							// 6인자 : 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,			// 7, 8인자 : 비트맵을 출력할 시작 좌표
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9, 10인자 : 복사할 비트맵의 X,Y 사이즈	
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));			// 11인자 : 제거하고자 하는 색상

}

void CExplosion::Release(void)
{

}


void CExplosion::Run_Time(void)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	float	fY = 0.f;
	//if (dwLifeTime + 100 <= GetTickCount())
	//{
	//	m_pFrameKey = L"BOMB";
	//	m_eState = RUNTIME;
	//}
	if (dwLifeTime <= GetTickCount())
	{
		m_pFrameKey = L"Explosion";
		m_eState = EXPLO;
	}


	if (dwLifeTime + 100 <= GetTickCount())
		m_bDead = true;

}

void CExplosion::Motion_Change(void)
{
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{

		case EXPLO:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 20;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}

		m_ePreState = m_eState;
	}
}

void CExplosion::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/effect_029_explosion.bmp", L"Explosion");


}

void CExplosion::First_State(void)
{
	m_pFrameKey = L"Explosion";
	m_eState = EXPLO;
	m_ePreState = EXPLO;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 11;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 20;
	m_tFrame.dwFrameTime = GetTickCount();

}
