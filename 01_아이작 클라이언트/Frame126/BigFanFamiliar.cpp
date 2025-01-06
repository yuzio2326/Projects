#include "stdafx.h"
#include "BigFanFamiliar.h"
#include "Explosion.h"//���� ����ó��
#include "Shield.h"
#include "AbstactFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "PlayerBullet.h"


CBigFanFamiliar::CBigFanFamiliar()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CBigFanFamiliar::~CBigFanFamiliar()
{
	Release();
}

void CBigFanFamiliar::Initialize(void)
{
	m_tInfo.fX = 200.f;		// ���� X
	m_tInfo.fY = 100.f;		// ���� Y

	m_tInfo.fCX = 32.f;	//  ���� ������
	m_tInfo.fCY = 32.f;	//  ���� ������

	m_fSpeed = 1.5f;

	dwLifeTime = GetTickCount();

	m_fBigFanFamiliarDistance = 30.f;

	m_eGroup = FAMILIAR;

	Insert_Texture();
	First_State();

	//������ �ֱ�
	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Success.wav", SOUND_EFFECT, g_fSound);

}

int CBigFanFamiliar::Update(void)
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
		m_tInfo.fX = long(m_pTarget->Get_Info().fX + cosf(m_fAngle * (PI / 180.f)) * m_fBigFanFamiliarDistance);
		m_tInfo.fY = long(m_pTarget->Get_Info().fY - sinf(m_fAngle * (PI / 180.f)) * m_fBigFanFamiliarDistance);

	}
	
	Run_Time();
	Motion_Change();
	Move_Frame();
	// ���ʿ��� ���� �Ǵ� �������� ��ȭ�� ���� ������ Update_Rect�Լ��� ȣ��

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBigFanFamiliar::Late_Update(void)
{

}

void CBigFanFamiliar::Render(HDC hDC)
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

void CBigFanFamiliar::Release(void)
{

}


void CBigFanFamiliar::Run_Time(void)
{


}

void CBigFanFamiliar::Motion_Change(void)
{
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{

		case RUNTIME:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		}

		m_ePreState = m_eState;
	}
}

void CBigFanFamiliar::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Familar/familiar_orbitals_279_bigfan.bmp", L"BigFanFamiliar");


}

void CBigFanFamiliar::First_State(void)
{
	m_pFrameKey = L"BigFanFamiliar";
	m_eState = RUNTIME;
	m_ePreState = RUNTIME;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

}
