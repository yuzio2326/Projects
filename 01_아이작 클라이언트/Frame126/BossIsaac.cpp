#include "stdafx.h"
#include "BossIsaac.h"
#include "MonsterBullet.h"//���� ����ó��
#include "IsaacForm.h"
#include "AbstactFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"


CBossIsaac::CBossIsaac()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CBossIsaac::~CBossIsaac()
{
	Release();
}

void CBossIsaac::Initialize(void)
{
	m_tInfo.fX = 400.f;		// ���� X
	m_tInfo.fY = 300.f;		// ���� Y

	m_tInfo.fCX = 64.f;	//  ���� ������
	m_tInfo.fCY = 64.f;	//  ���� ������

	m_fSpeed = 0.f;

	m_iHP = 100.f;
	dwChangeATK = GetTickCount();
	dwATKTime1 = GetTickCount();
	dwATKTime2 = GetTickCount();


	m_eGroup = GAMEOBJECT;

	Insert_Texture();
	First_State();

	//������ �ֱ�
	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Success.wav", SOUND_EFFECT, g_fSound);

}

int CBossIsaac::Update(void)
{

	if (true == m_bDead)
	{
		//IsaacPhase2 �����ϱ�
		//������ form dead ó�� ���� phase2 �� ����
		CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstactFactory<CIsaacForm>::Create(m_tInfo.fX, m_tInfo.fY, 0));
		return OBJ_DEAD;
	}

	if (m_iHP <= 0)
		m_bDead = true;

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	//player �߰� ���� �Լ�
	{

	if (m_pTarget)
	{
		float	fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
		float	fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		m_fAngle = acosf(fWidth / fDiagonal);

		// ���� ���� ������ ��׸��� �������. �򰥸��� �� ��
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
	// ���ʿ��� ���� �Ǵ� �������� ��ȭ�� ���� ������ Update_Rect�Լ��� ȣ��

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBossIsaac::Late_Update(void)
{

}

void CBossIsaac::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = m_pBmpMgr->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,							// 1���� : ���� ���� ���������� �׸��� �׸� DC
		(int)m_tRect.left + iScrollX,	// 2,3���� : 2, 3���� : ���� ���� ��ġ�� ��ǥ�� ����(L, T ��ǥ)
		(int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,				// 4,5 ���� : ���� ���� �ؽ�ó�� X, Y ������
		(int)m_tInfo.fCY,
		hMemDC,							// 6���� : ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,			// 7, 8���� : ��Ʈ���� ����� ���� ��ǥ
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9, 10���� : ������ ��Ʈ���� X,Y ������	
		(int)m_tInfo.fCY,
		RGB(195, 195, 195));			// 11���� : �����ϰ��� �ϴ� ����

}

void CBossIsaac::Release(void)
{

}


void CBossIsaac::Run_Time(void)
{
	if (dwChangeATK < GetTickCount())
	{
		//0.4~ ���� ����
		if (dwATKTime1 + 1000 <= GetTickCount())
		{
			//+��
			CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 0));
			CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 90));
			CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 180));
			CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 270));

			dwATKTime1 = GetTickCount() + 800;
		}

		m_pFrameKey = L"BossIsaac";
		m_eState = STANDSHOT;
	}
	if (dwChangeATK + 2000 < GetTickCount())
	{
		if (dwATKTime2 + 1000 < GetTickCount())
		{
			CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 45));
			CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 135));
			CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 225));
			CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 315));
			dwATKTime2 = GetTickCount()+1000;
		}
/*		m_pFrameKey = L"BossIsaac";
		m_eState = SITSHOT*/;
		//dwChangeATK = GetTickCount();

	}

	if (dwChangeATK + 5000 < GetTickCount())
	{
		if (dwATKTime1 + 400 < GetTickCount())
		{
			CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
			dwATKTime1 = GetTickCount();
		}
		if (dwATKTime2 < GetTickCount())
		{
			dwATKTime2 = GetTickCount()+400;
		}

		m_pFrameKey = L"BossIsaac";
		m_eState = SITSHOT;
	}
	if (dwChangeATK + 10000 < GetTickCount())
		dwChangeATK = GetTickCount();

}

void CBossIsaac::Motion_Change(void)
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
		case STANDSHOT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 80;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case SITSHOT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameMotion = 1;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case FORMCHANGE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameMotion = 2;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		}

		m_ePreState = m_eState;
	}
}

void CBossIsaac::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/boss_075_isaac.bmp", L"BossIsaac");


}

void CBossIsaac::First_State(void)
{
	m_pFrameKey = L"BossIsaac";
	m_eState = IDLE;
	m_ePreState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();

}
