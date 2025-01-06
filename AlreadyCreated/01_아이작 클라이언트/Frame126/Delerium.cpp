#include "stdafx.h"
#include "Delerium.h"
#include "MonsterBullet.h"//눈물 생성처럼
#include "IsaacForm.h"
#include "AbstactFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "SceneMgr.h"
#include "MonsterInclude.h"
#include "Explosion.h"

CDelerium::CDelerium()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CDelerium::~CDelerium()
{
	Release();
}

void CDelerium::Initialize(void)
{
	m_tInfo.fX = 400.f;		// 중점 X
	m_tInfo.fY = 300.f;		// 중점 Y

	//m_tInfo.fCX = 163.f;	//  가로 사이즈
	//m_tInfo.fCY = 150.f;	//  세로 사이즈

	m_fSpeed = 1.5f;

	m_iHP = 100;
	dwChangeATK = GetTickCount();
	dwATKTime1 = GetTickCount();
	dwATKTime2 = GetTickCount();
	dwAtkStart = GetTickCount();
	t_fAngle = 0;

	m_eGroup = FLYMONSTER;

	Insert_Texture();
	First_State();

	iRandMontion = 0;
	//폭발음 넣기
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlaySound(L"delirium fight.ogg", SOUND_BGM, g_fSound);
}

int CDelerium::Update(void)
{

	if (true == m_bDead)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SCENE_CREDIT);

		return OBJ_DEAD;
	}
	CSoundMgr::Get_Instance()->PlaySoundW(L"delirium fight.ogg", SOUND_BGM, g_fSound);


	if (m_iHP <= 0)
		m_bDead = true;

	if (dwAtkStart + 5000 < GetTickCount())
	{
		iRandMontion = rand() % 5;
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

void CDelerium::Late_Update(void)
{

}

void CDelerium::Render(HDC hDC)
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

void CDelerium::Release(void)
{

}


void CDelerium::Run_Time(void)
{


	//공격 타입 0일 때 원래 모습에 1초동안
	//m_tInfo.fCX = 163.f;	//  가로 사이즈 복구
	//m_tInfo.fCY = 150.f;	//  세로 사이즈	복구
	m_pFrameKey = L"Delirium";
	m_eState = IDLE;
	//m_fSpeed = 1.f;
	//추격
	m_tInfo.fY -= sinf(m_fAngle * (PI / 180.f)) * m_fSpeed;
	m_tInfo.fX += cosf(m_fAngle * (PI / 180.f)) * m_fSpeed;


	//공격 타입 0의 시간 3초
	// FORM2 fly form, atktype spredbullet, form type flybetter
	if (iRandMontion == 0)
	{
		
		//크기 변환
		m_tInfo.fCX = 80.f;
		m_tInfo.fCY = 64.f;
		//변환할 폼
		m_pFrameKey = L"DeliriumForm2";
		m_eState = FORM2;
		//공격시작
		if (dwChangeATK < GetTickCount())
		{
			//속도 변환
			m_fSpeed = 0;

			//0.3초마다 총알 발사
			if (dwATKTime1 + 500 <= GetTickCount())
			{

				// 공격 종류
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 0));
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 90));
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 180));
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 270));
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 45));
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 135));
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 225));
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 315));

				dwATKTime1 = GetTickCount()+100;
			}
			

		}
		if(dwChangeATK + 3000 < GetTickCount())
			dwChangeATK = GetTickCount();
	}
	//norm type
	if (iRandMontion == 1)
	{
		m_fSpeed = 0.5f;
		m_tInfo.fCX = 163.f;	//  가로 사이즈 복구
		m_tInfo.fCY = 150.f;	//  세로 사이즈	복구
		//추격
		m_tInfo.fY -= sinf(m_fAngle * (PI / 180.f)) * m_fSpeed;
		m_tInfo.fX += cosf(m_fAngle * (PI / 180.f)) * m_fSpeed;

			m_pFrameKey = L"Delirium";
			m_eState = IDLE;

		if (dwChangeATK + 1000 < GetTickCount())
		{
			if (dwATKTime1 + 200 < GetTickCount())
			{
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
				dwATKTime1 = GetTickCount();

			}

			m_pFrameKey = L"Delirium";
			m_eState = IDLE;
		}
		if (dwChangeATK + 3000 < GetTickCount())
			dwChangeATK = GetTickCount();

	}
	//loki type  explosion
	if (iRandMontion == 2)
	{

		//크기 변환
		m_tInfo.fCX = 48.f;
		m_tInfo.fCY = 48.f;
		//변환할 폼
		m_pFrameKey = L"DeliriumForm3";
		m_eState = FORM3;
		//공격시작
		if (dwChangeATK < GetTickCount())
		{
			//속도 변환
			m_fSpeed = 0.8f;

			//N초마다 공격 실행
			m_pFrameKey = L"DeliriumForm3";
			m_eState = FORM3_1;

			if (dwATKTime1 + 1500 <= GetTickCount())
			{
				CObjMgr::Get_Instance()->AddObject(OBJ_EXPLOSION, CAbstactFactory<CExplosion>::Create(m_tInfo.fX + 100.f, m_tInfo.fY));
				CObjMgr::Get_Instance()->AddObject(OBJ_EXPLOSION, CAbstactFactory<CExplosion>::Create(m_tInfo.fX , m_tInfo.fY - 100.f));
				CObjMgr::Get_Instance()->AddObject(OBJ_EXPLOSION, CAbstactFactory<CExplosion>::Create(m_tInfo.fX - 100.f, m_tInfo.fY));
				CObjMgr::Get_Instance()->AddObject(OBJ_EXPLOSION, CAbstactFactory<CExplosion>::Create(m_tInfo.fX , m_tInfo.fY + 100.f));
				
				
				dwATKTime1 = GetTickCount() + 1500;
			}
			if (dwATKTime2 + 1500 <= GetTickCount())
			{
				m_eState = FORM3_2;
				CObjMgr::Get_Instance()->AddObject(OBJ_EXPLOSION, CAbstactFactory<CExplosion>::Create(m_tInfo.fX + 100.f, m_tInfo.fY + 100.f));
				CObjMgr::Get_Instance()->AddObject(OBJ_EXPLOSION, CAbstactFactory<CExplosion>::Create(m_tInfo.fX + 100.f, m_tInfo.fY - 100.f));
				CObjMgr::Get_Instance()->AddObject(OBJ_EXPLOSION, CAbstactFactory<CExplosion>::Create(m_tInfo.fX - 100.f, m_tInfo.fY + 100.f));
				CObjMgr::Get_Instance()->AddObject(OBJ_EXPLOSION, CAbstactFactory<CExplosion>::Create(m_tInfo.fX - 100.f, m_tInfo.fY - 100.f));

				dwATKTime2 = GetTickCount()+1500;
			}


		}
		if (dwChangeATK + 5000 < GetTickCount())
			dwChangeATK = GetTickCount();
	}
	//roll type
	if (iRandMontion == 3)
	{
		m_tInfo.fCX = 96.f;
		m_tInfo.fCY = 96.f;
		m_fSpeed = 1.2f;
								//추격
		m_tInfo.fY -= sinf(m_fAngle * (PI / 180.f)) * m_fSpeed;
		m_tInfo.fX += cosf(m_fAngle * (PI / 180.f)) * m_fSpeed;


		//크기 변환
		//변환할 폼
		m_pFrameKey = L"DeliriumForm7";
		m_eState = FORM7;
		//공격시작
		if (dwChangeATK < GetTickCount())
		{
			//속도 변환
			m_fSpeed = 2.f;

			//N초마다 공격 실행
			if (dwATKTime1 + 1000 <= GetTickCount())
			{
				//+자
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 0));
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 90));
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 180));
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 270));


				dwATKTime1 = GetTickCount() + 500;
			}
			if (dwATKTime2 + 500 <= GetTickCount())
			{
				//x자
				m_eState = FORM3_2;
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 45));
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 135));
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 225));
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 315));

				dwATKTime2 = GetTickCount() + 1000;
			}


		}
		if (dwChangeATK + 3000 < GetTickCount())
			dwChangeATK = GetTickCount();
	}
	//little horn	troll bomb
	if (iRandMontion == 4)
	{

		//크기 변환
		m_tInfo.fCX = 48.f;
		m_tInfo.fCY = 48.f;
		//변환할 폼
		m_pFrameKey = L"DeliriumForm3";
		m_eState = FORM3;
		//공격시작
		if (dwChangeATK < GetTickCount())
		{
			//속도 변환
			m_fSpeed = 0.5;

			//N초마다 공격 실행
			m_pFrameKey = L"DeliriumForm8";
			m_eState = FORM8;

			if (dwATKTime1 + 1000 <= GetTickCount())
			{
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
				CObjMgr::Get_Instance()->AddObject(OBJ_BOMB, CAbstactFactory<CTrollBomb>::Create(m_pTarget->Get_Info().fX+10.f, m_pTarget->Get_Info().fY+10.f));
				dwATKTime1 = GetTickCount() + 1000;
			}
		


		}
		if (dwChangeATK + 5000 < GetTickCount())
			dwChangeATK = GetTickCount();
	}

	/*
	if (iRandMontion == 2)
	{
		m_tInfo.fCX = 163.f;	//  가로 사이즈 복구
		m_tInfo.fCY = 150.f;	//  세로 사이즈	복구
		m_tInfo.fX += cosf(m_fAngle * (PI / 180.f)) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle * (PI / 180.f)) * m_fSpeed;

		if (dwChangeATK + 4000 < GetTickCount())
		{
			m_fSpeed = 0;
			t_fAngle+=30.f;
			if (dwATKTime1 + 100 < GetTickCount())
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
	*/



}

