#include "stdafx.h"
#include "TileMgr.h"
#include "AbstactFactory.h"
#include "ScrollMgr.h"

CTileMgr*	CTileMgr::m_pInstance = nullptr;

CTileMgr::CTileMgr()
{
}

CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize(void)
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float	fX = float((TILECX * j) + (TILECX >> 1));
			float	fY = float((TILECY * i) + (TILECY >> 1));

			CObj*	pObj = CAbstactFactory<CTile>::Create(fX, fY);
			m_vecTile.push_back(pObj);
		}
	}
}

void CTileMgr::Update(void)
{
	for (auto& iter : m_vecTile)
		iter->Update();
}

void CTileMgr::Late_Update(void)
{
}

void CTileMgr::Render(HDC _DC)
{
	/*for (auto& iter : m_vecTile)
		iter->Render(_DC);*/

	int	iCullX = int(abs(CScrollMgr::Get_Instance()->Get_ScrollX() / TILECX));
	int	iCullY = int(abs(CScrollMgr::Get_Instance()->Get_ScrollY() / TILECY));

	int	iCullEndX = iCullX + WINCX / TILECX + 2;
	int	iCullEndY = iCullY + WINCY / TILECY + 2;


	for (int i = iCullY; i < iCullEndY; ++i)
	{
		for (int j = iCullX; j < iCullEndX; ++j)
		{
			int	iIndex = i * TILEX + j;

			if(0 > iIndex || (size_t)iIndex >= m_vecTile.size())
				continue;

			m_vecTile[iIndex]->Render(_DC);
		}
	}


}

void CTileMgr::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());
	m_vecTile.clear();
}

void CTileMgr::Picking(POINT& pt, int _iDrawID, int _iOption)
{
	int		x = pt.x / TILECX;
	int		y = pt.y / TILECY;

	int		iIndex = y * TILEX + x;

	if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
		return;


	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID(_iDrawID);
	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Option(_iOption);


}

void CTileMgr::Save_Tile(void)
{
	HANDLE		hFile = CreateFile(L"../Data/Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	int	iDrawID = 0, iOption = 0;
	DWORD		dwByte = 0;

	for (auto& iter : m_vecTile)
	{
		iDrawID = dynamic_cast<CTile*>(iter)->Get_DrawID();
		iOption = dynamic_cast<CTile*>(iter)->Get_Option();

		WriteFile(hFile, &iter->Get_Info(), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Tile Save", L"성공", MB_OK);

}

void CTileMgr::Load_Tile(void)
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

		CObj*		pTile = CAbstactFactory<CTile>::Create(tInfo.fX, tInfo.fY);
		dynamic_cast<CTile*>(pTile)->Set_DrawID(iDrawID);
		dynamic_cast<CTile*>(pTile)->Set_Option(iOption);

		m_vecTile.push_back(pTile);

	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Tile Load", L"성공", MB_OK);
}
