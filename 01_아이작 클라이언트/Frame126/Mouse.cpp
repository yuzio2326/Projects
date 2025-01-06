#include "stdafx.h"
#include "Mouse.h"


CMouse::CMouse()
{
}


CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
}

int CMouse::Update(void)
{
	POINT	ptMouse{};

	GetCursorPos(&ptMouse);	// ���콺 Ŀ���� ��ġ ��ǥ�� ������ �Լ�,
	ScreenToClient(g_hWnd, &ptMouse);	// ��ü ��ũ�� ������ ��ǥ�� �츮�� ������ Ŭ���̾�Ʈ ��ǥ�� ��ȯ

	m_tInfo.fX = (float)ptMouse.x;
	m_tInfo.fY = (float)ptMouse.y;

	Update_Rect();
	ShowCursor(false);	// ���콺 Ŀ���� �׸� ������ �����ϴ� �Լ�

	return OBJ_NOEVENT;
}

void CMouse::Late_Update(void)
{
	
}

void CMouse::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMouse::Release(void)
{
	
}
