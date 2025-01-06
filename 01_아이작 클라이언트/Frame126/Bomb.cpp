#include "stdafx.h"
#include "Bomb.h"
#include "Explosion.h"//���� ����ó��
#include "Shield.h"
#include "AbstactFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"


CBomb::CBomb()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CBomb::~CBomb()
{
	Release();
}

void CBomb::Initialize(void)
{
	//m_tInfo.fX = 200.f;		// ���� X
	//m_tInfo.fY = 100.f;		// ���� Y

	m_tInfo.fCX = 32.f;	//  ���� ������
	m_tInfo.fCY = 32.f;	//  ���� ������

	m_fSpeed = 1.f;

	dwLifeTime = GetTickCount();
	
	m_eGroup = GAMEOBJECT;

	Insert_Texture();
	First_State();
	
	//������ �ֱ�
	CSoundMgr::Get_Instance()->PlaySoundW(L"firedeath hiss.wav", SOUND_BGM, g_fSound);
	//CSoundMgr::Get_Instance()->PlaySoundW(L"boss explosions 0.wav", SOUND_EFFECT, g_fSound);
	CSoundMgr::Get_Instance()->PlaySound(L"firedeath hiss.wav", SOUND_ITEM_EFFECT, g_fSound);

	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Success.wav", SOUND_EFFECT, g_fSound);
	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Item/boss explosions 0.wav", SOUND_EFFECT, g_fSound);
}

int CBomb::Update(void)
{

	if (true == m_bDead)
	{
		CObjMgr::Get_Instance()->AddObject(OBJ_EXPLOSION, CAbstactFactory<CExplosion>::Create(m_tInfo.fX, m_tInfo.fY, 0));
	/*	CSoundMgr::Get_Instance()->PlaySound(L"boss explosions 0.wav", SOUND_EFFECT, g_fSound);
		CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_EFFECT, g_fSound);
*/
		return OBJ_DEAD;
	}

	Run_Time();

	Motion_Change();

	Move_Frame();
	// ���ʿ��� ���� �Ǵ� �������� ��ȭ�� ���� ������ Update_Rect�Լ��� ȣ��

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBomb::Late_Update(void)
{
	
}

void CBomb::Render(HDC hDC)
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
			RGB(255, 255, 255));			// 11���� : �����ϰ��� �ϴ� ����

}

void CBomb::Release(void)
{

}


void CBomb::Run_Time(void)
{

	//if (dwLifeTime + 100 <= GetTickCount())
	//{
	//	m_pFrameKey = L"BOMB";
	//	m_eState = RUNTIME;
	//}
	if (dwLifeTime + 1000 <= GetTickCount())
	{
		m_pFrameKey = L"BOMB";
		m_eState = BIG;
	}


	if (dwLifeTime + 2000 <= GetTickCount())
		m_bDead = true;

}

void CBomb::Motion_Change(void)
{
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{

		case RUNTIME:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case BIG:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}

		m_ePreState = m_eState;
	}
}

void CBomb::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/balloon_bomb.bmp", L"BOMB");


}

void CBomb::First_State(void)
{
	m_pFrameKey = L"BOMB";
	m_eState = RUNTIME;
	m_ePreState = RUNTIME;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

}
