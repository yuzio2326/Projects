#include "stdafx.h"
#include "Tears.h"
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



CTears::CTears()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CTears::~CTears()
{
	Release();
}

void CTears::Initialize(void)
{
	m_tInfo.fX = 100.f;		// ���� X
	m_tInfo.fY = 100.f;		// ���� Y

	m_tInfo.fCX = 64.f;	// �÷��̾� ���� ������
	m_tInfo.fCY = 64.f;	// �÷��̾� ���� ������

	m_fSpeed = 1.f;

	m_eGroup = GAMEOBJECT;

	Insert_Texture();
	First_State();

	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Success.wav", SOUND_EFFECT, g_fSound);
	
}

int CTears::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	Motion_Change();

	// ���ʿ��� ���� �Ǵ� �������� ��ȭ�� ���� ������ Update_Rect�Լ��� ȣ��
	Move_Frame();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CTears::Late_Update(void)
{

}

void CTears::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
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
		(int)m_tRect.left + iScrollX-1.f,	// 2,3���� : 2, 3���� : ���� ���� ��ġ�� ��ǥ�� ����(L, T ��ǥ)
		(int)m_tRect.top + iScrollY + 9.f,
		(int)m_tInfo.fCX,				// 4,5 ���� : ���� ���� �ؽ�ó�� X, Y ������
		(int)m_tInfo.fCY ,
		hMemDC,							// 6���� : ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,			// 7, 8���� : ��Ʈ���� ����� ���� ��ǥ
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9, 10���� : ������ ��Ʈ���� X,Y ������	
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));
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
			RGB(255, 255, 255));			// 11���� : �����ϰ��� �ϴ� ����
	}
}

void CTears::Release(void)
{
	
}


void CTears::Motion_Change(void)
{		
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{
		case IDLE:
			m_tFrame.iFrameStart	= 0;
			m_tFrame.iFrameEnd		= 0;
			m_tFrame.iFrameMotion	= 0;
			m_tFrame.dwFrameSpeed	= 500;
			m_tFrame.dwFrameTime    = GetTickCount();
			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 500;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		}

		m_ePreState = m_eState;
	}
}

void CTears::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/poptears.bmp", L"Tears");
}

void CTears::First_State(void)
{
	m_pFrameKey = L"Tears";
	m_eState = IDLE;
	m_ePreState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 500;
	m_tFrame.dwFrameTime = GetTickCount();
}
