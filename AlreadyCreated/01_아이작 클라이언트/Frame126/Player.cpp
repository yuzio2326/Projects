#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "AbstactFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "Bomb.h"
#include "PlayerBullet.h"
#include "Rock.h"
#include "MonsterInclude.h"
#include "HeartInclude.h"
#include "PlayerBody.h"
#include "CollisionMgr.h"
#include "ItemInclude.h"
#include "Prism.h"


CPlayer::CPlayer()
	: m_pBmpMgr(CBmpMgr::Get_Instance())
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{



	m_tInfo.fX = 100.f;		// ���� X
	m_tInfo.fY = 100.f;		// ���� Y

	m_tInfo.fCX = 32.f;	// �÷��̾� ���� ������
	m_tInfo.fCY = 30.f;	// �÷��̾� ���� ������

	m_fSpeed = 3.f;

	m_fTime = 0.f;
	
	bDelay = false;

	
	m_iHP = 12;
	m_iMaxHP = 12;	//2�� �ް�����

	m_iCheckHP = m_iHP;

	//m_iCheckPlayerHP = m_iHP;
	m_fATKDMG = 1.f;
	//�����Ÿ�
	m_fRange = 1000;
	//���ݼӵ�
	m_iShotSpeed = 800;
	dwshotSpeed = GetTickCount();
	m_iBomb = 15;
	m_iKey = 10;
	m_iCoin = 20;
	m_iBulletNum = 1;
	dwDelay = GetTickCount();
	DMG = true;


	m_eGroup = GAMEOBJECT;

	Insert_Texture();
	First_State();

	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Success.wav", SOUND_PLAYER, g_fSound);
	
}

int CPlayer::Update(void)
{
	if (m_iHP <= 6)
		m_iHP = 6;

	if (m_iCheckHP <= 0)
		m_bDead = true;

	if (true == m_bDead)
		return OBJ_DEAD;

	if (m_iMaxHP < m_iHP)
		m_iHP = m_iMaxHP;
	//{

	//	// ���⿡ ��� �� �ְ� PRESS ENTER TO MAKE PLAYER �ϱ�
	//}
	//ü�� ȸ���� check �� ȸ���� ü������ �ٲ�
	//if (m_iCheckHP < m_iHP)
	//{
	//	m_iCheckHP = m_iHP;
	//}

	//// �������� ������
	//if (m_bHit == true)
	//{
	//	m_iCheckHP = m_iHP;
	//	if (dwDelay + 2000 < GetTickCount())
	//	{

	//		dwDelay = GetTickCount();
	//	}
	//}
	
	//������ �ƴҶ� 
	if (dwDelay < GetTickCount())
	{
		if (DMG == true)
		{
			
			//�������� ������
			if (m_iHP < m_iCheckHP)
			{
				//üũ�� ���� hp�� �����ϰ� �������� ������.
				m_iCheckHP = m_iHP;
				

				CSoundMgr::Get_Instance()->PlaySound(L"hurt grunt 2.wav", SOUND_PLAYER, g_fSound);
				CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_PLAYER, g_fSound);
			
				DMG = false;
				dwDelay = GetTickCount();
			}
		}
		if (DMG == false)//�����̸�
		{
			//hp�� ������ �ξ��� hp �� �־� ��� �ش� ü���� ���� ��Ű�� 
			m_tInfo.fCX = 64.f;
			m_tInfo.fCY = 64.f;
			//m_eState = HIT;
			//m_pFrameKey = L"Player_Isaac";

			//���߿� ȸ���� ü���� �ٲ�
			if (m_iCheckHP < m_iHP)
				m_iCheckHP = m_iHP;


			if (dwDelay + 100< GetTickCount())
			{
				m_eState = HIT;
				m_pFrameKey = L"Player_Isaac";
			}


				m_iHP = m_iCheckHP;
			//2�ʰ� ���� �ڿ� ������ Ǭ��.
			if (dwDelay + 2000 < GetTickCount())
			{
				DMG = true;
				dwDelay = GetTickCount();
			}
			//if (dwDelay + 4000 < GetTickCount())
				//dwDelay = GetTickCount();
		}

	}


	//�������� ���� ��
	//if (m_iHP < m_iCheckPlayerHP)
	//{
	//	//����ó��
	//	m_iCheckPlayerHP = m_iHP;
	//}
	////ȸ����
	//if (m_iCheckPlayerHP < m_iHP)
	//{
	//	m_iCheckPlayerHP = m_iHP;
	//}



	Key_Input();
	OffSet();
	Motion_Change();
	
	if (99 < m_iBomb)
		m_iBomb = 99;
	if (99 < m_iKey)
		m_iKey = 99;
	if (99 < m_iCoin)
		m_iCoin = 99;
	// ���ʿ��� ���� �Ǵ� �������� ��ȭ�� ���� ������ Update_Rect�Լ��� ȣ��
	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;

}

