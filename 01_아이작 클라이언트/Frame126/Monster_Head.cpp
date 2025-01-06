#include "stdafx.h"
#include "Monster_Head.h"
#include "AbstactFactory.h"
#include "ScrewBullet.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "Bullet.h"



CMonsterHead::CMonsterHead()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CMonsterHead::~CMonsterHead()
{
	Release();
}

void CMonsterHead::Initialize(void)
{
	m_tInfo.fX = 500.f;		// ���� X
	m_tInfo.fY = 200.f;		// ���� Y

	m_tInfo.fCX = 100.f;	//  ���� ������
	m_tInfo.fCY = 60.f;	//  ���� ������

	m_fSpeed = 2.5f;


	
	m_iHP = 6;
	m_fPlayerATK = 1;
	m_iShotSpeed = 300;
	dwshotSpeed = GetTickCount();
	dwCoolTime = GetTickCount();

	m_eGroup = GAMEOBJECT;

	Insert_Texture();
	First_State();

	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Success.wav", SOUND_EFFECT, g_fSound);
	
}

int CMonsterHead::Update(void)
{

	if (m_iHP <= 0)
		m_bDead = true;

	if (true == m_bDead)
		return OBJ_DEAD;

	Random_ACT();

	Motion_Change();

	// ���ʿ��� ���� �Ǵ� �������� ��ȭ�� ���� ������ Update_Rect�Լ��� ȣ��
	Move_Frame();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonsterHead::Late_Update(void)
{

}

void CMonsterHead::Render(HDC hDC)
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
						(int)m_tRect.top + iScrollY,
						(int)m_tInfo.fCX,				// 4,5 ���� : ���� ���� �ؽ�ó�� X, Y ������	//ũ�� �ø���
						(int)m_tInfo.fCY, 
						hMemDC,							// 6���� : ��Ʈ���� ������ �ִ� DC
						m_tFrame.iFrameStart * (int)m_tInfo.fCX,			// 7, 8���� : ��Ʈ���� ����� ���� ��ǥ
						m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
						(int)m_tInfo.fCX,		// 9, 10���� : ������ ��Ʈ���� X,Y ������	
						(int)m_tInfo.fCY,
						RGB(255, 255, 255));			// 11���� : �����ϰ��� �ϴ� ����
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
			(int)m_tRect.left + iScrollX,	// 2,3���� : 2, 3���� : ���� ���� ��ġ�� ��ǥ�� ����(L, T ��ǥ)
			(int)m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,				// 4,5 ���� : ���� ���� �ؽ�ó�� X, Y ������	//ũ�� �ø���
			(int)m_tInfo.fCY,
			hStretchDC,							// 6���� : ��Ʈ���� ������ �ִ� DC
			0,						// 7, 8���� : ��Ʈ���� ����� ���� ��ǥ
			0,
			(int)m_tInfo.fCX,		// 9, 10���� : ������ ��Ʈ���� X,Y ������	
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));			// 11���� : �����ϰ��� �ϴ� ����
	}
	
}

void CMonsterHead::Release(void)
{
	
}

