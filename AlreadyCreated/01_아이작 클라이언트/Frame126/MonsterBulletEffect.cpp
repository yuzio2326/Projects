#include "stdafx.h"
#include "MonsterBulletEffect.h"
#include "Explosion.h"//눈물 생성처럼
#include "Shield.h"
#include "AbstactFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"


CMonsterBulletEffect::CMonsterBulletEffect()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CMonsterBulletEffect::~CMonsterBulletEffect()
{
	Release();
}

void CMonsterBulletEffect::Initialize(void)
{
	//bullet의 공격력 가지고와서 그만큼 크기 늘리기
	m_tInfo.fCX = 64.f;	//  가로 사이즈
	m_tInfo.fCY = 64.f;	//  세로 사이즈

	

	dwLifeTime = GetTickCount();

	m_eGroup = EFFECT;

	Insert_Texture();
	First_State();

	//효과음 넣기
	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Success.wav", SOUND_EFFECT, g_fSound);

}

int CMonsterBulletEffect::Update(void)
{

	if (true == m_bDead)
	{

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

void CMonsterBulletEffect::Late_Update(void)
{


}

void CMonsterBulletEffect::Render(HDC hDC)
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

void CMonsterBulletEffect::Release(void)
{

}


void CMonsterBulletEffect::Run_Time(void)
{

	//if (dwLifeTime + 100 <= GetTickCount())
	//{
	//	m_pFrameKey = L"BOMB";
	//	m_eState = RUNTIME;
	//}


	if (dwLifeTime + 320 <= GetTickCount())
	{
		m_bDead = true;
	}

}

void CMonsterBulletEffect::Motion_Change(void)
{

}

void CMonsterBulletEffect::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/MonsterBulletpop.bmp", L"MonsterBulletEffect");


}

void CMonsterBulletEffect::First_State(void)
{
	m_pFrameKey = L"MonsterBulletEffect";
	m_eState = RUNTIME;
	m_ePreState = RUNTIME;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 15;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 20;
	m_tFrame.dwFrameTime = GetTickCount();

}
