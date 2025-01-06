#include "stdafx.h"
#include "Bomb.h"
#include "Explosion.h"//눈물 생성처럼
#include "Shield.h"
#include "AbstactFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"


CBomb::CBomb()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CBomb::~CBomb()
{
	Release();
}

void CBomb::Initialize(void)
{
	//m_tInfo.fX = 200.f;		// 중점 X
	//m_tInfo.fY = 100.f;		// 중점 Y

	m_tInfo.fCX = 32.f;	//  가로 사이즈
	m_tInfo.fCY = 32.f;	//  세로 사이즈

	m_fSpeed = 1.f;

	dwLifeTime = GetTickCount();
	
	m_eGroup = GAMEOBJECT;

	Insert_Texture();
	First_State();
	
	//폭발음 넣기
	CSoundMgr::Get_Instance()->PlaySoundW(L"firedeath hiss.wav", SOUND_BGM, g_fSound);
	//CSoundMgr::Get_Instance()->PlaySoundW(L"boss explosions 0.wav", SOUND_EFFECT, g_fSound);
	CSoundMgr::Get_Instance()->PlaySound(L"firedeath hiss.wav", SOUND_ITEM_EFFECT, g_fSound);

	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Success.wav", SOUND_EFFECT, g_fSound);
	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Item/boss explosions 0.wav", SOUND_EFFECT, g_fSound);
}

int CBomb::Update(void)
{

	if (true == m_bDead)
	{
		CObjMgr::Get_Instance()->AddObject(OBJ_EXPLOSION, CAbstactFactory<CExplosion>::Create(m_tInfo.fX, m_tInfo.fY, 0));
	/*	CSoundMgr::Get_Instance()->PlaySound(L"boss explosions 0.wav", SOUND_EFFECT, g_fSound);
		CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_EFFECT, g_fSound);
*/
		return OBJ_DEAD;
	}

	Run_Time();

	Motion_Change();

	Move_Frame();
	// 위쪽에서 중점 또는 사이즈의 변화를 끝낸 다음에 Update_Rect함수를 호출

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBomb::Late_Update(void)
{
	
}

void CBomb::Render(HDC hDC)
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

void CBomb::Release(void)
{

}


void CBomb::Run_Time(void)
{

	//if (dwLifeTime + 100 <= GetTickCount())
	//{
	//	m_pFrameKey = L"BOMB";
	//	m_eState = RUNTIME;
	//}
	if (dwLifeTime + 1000 <= GetTickCount())
	{
		m_pFrameKey = L"BOMB";
		m_eState = BIG;
	}


	if (dwLifeTime + 2000 <= GetTickCount())
		m_bDead = true;

}

void CBomb::Motion_Change(void)
{
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{

		case RUNTIME:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case BIG:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}

		m_ePreState = m_eState;
	}
}

void CBomb::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/balloon_bomb.bmp", L"BOMB");


}

void CBomb::First_State(void)
{
	m_pFrameKey = L"BOMB";
	m_eState = RUNTIME;
	m_ePreState = RUNTIME;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

}
