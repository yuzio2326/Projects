#pragma once

#include "Tile.h"

class CTileMgr
{
public:
	CTileMgr();
	~CTileMgr();

public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC _DC);
	void		Release(void);

public:
	void	Picking(POINT& pt, int _iDrawID, int _iOption);
	void	Save_Tile(void);
	void	Load_Tile(void);

public:
	static CTileMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CTileMgr;
		}

		return m_pInstance;
	}

	static void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static	CTileMgr*		m_pInstance;
	vector<CObj*>			m_vecTile;

};

