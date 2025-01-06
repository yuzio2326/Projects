#pragma once

#include "Include.h"

class CMyBmp
{
public:
	HDC			Get_MemDC() { return m_hMemDC; }

public:
	void		Load_Bmp(const TCHAR* pFilePath);
	void		Release(void);

private:
	HDC			m_hMemDC;

	HBITMAP		m_hBitMap;
	HBITMAP		m_hOldMap;


public:
	CMyBmp();
	~CMyBmp();
};

