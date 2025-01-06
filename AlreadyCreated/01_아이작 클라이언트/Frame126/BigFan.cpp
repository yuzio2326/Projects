#include "stdafx.h"
#include "BigFan.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "HeartInclude.h"
#include "AbstactFactory.h"
#include "SoundMgr.h"
#include "BigFanFamiliar.h"
CBigFan::CBigFan()
{
}


CBigFan::~CBigFan()
{
	Release();
}

void CBigFan::Initialize(void)
{
	m_tInfo.fX = 200.f;		// ���� X
	m_tInfo.fY = 300.f;		// ���� Y

	m_tInfo.fCX = 32.f;	//  ���� ������
	m_tInfo.fCY = 32.f;	//  ���� ������

	m_fSpeed = 100.f;

	m_eGroup = GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/collectibles_279_bigfan.bmp", L"BigFan");




}

int CBigFan::Update(void)
{

	if (true == m_bDead)
	{
		CObjMgr::Get_Instance()->AddObject(OBJ_SHIELD, CAbstactFactory<CBigFanFamiliar>::Create());

		CSoundMgr::Get_Instance()->PlaySound(L"power up1.wav", SOUND_ITEM, g_fSound);
		CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_ITEM, g_fSound);

		return OBJ_DEAD;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBigFan::Late_Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing('Q'))
		m_fAngle += 45.f;
}

void CBigFan::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BigFan");

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
		(int)m_tRect.left + iScrollX,	// 2,3���� : 2, 3���� : ���� ���� ��ġ�� ��ǥ�� ����(L, T ��ǥ)
		(int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,				// 4,5 ���� : ���� ���� �ؽ�ó�� X, Y ������	//ũ�� �ø���
		(int)m_tInfo.fCY,
		hMemDC,							// 6���� : ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,			// 7, 8���� : ��Ʈ���� ����� ���� ��ǥ
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9, 10���� : ������ ��Ʈ���� X,Y ������	
		(int)m_tInfo.fCY,
		RGB(195, 195, 195));			// 11���� : �����ϰ��� �ϴ� ����



}

void CBigFan::Release(void)
{

}

void CBigFan::Motion_Change(void)
{

}

void CBigFan::Insert_Texture(void)
{
}

void CBigFan::First_State(void)
{
}
