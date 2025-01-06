#pragma once

#include "Room.h"
#include "Obj.h"

class CRoom1 :
	public CRoom
{
public:
	CRoom1();
	virtual ~CRoom1();

public:
	virtual  void	Initialize(float _fX, float _fY) override;
	virtual  int Update(void) override;
	virtual  void Release(void) override;

private:
	CObj* m_pObj1;
	CObj* m_pObj2;
	CObj* m_pObj3;
};

