#pragma once
#include "Obj.h"
#include "ObjMgr.h"
class CPickupHeartHalf :
	public CObj
{
public:
	enum STATE { IDLE, DEAD, END };

public:
	CPickupHeartHalf();
	virtual ~CPickupHeartHalf();

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

private:
	POINT		m_tPoint[3];	// 좌 상단, 우 상단, 좌 하단

	int				m_iRockHP;

	STATE			m_eState = END;
	STATE			m_ePreState = END;

	DWORD			dw_CoolTime;

};

