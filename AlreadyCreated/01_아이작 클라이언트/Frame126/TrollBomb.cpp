#include "stdafx.h"
#include "TrollBomb.h"
#include "Explosion.h"//눈물 생성처럼
#include "Shield.h"
#include "AbstactFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"


CTrollBomb::CTrollBomb()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CTrollBomb::~CTrollBomb()
{
	Release();
}

void CTrollBomb::Initialize(void)
{
	m_tInfo.fX = 200.f;		// 중점 X
	m_tInfo.fY = 100.f;		// 중점 Y

	m_tInfo.fCX = 32.f;	//  가로 사이즈
	m_tInfo.fCY = 32.f;	//  세로 사이즈

	m_fSpeed = 3.f;

	dwLifeTime = GetTickCount();
	
	m_eGroup = GAMEOBJECT;

	Insert_Texture();
	First_State();
	
	//폭발음 넣기
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Item/firedeath hiss.wav", SOUND_EFFECT, g_fSound);

}

int CTrollBomb::Update(void)
{

	if (true == m_bDead)
	{
		CObjMgr::Get_Instance()->AddObject(OBJ_EXPLOSION, CAbstactFactory<CExplosion>::Create(m_tInfo.fX, m_tInfo.fY, 0));
		return OBJ_DEAD;
	}

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	//player 추격 관련 함수
	{

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
	}


	Run_Time();

	Motion_Change();

	Move_Frame();
	// 위쪽에서 중점 또는 사이즈의 변화를 끝낸 다음에 Update_Rect함수를 호출

	Update_Rect();

	return OBJ_NOEVENT;
}

void CTrollBomb::Late_Update(void)
{
	
}

void CTrollBomb::Render(HDC hDC)
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

void CTrollBomb::Release(void)
{

}


void CTrollBomb::Run_Time(void)
{

	//if (dwLifeTime + 100 <= GetTickCount())
	//{
	//	m_pFrameKey = L"BOMB";
	//	m_eState = RUNTIME;
	//}
	if (dwLifeTime + 2000 <= GetTickCount())
	{
		m_pFrameKey = L"TrollBomb";
		m_eState = BIG;
	}


	if (dwLifeTime + 1000 <= GetTickCount())
		m_bDead = true;

}

void CTrollBomb::Motion_Change(void)
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
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}

		m_ePreState = m_eState;
	}
}

void CTrollBomb::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/TrollBombbmp.bmp", L"TrollBomb");


}

void CTrollBomb::First_State(void)
{
	m_pFrameKey = L"TrollBomb";
	m_eState = RUNTIME;
	m_ePreState = RUNTIME;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

}
