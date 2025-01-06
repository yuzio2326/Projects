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

	m_hMemDC = CreateCompatibleDC(hDC);	// 인자값에 해당하는 dc를 호환할 수 있는 화면 dc를 생성해주는 함수
	ReleaseDC(g_hWnd, hDC);				// 레퍼런스 카운트 감소

										// 경로에 있는 비트맵 이미지 읽어들여오는 함수
	m_hBitMap = (HBITMAP)LoadImage(NULL,		// 프로그램 인스턴스 핸들, 이미지는 프로그램에서 읽어올 것이 아니라 파일로 읽어올 것이기 때문에 null
		pFilePath,	// 파일의 경로
		IMAGE_BITMAP,	// 어떤 타입으로 읽어올지 전달하는 플래그
		0,			// 4,5 인자 : 가로, 세로 크기를 전달, 파일에서 읽어올 것이기 때문에 따로 설정할 필요가 없음
		0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION); // LR_LOADFROMFILE : 파일에서 이미지를 불러오겠다, LR_CREATEDIBSECTION : 읽어온 파일을 DIB형태로 변환

												// 준비한 dc의 gdi오브젝트에 불러온 비트맵을 선택하기 위해 사용하는 함수
	m_hOldMap = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);


}

void CMyBmp::Release(void)
{
	SelectObject(m_hMemDC, m_hOldMap);
	DeleteObject(m_hBitMap);		// loadimage 불러온 오브젝트를 삭제하는 함수, 단 현재 dc에 의해 선택된 gdi오브젝트는 해제할 수가 없다.
	DeleteDC(m_hMemDC);				// 현재 사용되고 있는 객체를 함부로 삭제하도록 둘 수 없기 때문에 생긴 안전 장치 역할을 하는 규정
}
