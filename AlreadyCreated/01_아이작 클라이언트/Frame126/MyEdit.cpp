#include "stdafx.h"
#include "MyEdit.h"
#include "TileMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "Meterial.h"


CMyEdit::CMyEdit()
{
}


CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize(void)
{
	
	CTileMgr::Get_Instance()->Initialize();
}

void CMyEdit::Update(void)
{
	Key_Input();
	CTileMgr::Get_Instance()->Update();


	//ProcessDrag();

}

void CMyEdit::Late_Update(void)
{
	CTileMgr::Get_Instance()->Late_Update();
}

void CMyEdit::Render(HDC _DC)
{
	CTileMgr::Get_Instance()->Render(_DC);
}

void CMyEdit::Release(void)
{
	CTileMgr::Get_Instance()->Destroy_Instance();
}

void CMyEdit::Save_File(void)
{
	CTileMgr::Get_Instance()->Save_Tile();
	
}

void CMyEdit::Load_File(void)
{
	CTileMgr::Get_Instance()->Load_Tile();
}

void CMyEdit::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		CScrollMgr::Get_Instance()->Set_ScrollY(5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		CScrollMgr::Get_Instance()->Set_ScrollY(-5.f);

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		/*float mfX = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fX;
		float mfY = CObjMgr::Get_Instance()->Get_Target(OBJ_MOUSE, nullptr)->Get_Info().fY;
		mfX -= CScrollMgr::Get_Instance()->Get_ScrollX();
		mfY -= CScrollMgr::Get_Instance()->Get_ScrollY();
*/
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();
		
		CTileMgr::Get_Instance()->Picking(pt, 1, 0);

	}

	if (CKeyMgr::Get_Instance()->Key_Down('S'))
		Save_File();

	if (CKeyMgr::Get_Instance()->Key_Down('D'))
		Load_File();
}
