#pragma once
#include "Obj.h"
#include "BmpMgr.h"

class CPlayer :	public CObj
{
public:
	enum STATE { IDLE_BODY, WALK_DOWN, WALK_RIGHT, WALK_UP, WALK_LEFT, USE_ITEM_BODY,HIT_BODY,
		IDLE, ATTACK_DOWN, ATTACK_RIGHT, ATTACK_UP, ATTACK_LEFT, HIT, USE_ITEM, DEAD, END };

public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	//virtual void On_Event(CObj* _pObj) override;


private:
	void		Key_Input(void);
	void		Jumping(void);
	void		OffSet(void);
	void		Motion_Change(void);
	void		Insert_Texture(void);
	void		First_State(void);


	CObj*		Create_Bullet(DIR eDir);

private:
	bool			m_bJump;
	float			m_fJumpPower;
	float			m_fTime;

	bool			DMG;

	bool			m_bStretch = true;



protected:
	float			m_fPlayerATK;
	int				m_iCheckPlayerHP;

	DWORD			dwshotSpeed;
	DWORD			dwDelay;
	DWORD			dwImgChange;

	bool			bDelay;
	INFO			m_tBodyinfo;


	CBmpMgr*		m_pBmpMgr;
	STATE			m_eState = END;
	STATE			m_ePreState = END;

};

