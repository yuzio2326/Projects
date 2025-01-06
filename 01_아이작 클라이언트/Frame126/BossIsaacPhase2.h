#pragma once
#include "Obj.h"
#include "BmpMgr.h"

class CBossIsaacPhase2 : public CObj
{
public:
	enum STATE { IDLE, FLYING, STANDFLY, DEAD, END };

public:
	CBossIsaacPhase2();
	virtual ~CBossIsaacPhase2();

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
	float			t_fAngle;
	int				iRandMontion;

	DWORD			dwAtkStart;
	DWORD			dwChangeATK;
	DWORD			dwATKTime1;
	DWORD			dwATKTime2;


};