void CMonsterHead::Random_ACT(void)
{
	int iMonsterAtk = 0; 
	if (dwCoolTime + 1000 <= GetTickCount()) 
	{
		iMonsterAtk= 0;
		dwCoolTime = GetTickCount();
	}
	dwCoolTime = GetTickCount();


	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	float	fY = 0.f;
	//
	if (iMonsterAtk==0)
	{
		
		m_pFrameKey = L"back_shot";
		m_eState = ATTACK_UP;
		//getticcount �ֱ�
		if (dwshotSpeed + m_iShotSpeed < GetTickCount())
		{
			CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CBullet>::Create(m_tInfo.fX + iScrollX, m_tInfo.fY + iScrollY, 90.f));
			dwshotSpeed = GetTickCount();
		}

		
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
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
		m_pFrameKey = L"side_shot";
		m_eState = ATTACK_LEFT;
		m_bStretch = false;
		if (dwshotSpeed + m_iShotSpeed < GetTickCount())
		{
			CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CBullet>::Create(m_tInfo.fX + iScrollX, m_tInfo.fY + iScrollY, 180.f));
			dwshotSpeed = GetTickCount();
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('S'))
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
		m_pFrameKey = L"front_shot";
		m_eState = ATTACK_DOWN;
		if (dwshotSpeed + m_iShotSpeed < GetTickCount())
		{
			CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CBullet>::Create(m_tInfo.fX + iScrollX, m_tInfo.fY + iScrollY, 270.f));
			dwshotSpeed = GetTickCount();
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
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
		m_pFrameKey = L"side_shot";
		m_eState = ATTACK_LEFT;
		m_bStretch = true;
		if (dwshotSpeed + m_iShotSpeed < GetTickCount())
		{
			CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CBullet>::Create(m_tInfo.fX + iScrollX, m_tInfo.fY + iScrollY, 0.f));
			dwshotSpeed = GetTickCount();
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
			m_tInfo.fY += m_fSpeed;
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
			m_tInfo.fY -= m_fSpeed;
		m_pFrameKey = L"Player_Isaac";
		m_eState = IDLE;
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
			m_tInfo.fY += m_fSpeed;
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
			m_tInfo.fY -= m_fSpeed;
		m_pFrameKey = L"Player_Isaac";
		m_eState = IDLE;
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
		m_pFrameKey = L"Player_Isaac";
		m_eState = IDLE;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
		m_pFrameKey = L"Player_Isaac";
		m_eState = IDLE;
	}
	//
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
	{
		/*if (m_bJump)
			return;

		m_bJump = true;	*/

		//m_pFrameKey = L"Player_UP";
		m_pFrameKey = L"Player_Isaac";
		m_eState = USE_ITEM;

	}
	else
		//return ;
		m_eState = IDLE;


	

}


void CMonsterHead::Motion_Change(void)
{		
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{
		case IDLE:
			m_tFrame.iFrameStart	= 0;
			m_tFrame.iFrameEnd		= 0;
			m_tFrame.iFrameMotion	= 0;
			m_tFrame.dwFrameSpeed	= 800;
			m_tFrame.dwFrameTime    = GetTickCount();
			break;

	
		case ATTACK_DOWN:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 1;
				m_tFrame.iFrameMotion = 0;
				m_tFrame.dwFrameSpeed = m_iShotSpeed*0.5f;
				m_tFrame.dwFrameTime = GetTickCount();
				break;


		case ATTACK_RIGHT:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 1;
				m_tFrame.iFrameMotion = 0;
				m_tFrame.dwFrameSpeed = m_iShotSpeed*0.5f;
				m_tFrame.dwFrameTime = GetTickCount();
				break;


		case ATTACK_UP:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 1;
				m_tFrame.iFrameMotion = 0;
				m_tFrame.dwFrameSpeed = m_iShotSpeed*0.5f;
				m_tFrame.dwFrameTime = GetTickCount();
				break;


		case ATTACK_LEFT:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 1;
				m_tFrame.iFrameMotion = 0;
				m_tFrame.dwFrameSpeed = m_iShotSpeed*0.5f;
				m_tFrame.dwFrameTime = GetTickCount();
			break;

		case HIT:
			m_tFrame.iFrameStart = 3;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameMotion = 6;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case USE_ITEM:
			m_tFrame.iFrameStart = 8;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 1000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		case DEAD:
			m_tFrame.iFrameStart = 6;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iFrameMotion = 5;
			m_tFrame.dwFrameSpeed = 2000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}

		m_ePreState = m_eState;
	}
}

void CMonsterHead::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/megasatan1.bmp", L"Player_Isaac");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/megasatan1.bmp", L"side_shot");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/megasatan1.bmp", L"back_shot");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/megasatan1.bmp", L"front_shot");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Stretch.bmp", L"Stretch");

}

void CMonsterHead::First_State(void)
{
	m_pFrameKey = L"Player_Isaac";
	m_eState = IDLE;
	m_ePreState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 500;
	m_tFrame.dwFrameTime = GetTickCount();
}

CObj * CMonsterHead::Create_Bullet(DIR eDir)
{
	CObj*		pBullet = nullptr;
	pBullet = CAbstactFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, eDir);

	return pBullet;
}
