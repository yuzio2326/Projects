#pragma once
#include "Include.h"

class CRoom
{
public:
	CRoom();
	virtual ~CRoom();

public:
	virtual  void	Initialize(float _fX, float _fY) PURE;
	virtual  int	Update(void) PURE;
	virtual  void Release(void) PURE;
	void   Set_Pos(float _fX, float _fY);

protected:
	RECT m_tRect;
};

