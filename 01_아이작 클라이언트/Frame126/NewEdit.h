#pragma once

#include "Include.h"
#include "stdafx.h"
#include "Line.h"
#include "Obj.h"
#define BWIDTH 50

class CNewEdit
{
public :
	enum EDIT_MODE{EDIT1, EDIT2, EDIT_END};
	EDIT_MODE m_eMode;
	void Set_EditMode(EDIT_MODE _eMode)
	{
		m_eMode = _eMode;
	}
private :
	const TCHAR* FILEPATH[11] = { L"../Data/Line.dat" ,
		L"../Data/Obstacle.dat" ,
		L"../Data/CObstacle.dat",
		L"../Data/CFlower.dat",
		L"../Data/CUFMonster.dat",
		L"../Data/CMushroom.dat",
		L"../Data/CBMonster.dat",
		L"../Data/IObstacle.dat",
		L"../Data/CBoss.dat",
		L"../Data/CFlag.dat",
		L"../Data/CGhost.dat",
	};
private:
	enum eDir { LEFT, TOP, RIGHT, BOTTOM };
	enum ePRO { PRO_LINE, PRO_BLOCK, PRO_CBLOCK,PRO_BOSS, PRO_IBLOCK, PRO_FMONSTER, PRO_UFMONSTER, PRO_MMONSTER, PRO_BMONSTER, PRO_FLAG, PRO_GHOST};
	ePRO	m_ePro;
	float	m_fSpeed = 0.f;
private :
	void ProcessDrag();
	void ProcessBLockLineY(float _y);
	void ProcessCBLockLineY(float _y);
	void ProcessCUFMonLineY(float _y);
	void ProcessCFMonLineY(float _y);
	void ProcessLineY(float _y, ePRO _ePro);

	// �߰�
	void ProcessMMonLineY(float _y);
	void ProcessBMonLineY(float _y);
	void ProcessIBLockLineY(float _y);
private :
	void ProcessFlower();
	void ProcessUFMonster();
	void ProcessLine();
	void ProcessBlock();
	void ProcessCBlock();
	void ProcessInitLine();

	// �߰�
	void ProcessMMonster();
	void ProcessBMonster();
	void ProcessIBlock();
	void ProcessBoss();
	void ProcessFlag();
	void ProcessGhost();
private:
	CNewEdit();
	~CNewEdit();

public:
	void	Initialize(void);
	int		Update(void);
	void	Late_Update(void);
	void	Render(HDC _DC);
	void	Release(void);

	void	Save_File(void);
	void	Load_File(void);
public:
	static		CNewEdit*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CNewEdit;
		}
		return m_pInstance;
	}

	static void			Destroy_Instance(void)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
private:
	static		CNewEdit*		m_pInstance;
	LINEPOINT					m_tLinePoint[2];
	map<const TCHAR*, list<CLine*>*> m_ObjMap;
	list<CLine*>				m_LineList;
	list<CObj*>					m_ObList;
	list<CObj*>					m_CObList;
	list<CObj*>					m_UFMonList;
	list<CObj*>					m_BossList;
	list<CObj*>					m_FMonList;
	list<CObj*>					m_MMonList;
	list<CObj*>					m_BMonList;
	list<CObj*>					m_IObList;
	list<CObj*>					m_FlagList;
	list<CObj*>					m_GhostList;

	bool						m_bPress = false;
	bool						m_bRPress = false;
	float						m_fAngle = 0.f;
	CLine*						m_pLine;
	RECT*						m_pRect;
	POINT						m_tPoint;
public:
	list<CLine*>* Get_List() { return &m_LineList; }
	list<CObj*>* Get_ObstacleList() { return &m_ObList; }
	list<CObj*>* Get_CObstacleList() { return &m_CObList; }
};

