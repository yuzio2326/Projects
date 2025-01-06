#include "stdafx.h"
#include "Room.h"

CRoom::CRoom()
{
	ZeroMemory(&m_tRect, sizeof(RECT));
}


CRoom::~CRoom()
{
}

void CRoom::Initialize(float _fX, float _fY)
{
}

void CRoom::Set_Pos(float _fX, float _fY)
{
	m_tRect.left += _fX;
	m_tRect.right += _fX;
	m_tRect.top += _fY;
	m_tRect.bottom += _fY;
}
