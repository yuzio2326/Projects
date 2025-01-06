#include "stdafx.h"
#include "IsaacForm.h"
#include "Explosion.h"//눈물 생성처럼
#include "BossIsaacPhase2.h"
#include "AbstactFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"


CIsaacForm::CIsaacForm()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CIsaacForm::~CIsaacForm()
{
	Release();
}

void CIsaacForm::Initialize(void)
{
	//bullet의 공격력 가지고와서 그만큼 크기 늘리기
	m_tInfo.fCX = 80.f;	//  가로 사이즈
	m_tInfo.fCY = 60.f;	//  세로 사이즈

	

	dwLifeTime = GetTickCount();

	m_eGroup = EFFECT;

	Insert_Texture();
	First_State();

	//효과음 넣기
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/holy!.wav", SOUND_EFFECT, g_fSound);
	CSoundMgr::Get_Instance()->PlaySound(L"holy!.wav", SOUND_ITEM_EFFECT, g_fSound);

}

int CIsaacForm::Update(void)
{

	if (true == m_bDead)
	{
		CObjMgr::Get_Instance()->AddObject(OBJ_FYING_MONSTER, CAbstactFactory<CBossIsaacPhase2>::Create(m_tInfo.fX, m_tInfo.fY, 0));
		return OBJ_DEAD;
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

void CIsaacForm::Late_Update(void)
{


}

void CIsaacForm::Render(HDC hDC)
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

void CIsaacForm::Release(void)
{

}


void CIsaacForm::Run_Time(void)
{

	//if (dwLifeTime + 100 <= GetTickCount())
	//{
	//	m_pFrameKey = L"BOMB";
	//	m_eState = RUNTIME;
	//}
	if (dwLifeTime + 500 <= GetTickCount())
	{
		m_pFrameKey = L"BossIsaac";
		m_eState = CHANGE;
	}

	if (dwLifeTime + 800 <= GetTickCount())
	{
		m_bDead = true;
	}

}

void CIsaacForm::Motion_Change(void)
{
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{

		case READY:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameMotion = 2;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CHANGE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameMotion = 3;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;;

		}

		m_ePreState = m_eState;
	}
}

void CIsaacForm::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/boss_075_isaac.bmp", L"BossIsaac");

}

void CIsaacForm::First_State(void)
{
	m_pFrameKey = L"BossIsaac";
	m_eState = READY;
	m_ePreState = READY;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameMotion = 2;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();

}
