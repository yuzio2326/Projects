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

	GetCursorPos(&ptMouse);	// 마우스 커서의 위치 좌표를 얻어오는 함수,
	ScreenToClient(g_hWnd, &ptMouse);	// 전체 스크린 영역의 좌표를 우리가 생성한 클라이언트 좌표로 변환

	m_tInfo.fX = (float)ptMouse.x;
	m_tInfo.fY = (float)ptMouse.y;

	Update_Rect();
	ShowCursor(false);	// 마우스 커서를 그릴 것인지 설정하는 함수

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
