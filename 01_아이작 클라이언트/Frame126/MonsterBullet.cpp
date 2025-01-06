#include "stdafx.h"
#include "MonsterBullet.h"
#include "MonsterBulletEffect.h"//���� ����ó��
#include "Shield.h"
#include "AbstactFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"


CMonsterBullet::CMonsterBullet()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CMonsterBullet::~CMonsterBullet()
{
	Release();
}

void CMonsterBullet::Initialize(void)
{
	m_tInfo.fX = 200.f;		// ���� X
	m_tInfo.fY = 200.f;		// ���� Y


	m_fATKDMG = 1.f;
	m_fSpeed = 4.5f;
	m_frange = 1000.f;

	m_tInfo.fCX = 15.f+ m_fATKDMG;	//  ���� ������
	m_tInfo.fCY = 15.f+ m_fATKDMG;	//  ���� ������

	
	dwLifeTime = GetTickCount();

	m_eGroup = GAMEOBJECT;

	Insert_Texture();
	First_State();

	//ȿ���� �ֱ�
	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Success.wav", SOUND_EFFECT, g_fSound);

}

int CMonsterBullet::Update(void)
{

	if (true == m_bDead)
	{
		CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstactFactory<CMonsterBulletEffect>::Create(m_tInfo.fX, m_tInfo.fY, 0));
		return OBJ_DEAD;
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

void CMonsterBullet::Late_Update(void)
{
	//if (50 >= m_tRect.left || WINCX - 50 <= m_tRect.right ||
	//	50 >= m_tRect.top || WINCY - 50 <= m_tRect.bottom)
	//{
	//	
	//	m_bDead = true;
	//}

}

void CMonsterBullet::Render(HDC hDC)
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

void CMonsterBullet::Release(void)
{

}


void CMonsterBullet::Run_Time(void)
{



}

void CMonsterBullet::Motion_Change(void)
{
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{

		case RUNTIME:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		}

		m_ePreState = m_eState;
	}
}

void CMonsterBullet::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/MonsterBullet.bmp", L"MBullet");


}

void CMonsterBullet::First_State(void)
{
	m_pFrameKey = L"MBullet";
	m_eState = RUNTIME;
	m_ePreState = RUNTIME;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

}
