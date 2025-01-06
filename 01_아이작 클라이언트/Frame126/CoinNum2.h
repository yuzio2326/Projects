#pragma once
#include "Obj.h"
#include "ObjMgr.h"
class CCoinNum2 :
	public CObj
{
public:
	enum STATE { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, END };

public:
	CCoinNum2();
	virtual ~CCoinNum2();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	//행동 패턴 넣고 모션 넣기
private:
	void		Motion_Change(void);	//random act
	void		Insert_Texture(void);
	void		First_State(void);
	void		CountCoin(void);

private:
	POINT		m_tPoint[3];	// 좌 상단, 우 상단, 좌 하단

	STATE			m_eState = END;
	STATE			m_ePreState = END;

	DWORD			dw_CoolTime;

	int			HPArr[20];

};

