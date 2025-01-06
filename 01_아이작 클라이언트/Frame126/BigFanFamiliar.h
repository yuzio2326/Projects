#pragma once
#include "Obj.h"
#include "BmpMgr.h"

class CBigFanFamiliar : public CObj
{
public:
	enum STATE { RUNTIME, BIG , END };

public:
	CBigFanFamiliar();
	virtual ~CBigFanFamiliar();

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

	DWORD			dwLifeTime;

	float			m_fBigFanFamiliarDistance;
	CObj*			m_pTargetBullet;
	float			m_fBulletAngle;
	float			m_fDistanceAngle;



};

