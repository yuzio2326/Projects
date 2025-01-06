#pragma once

#include "Wall.h"
#include "SideWall.h"

class CWallMgr
{
public:
	CWallMgr();
	~CWallMgr();

public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC _DC);
	void		Release(void);

public:
	void	Picking(POINT& pt, int _iDrawID, int _iOption);
	void	Save_Wall(void);
	void	Load_Wall(void);

public:
	static CWallMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CWallMgr;
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
	static	CWallMgr*		m_pInstance;
	vector<CObj*>			m_vecWall;

};

