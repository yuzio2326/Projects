#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "AbstactFactory.h"
#include "MyButton.h"
#include "ObjMgr.h"

CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Logo.bmp", L"Menu");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Start.bmp", L"Start");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Edit.bmp", L"Edit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Exit.bmp", L"Exit");

	CObj*	pObj = CAbstactFactory<CMyButton>::Create(200.f, 400.f);
	pObj->Set_FrameKey(L"Start");
	CObjMgr::Get_Instance()->AddObject(OBJ_BUTTON, pObj);

	pObj = CAbstactFactory<CMyButton>::Create(400.f, 400.f);
	pObj->Set_FrameKey(L"Edit");
	CObjMgr::Get_Instance()->AddObject(OBJ_BUTTON, pObj);

	pObj = CAbstactFactory<CMyButton>::Create(600.f, 400.f);
	pObj->Set_FrameKey(L"Exit");
	CObjMgr::Get_Instance()->AddObject(OBJ_BUTTON, pObj);

}

void CMyMenu::Update(void)
{
	CObjMgr::Get_Instance()->Update();
}

void CMyMenu::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMyMenu::Render(HDC _DC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Menu");

	BitBlt(_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(_DC);
}

void CMyMenu::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BUTTON);
}
