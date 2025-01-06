#include "stdafx.h"
#include "Monster.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"

CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
	m_tInfo.fX = 400.f;		// 중점 X
	m_tInfo.fY = 200.f;		// 중점 Y

	m_tInfo.fCX = 100.f;	// 플레이어 가로 사이즈
	m_tInfo.fCY = 60.f;	// 플레이어 세로 사이즈

	m_iHP = 5.f;	

	m_fSpeed = -0.5f;
	
	m_eGroup = GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/megasatan1.bmp", L"Monster");


	

}

int CMonster::Update(void)
{

	if (m_iHP <= 0)
		m_bDead = true;


	if (true == m_bDead)
		return OBJ_DEAD;
	
	Update_Rect();
	m_tInfo.fX += m_fSpeed;
	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing('Q'))
		m_fAngle += 1.f;
}

void CMonster::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Monster");
	
	//BitBlt(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tInfo.fCX, m_tInfo.fCY, hMemDC, 0, 0, SRCCOPY);
	// 1인자 : 복사 받을 최종적으로 그림을 그릴 DC
	// 2, 3인자 : 복사 받을 위치의 좌표를 전달(L, T 좌표)
	// 4, 5인자 : 복사 받을 텍스처의 X, Y 사이즈
	// 6 인자 : 비트맵을 가지고 있는 DC
	// 7, 8인자 : 비트맵을 출력할 시작 좌표(L, T좌표)
	// 9인자 : 출력 효과를 설정 SRCCOPY : 그대로 출력
		GdiTransparentBlt(hDC,							// 1인자 : 복사 받을 최종적으로 그림을 그릴 DC
			(int)m_tRect.left ,	// 2,3인자 : 2, 3인자 : 복사 받을 위치의 좌표를 전달(L, T 좌표)
			(int)m_tRect.top ,
			(int)m_tInfo.fCX,				// 4,5 인자 : 복사 받을 텍스처의 X, Y 사이즈	//크기 늘리기
			(int)m_tInfo.fCY,
			hMemDC,							// 6인자 : 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,			// 7, 8인자 : 비트맵을 출력할 시작 좌표
			m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,		// 9, 10인자 : 복사할 비트맵의 X,Y 사이즈	
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));			// 11인자 : 제거하고자 하는 색상

	

}

void CMonster::Release(void)
{
	
}

void CMonster::Motion_Change(void)
{

}

void CMonster::Insert_Texture(void)
{
}

void CMonster::First_State(void)
{
}
