#include "stdafx.h"
#include "BulletMonster.h"
#include "Explosion.h"//���� ����ó��
#include "Shield.h"
#include "AbstactFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "MonsterBullet.h"

CBulletMonster::CBulletMonster()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CBulletMonster::~CBulletMonster()
{
	Release();
}

void CBulletMonster::Initialize(void)
{
	m_tInfo.fX = 200.f;		// ���� X
	m_tInfo.fY = 100.f;		// ���� Y

	m_tInfo.fCX = 32.f;	//  ���� ������
	m_tInfo.fCY = 32.f;	//  ���� ������

	m_fSpeed = 0.2f;

	m_iHP = 10.f;
	dwLifeTime = GetTickCount();

	m_fDistance = 200.f;

	m_eGroup = MONSTER;

	dwATKTime = GetTickCount();

	Insert_Texture();
	First_State();

	//������ �ֱ�
	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Success.wav", SOUND_EFFECT, g_fSound);

}

int CBulletMonster::Update(void)
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
		//��ǥ�� �޾� �߻�
		if (fDiagonal<m_fDistance)
		{
			m_pFrameKey = L"BulletMonster";
			m_eState = SHOT;

			if (dwATKTime + 999 < GetTickCount())
			{
				CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/fat wiggle.wav", SOUND_EFFECT, g_fSound);
				CSoundMgr::Get_Instance()->PlaySound(L"fat wiggle.wav", SOUND_EFFECT, g_fSound);

				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_BULLET, CAbstactFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
				dwATKTime = GetTickCount();
			}
		}
		else
		{
			m_pFrameKey = L"BulletMonster";
			m_eState = IDLE;

		}
	}

	// �߰�
	m_tInfo.fX += cosf(m_fAngle * (PI / 180.f)) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * (PI / 180.f)) * m_fSpeed;



	Run_Time();
	Motion_Change();
	Move_Frame();
	// ���ʿ��� ���� �Ǵ� �������� ��ȭ�� ���� ������ Update_Rect�Լ��� ȣ��

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBulletMonster::Late_Update(void)
{

}

void CBulletMonster::Render(HDC hDC)
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

void CBulletMonster::Release(void)
{

}


void CBulletMonster::Run_Time(void)
{


}

void CBulletMonster::Motion_Change(void)
{
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{

		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case SHOT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 333;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		}

		m_ePreState = m_eState;
	}
}

void CBulletMonster::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/monster_029_horf.bmp", L"BulletMonster");


}

void CBulletMonster::First_State(void)
{
	m_pFrameKey = L"BulletMonster";
	m_eState = IDLE;
	m_ePreState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 300;
	m_tFrame.dwFrameTime = GetTickCount();

}
