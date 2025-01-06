#include "stdafx.h"
#include "TrollBomb.h"
#include "Explosion.h"//���� ����ó��
#include "Shield.h"
#include "AbstactFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"


CTrollBomb::CTrollBomb()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CTrollBomb::~CTrollBomb()
{
	Release();
}

void CTrollBomb::Initialize(void)
{
	m_tInfo.fX = 200.f;		// ���� X
	m_tInfo.fY = 100.f;		// ���� Y

	m_tInfo.fCX = 32.f;	//  ���� ������
	m_tInfo.fCY = 32.f;	//  ���� ������

	m_fSpeed = 3.f;

	dwLifeTime = GetTickCount();
	
	m_eGroup = GAMEOBJECT;

	Insert_Texture();
	First_State();
	
	//������ �ֱ�
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Item/firedeath hiss.wav", SOUND_EFFECT, g_fSound);

}

int CTrollBomb::Update(void)
{

	if (true == m_bDead)
	{
		CObjMgr::Get_Instance()->AddObject(OBJ_EXPLOSION, CAbstactFactory<CExplosion>::Create(m_tInfo.fX, m_tInfo.fY, 0));
		return OBJ_DEAD;
	}

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	//player �߰� ���� �Լ�
	{

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
	}


	Run_Time();

	Motion_Change();

	Move_Frame();
	// ���ʿ��� ���� �Ǵ� �������� ��ȭ�� ���� ������ Update_Rect�Լ��� ȣ��

	Update_Rect();

	return OBJ_NOEVENT;
}

void CTrollBomb::Late_Update(void)
{
	
}

void CTrollBomb::Render(HDC hDC)
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

void CTrollBomb::Release(void)
{

}


void CTrollBomb::Run_Time(void)
{

	//if (dwLifeTime + 100 <= GetTickCount())
	//{
	//	m_pFrameKey = L"BOMB";
	//	m_eState = RUNTIME;
	//}
	if (dwLifeTime + 2000 <= GetTickCount())
	{
		m_pFrameKey = L"TrollBomb";
		m_eState = BIG;
	}


	if (dwLifeTime + 1000 <= GetTickCount())
		m_bDead = true;

}

void CTrollBomb::Motion_Change(void)
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
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}

		m_ePreState = m_eState;
	}
}

void CTrollBomb::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/TrollBombbmp.bmp", L"TrollBomb");


}

void CTrollBomb::First_State(void)
{
	m_pFrameKey = L"TrollBomb";
	m_eState = RUNTIME;
	m_ePreState = RUNTIME;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

}
