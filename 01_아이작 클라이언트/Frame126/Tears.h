#pragma once
#include "Obj.h"
#include "BmpMgr.h"

class CTears :	public CObj
{
public:
	enum TEARS { IDLE, DEAD, END };

public:
	CTears();
	virtual ~CTears();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:

	void		Motion_Change(void);
	void		Insert_Texture(void);
	void		First_State(void);

private:
	bool			m_bJump;
	float			m_fJumpPower;
	float			m_fTime;

	bool			m_bStretch = true;

	CBmpMgr*		m_pBmpMgr;
	TEARS			m_eState = END;
	TEARS			m_ePreState = END;

};

