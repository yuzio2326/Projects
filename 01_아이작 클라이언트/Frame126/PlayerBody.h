#pragma once
#include "Obj.h"
#include "BmpMgr.h"

class CPlayerBody :	public CObj
{
public:
	enum STATE { IDLE, WALK_DOWN, WALK_RIGHT, WALK_UP, WALK_LEFT, HIT, USE_ITEM, DEAD, END };

public:
	CPlayerBody();
	virtual ~CPlayerBody();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Key_Input(void);
	void		OffSet(void);
	void		Motion_Change(void);
	void		Insert_Texture(void);
	void		First_State(void);

private:

	float			m_fJumpPower;
	float			m_fTime;
	int				m_iCheckPlayerHP;
	bool			m_bStretch = true;
	bool			DMG;

	CBmpMgr*		m_pBmpMgr;
	STATE			m_eState = END;
	STATE			m_ePreState = END;
	DWORD			dw_die;

	DWORD			dwshotSpeed;
	DWORD			dwDelay;


};

