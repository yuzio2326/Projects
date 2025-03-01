#include "stdafx.h"
#include "Goblin.h"
#include "MonsterBullet.h"//눈물 생성처럼
#include "Shield.h"
#include "AbstactFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"


CGoblin::CGoblin()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CGoblin::~CGoblin()
{
	Release();
}

void CGoblin::Initialize(void)
{
	m_tInfo.fX = 200.f;		// 중점 X
	m_tInfo.fY = 200.f;		// 중점 Y

	m_tInfo.fCX = 64.f;	//  가로 사이즈
	m_tInfo.fCY = 64.f;	//  세로 사이즈

	m_fSpeed = 1.f;

	m_iHP = 15.f;
	dwLifeTime = GetTickCount();

	m_eGroup = GAMEOBJECT;

	Insert_Texture();
	First_State();

	//폭발음 넣기
	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Success.wav", SOUND_EFFECT, g_fSound);

}

int CGoblin::Update(void)
{

	if (true == m_bDead)
	{
		return OBJ_DEAD;
	}

	if (m_iHP <= 0)
		m_bDead = true;

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	if (m_pTarget)
	{
		float	fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
		float	fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		m_fAngle = acosf(fWidth / fDiagonal);

		// 굳이 라디안 각도를 디그리로 만들었음. 헷갈리지 말 것
		m_fAngle = m_fAngle * (180.f / PI);

		if (m_tInfo.fY < m_pTarget->Get_Info().fY)
			m_fAngle *= -1.f;
	}

	m_tInfo.fX += cosf(m_fAngle * (PI / 180.f)) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * (PI / 180.f)) * m_fSpeed;




	Run_Time();
	Motion_Change();
	Move_Frame();
	// 위쪽에서 중점 또는 사이즈의 변화를 끝낸 다음에 Update_Rect함수를 호출

	Update_Rect();

	return OBJ_NOEVENT;
}

void CGoblin::Late_Update(void)
{

}

void CGoblin::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = m_pBmpMgr->Find_Image(m_pFrameKey);
	HDC hStretchDC = m_pBmpMgr->Find_Image(L"Stretch");
	if (m_bStretch)
	{
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
			(int)m_tRect.left + iScrollX,	// 2,3인자 : 2, 3인자 : 복사 받을 위치의 좌표를 전달(L, T 좌표)
			(int)m_tRect.top + iScrollY,
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

void CGoblin::Release(void)
{

}


void CGoblin::Run_Time(void)
{
	if (5 < m_iHP) 
	{
		if ((m_tInfo.fX < m_pTarget->Get_Info().fX))
		{
			m_pFrameKey = L"Goblin";
			m_eState = RUNTIME;
			m_bStretch = true;
		}
		if ((m_pTarget->Get_Info().fX < m_tInfo.fX))
		{
			m_pFrameKey = L"Goblin";
			m_eState = RUNTIME;
			m_bStretch = false;
		}
	}
	else if (m_iHP <= 5 && dwLifeTime <= GetTickCount())
	{
		m_pFrameKey = L"Goblin";
		m_eState = STAY;
	}

}

void CGoblin::Motion_Change(void)
{
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{
		case STAY:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 2000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

			case REVIVAL1:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

			case REVIVAL2:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 1;
				m_tFrame.iFrameMotion = 1;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
				break;

			case REVIVAL3:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.iFrameMotion = 2;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
				break;

			case REVIVAL4:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.iFrameMotion = 3;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
				break;


			case RUNTIME:
				m_tFrame.iFrameStart = 3;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.iFrameMotion = 3;
				m_tFrame.dwFrameSpeed = 5000;
				m_tFrame.dwFrameTime = GetTickCount();
				break;


		}

		m_ePreState = m_eState;
	}
}

void CGoblin::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/monster_161_globin.bmp", L"Goblin");


}

void CGoblin::First_State(void)
{
	m_pFrameKey = L"Goblin";
	m_eState = RUNTIME;
	m_ePreState = RUNTIME;

	m_tFrame.iFrameStart = 3;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iFrameMotion = 3;
	m_tFrame.dwFrameSpeed = 5000;
	m_tFrame.dwFrameTime = GetTickCount();

}