void CPlayer::Late_Update(void)
{


	////������ �ƴҶ� 
	//if (DMG == true)
	//{

	//	//�������� ������
	//	if (m_iHP < m_iCheckHP)
	//	{
	//		//üũ�� ���� hp�� �����ϰ� �������� ������.
	//		m_iCheckHP = m_iHP;
	//		DMG = false;
	//	}

	//}
	//else//�����̸�
	//{
	//	//hp�� ������ �ξ��� hp �� �־� ��� �ش� ü���� ���� ��Ű�� 
	//	m_iHP = m_iCheckHP;
	//	//2�ʰ� ���� �ڿ� ������ Ǭ��.
	//	if (dwDelay + 2000 < GetTickCount())
	//	{
	//		DMG == true;
	//		dwDelay = GetTickCount();
	//	}
	//}
	/*if (m_iHP < m_iCheckPlayerHP)
	{
		if (dwDelay + 2000 < GetTickCount())
		{

			bDelay = true;
			dwDelay = GetTickCount();
		}

		if (bDelay == true)
		{
			m_iHP = m_iCheckPlayerHP;
		}
		else if (bDelay == false)
		{
			m_iCheckPlayerHP = m_iHP;
		}

	}*/

	//if (m_iCheckHP < m_iHP)
	//{
	//	m_iCheckHP = m_iHP;
	//}

	//// �������� ������
	//if (m_bHit == true)
	//{
	//	m_iCheckHP = m_iHP;
	//	if (dwDelay + 2000 < GetTickCount())
	//	{

	//		dwDelay = GetTickCount();
	//	}
	//}
}

void CPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX(); 
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = m_pBmpMgr->Find_Image(m_pFrameKey);
	HDC hStretchDC = m_pBmpMgr->Find_Image(L"Stretch");

	//BitBlt(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tInfo.fCX, m_tInfo.fCY, hMemDC, 0, 0, SRCCOPY);
	// 1���� : ���� ���� ���������� �׸��� �׸� DC
	// 2, 3���� : ���� ���� ��ġ�� ��ǥ�� ����(L, T ��ǥ)
	// 4, 5���� : ���� ���� �ؽ�ó�� X, Y ������
	// 6 ���� : ��Ʈ���� ������ �ִ� DC
	// 7, 8���� : ��Ʈ���� ����� ���� ��ǥ(L, T��ǥ)
	// 9���� : ��� ȿ���� ���� SRCCOPY : �״�� ���
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
						RGB(195, 195, 195));			// 11���� : �����ϰ��� �ϴ� ����
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
			RGB(195, 195, 195));			// 11���� : �����ϰ��� �ϴ� ����
	}
	
}

void CPlayer::Release(void)
{
	
}

//void CPlayer::On_Event(CObj * _pObj)
//{
//	switch (_pObj->Get_ID())
//	{
//
//	default:
//		break;
//	}
//}

