#include "stdafx.h"
#include "WallMgr.h"
#include "AbstactFactory.h"
#include "ScrollMgr.h"

CWallMgr*	CWallMgr::m_pInstance = nullptr;

CWallMgr::CWallMgr()
{
}

CWallMgr::~CWallMgr()
{
	Release();
}

void CWallMgr::Initialize(void)
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float	fX = float((TILECX * j) + (TILECX >> 1));
			float	fY = float((TILECY * i) + (TILECY >> 1));

			CObj*	pObj = CAbstactFactory<CWall>::Create(fX, fY);
			m_vecWall.push_back(pObj);
		}
	}
}

void CWallMgr::Update(void)
{
	for (auto& iter : m_vecWall)
		iter->Update();
}

void CWallMgr::Late_Update(void)
{
}

void CWallMgr::Render(HDC _DC)
{
	/*for (auto& iter : m_vecTile)
		iter->Render(_DC);*/

	int	iCullX = int(abs(CScrollMgr::Get_Instance()->Get_ScrollX()*2 / TILECX));
	int	iCullY = int(abs(CScrollMgr::Get_Instance()->Get_ScrollY()*2 / TILECY));

	int	iCullEndX = iCullX + WINCX / TILECX + 2;
	int	iCullEndY = iCullY + WINCY / TILECY + 2;


	for (int i = iCullY; i < iCullEndY; ++i)
	{
		for (int j = iCullX; j < iCullEndX; ++j)
		{
			int	iIndex = i * TILEX + j;

			if(0 > iIndex || (size_t)iIndex >= m_vecWall.size())
				continue;

			m_vecWall[iIndex]->Render(_DC);
		}
	}


}

void CWallMgr::Release(void)
{
	for_each(m_vecWall.begin(), m_vecWall.end(), CDeleteObj());
	m_vecWall.clear();
}

void CWallMgr::Picking(POINT& pt, int _iDrawID, int _iOption)
{
	int		x = pt.x / TILECX;
	int		y = pt.y / TILECY;

	int		iIndex = y * TILEX + x;

	if (0 > iIndex || m_vecWall.size() <= (size_t)iIndex)
		return;


	dynamic_cast<CWall*>(m_vecWall[iIndex])->Set_DrawID(_iDrawID);
	dynamic_cast<CWall*>(m_vecWall[iIndex])->Set_Option(_iOption);


}

void CWallMgr::Save_Wall(void)
{
	HANDLE		hFile = CreateFile(L"../Data/Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	int	iDrawID = 0, iOption = 0;
	DWORD		dwByte = 0;

	for (auto& iter : m_vecWall)
	{
		iDrawID = dynamic_cast<CWall*>(iter)->Get_DrawID();
		iOption = dynamic_cast<CWall*>(iter)->Get_Option();

		WriteFile(hFile, &iter->Get_Info(), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Tile Save", L"성공", MB_OK);

}

void CWallMgr::Load_Wall(void)
{
	HANDLE		hFile = CreateFile(L"../Data/Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	INFO	tInfo{};

	int	iDrawID = 0, iOption = 0;
	DWORD		dwByte = 0;

	while(true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj*		pTile = CAbstactFactory<CWall>::Create(tInfo.fX, tInfo.fY);
		dynamic_cast<CWall*>(pTile)->Set_DrawID(iDrawID);
		dynamic_cast<CWall*>(pTile)->Set_Option(iOption);

		m_vecWall.push_back(pTile);

	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Wall Load", L"성공", MB_OK);
}
