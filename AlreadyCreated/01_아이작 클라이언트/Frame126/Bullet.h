#pragma once
#include "Obj.h"
#include "BmpMgr.h"
class CBullet :
	public CObj
{
public:
	enum TEARS { ATK, DEAD, END };

public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Atk_Time(void);
	void		Motion_Change(void);
	void		Insert_Texture(void);
	void		First_State(void);


private:
	CBmpMgr*		m_pBmpMgrX;
	TEARS			m_eState = END;
	TEARS			m_ePreState = END;

	DWORD			dwLifeTime;
	float			m_frange;

};