void CPlayer::Key_Input(void)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	float	fY = 0.f;
	//
	m_tInfo.fCX = 32.f;	// �÷��̾� ���� ������
	m_tInfo.fCY = 30.f;	// �÷��̾� ���� ������

	if (CKeyMgr::Get_Instance()->Key_Pressing('W'))
	{
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		{
			m_tInfo.fX -= m_fSpeed;
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
				m_tInfo.fY += m_fSpeed;
			else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
				m_tInfo.fY -= m_fSpeed;
		}

		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		{
			m_tInfo.fX += m_fSpeed;
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
				m_tInfo.fY += m_fSpeed;
			else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
				m_tInfo.fY -= m_fSpeed;

		}

		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			m_tInfo.fY += m_fSpeed;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			m_tInfo.fY -= m_fSpeed;
		}
		m_pFrameKey = L"back_shot";
		m_eState = ATTACK_UP;
		//getticcount �ֱ�
		if (dwshotSpeed + m_iShotSpeed < GetTickCount())
		{
			if (3 <= m_iBulletNum)
			{
				CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, 75.f));
				CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, 85.f));
				CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, 95.f));
				CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, 105.f));

			}
			else
				CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX , m_tInfo.fY , 90.f));

			dwshotSpeed = GetTickCount();
		}

		
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
	{
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		{
			m_tInfo.fX -= m_fSpeed;
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
				m_tInfo.fY += m_fSpeed;
			else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
				m_tInfo.fY -= m_fSpeed;
		}

		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		{
			m_tInfo.fX += m_fSpeed;
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
				m_tInfo.fY += m_fSpeed;
			else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
				m_tInfo.fY -= m_fSpeed;

		}

		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			m_tInfo.fY += m_fSpeed;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			m_tInfo.fY -= m_fSpeed;
		}
		m_pFrameKey = L"side_shot";
		m_eState = ATTACK_LEFT;
		m_bStretch = false;
		if (dwshotSpeed + m_iShotSpeed < GetTickCount())
		{
			if (3 <= m_iBulletNum)
			{
				CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, 165.f));
				CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, 175.f));
				CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, 185.f));
				CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, 195.f));

			}
			else
				CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX , m_tInfo.fY , 180.f));

			dwshotSpeed = GetTickCount();
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('S'))
	{
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		{
			m_tInfo.fX -= m_fSpeed;
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
				m_tInfo.fY += m_fSpeed;
			else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
				m_tInfo.fY -= m_fSpeed;
		}

		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		{
			m_tInfo.fX += m_fSpeed;
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
				m_tInfo.fY += m_fSpeed;
			else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
				m_tInfo.fY -= m_fSpeed;

		}

		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			m_tInfo.fY += m_fSpeed;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			m_tInfo.fY -= m_fSpeed;
		}
		m_pFrameKey = L"front_shot";
		m_eState = ATTACK_DOWN;
		if (dwshotSpeed + m_iShotSpeed < GetTickCount())
		{
			if (3 <= m_iBulletNum)
			{
				CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, 255.f));
				CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, 275.f));
				CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, 285.f));
				CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, 265.f));

			}
			else
				CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX , m_tInfo.fY , 270.f));

			dwshotSpeed = GetTickCount();
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
	{
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		{
			m_tInfo.fX -= m_fSpeed;
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
				m_tInfo.fY += m_fSpeed;
			else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
				m_tInfo.fY -= m_fSpeed;
		}

		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		{
			m_tInfo.fX += m_fSpeed;
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
				m_tInfo.fY += m_fSpeed;
			else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
				m_tInfo.fY -= m_fSpeed;

		}

		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			m_tInfo.fY += m_fSpeed;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			m_tInfo.fY -= m_fSpeed;
		}
		m_pFrameKey = L"side_shot";
		m_eState = ATTACK_LEFT;
		m_bStretch = true;
		if (dwshotSpeed + m_iShotSpeed < GetTickCount())
		{
			if (3 <= m_iBulletNum)
			{
				CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, 15.f));
				CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, 5.f));
				CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, 355.f));
				CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, 345.f));
			}
			else
				CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstactFactory<CPlayerBullet>::Create(m_tInfo.fX , m_tInfo.fY, 0.f));


			dwshotSpeed = GetTickCount();
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
			m_tInfo.fY += m_fSpeed;
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
			m_tInfo.fY -= m_fSpeed;
		m_pFrameKey = L"Player_Isaac";
		m_eState = IDLE;
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
			m_tInfo.fY += m_fSpeed;
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
			m_tInfo.fY -= m_fSpeed;
		m_pFrameKey = L"Player_Isaac";
		m_eState = IDLE;
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
		m_pFrameKey = L"Player_Isaac";
		m_eState = IDLE;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
		m_pFrameKey = L"Player_Isaac";
		m_eState = IDLE;
	}
	//
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		/*if (m_bJump)
			return;

		m_bJump = true;	*/

		//m_pFrameKey = L"Player_UP";
		if(3<=m_iCoin)
			CObjMgr::Get_Instance()->AddObject(OBJ_UI, CAbstactFactory<CActive1>::Create(m_tInfo.fX, m_tInfo.fY, 0));

		m_pFrameKey = L"Player_Isaac";
		m_eState = USE_ITEM;

	}
	else
		//return ;
		m_eState = IDLE;
	if (CKeyMgr::Get_Instance()->Key_Pressing('E'))
	{
		if (m_iBomb > 0)
		{
			if (dwshotSpeed + 200 < GetTickCount())
			{
				CObjMgr::Get_Instance()->AddObject(OBJ_BOMB, CAbstactFactory<CBomb>::Create(m_tInfo.fX, m_tInfo.fY + 5.f, 0));
				dwshotSpeed = GetTickCount();
				--m_iBomb;
			}
		}
		else
			return;

	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('R'))
	{
		if (m_iBomb > 0)
		{
			if (dwshotSpeed + 200 < GetTickCount())
			{
				CObjMgr::Get_Instance()->AddObject(OBJ_BOMB, CAbstactFactory<CTrollBomb>::Create(m_tInfo.fX, m_tInfo.fY + 5.f, 0));
				dwshotSpeed = GetTickCount();
			}
		}

	}
	else if (CKeyMgr::Get_Instance()->Key_Down('Z'))
	{
		if (m_iBomb > 0)
		{
			if (dwshotSpeed + 200 < GetTickCount())
			{
				CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstactFactory<CBossIsaac>::Create());
				dwshotSpeed = GetTickCount();
			}
		}

	}
	else if (CKeyMgr::Get_Instance()->Key_Down('X'))
	{
		if (m_iBomb > 0)
		{
			if (dwshotSpeed + 200 < GetTickCount())
			{
				CObjMgr::Get_Instance()->AddObject(OBJ_FAMILIAR, CAbstactFactory<CPrism>::Create());
				dwshotSpeed = GetTickCount();
			}
		}

	}
	else if (CKeyMgr::Get_Instance()->Key_Down('C'))
	{
		if (m_iBomb > 0)
		{
			if (dwshotSpeed + 200 < GetTickCount())
			{
				CObjMgr::Get_Instance()->AddObject(OBJ_FYING_MONSTER, CAbstactFactory<CBulletFly>::Create());
				dwshotSpeed = GetTickCount();
			}
		}

	}
	else if (CKeyMgr::Get_Instance()->Key_Down('F'))
	{
		if (m_iBomb > 0)
		{
			if (dwshotSpeed + 200 < GetTickCount())
			{
				CObjMgr::Get_Instance()->AddObject(OBJ_METERIAL, CAbstactFactory<CRock>::Create(m_tInfo.fX,m_tInfo.fY));
				dwshotSpeed = GetTickCount();
			}
		}

	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_F1))
	{
		g_fSound -= 0.01f;

		if (g_fSound > 1.f)
			g_fSound = 1.f;

		CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_EFFECT, g_fSound);
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_F2))
	{
		g_fSound += 0.01f;

		if (g_fSound > 1.f)
			g_fSound = 1.f;

		CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_EFFECT, g_fSound);
	}
	
	if (CKeyMgr::Get_Instance()->Key_Down(VK_F3))
	{
		//CSoundMgr::Get_Instance()->PlaySound(L"boss explosions 0.wav", SOUND_EFFECT, g_fSound);
		return;
	}
	

}


