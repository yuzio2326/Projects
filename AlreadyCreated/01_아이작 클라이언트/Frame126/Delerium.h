#pragma once
#include "Obj.h"
#include "BmpMgr.h"

class CDelerium : public CObj
{
public:
	enum STATE { IDLE, FORM1, FORM2, FORM3, FORM3_1, FORM3_2, FORM4, FORM5, FORM6, FORM7, FORM8, FORM9, DEAD, END };

public:
	CDelerium();
	virtual ~CDelerium();

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

