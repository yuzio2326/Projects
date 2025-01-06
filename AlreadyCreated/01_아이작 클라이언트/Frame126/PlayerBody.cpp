#include "stdafx.h"
#include "PlayerBody.h"
#include "Bullet.h"
#include "Shield.h"
#include "AbstactFactory.h"
#include "ScrewBullet.h"
#include "ObjMgr.h"
#include "GuideBullet.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "BmpMgr.h"
#include "Bomb.h"
#include "Player.h"



CPlayerBody::CPlayerBody()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CPlayerBody::~CPlayerBody()
{
	Release();
}

void CPlayerBody::Initialize(void)
{
	m_tInfo.fX = 100.f;
	m_tInfo.fY = 100.f;

	m_tInfo.fCX = 32.f;	// �÷��̾� ���� ������
	m_tInfo.fCY = 30.f;	// �÷��̾� ���� ������

	dw_die = GetTickCount();

	m_fSpeed = 3.f;

	m_iHP = CObjMgr::Get_Instance()->Get_Player()->Get_HP();
	m_iMaxHP = CObjMgr::Get_Instance()->Get_Player()->Get_MAXHP();

	m_iCheckPlayerHP = m_iHP;

	m_fTime = 0.f;
	m_fJumpPower = 15.f;

	m_fATKDMG = 10.f;
	
	DMG = true;
	

	m_eGroup = PLAYER;

	Insert_Texture();
	First_State();

	
}

int CPlayerBody::Update(void)
{
	m_tInfo.fX = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX;		// ���� X
	m_tInfo.fY = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY;		// ���� Y

	if (m_iCheckPlayerHP <= 0)
		m_bDead = true;

	if (true == m_bDead)
		return OBJ_DEAD;

	m_iHP = CObjMgr::Get_Instance()->Get_Player()->Get_HP();
	m_iMaxHP = CObjMgr::Get_Instance()->Get_Player()->Get_MAXHP();

	//�������� ���� ��
	//if (m_iHP < m_iCheckPlayerHP)
	//{
	//	//����ó��
	//	m_iCheckPlayerHP = m_iHP;
	//}
	////ȸ����
	//if (m_iCheckPlayerHP < m_iHP)
	//{
	//	m_iCheckPlayerHP = m_iHP;
	//}
	//������ �ƴҶ� 
	//if (DMG == true)
	//{

	//	//�������� ������
	//	if (m_iHP < m_iCheckHP)
	//	{
	//		//üũ�� ���� hp�� �����ϰ� �������� ������.
	//		m_iCheckHP = m_iHP;
	//		DMG = false;
	//	}

	//}
	//if(DMG!=true)	//�����̸�
	//{
	//	//hp�� ������ �ξ��� hp �� �־� ��� �ش� ü���� ���� ��Ű�� 
	//	m_iHP = m_iCheckHP;
	//	//2�ʰ� ���� �ڿ� ������ Ǭ��.
	//	if (dwDelay + 2000 < GetTickCount())
	//	{
	//		DMG = true;
	//		dwDelay = GetTickCount();
	//	}
	//}

	//if (m_iCheckHP < m_iHP)
	//{
	//	m_iCheckHP = m_iHP;
	//}

	Key_Input();
	OffSet();
	Motion_Change();

	// ���ʿ��� ���� �Ǵ� �������� ��ȭ�� ���� ������ Update_Rect�Լ��� ȣ��
	Move_Frame();

	if (m_iHP <= 0) 
	{
		m_pFrameKey = L"Player_Isaac";
		m_eState = DEAD;
		if (dw_die + 1000<GetTickCount()) 
		{
			m_bDead = true;
			dw_die = GetTickCount();
		}
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayerBody::Late_Update(void)
{

}

void CPlayerBody::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX(); 
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = m_pBmpMgr->Find_Image(m_pFrameKey);
	HDC hStretchDC = m_pBmpMgr->Find_Image(L"Stretch");

	//BitBlt(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tInfo.fCX, m_tInfo.fCY, hMemDC, 0, 0, SRCCOPY);
	// 1���� : ���� ���� ���������� �׸��� �׸� DC
	// 2, 3���� : ���� ���� ��ġ�� ��ǥ�� ����(L, T ��ǥ)
	// 4, 5���� : ���� ���� �ؽ�ó�� X, Y ������
	// 6 ���� : ��Ʈ���� ������ �ִ� DC
	// 7, 8���� : ��Ʈ���� ����� ���� ��ǥ(L, T��ǥ)
	// 9���� : ��� ȿ���� ���� SRCCOPY : �״�� ���
	if (m_bStretch)
	{

	GdiTransparentBlt(hDC,							// 1���� : ���� ���� ���������� �׸��� �׸� DC
		(int)m_tRect.left + iScrollX,	// 2,3���� : 2, 3���� : ���� ���� ��ġ�� ��ǥ�� ����(L, T ��ǥ)
		(int)m_tRect.top + iScrollY + 8.f,
		(int)m_tInfo.fCX,				// 4,5 ���� : ���� ���� �ؽ�ó�� X, Y ������
		(int)m_tInfo.fCY ,
		hMemDC,							// 6���� : ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,			// 7, 8���� : ��Ʈ���� ����� ���� ��ǥ
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9, 10���� : ������ ��Ʈ���� X,Y ������	
		(int)m_tInfo.fCY,
		RGB(195, 195, 195));
	}
	else
	{
		StretchBlt(hStretchDC,	// ����� �̹��� �ڵ�
			0,			// 2, 3���� : ���� ���� ��ġ�� ��ǥ�� ����(L, T ��ǥ)
			0,
			m_tInfo.fCX,	// 4, 5���� : ����� �̹��� ������
			m_tInfo.fCY,
			hMemDC,			// 6���� : �����ؼ� ����ϰ��� �ϴ� �ؽ�ó �̹��� �ڵ�
			m_tFrame.iFrameStart * (int)m_tInfo.fCX + m_tInfo.fCX, // 7,8���� : ������ �̹����� ������ x,y ��ǥ
			m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
			-m_tInfo.fCX,
			m_tInfo.fCY,
			SRCCOPY);

		GdiTransparentBlt(hDC,							// 1���� : ���� ���� ���������� �׸��� �׸� DC
			(int)m_tRect.left + iScrollX-1.f,	// 2,3���� : 2, 3���� : ���� ���� ��ġ�� ��ǥ�� ����(L, T ��ǥ)
			(int)m_tRect.top + iScrollY + 9.f,
			(int)m_tInfo.fCX,				// 4,5 ���� : ���� ���� �ؽ�ó�� X, Y ������	//ũ�� �ø���
			(int)m_tInfo.fCY,
			hStretchDC,							// 6���� : ��Ʈ���� ������ �ִ� DC
			0,						// 7, 8���� : ��Ʈ���� ����� ���� ��ǥ
			0,
			(int)m_tInfo.fCX,		// 9, 10���� : ������ ��Ʈ���� X,Y ������	
			(int)m_tInfo.fCY,
			RGB(195, 195, 195));			// 11���� : �����ϰ��� �ϴ� ����
	}
}

void CPlayerBody::Release(void)
{
	
}

void CPlayerBody::Key_Input(void)
{

	float	fY = 0.f;
	m_tInfo.fCX = 32.f;	// �÷��̾� ���� ������
	m_tInfo.fCY = 30.f;	// �÷��̾� ���� ������

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		m_pFrameKey = L"Player_Isaac";
		m_eState = WALK_LEFT;
		m_bStretch = false;
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			m_tInfo.fY += m_fSpeed;
			m_pFrameKey = L"Player_Isaac";
			m_eState = WALK_DOWN;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			m_tInfo.fY -= m_fSpeed;
			m_pFrameKey = L"Player_Isaac";
			m_eState = WALK_UP;
		}
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		m_pFrameKey = L"Player_Isaac";
		m_eState = WALK_RIGHT;
		m_bStretch = true;
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			m_tInfo.fY += m_fSpeed;
			m_pFrameKey = L"Player_Isaac";
			m_eState = WALK_DOWN;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			m_tInfo.fY -= m_fSpeed;
			m_pFrameKey = L"Player_Isaac";
			m_eState = WALK_UP;
		}
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
		m_pFrameKey = L"Player_Isaac";
		m_eState = WALK_DOWN;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
		m_pFrameKey = L"Player_Isaac";
		m_eState = WALK_UP;
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
	{
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		{
			m_tInfo.fX -= m_fSpeed;
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
				m_tInfo.fY += m_fSpeed;
			else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
				m_tInfo.fY -= m_fSpeed;
		}

		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		{
			m_tInfo.fX += m_fSpeed;
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
				m_tInfo.fY += m_fSpeed;
			else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
				m_tInfo.fY -= m_fSpeed;

		}

		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			m_tInfo.fY += m_fSpeed;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			m_tInfo.fY -= m_fSpeed;
		}
		m_pFrameKey = L"Player_Isaac";
		m_eState = USE_ITEM;

	}
	else if (m_iHP < m_iCheckHP)
	{
		m_pFrameKey = L"Player_Isaac";
		m_eState = HIT;
	}
	else
		m_eState = IDLE;



}



