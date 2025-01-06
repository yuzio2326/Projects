#include "stdafx.h"
#include "Switch.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "AbstactFactory.h"
#include "MonsterInclude.h"
#include "ItemInclude.h"
#include "Meterial.h"
#include "SoundMgr.h"

CSwitch::CSwitch()
{
}


CSwitch::~CSwitch()
{
	Release();
}

void CSwitch::Initialize(void)
{
	m_tInfo.fX = 100.f;		// ���� X
	m_tInfo.fY = 100.f;		// ���� Y

	m_tInfo.fCX = 32.f;	//  ���� ������
	m_tInfo.fCY = 32.f;	//  ���� ������

	m_fSpeed = 100.f;

	m_eGroup = BACKGROUND;

	Insert_Texture();

	bSwitchOn = false;
	m_iStageNum = 1;
	dw_CoolTime = GetTickCount();
}

int CSwitch::Update(void)
{

	if (true == m_bDead)
		return OBJ_DEAD;
	
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);
	
	float	fWidth = fabs(m_pTarget->Get_Info().fX - m_tInfo.fX);
	float	fHeight = fabs(m_pTarget->Get_Info().fY - m_tInfo.fY);

	float	fBCX = (m_pTarget->Get_Info().fCX + m_tInfo.fCX)*0.3f;
	float	fBCY = (m_pTarget->Get_Info().fCY + m_tInfo.fCY)*0.4f;

	//����ġ�� �������
	//if ((fBCX > fWidth) && (fBCY > fHeight))
	//{
	//	bSwitchOn = true;

	//}

	//����ġ�� ��������
	if (bSwitchOn == false)
	{
		m_pFrameKey = L"Switch";
		m_eState = SWITCH_OFF;
		//����ġ�� �÷��̾ �������
		if ((fBCX > fWidth) && (fBCY > fHeight))
		{
			//����ġ�� ����
			m_pFrameKey = L"Switch";
			m_eState = SWITCH_ON;
			//dw_CoolTime = GetTickCount();
			bSwitchOn = true;
			Add_Monster();
			//addmonster�� �ϰ� m_iStageNum�� 10�ʸ��� �ϳ� �ø��� 10�ʸ��� ��ȯ
			//m_iStageNum = 1;
			//10�ʰ� ������ ���� stage�� 1 ���δ�.
			if (dw_CoolTime +10000<=GetTickCount())
			{
				//m_iStageNum += 1;
				dw_CoolTime = GetTickCount();
			}

		}

	}

	//����ġ�� ��������

	if (bSwitchOn == true)
	{

		//10�� �Ŀ� ��ư�� �ö��
		if (dw_CoolTime + 10000 <= GetTickCount())
		{
			m_iStageNum += 1;
			m_pFrameKey = L"Switch";
			m_eState = SWITCH_OFF;
			bSwitchOn = false;
			dw_CoolTime=GetTickCount();

		}


	}




	Update_Rect();


	Motion_Change();
	Move_Frame();

	return OBJ_NOEVENT;
}

void CSwitch::Late_Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing('Q'))
		m_fAngle += 45.f;
}

void CSwitch::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Switch");
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//BitBlt(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tInfo.fCX, m_tInfo.fCY, hMemDC, 0, 0, SRCCOPY);
	// 1���� : ���� ���� ���������� �׸��� �׸� DC
	// 2, 3���� : ���� ���� ��ġ�� ��ǥ�� ����(L, T ��ǥ)
	// 4, 5���� : ���� ���� �ؽ�ó�� X, Y ������
	// 6 ���� : ��Ʈ���� ������ �ִ� DC
	// 7, 8���� : ��Ʈ���� ����� ���� ��ǥ(L, T��ǥ)
	// 9���� : ��� ȿ���� ���� SRCCOPY : �״�� ���

	//switch
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
		RGB(153, 217, 234));			// 11���� : �����ϰ��� �ϴ� ����
	
	//spike
	//GdiTransparentBlt(hDC,							// 1���� : ���� ���� ���������� �׸��� �׸� DC
	//	(int)m_tRect.left + iScrollX,	// 2,3���� : 2, 3���� : ���� ���� ��ġ�� ��ǥ�� ����(L, T ��ǥ)
	//	(int)m_tRect.top + iScrollY,
	//	(int)m_tInfo.fCX,				// 4,5 ���� : ���� ���� �ؽ�ó�� X, Y ������	//ũ�� �ø���
	//	(int)m_tInfo.fCY,
	//	hMemDC,							// 6���� : ��Ʈ���� ������ �ִ� DC
	//	m_tFrame.iFrameStart * (int)m_tInfo.fCX,			// 7, 8���� : ��Ʈ���� ����� ���� ��ǥ
	//	m_tFrame.iFrameMotion * (int)m_tInfo.fCY+96.f,
	//	(int)m_tInfo.fCX,		// 9, 10���� : ������ ��Ʈ���� X,Y ������	
	//	(int)m_tInfo.fCY,
	//	RGB(153, 217, 234));			// 11���� : �����ϰ��� �ϴ� ����
	



}

void CSwitch::Release(void)
{

}

void CSwitch::Motion_Change(void)
{
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{

		case SWITCH_OFF:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case SWITCH_ON:
			m_tFrame.iFrameStart = 1;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case SPIKE_ON:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameMotion = 2;
			m_tFrame.dwFrameSpeed = 10000000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case SPIKE_OFF:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameMotion = 2;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		}

		m_ePreState = m_eState;
	}
}

void CSwitch::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/grid_pressureplate1.bmp", L"Switch");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/grid_pressureplate.bmp", L"Spike");


}

void CSwitch::First_State(void)
{
}

