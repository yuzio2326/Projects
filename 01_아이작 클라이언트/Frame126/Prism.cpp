#include "stdafx.h"
#include "Prism.h"
#include "Explosion.h"//눈물 생성처럼
#include "Shield.h"
#include "AbstactFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "PlayerBullet.h"


CPrism::CPrism()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CPrism::~CPrism()
{
	Release();
}

void CPrism::Initialize(void)
{
	m_tInfo.fX = 200.f;		// 중점 X
	m_tInfo.fY = 100.f;		// 중점 Y

	m_tInfo.fCX = 32.f;	//  가로 사이즈
	m_tInfo.fCY = 32.f;	//  세로 사이즈

	m_fSpeed = 1.f;

	dwLifeTime = GetTickCount();

	m_fPrismDistance = 50.f;

	m_eGroup = FAMILIAR;

	Insert_Texture();
	First_State();

	//폭발음 넣기
	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Success.wav", SOUND_EFFECT, g_fSound);

}

int CPrism::Update(void)
{

	if (true == m_bDead)
	{
		return OBJ_DEAD;
	}

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	if (m_pTarget)
	{
		m_fAngle -= m_fSpeed;
		//움직이는 프리즘의 위치는 플레이어의 위치 XY를 받아 구 형태로 움직인다.
		m_tInfo.fX = long(m_pTarget->Get_Info().fX + cosf(m_fAngle * (PI / 180.f)) * m_fPrismDistance);
		m_tInfo.fY = long(m_pTarget->Get_Info().fY - sinf(m_fAngle * (PI / 180.f)) * m_fPrismDistance);

	}
	
	//prism과 bullet 처리
	m_pTargetBullet = CObjMgr::Get_Instance()->Get_Target(OBJ_BULLET, this);

	//bullet이 있을때
	if (m_pTargetBullet)
	{

		//내가 원하는건 bullet하고 prism 사이의 각도를 원하는거임

		//bullet의 방향을 받고
		float	fWidth = fabs(m_pTargetBullet->Get_Info().fX - m_tInfo.fX);
		float	fHeight = fabs(m_pTargetBullet->Get_Info().fY - m_tInfo.fY);
		/*
		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
		m_fDistanceAngle = atan2(m_pTargetBullet->Get_Info().fY - m_tInfo.fY, m_pTargetBullet->Get_Info().fX - m_tInfo.fX);
			//(fWidth / fDiagonal);

		m_fDistanceAngle = m_fDistanceAngle * (180.f / PI);

		if (m_tInfo.fY < m_pTargetBullet->Get_Info().fY)
			m_fDistanceAngle *= -1.f;

		m_tInfo.fX += cosf(m_fAngle * (PI / 180.f)) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle * (PI / 180.f)) * m_fSpeed;


		*/
		float	fBCX = (m_pTargetBullet->Get_Info().fCX + m_tInfo.fCX)*0.5f;
		float	fBCY = (m_pTargetBullet->Get_Info().fCY + m_tInfo.fCY)*0.5f;


		if ((fBCX > fWidth) && (fBCY > fHeight))
		{

			CObjMgr::Get_Instance()->AddObject(OBJ_ITEM_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle + 10.f));
			CObjMgr::Get_Instance()->AddObject(OBJ_ITEM_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle - 30.f));
			CObjMgr::Get_Instance()->AddObject(OBJ_ITEM_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle - 10.f));
			CObjMgr::Get_Instance()->AddObject(OBJ_ITEM_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle + 30.f));
				
			//앵글 및 위치값에 따른 계산을 끝내고 target이 된 bullet을 삭제
			m_pTargetBullet->Set_Dead();
		}


	}

	




	Run_Time();
	Motion_Change();
	Move_Frame();
	// 위쪽에서 중점 또는 사이즈의 변화를 끝낸 다음에 Update_Rect함수를 호출

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPrism::Late_Update(void)
{

}

void CPrism::Render(HDC hDC)
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
		RGB(195, 195, 195));			// 11인자 : 제거하고자 하는 색상

}

void CPrism::Release(void)
{

}


void CPrism::Run_Time(void)
{


}

void CPrism::Motion_Change(void)
{
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{

		case RUNTIME:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		}

		m_ePreState = m_eState;
	}
}

void CPrism::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Familar/familiar_123_angelic_prism.bmp", L"Prism");


}

void CPrism::First_State(void)
{
	m_pFrameKey = L"Prism";
	m_eState = RUNTIME;
	m_ePreState = RUNTIME;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 11;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

}
