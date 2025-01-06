#include "stdafx.h"
#include "Goblin.h"
#include "MonsterBullet.h"//���� ����ó��
#include "Shield.h"
#include "AbstactFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"


CGoblin::CGoblin()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CGoblin::~CGoblin()
{
	Release();
}

void CGoblin::Initialize(void)
{
	m_tInfo.fX = 200.f;		// ���� X
	m_tInfo.fY = 200.f;		// ���� Y

	m_tInfo.fCX = 64.f;	//  ���� ������
	m_tInfo.fCY = 64.f;	//  ���� ������

	m_fSpeed = 1.f;

	m_iHP = 15.f;
	dwLifeTime = GetTickCount();

	m_eGroup = GAMEOBJECT;

	Insert_Texture();
	First_State();

	//������ �ֱ�
	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Success.wav", SOUND_EFFECT, g_fSound);

}

int CGoblin::Update(void)
{

	if (true == m_bDead)
	{
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

void CGoblin::Late_Update(void)
{

}

void CGoblin::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = m_pBmpMgr->Find_Image(m_pFrameKey);
	HDC hStretchDC = m_pBmpMgr->Find_Image(L"Stretch");
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

void CGoblin::Release(void)
{

}


void CGoblin::Run_Time(void)
{
	if (5 < m_iHP) 
	{
		if ((m_tInfo.fX < m_pTarget->Get_Info().fX))
		{
			m_pFrameKey = L"Goblin";
			m_eState = RUNTIME;
			m_bStretch = true;
		}
		if ((m_pTarget->Get_Info().fX < m_tInfo.fX))
		{
			m_pFrameKey = L"Goblin";
			m_eState = RUNTIME;
			m_bStretch = false;
		}
	}
	else if (m_iHP <= 5 && dwLifeTime <= GetTickCount())
	{
		m_pFrameKey = L"Goblin";
		m_eState = STAY;
	}

}

void CGoblin::Motion_Change(void)
{
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{
		case STAY:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 2000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

			case REVIVAL1:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

			case REVIVAL2:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 1;
				m_tFrame.iFrameMotion = 1;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
				break;

			case REVIVAL3:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.iFrameMotion = 2;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
				break;

			case REVIVAL4:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.iFrameMotion = 3;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
				break;


			case RUNTIME:
				m_tFrame.iFrameStart = 3;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.iFrameMotion = 3;
				m_tFrame.dwFrameSpeed = 5000;
				m_tFrame.dwFrameTime = GetTickCount();
				break;


		}

		m_ePreState = m_eState;
	}
}

void CGoblin::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/monster_161_globin.bmp", L"Goblin");


}

void CGoblin::First_State(void)
{
	m_pFrameKey = L"Goblin";
	m_eState = RUNTIME;
	m_ePreState = RUNTIME;

	m_tFrame.iFrameStart = 3;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iFrameMotion = 3;
	m_tFrame.dwFrameSpeed = 5000;
	m_tFrame.dwFrameTime = GetTickCount();

}
