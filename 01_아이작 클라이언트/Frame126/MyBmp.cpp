#include "stdafx.h"
#include "MyBmp.h"


CMyBmp::CMyBmp()
{
}


CMyBmp::~CMyBmp()
{
	Release();
}
void CMyBmp::Load_Bmp(const TCHAR * pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(hDC);	// ���ڰ��� �ش��ϴ� dc�� ȣȯ�� �� �ִ� ȭ�� dc�� �������ִ� �Լ�
	ReleaseDC(g_hWnd, hDC);				// ���۷��� ī��Ʈ ����

										// ��ο� �ִ� ��Ʈ�� �̹��� �о�鿩���� �Լ�
	m_hBitMap = (HBITMAP)LoadImage(NULL,		// ���α׷� �ν��Ͻ� �ڵ�, �̹����� ���α׷����� �о�� ���� �ƴ϶� ���Ϸ� �о�� ���̱� ������ null
		pFilePath,	// ������ ���
		IMAGE_BITMAP,	// � Ÿ������ �о���� �����ϴ� �÷���
		0,			// 4,5 ���� : ����, ���� ũ�⸦ ����, ���Ͽ��� �о�� ���̱� ������ ���� ������ �ʿ䰡 ����
		0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION); // LR_LOADFROMFILE : ���Ͽ��� �̹����� �ҷ����ڴ�, LR_CREATEDIBSECTION : �о�� ������ DIB���·� ��ȯ

												// �غ��� dc�� gdi������Ʈ�� �ҷ��� ��Ʈ���� �����ϱ� ���� ����ϴ� �Լ�
	m_hOldMap = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);


}

void CMyBmp::Release(void)
{
	SelectObject(m_hMemDC, m_hOldMap);
	DeleteObject(m_hBitMap);		// loadimage �ҷ��� ������Ʈ�� �����ϴ� �Լ�, �� ���� dc�� ���� ���õ� gdi������Ʈ�� ������ ���� ����.
	DeleteDC(m_hMemDC);				// ���� ���ǰ� �ִ� ��ü�� �Ժη� �����ϵ��� �� �� ���� ������ ���� ���� ��ġ ������ �ϴ� ����
}