void CPlayerBody::OffSet(void)
{
	int		iOffset = WINCX >> 1;
	
	int		iOffsetLeftX = 100;
	int		iOffsetRightX = 800;

	int		iOffsetTop = 100;
	int		iOffsetBottom = 540;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	// �߰� �������� �÷��̾ ������ ���ϴ� ���
	if (iOffsetLeftX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffsetRightX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	if (iOffsetTop > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	if (iOffsetBottom < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
}

void CPlayerBody::Motion_Change(void)
{		
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{
		case IDLE:
			m_tFrame.iFrameStart	= 0;
			m_tFrame.iFrameEnd		= 1;
			m_tFrame.iFrameMotion	= 1;
			m_tFrame.dwFrameSpeed	= 800;
			m_tFrame.dwFrameTime    = GetTickCount();
			break;

		case WALK_UP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameMotion = 1;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case WALK_DOWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameMotion = 1;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		case WALK_RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameMotion = 2;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case WALK_LEFT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameMotion = 2;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		
		case HIT:
			m_tFrame.iFrameStart = 2;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameMotion = 3;
			m_tFrame.dwFrameSpeed = 1000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case USE_ITEM:
			m_tFrame.iFrameStart = 8;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iFrameMotion = 1;
			m_tFrame.dwFrameSpeed = 1000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		case DEAD:
			m_tFrame.iFrameStart = 8;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iFrameMotion = 1;
			m_tFrame.dwFrameSpeed = 1000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}

		m_ePreState = m_eState;
	}
}

void CPlayerBody::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/character_001_isaac.bmp", L"Player_Isaac");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Stretch.bmp", L"Stretch");

}

void CPlayerBody::First_State(void)
{
	m_pFrameKey = L"Player_Isaac";
	m_eState = IDLE;
	m_ePreState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameMotion = 1;
	m_tFrame.dwFrameSpeed = 500;
	m_tFrame.dwFrameTime = GetTickCount();
}
