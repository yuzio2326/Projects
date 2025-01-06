#include "stdafx.h"
#include "OwnKey.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "Player.h"
COwnKey::COwnKey()
{
}


COwnKey::~COwnKey()
{
	Release();
}

void COwnKey::Initialize(void)
{
	m_tInfo.fX = 16.f;		// ���� X
	m_tInfo.fY = 160.f;		// ���� Y

	m_tInfo.fCX = 16.f;	//  ���� ������
	m_tInfo.fCY = 16.f;	//  ���� ������

	m_fSpeed = 100.f;

	m_iHP = CObjMgr::Get_Instance()->Get_Player()->Get_HP();
	m_iMaxHP = CObjMgr::Get_Instance()->Get_Player()->Get_MAXHP();
	m_eGroup = UI;

	Insert_Texture();

	First_State();

}

int COwnKey::Update(void)
{

	if (m_iHP <= 0)
		m_bDead = true;


	if (true == m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	//get bomb
	//m_iHP = CObjMgr::Get_Instance()->Get_Player()->Get_HP();

	Motion_Change();
	Move_Frame();

	return OBJ_NOEVENT;
}

void COwnKey::Late_Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing('Q'))
		m_fAngle += 45.f;
}

void COwnKey::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"OwnItem");

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//BitBlt(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tInfo.fCX, m_tInfo.fCY, hMemDC, 0, 0, SRCCOPY);
	// 1���� : ���� ���� ���������� �׸��� �׸� DC
	// 2, 3���� : ���� ���� ��ġ�� ��ǥ�� ����(L, T ��ǥ)
	// 4, 5���� : ���� ���� �ؽ�ó�� X, Y ������
	// 6 ���� : ��Ʈ���� ������ �ִ� DC
	// 7, 8���� : ��Ʈ���� ����� ���� ��ǥ(L, T��ǥ)
	// 9���� : ��� ȿ���� ���� SRCCOPY : �״�� ���
	GdiTransparentBlt(hDC,							// 1���� : ���� ���� ���������� �׸��� �׸� DC
		(int)m_tRect.left,	// 2,3���� : 2, 3���� : ���� ���� ��ġ�� ��ǥ�� ����(L, T ��ǥ)
		(int)m_tRect.top,
		(int)m_tInfo.fCX+16.f,				// 4,5 ���� : ���� ���� �ؽ�ó�� X, Y ������	//ũ�� �ø���
		(int)m_tInfo.fCY+16.f,
		hMemDC,							// 6���� : ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,			// 7, 8���� : ��Ʈ���� ����� ���� ��ǥ
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9, 10���� : ������ ��Ʈ���� X,Y ������	
		(int)m_tInfo.fCY,
		RGB(153, 217, 234));			// 11���� : �����ϰ��� �ϴ� ����



}

void COwnKey::Release(void)
{

}

void COwnKey::Motion_Change(void)
{
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{

		case COIN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case KEY:
			m_tFrame.iFrameStart = 1;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		
		case BOMB:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameMotion = 1;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		}

		m_ePreState = m_eState;
	}
}

void COwnKey::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/hudpickups.bmp", L"OwnItem");

}

void COwnKey::First_State(void)
{
	m_pFrameKey = L"OwnItem";
	m_eState = BOMB;
	m_ePreState = BOMB;


	m_tFrame.iFrameStart = 1;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 10000000;
	m_tFrame.dwFrameTime = GetTickCount();

}
