#include "stdafx.h"
#include "PlayerBulletEffect.h"
#include "Explosion.h"//���� ����ó��
#include "Shield.h"
#include "AbstactFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"


CPlayerBulletEffect::CPlayerBulletEffect()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CPlayerBulletEffect::~CPlayerBulletEffect()
{
	Release();
}

void CPlayerBulletEffect::Initialize(void)
{
	//bullet�� ���ݷ� ������ͼ� �׸�ŭ ũ�� �ø���
	m_tInfo.fCX = 64.f;	//  ���� ������
	m_tInfo.fCY = 64.f;	//  ���� ������

	m_pTarget = CObjMgr::Get_Instance()->Get_Status(OBJ_BULLET, this);

	m_fATKDMG = CObjMgr::Get_Instance()->Get_Player()->Get_ATKDMG();//m_pTarget->Get_ATKDMG();

	dwLifeTime = GetTickCount();

	m_eGroup = EFFECT;

	Insert_Texture();
	First_State();

	//ȿ���� �ֱ�
	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Success.wav", SOUND_EFFECT, g_fSound);

}

int CPlayerBulletEffect::Update(void)
{

	if (true == m_bDead)
	{

		return OBJ_DEAD;
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

void CPlayerBulletEffect::Late_Update(void)
{


}

void CPlayerBulletEffect::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = m_pBmpMgr->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,							// 1���� : ���� ���� ���������� �׸��� �׸� DC
		(int)m_tRect.left + iScrollX,	// 2,3���� : 2, 3���� : ���� ���� ��ġ�� ��ǥ�� ����(L, T ��ǥ)
		(int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX+ m_fATKDMG*10,				// 4,5 ���� : ���� ���� �ؽ�ó�� X, Y ������
		(int)m_tInfo.fCY+ m_fATKDMG*10,
		hMemDC,							// 6���� : ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,			// 7, 8���� : ��Ʈ���� ����� ���� ��ǥ
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9, 10���� : ������ ��Ʈ���� X,Y ������	
		(int)m_tInfo.fCY,
		RGB(195, 195, 195));			// 11���� : �����ϰ��� �ϴ� ����

}

void CPlayerBulletEffect::Release(void)
{

}


void CPlayerBulletEffect::Run_Time(void)
{

	//if (dwLifeTime + 100 <= GetTickCount())
	//{
	//	m_pFrameKey = L"BOMB";
	//	m_eState = RUNTIME;
	//}


	if (dwLifeTime + 320 <= GetTickCount())
	{
		m_bDead = true;
	}

}

void CPlayerBulletEffect::Motion_Change(void)
{

}

void CPlayerBulletEffect::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/poptear.bmp", L"BulletEffect");


}

void CPlayerBulletEffect::First_State(void)
{
	m_pFrameKey = L"BulletEffect";
	m_eState = RUNTIME;
	m_ePreState = RUNTIME;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 15;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 20;
	m_tFrame.dwFrameTime = GetTickCount();

}
