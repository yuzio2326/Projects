#include "stdafx.h"
#include "BossIsaacPhase2.h"
#include "MonsterBullet.h"//눈물 생성처럼
#include "IsaacForm.h"
#include "AbstactFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "SceneMgr.h"


CBossIsaacPhase2::CBossIsaacPhase2()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CBossIsaacPhase2::~CBossIsaacPhase2()
{
	Release();
}

void CBossIsaacPhase2::Initialize(void)
{
	m_tInfo.fX = 400.f;		// 중점 X
	m_tInfo.fY = 300.f;		// 중점 Y

	m_tInfo.fCX = 64.f;	//  가로 사이즈
	m_tInfo.fCY = 60.f;	//  세로 사이즈

	m_fSpeed = 1.5f;

	m_iHP = 150.f;
	dwChangeATK = GetTickCount();
	dwATKTime1 = GetTickCount();
	dwATKTime2 = GetTickCount();
	dwAtkStart = GetTickCount();
	t_fAngle = 0;

	m_eGroup = GAMEOBJECT;

	Insert_Texture();
	First_State();

	iRandMontion = 0;
	//폭발음 넣기
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlaySound(L"isaac fight.ogg", SOUND_BGM, g_fSound);

}

int CBossIsaacPhase2::Update(void)
{

	if (true == m_bDead)
	{
		//CSceneMgr::Get_Instance()->Scene_Change(SCENE_CREDIT);

		return OBJ_DEAD;
	}
	CSoundMgr::Get_Instance()->PlaySoundW(L"isaac fight.ogg", SOUND_BGM, g_fSound);


	if (m_iHP <= 0)
		m_bDead = true;

	if (dwAtkStart + 8000 < GetTickCount())
	{
		iRandMontion = rand() % 3;
		dwAtkStart = GetTickCount();
	}

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	//player 추격 관련 함수
	

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

	




	Run_Time();
	Motion_Change();
	Move_Frame();
	// 위쪽에서 중점 또는 사이즈의 변화를 끝낸 다음에 Update_Rect함수를 호출

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBossIsaacPhase2::Late_Update(void)
{

}

void CBossIsaacPhase2::Render(HDC hDC)
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

void CBossIsaacPhase2::Release(void)
{
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/holy!.wav", SOUND_EFFECT, g_fSound);
	CSoundMgr::Get_Instance()->PlaySound(L"holy!.wav", SOUND_ITEM_EFFECT, g_fSound);

}


void CBossIsaacPhase2::Run_Time(void)
{

	if (iRandMontion == 0)
	{
		m_tInfo.fX += cosf(m_fAngle * (PI / 180.f)) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle * (PI / 180.f)) * m_fSpeed;

		if (dwChangeATK +4000< GetTickCount())
		{
			//m_fSpeed = 0;
			//0.4~ 부터 실행
			if (dwATKTime1  <= GetTickCount())
			{
				//*자
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 0));
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 90));
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 180));
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 270));
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 45));
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 135));
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 225));
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 315));

				dwATKTime1 = GetTickCount() + 350;
			}

			m_pFrameKey = L"BossIsaac";
			m_eState = FLYING;
		}
		if(dwChangeATK + 8000 < GetTickCount())
		{
			m_fSpeed = 1.5f;
			dwChangeATK = GetTickCount();
		}
	}

	if (iRandMontion == 1)
	{
		m_fSpeed = 1.5f;
				m_tInfo.fX += cosf(m_fAngle * (PI / 180.f)) * m_fSpeed;
				m_tInfo.fY -= sinf(m_fAngle * (PI / 180.f)) * m_fSpeed;
			
		if (dwChangeATK + 4000 < GetTickCount())
		{
			if (dwATKTime1 + 200 < GetTickCount())
			{
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
				dwATKTime1 = GetTickCount();

			}

			m_pFrameKey = L"BossIsaac";
			m_eState = STANDFLY;
		}
		if (dwChangeATK + 8000 < GetTickCount())
			dwChangeATK = GetTickCount();

	}

	if (iRandMontion == 2)
	{
	
		m_tInfo.fX += cosf(m_fAngle * (PI / 180.f)) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle * (PI / 180.f)) * m_fSpeed;

		if (dwChangeATK + 4000 < GetTickCount())
		{
			m_fSpeed = 0;
				t_fAngle+=30.f;
			if (dwATKTime1 + 300 < GetTickCount())
			{
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, t_fAngle));
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, t_fAngle+90.f));
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, t_fAngle+180.f));
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, t_fAngle+270.f));
				dwATKTime1 = GetTickCount();
			}
		}

		if (dwChangeATK + 8000 < GetTickCount())
		{
			m_fSpeed = 1.5f;
			dwChangeATK = GetTickCount();
		}
	}

}

void CBossIsaacPhase2::Motion_Change(void)
{
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{

		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case FLYING:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameMotion = 4;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case STANDFLY:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameMotion = 4;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case DEAD:
			m_tFrame.iFrameStart = 3;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameMotion = 2;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		}

		m_ePreState = m_eState;
	}
}

void CBossIsaacPhase2::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/boss_075_isaac.bmp", L"BossIsaac");


}

void CBossIsaacPhase2::First_State(void)
{
	m_pFrameKey = L"BossIsaac";
	m_eState = IDLE;
	m_ePreState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iFrameMotion = 4;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

}
