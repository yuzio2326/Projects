#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"

CBullet::CBullet()
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize(void)
{
	m_fATKDMG = CObjMgr::Get_Instance()->Get_Player()->Get_ATKDMG();
	//�������� Ŀ������ ũ�⵵ ����
	m_tInfo.fCX = 15.f + m_fATKDMG;
	m_tInfo.fCY = 15.f + m_fATKDMG;

	m_fSpeed = 4.5f;
	m_frange = 600.f;
	dwLifeTime = GetTickCount();
	m_eGroup = GAMEOBJECT;


	Insert_Texture();
	First_State();

}

int CBullet::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += cosf(m_fAngle * (PI / 180.f)) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * (PI / 180.f)) * m_fSpeed;

	Atk_Time();
	Motion_Change();
	Move_Frame();



	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update(void)
{
	//���� ������ ������
	if (50 >= m_tRect.left || WINCX - 50 <= m_tRect.right ||
		50 >= m_tRect.top || WINCY - 50 <= m_tRect.bottom)
	{
		m_bDead = true;
	}
}

void CBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Tears");//�̹��� �ȳ���
	//HDC hMemDC = m_pBmpMgrX->Find_Image(m_pFrameKey);//����
	//HDC hMemDC = m_pBmpMgrX->Find_Image(m_pFrameKey);
	//HDC hMemDC = m_pBmpMgr->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,							// 1���� : ���� ���� ���������� �׸��� �׸� DC
		(int)m_tRect.left + iScrollX,	// 2,3���� : 2, 3���� : ���� ���� ��ġ�� ��ǥ�� ����(L, T ��ǥ)
		(int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX+ m_fATKDMG,				// 4,5 ���� : ���� ���� �ؽ�ó�� X, Y ������
		(int)m_tInfo.fCY+ m_fATKDMG,
		hMemDC,							// 6���� : ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,			// 7, 8���� : ��Ʈ���� ����� ���� ��ǥ
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9, 10���� : ������ ��Ʈ���� X,Y ������	
		(int)m_tInfo.fCY,
		RGB(195, 195, 195));			// 11���� : �����ϰ��� �ϴ� ����



}

void CBullet::Release(void)
{
	
}

void CBullet::Atk_Time(void)
{
	if (dwLifeTime + m_frange <= GetTickCount())
	{
		m_tInfo.fX = 0;
		m_tInfo.fY = 0;
		m_pFrameKey = L"Tears";
		m_eState = DEAD;
	}
}

void CBullet::Motion_Change(void)
{
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{

		case ATK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}

		m_ePreState = m_eState;
	}
}

void CBullet::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/effect_029_explosion.bmp", L"Tears");

}

void CBullet::First_State(void)
{
	m_pFrameKey = L"Tears";
	m_eState = ATK;
	m_ePreState = ATK;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
}
