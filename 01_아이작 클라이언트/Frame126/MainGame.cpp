#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
#include "PlayerBody.h"
#include "Monster.h"
#include "Mouse.h"
#include "AbstactFactory.h"
#include "CollisionMgr.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "SoundMgr.h"

CMainGame::CMainGame()
	: m_pObjMgr(CObjMgr::Get_Instance())
{
#ifdef _DEBUG
	m_dwTime = GetTickCount();
	m_iFPS = 0;
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 32);
#endif

}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);
		
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");

	// 시작 장면( 첫 장면)
	CSceneMgr::Get_Instance()->Scene_Change(SCENE_LOGO);
	CSoundMgr::Get_Instance()->Initialize();
}

void CMainGame::Update(void)
{

	CKeyMgr::Get_Instance()->Update();
	CSceneMgr::Get_Instance()->Update();
	
}

void CMainGame::Late_Update(void)
{
	CScrollMgr::Get_Instance()->Scroll_Lock();
	CSceneMgr::Get_Instance()->Late_Update();
	m_pObjMgr->Late_Update();	
}

void CMainGame::Render(void)
{
	if (SCENE_LOGO == CSceneMgr::Get_Instance()->Get_SceneID()|| SCENE_CREDIT == CSceneMgr::Get_Instance()->Get_SceneID())
		return;
	
	HDC hBackBuffer = CBmpMgr::Get_Instance()->Find_Image(L"Back");
	
	CSceneMgr::Get_Instance()->Render(hBackBuffer);

	BitBlt(m_DC, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);
	
#ifdef _DEBUG
	// FPS 출력
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		wsprintf(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);	// 윈도우 타이틀에 문자열을 출력하는 함수

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}
#endif
}

void CMainGame::Release(void)
{
	CSoundMgr::Get_Instance()->Destroy_Instance();
	CTileMgr::Get_Instance()->Destroy_Instance();
	CBmpMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CSceneMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CLineMgr::Get_Instance()->Destroy_Instance();
	m_pObjMgr->Destroy_Instance();

	ReleaseDC(g_hWnd, m_DC);
}
