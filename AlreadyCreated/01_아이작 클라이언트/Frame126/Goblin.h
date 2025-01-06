#pragma once
#include "Obj.h"
#include "BmpMgr.h"

class CGoblin : public CObj
{
public:
	enum STATE { RUNTIME, LEFTMOVE, STAY, REVIVAL1, REVIVAL2, REVIVAL3, REVIVAL4 , END };

public:
	CGoblin();
	virtual ~CGoblin();

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

	bool			m_bStretch = true;

	DWORD			dwLifeTime;
	DWORD			dwRevivalTime;



};

