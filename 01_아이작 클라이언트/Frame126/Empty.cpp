#include "stdafx.h"
#include "Empty.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CEmpty::CEmpty()
{
}


CEmpty::~CEmpty()
{
	Release();
}

void CEmpty::Initialize(void)
{
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/Logo.bmp", L"Logo");

	m_hVideo = MCIWndCreate(g_hWnd, nullptr, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, L"../Video/014_defeating_in_the_chest_the-end.wmv");
	// 1. 부모의 윈도우 핸들
	// 2. mci윈도우를 사용하는 인스턴스 핸들
	// 3. 윈도우 모양 설정
	// 4. 재생할 파일의 경로

	// 동영상을 재생할 창 크기를 설정
	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);

	// 동영상 재생
	MCIWndPlay(m_hVideo);

}

void CEmpty::Update(void)
{
	if (MCIWndGetLength(m_hVideo) <= MCIWndGetPosition(m_hVideo)
		|| CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SCENE_MENU);
		return;
	}
}

void CEmpty::Late_Update(void)
{


}

void CEmpty::Render(HDC _DC)
{
	//HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Logo");

	//BitBlt(_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

}

void CEmpty::Release(void)
{
	MCIWndClose(m_hVideo);
}
