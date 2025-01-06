#include "stdafx.h"
#include "BulletFly.h"
#include "MonsterBullet.h"//���� ����ó��
#include "Shield.h"
#include "AbstactFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"


CBulletFly::CBulletFly()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CBulletFly::~CBulletFly()
{
	Release();
}

void CBulletFly::Initialize(void)
{
	m_tInfo.fX = 200.f;		// ���� X
	m_tInfo.fY = 200.f;		// ���� Y

	m_tInfo.fCX = 32.f;	//  ���� ������
	m_tInfo.fCY = 32.f;	//  ���� ������

	m_fSpeed = 0.5f;

	m_iHP = 5.f;
	dwLifeTime = GetTickCount();

	m_eGroup = GAMEOBJECT;

	Insert_Texture();
	First_State();

	//������ �ֱ�
	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Success.wav", SOUND_EFFECT, g_fSound);

}

int CBulletFly::Update(void)
{

	if (true == m_bDead)
	{
		CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 0));
		CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 45));
		CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 90));
		CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 135));
		CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 180));
		CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 225));
		CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 270));
		CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, 315));
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

		// ���� ���� ������ ��׸��� �������. �򰥸��� �� ��
		m_fAngle = m_fAngle * (180.f / PI);

		if (m_tInfo.fY < m_pTarget->Get_Info().fY)
			m_fAngle *= -1.f;
	}

	m_tInfo.fX += cosf(m_fAngle * (PI / 180.f)) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * (PI / 180.f)) * m_fSpeed;




	Run_Time();
	Motion_Change();
	Move_Frame();
	// ���ʿ��� ���� �Ǵ� �������� ��ȭ�� ���� ������ Update_Rect�Լ��� ȣ��

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBulletFly::Late_Update(void)
{

}

void CBulletFly::Render(HDC hDC)
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
		RGB(255, 255, 255));			// 11���� : �����ϰ��� �ϴ� ����

}

void CBulletFly::Release(void)
{

}


void CBulletFly::Run_Time(void)
{


}

void CBulletFly::Motion_Change(void)
{
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{

		case RUNTIME:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		}

		m_ePreState = m_eState;
	}
}

void CBulletFly::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/monster_101_redboomfly.bmp", L"BloodFly");


}

void CBulletFly::First_State(void)
{
	m_pFrameKey = L"BloodFly";
	m_eState = RUNTIME;
	m_ePreState = RUNTIME;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();

}
