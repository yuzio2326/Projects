#include "stdafx.h"
#include "Prism.h"
#include "Explosion.h"//���� ����ó��
#include "Shield.h"
#include "AbstactFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "PlayerBullet.h"


CPrism::CPrism()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CPrism::~CPrism()
{
	Release();
}

void CPrism::Initialize(void)
{
	m_tInfo.fX = 200.f;		// ���� X
	m_tInfo.fY = 100.f;		// ���� Y

	m_tInfo.fCX = 32.f;	//  ���� ������
	m_tInfo.fCY = 32.f;	//  ���� ������

	m_fSpeed = 1.f;

	dwLifeTime = GetTickCount();

	m_fPrismDistance = 50.f;

	m_eGroup = FAMILIAR;

	Insert_Texture();
	First_State();

	//������ �ֱ�
	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Success.wav", SOUND_EFFECT, g_fSound);

}

int CPrism::Update(void)
{

	if (true == m_bDead)
	{
		return OBJ_DEAD;
	}

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	if (m_pTarget)
	{
		m_fAngle -= m_fSpeed;
		//�����̴� �������� ��ġ�� �÷��̾��� ��ġ XY�� �޾� �� ���·� �����δ�.
		m_tInfo.fX = long(m_pTarget->Get_Info().fX + cosf(m_fAngle * (PI / 180.f)) * m_fPrismDistance);
		m_tInfo.fY = long(m_pTarget->Get_Info().fY - sinf(m_fAngle * (PI / 180.f)) * m_fPrismDistance);

	}
	
	//prism�� bullet ó��
	m_pTargetBullet = CObjMgr::Get_Instance()->Get_Target(OBJ_BULLET, this);

	//bullet�� ������
	if (m_pTargetBullet)
	{

		//���� ���ϴ°� bullet�ϰ� prism ������ ������ ���ϴ°���

		//bullet�� ������ �ް�
		float	fWidth = fabs(m_pTargetBullet->Get_Info().fX - m_tInfo.fX);
		float	fHeight = fabs(m_pTargetBullet->Get_Info().fY - m_tInfo.fY);
		/*
		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
		m_fDistanceAngle = atan2(m_pTargetBullet->Get_Info().fY - m_tInfo.fY, m_pTargetBullet->Get_Info().fX - m_tInfo.fX);
			//(fWidth / fDiagonal);

		m_fDistanceAngle = m_fDistanceAngle * (180.f / PI);

		if (m_tInfo.fY < m_pTargetBullet->Get_Info().fY)
			m_fDistanceAngle *= -1.f;

		m_tInfo.fX += cosf(m_fAngle * (PI / 180.f)) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle * (PI / 180.f)) * m_fSpeed;


		*/
		float	fBCX = (m_pTargetBullet->Get_Info().fCX + m_tInfo.fCX)*0.5f;
		float	fBCY = (m_pTargetBullet->Get_Info().fCY + m_tInfo.fCY)*0.5f;


		if ((fBCX > fWidth) && (fBCY > fHeight))
		{

			CObjMgr::Get_Instance()->AddObject(OBJ_ITEM_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle + 10.f));
			CObjMgr::Get_Instance()->AddObject(OBJ_ITEM_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle - 30.f));
			CObjMgr::Get_Instance()->AddObject(OBJ_ITEM_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle - 10.f));
			CObjMgr::Get_Instance()->AddObject(OBJ_ITEM_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle + 30.f));
				
			//�ޱ� �� ��ġ���� ���� ����� ������ target�� �� bullet�� ����
			m_pTargetBullet->Set_Dead();
		}


	}

	




	Run_Time();
	Motion_Change();
	Move_Frame();
	// ���ʿ��� ���� �Ǵ� �������� ��ȭ�� ���� ������ Update_Rect�Լ��� ȣ��

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPrism::Late_Update(void)
{

}

void CPrism::Render(HDC hDC)
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

void CPrism::Release(void)
{

}


void CPrism::Run_Time(void)
{


}

void CPrism::Motion_Change(void)
{
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{

		case RUNTIME:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		}

		m_ePreState = m_eState;
	}
}

void CPrism::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Familar/familiar_123_angelic_prism.bmp", L"Prism");


}

void CPrism::First_State(void)
{
	m_pFrameKey = L"Prism";
	m_eState = RUNTIME;
	m_ePreState = RUNTIME;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 11;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

}