void CSwitch::Add_Monster(void)
{
	if (m_iStageNum == 1)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"mushroom poof 2.wav", SOUND_EFFECT, g_fSound);
		//������ ����+ ���� ����(������ ��ġ�� 100,100�� �����ϱ�)
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CPickupCoin>::Create(420, 300));
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CMagicMushroom>::Create(100, 80));
		CObjMgr::Get_Instance()->AddObject(OBJ_METERIAL, CAbstactFactory<CRock>::Create(128, 80));
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CPickupBomb>::Create(480, 300));
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CPickupHeart>::Create(450, 300));
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CPickupKey>::Create(390, 300));
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CMagicMushroom>::Create(400, 200));
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<Cmutantspider>::Create(350, 200));
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CPrismItem>::Create(300, 200));
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CBigFan>::Create(250, 200));
		//���ع� ����
		for (int i=0; i < 3; i++)
			CObjMgr::Get_Instance()->AddObject(OBJ_METERIAL, CAbstactFactory<CRock>::Create(80 + 32 * i, 120));

		

	}
	if (m_iStageNum == 2)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"mushroom poof 2.wav", SOUND_EFFECT, g_fSound);

		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CPickupHeartHalf>::Create(380, 300));
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CPickupCoin>::Create(400, 300));
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CPickupBomb>::Create(420, 300));
		CObjMgr::Get_Instance()->AddObject(OBJ_FYING_MONSTER, CAbstactFactory<CBombFly>::Create(100, 100));
		CObjMgr::Get_Instance()->AddObject(OBJ_FYING_MONSTER, CAbstactFactory<CBombFly>::Create(700, 100));
		CObjMgr::Get_Instance()->AddObject(OBJ_FYING_MONSTER, CAbstactFactory<CBombFly>::Create(700, 600));
		CObjMgr::Get_Instance()->AddObject(OBJ_FYING_MONSTER, CAbstactFactory<CBombFly>::Create(100, 600));

		for (int i = 0; i < 6; i++)
		{
			CObjMgr::Get_Instance()->AddObject(OBJ_METERIAL, CAbstactFactory<CRock>::Create(320 + 32 * i, 350));
			CObjMgr::Get_Instance()->AddObject(OBJ_METERIAL, CAbstactFactory<CRock>::Create(320 + 32 * i, 550));
			CObjMgr::Get_Instance()->AddObject(OBJ_METERIAL, CAbstactFactory<CRock>::Create(320, 350 + 32 * i));
			CObjMgr::Get_Instance()->AddObject(OBJ_METERIAL, CAbstactFactory<CRock>::Create(478, 350 + 32 * i));

		}
	}
	if (m_iStageNum == 3)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"mushroom poof 2.wav", SOUND_EFFECT, g_fSound);
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CPickupHeart2>::Create(380, 300));
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CPickupCoin>::Create(400, 300));
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CPickupCoin>::Create(410, 290));
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CPickupBomb2>::Create(420, 300));
		CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, CAbstactFactory<CPickupKey>::Create(440, 300));
		CObjMgr::Get_Instance()->AddObject(OBJ_FYING_MONSTER, CAbstactFactory<CBombFly>::Create(100, 100));
		CObjMgr::Get_Instance()->AddObject(OBJ_FYING_MONSTER, CAbstactFactory<CBombFly>::Create(700, 100));
		CObjMgr::Get_Instance()->AddObject(OBJ_FYING_MONSTER, CAbstactFactory<CBombFly>::Create(700, 600));
		CObjMgr::Get_Instance()->AddObject(OBJ_FYING_MONSTER, CAbstactFactory<CBombFly>::Create(100, 600));

		CObjMgr::Get_Instance()->AddObject(OBJ_FYING_MONSTER, CAbstactFactory<CBulletFly>::Create(400, 100));
		CObjMgr::Get_Instance()->AddObject(OBJ_FYING_MONSTER, CAbstactFactory<CBulletFly>::Create(100, 300));
		CObjMgr::Get_Instance()->AddObject(OBJ_FYING_MONSTER, CAbstactFactory<CBulletFly>::Create(700, 300));
		CObjMgr::Get_Instance()->AddObject(OBJ_FYING_MONSTER, CAbstactFactory<CBulletFly>::Create(400, 600));

		//CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstactFactory<CDelerium>::Create());

	}
	//Ÿ�� bullet monster�߰�
	if (m_iStageNum == 4)
	{
	CSoundMgr::Get_Instance()->PlaySound(L"mushroom poof 2.wav", SOUND_EFFECT, g_fSound);
	CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstactFactory<CBulletMonster>::Create(200, 200));
	CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstactFactory<CBulletMonster>::Create(400, 200));
	CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstactFactory<CBulletMonster>::Create(600, 200));
	CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstactFactory<CBulletMonster>::Create(200, 600));
	CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstactFactory<CBulletMonster>::Create(400, 600));
	CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstactFactory<CBulletMonster>::Create(600, 600));

	}
	//Ÿ�� �ٰ����� monster�߰�
/*	if (m_iStageNum == 5)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"mushroom poof 2.wav", SOUND_EFFECT, g_fSound);

	}*/
	//boss isaac ����
	if (m_iStageNum == 5)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"mushroom poof 2.wav", SOUND_EFFECT, g_fSound);
		CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstactFactory<CBossIsaac>::Create());

	}
	//delerium ����
	if (m_iStageNum == 6)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"mushroom poof 2.wav", SOUND_EFFECT, g_fSound);
		CObjMgr::Get_Instance()->AddObject(OBJ_FYING_MONSTER, CAbstactFactory<CDelerium>::Create());
	}

	//����	
	//if (m_iStageNum == 3)
	//{
		//CSoundMgr::Get_Instance()->PlaySound(L"mushroom poof 2.wav", SOUND_EFFECT, g_fSound);

	//}
	//

}
