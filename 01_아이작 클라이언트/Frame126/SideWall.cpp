#include "stdafx.h"
#include "SideWall.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
CSideWall::CSideWall()
{
}


CSideWall::~CSideWall()
{
	Release();
}

void CSideWall::Initialize(void)
{
	m_tInfo.fX = 32.f;		// ���� X
	m_tInfo.fY = 32.f;		// ���� Y

	m_tInfo.fCX = 64.f;	//  ���� ������
	m_tInfo.fCY = 64.f;	//  ���� ������

	m_fSpeed = 100.f;

	m_eGroup = GAMEOBJECT;

	Insert_Texture();




}

int CSideWall::Update(void)
{

	if (true == m_bDead)
		return OBJ_DEAD;

	if (m_fAngle == 0.f)
	{
		m_pFrameKey = L"Side_Wall1";
		m_eState = LEFT_TOP;
	}
	if (m_fAngle == 90.f)
	{
		m_pFrameKey = L"Side_Wall2";
		m_eState = LEFT_BOTTOM;
	}
	if (m_fAngle == 180.f)
	{
		m_pFrameKey = L"Side_Wall3";
		m_eState = RIGHT_BOTTOM;
	}
	if (m_fAngle == 270.f)
	{
		m_pFrameKey = L"Side_Wall4";
		m_eState = RIGHT_TOP;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CSideWall::Late_Update(void)
{

}

void CSideWall::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

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

void CSideWall::Release(void)
{

}

void CSideWall::Motion_Change(void)
{

}

void CSideWall::Insert_Texture(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/side_wall1.bmp", L"Side_Wall1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/side_wall2.bmp", L"Side_Wall2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/side_wall3.bmp", L"Side_Wall3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/side_wall4.bmp", L"Side_Wall4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Plg.bmp", L"Rotation");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Reset.bmp", L"Reset");
}

void CSideWall::First_State(void)
{
}