void CDelerium::Motion_Change(void)
{
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{

		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case FORM1:
			m_tInfo.fCX = 340;
			m_tInfo.fCY = 75;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 70;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case FORM2:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case FORM3:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameMotion = 2;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case FORM3_1:
			m_tFrame.iFrameStart = 3;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameMotion = 2;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case FORM7:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameMotion = 2;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case FORM8:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameMotion = 1;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		}

		m_ePreState = m_eState;
	}
}

void CDelerium::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/deliriumforms/boss_delirium.bmp", L"Delirium");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/deliriumforms/91_megagurdy.bmp", L"DeliriumForm1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/deliriumforms/boss_007_dukeofflies.bmp", L"DeliriumForm2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/deliriumforms/boss_048_loki.bmp", L"DeliriumForm3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/deliriumforms/boss_070_itlives.bmp", L"DeliriumForm4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/deliriumforms/boss_072_thefallen.bmp", L"DeliriumForm5");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/deliriumforms/boss_082_krampus.bmp", L"DeliriumForm6");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/deliriumforms/boss_sistersvis.bmp", L"DeliriumForm7");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/deliriumforms/littlehorn.bmp", L"DeliriumForm8");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/deliriumforms/theforsaken.bmp", L"DeliriumForm9");


}

void CDelerium::First_State(void)
{
	m_pFrameKey = L"Delirium";
	m_eState = IDLE;
	m_ePreState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

}
