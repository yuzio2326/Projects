#include "stdafx.h"
#include "mutantspider.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
Cmutantspider::Cmutantspider()
{
}


Cmutantspider::~Cmutantspider()
{
	Release();
}

void Cmutantspider::Initialize(void)
{
	m_tInfo.fX = 200.f;		// 중점 X
	m_tInfo.fY = 200.f;		// 중점 Y

	m_tInfo.fCX = 32.f;	//  가로 사이즈
	m_tInfo.fCY = 32.f;	//  세로 사이즈

	m_fSpeed = 100.f;

	m_eGroup = GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/collectibles_153_mutantspider.bmp", L"mutantspider");




}

int Cmutantspider::Update(void)
{

	if (true == m_bDead)
	{
		CObjMgr::Get_Instance()->Get_Player()->Set_BulletNum(4);
		CObjMgr::Get_Instance()->Get_Player()->Set_ShotSpeed(+100);

		CSoundMgr::Get_Instance()->PlaySound(L"power up1.wav", SOUND_EFFECT, g_fSound);
		CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_EFFECT, g_fSound);

		return OBJ_DEAD;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void Cmutantspider::Late_Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing('Q'))
		m_fAngle += 45.f;
}

void Cmutantspider::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"mutantspider");

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

void Cmutantspider::Release(void)
{

}

void Cmutantspider::Motion_Change(void)
{

}

void Cmutantspider::Insert_Texture(void)
{
}

void Cmutantspider::First_State(void)
{
}
