#include "stdafx.h"
#include "KeyNum.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "Player.h"
CKeyNum::CKeyNum()
{
}


CKeyNum::~CKeyNum()
{
	Release();
}

void CKeyNum::Initialize(void)
{
	m_tInfo.fX = 60.f;		// ���� X
	m_tInfo.fY = 170.f;		// ���� Y

	m_tInfo.fCX = 14.f;	//  ���� ������
	m_tInfo.fCY = 14.f;	//  ���� ������

	m_fSpeed = 100.f;

	m_iHP = CObjMgr::Get_Instance()->Get_Player()->Get_HP();
	m_iMaxHP = CObjMgr::Get_Instance()->Get_Player()->Get_MAXHP();
	m_eGroup = UI;


	m_iKey = CObjMgr::Get_Instance()->Get_Player()->Get_Key();
	Insert_Texture();

	//First_State();

}

int CKeyNum::Update(void)
{
	m_iKey = CObjMgr::Get_Instance()->Get_Player()->Get_Key();

	if (m_iHP <= 0)
		m_bDead = true;


	if (true == m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	//get Key
	//m_iHP = CObjMgr::Get_Instance()->Get_Player()->Get_HP();

	CountKey();
	Motion_Change();
	Move_Frame();

	return OBJ_NOEVENT;
}

void CKeyNum::Late_Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing('Q'))
		m_fAngle += 45.f;
}

void CKeyNum::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Number");

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
		(int)m_tInfo.fCX+5.f,				// 4,5 ���� : ���� ���� �ؽ�ó�� X, Y ������	//ũ�� �ø���
		(int)m_tInfo.fCY+5.f,
		hMemDC,							// 6���� : ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,			// 7, 8���� : ��Ʈ���� ����� ���� ��ǥ
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9, 10���� : ������ ��Ʈ���� X,Y ������	
		(int)m_tInfo.fCY,
		RGB(153, 217, 234));			// 11���� : �����ϰ��� �ϴ� ����



}

void CKeyNum::Release(void)
{

}

void CKeyNum::Motion_Change(void)
{
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{

		case ONE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case ZERO:
			m_tFrame.iFrameStart = 1;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case TWO:
			m_tFrame.iFrameStart = 2;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case THREE:
			m_tFrame.iFrameStart = 3;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case FOUR:
			m_tFrame.iFrameStart = 4;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case FIVE:
			m_tFrame.iFrameStart = 5;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case SIX:
			m_tFrame.iFrameStart = 6;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case SEVEN:
			m_tFrame.iFrameStart = 7;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case EIGHT:
			m_tFrame.iFrameStart = 8;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case NINE:
			m_tFrame.iFrameStart = 9;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		}

		m_ePreState = m_eState;
	}
}

void CKeyNum::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Number1.bmp", L"Number");

}

void CKeyNum::First_State(void)
{
	m_pFrameKey = L"Number";
	m_eState = ZERO;
	m_ePreState = ZERO;


	m_tFrame.iFrameStart = 1;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 10000000;
	m_tFrame.dwFrameTime = GetTickCount();

}

void CKeyNum::CountKey(void)
{
	int		iKeyCount = m_iKey%10;

	if (iKeyCount == 0)
	{
		m_pFrameKey = L"Number";
		m_eState = ZERO;
	}
	else if (iKeyCount == 1)
	{
		m_pFrameKey = L"Number";
		m_eState = ONE;
	}
	else if (iKeyCount == 2)
	{
		m_pFrameKey = L"Number";
		m_eState = TWO;
	}
	else if (iKeyCount == 3)
	{
		m_pFrameKey = L"Number";
		m_eState = THREE;
	}
	else if (iKeyCount == 4)
	{
		m_pFrameKey = L"Number";
		m_eState = FOUR;
	}
	else if (iKeyCount == 5)
	{
		m_pFrameKey = L"Number";
		m_eState = FIVE;
	}
	else if (iKeyCount == 6)
	{
		m_pFrameKey = L"Number";
		m_eState = SIX;
	}
	else if (iKeyCount == 7)
	{
		m_pFrameKey = L"Number";
		m_eState = SEVEN;
	}
	else if (iKeyCount == 8)
	{
		m_pFrameKey = L"Number";
		m_eState = EIGHT;
	}
	else if (iKeyCount == 9)
	{
		m_pFrameKey = L"Number";
		m_eState = NINE;
	}
	else
	{
		return;
	}


}
