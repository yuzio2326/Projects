#pragma once
#include "Obj.h"
#include "ObjMgr.h"
class CPickupKey :
	public CObj
{
public:
	enum STATE { IDLE, DEAD, END };

public:
	CPickupKey();
	virtual ~CPickupKey();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	//�ൿ ���� �ְ� ��� �ֱ�
private:
	void		Motion_Change(void);	//random act
	void		Insert_Texture(void);
	void		First_State(void);

private:
	POINT		m_tPoint[3];	// �� ���, �� ���, �� �ϴ�

	int				m_iRockHP;

	STATE			m_eState = END;
	STATE			m_ePreState = END;

	DWORD			dw_CoolTime;

};

