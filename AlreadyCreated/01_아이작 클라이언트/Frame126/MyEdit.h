#pragma once
#include "Scene.h"
class CMyEdit :
	public CScene
{
public:
	CMyEdit();
	virtual ~CMyEdit();

private:
	const TCHAR* FILEPATH[11] = { L"../Data/Wall.dat" ,
		L"../Data/Door.dat" ,
		L"../Data/BossIsaac.dat",
		L"../Data/BossDelerium.dat",
		L"../Data/BombFly.dat",
		L"../Data/BulletFly.dat",
		L"../Data/Rock.dat",//
		L"../Data/IObstacle.dat",
		L"../Data/CBoss.dat",
		L"../Data/CFlag.dat",
		L"../Data/CGhost.dat",
	};

private:
	enum ePRO { PRO_LINE, PRO_BLOCK, PRO_CBLOCK, PRO_BOSS, PRO_IBLOCK, PRO_FMONSTER, PRO_UFMONSTER, PRO_MMONSTER, PRO_BMONSTER, PRO_FLAG, PRO_GHOST };
	ePRO	m_ePro;
//private:
//	void ProcessDrag();
//private:
//	void ProcessWall();
//	void ProcessBossIsaac();
//	void ProcessBombFly();
//	void ProcessBulletFly();
//	void ProcessRock();
//	void ProcessSideWall();


public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _DC) override;
	virtual void Release(void) override;

	void	Save_File(void);
	void	Load_File(void);

public:



private:
	//void ProcessDrag();


private:
	void	Key_Input();

};