void CPlayer::OffSet(void)
{
	int		iOffset = WINCX >> 1;
	
	int		iOffsetLeftX = 100;
	int		iOffsetRightX = 800;

	int		iOffsetTop = 100;
	int		iOffsetBottom = 540;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	// �߰� �������� �÷��̾ ������ ���ϴ� ���
	if (iOffsetLeftX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffsetRightX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	if (iOffsetTop > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	if (iOffsetBottom < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
}

void CPlayer::Motion_Change(void)
{		
	if (m_ePreState != m_eState)
	{
		switch (m_eState)
		{
		case IDLE:
			m_tFrame.iFrameStart	= 0;
			m_tFrame.iFrameEnd		= 0;
			m_tFrame.iFrameMotion	= 0;
			m_tFrame.dwFrameSpeed	= 800;
			m_tFrame.dwFrameTime    = GetTickCount();
			break;

	
		case ATTACK_DOWN:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 1;
				m_tFrame.iFrameMotion = 0;
				m_tFrame.dwFrameSpeed = m_iShotSpeed*0.2;
				m_tFrame.dwFrameTime = GetTickCount();
				break;


		case ATTACK_RIGHT:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 1;
				m_tFrame.iFrameMotion = 0;
				m_tFrame.dwFrameSpeed = m_iShotSpeed*0.2;
				m_tFrame.dwFrameTime = GetTickCount();
				break;


		case ATTACK_UP:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 1;
				m_tFrame.iFrameMotion = 0;
				m_tFrame.dwFrameSpeed = m_iShotSpeed*0.2;
				m_tFrame.dwFrameTime = GetTickCount();
				break;


		case ATTACK_LEFT:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 1;
				m_tFrame.iFrameMotion = 0;
				m_tFrame.dwFrameSpeed = m_iShotSpeed*0.2;
				m_tFrame.dwFrameTime = GetTickCount();
			break;

		case HIT:
			m_tFrame.iFrameStart = 2;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameMotion = 3;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case USE_ITEM:
			m_tFrame.iFrameStart = 8;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.dwFrameSpeed = 1000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		case DEAD:
			m_tFrame.iFrameStart = 6;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iFrameMotion = 5;
			m_tFrame.dwFrameSpeed = 2000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}

		m_ePreState = m_eState;
	}
}

void CPlayer::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/character_001_isaac.bmp", L"Player_Isaac");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/side_shot.bmp", L"side_shot");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/back_shot.bmp", L"back_shot");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/front_shot.bmp", L"front_shot");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Stretch.bmp", L"Stretch");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Active/collectibles_295_magicfingers.bmp", L"Stretch");




}

void CPlayer::First_State(void)
{
	m_pFrameKey = L"Player_Isaac";
	m_eState = IDLE;
	m_ePreState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.dwFrameSpeed = 500;
	m_tFrame.dwFrameTime = GetTickCount();
}

//CObj * CPlayer::Create_Bullet(DIR eDir)
//{
//	CObj*		pBullet = nullptr;
//	pBullet = CAbstactFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, eDir);
//
//	return pBullet;
//}
