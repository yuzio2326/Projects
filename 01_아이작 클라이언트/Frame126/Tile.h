#pragma once
#include "Obj.h"
class CTile :
	public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	int			Get_DrawID(void) { return m_iDrawID; }
	int			Get_Option(void) { return m_iOption; }

public:
	void		Set_DrawID(int iDrawID) { m_iDrawID = iDrawID; }
	void		Set_Option(int iOption) { m_iOption = iOption; }
		 
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	int			m_iDrawID;
	int			m_iOption;

};

