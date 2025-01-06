#pragma once
#include "Obj.h"
#include "BmpMgr.h"

class CBulletMonster : public CObj
{
public:
	enum STATE { IDLE, SHOT , END };

public:
	CBulletMonster();
	virtual ~CBulletMonster();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Run_Time(void);
	void		Motion_Change(void);
	void		Insert_Texture(void);
	void		First_State(void);

private:

	CBmpMgr*		m_pBmpMgr;
	STATE			m_eState = END;
	STATE			m_ePreState = END;
	float			m_fDistance;


	DWORD			dwLifeTime;
	DWORD			dwATKTime;

};

