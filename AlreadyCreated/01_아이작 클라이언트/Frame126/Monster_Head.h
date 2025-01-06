#pragma once
#include "Obj.h"
#include "BmpMgr.h"

class CMonsterHead :	public CObj
{
public:
	enum STATE { IDLE, ATTACK_DOWN, ATTACK_RIGHT, ATTACK_UP, ATTACK_LEFT, HIT, USE_ITEM, DEAD, END };

public:
	CMonsterHead();
	virtual ~CMonsterHead();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Random_ACT(void);
	void		Motion_Change(void);
	void		Insert_Texture(void);
	void		First_State(void);

	CObj*		Create_Bullet(DIR eDir);

private:
	bool			m_bJump;
	float			m_fJumpPower;
	float			m_fTime;

	bool			m_bStretch = true;



protected:
	float			m_fPlayerATK;
	int				m_iPlayerHP;
	int				m_iShotSpeed;

	DWORD			dwshotSpeed;

	CBmpMgr*		m_pBmpMgr;
	STATE			m_eState = END;
	STATE			m_ePreState = END;

	DWORD			dwCoolTime;

};

