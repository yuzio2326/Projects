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
	m_tInfo.fX = 100.f;		// 중점 X
	m_tInfo.fY = 100.f;		// 중점 Y

	m_tInfo.fCX = 32.f;	//  가로 사이즈
	m_tInfo.fCY = 32.f;	//  세로 사이즈

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

	//스위치에 닿았을때
	//if ((fBCX > fWidth) && (fBCY > fHeight))
	//{
	//	bSwitchOn = true;

	//}

	//스위치가 꺼졌을때
	if (bSwitchOn == false)
	{
		m_pFrameKey = L"Switch";
		m_eState = SWITCH_OFF;
		//스위치와 플레이어가 닿았을때
		if ((fBCX > fWidth) && (fBCY > fHeight))
		{
			//스위치가 눌림
			m_pFrameKey = L"Switch";
			m_eState = SWITCH_ON;
			//dw_CoolTime = GetTickCount();
			bSwitchOn = true;
			Add_Monster();
			//addmonster를 하고 m_iStageNum은 10초마다 하나 올리고 10초마다 소환
			//m_iStageNum = 1;
			//10초가 지날때 마다 stage를 1 높인다.
			if (dw_CoolTime +10000<=GetTickCount())
			{
				//m_iStageNum += 1;
				dw_CoolTime = GetTickCount();
			}

		}

	}

	//스위치가 켜졌을때

	if (bSwitchOn == true)
	{

		//10초 후에 버튼이 올라옴
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
	// 1인자 : 복사 받을 최종적으로 그림을 그릴 DC
	// 2, 3인자 : 복사 받을 위치의 좌표를 전달(L, T 좌표)
	// 4, 5인자 : 복사 받을 텍스처의 X, Y 사이즈
	// 6 인자 : 비트맵을 가지고 있는 DC
	// 7, 8인자 : 비트맵을 출력할 시작 좌표(L, T좌표)
	// 9인자 : 출력 효과를 설정 SRCCOPY : 그대로 출력

	//switch
	GdiTransparentBlt(hDC,							// 1인자 : 복사 받을 최종적으로 그림을 그릴 DC
		(int)m_tRect.left + iScrollX,	// 2,3인자 : 2, 3인자 : 복사 받을 위치의 좌표를 전달(L, T 좌표)
		(int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,				// 4,5 인자 : 복사 받을 텍스처의 X, Y 사이즈	//크기 늘리기
		(int)m_tInfo.fCY,
		hMemDC,							// 6인자 : 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,			// 7, 8인자 : 비트맵을 출력할 시작 좌표
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9, 10인자 : 복사할 비트맵의 X,Y 사이즈	
		(int)m_tInfo.fCY,
		RGB(153, 217, 234));			// 11인자 : 제거하고자 하는 색상
	
	//spike
	//GdiTransparentBlt(hDC,							// 1인자 : 복사 받을 최종적으로 그림을 그릴 DC
	//	(int)m_tRect.left + iScrollX,	// 2,3인자 : 2, 3인자 : 복사 받을 위치의 좌표를 전달(L, T 좌표)
	//	(int)m_tRect.top + iScrollY,
	//	(int)m_tInfo.fCX,				// 4,5 인자 : 복사 받을 텍스처의 X, Y 사이즈	//크기 늘리기
	//	(int)m_tInfo.fCY,
	//	hMemDC,							// 6인자 : 비트맵을 가지고 있는 DC
	//	m_tFrame.iFrameStart * (int)m_tInfo.fCX,			// 7, 8인자 : 비트맵을 출력할 시작 좌표
	//	m_tFrame.iFrameMotion * (int)m_tInfo.fCY+96.f,
	//	(int)m_tInfo.fCX,		// 9, 10인자 : 복사할 비트맵의 X,Y 사이즈	
	//	(int)m_tInfo.fCY,
	//	RGB(153, 217, 234));			// 11인자 : 제거하고자 하는 색상
	



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
		//아이템 생성+ 동전 생성(아이템 위치는 100,100에 생성하기)
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
		//방해물 생성
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
	//타겟 bullet monster추가
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
	//타겟 다가오는 monster추가
/*	if (m_iStageNum == 5)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"mushroom poof 2.wav", SOUND_EFFECT, g_fSound);

	}*/
	//boss isaac 생성
	if (m_iStageNum == 5)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"mushroom poof 2.wav", SOUND_EFFECT, g_fSound);
		CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstactFactory<CBossIsaac>::Create());

	}
	//delerium 생성
	if (m_iStageNum == 6)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"mushroom poof 2.wav", SOUND_EFFECT, g_fSound);
		CObjMgr::Get_Instance()->AddObject(OBJ_FYING_MONSTER, CAbstactFactory<CDelerium>::Create());
	}

	//복사	
	//if (m_iStageNum == 3)
	//{
		//CSoundMgr::Get_Instance()->PlaySound(L"mushroom poof 2.wav", SOUND_EFFECT, g_fSound);

	//}
	//

}
