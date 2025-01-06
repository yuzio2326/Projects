#include "stdafx.h"
#include "Wall.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
CWall::CWall()
{
}


CWall::~CWall()
{
	Release();
}

void CWall::Initialize(void)
{
	m_tInfo.fX = 100.f;		// ���� X
	m_tInfo.fY = 100.f;		// ���� Y

	m_tInfo.fCX = 64.f;	//  ���� ������
	m_tInfo.fCY = 64.f;	//  ���� ������

	m_fSpeed = 100.f;

	m_eGroup = GAMEOBJECT;

	Insert_Texture();




}

int CWall::Update(void)
{

	if (true == m_bDead)
		return OBJ_DEAD;

	if (m_fAngle == 0.f)
	{
		m_pFrameKey = L"Wall_Up";
		m_eState = UP;
	}
	if (m_fAngle == 90.f)
	{
		m_pFrameKey = L"Wall_Left";
		m_eState = LEFT;
	}
	if (m_fAngle == 180.f)
	{
		m_pFrameKey = L"Wall_Down";
		m_eState = DOWN;
	}
	if (m_fAngle == 270.f)
	{
		m_pFrameKey = L"Wall_Right";
		m_eState = RIGHT;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CWall::Late_Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
		m_fAngle += 90.f;
}

void CWall::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	HDC hRotationDC = CBmpMgr::Get_Instance()->Find_Image(L"Rotation");
	HDC hResetDC = CBmpMgr::Get_Instance()->Find_Image(L"Reset");

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
		RGB(255, 255, 255));			// 11���� : �����ϰ��� �ϴ� ����



}

void CWall::Release(void)
{

}

void CWall::Motion_Change(void)
{

}

void CWall::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/wall_up.bmp", L"Wall_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/wall_down.bmp", L"Wall_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/wall_left.bmp", L"Wall_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/wall_right.bmp", L"Wall_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Plg.bmp", L"Rotation");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Reset.bmp", L"Reset");

}

void CWall::First_State(void)
{
}
