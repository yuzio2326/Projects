#pragma once
#include "Obj.h"
#include "BmpMgr.h"

class CExplosion : public CObj
{
public:
	enum STATE { EXPLO, END };

public:
	CExplosion();
	virtual ~CExplosion();

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
	bool			m_bJump;
	float			m_fJumpPower;
	float			m_fTime;

	CBmpMgr*		m_pBmpMgr;
	STATE			m_eState = END;
	STATE			m_ePreState = END;

	bool			m_bStretch = true;


	DWORD			dwLifeTime;

};

