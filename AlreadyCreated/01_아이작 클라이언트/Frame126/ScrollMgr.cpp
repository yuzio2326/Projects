#include "stdafx.h"
#include "ScrollMgr.h"


CScrollMgr*	CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
}
void CScrollMgr::Scroll_Lock()
{
	if (0.f < m_fScrollX)	// �÷��̾ ���� ���� ����� ��
		m_fScrollX = 0.f;

	if (WINCX - TILEX * TILECX > m_fScrollX)	// �÷��̾ ������ ���� ����� ��
		m_fScrollX = WINCX - TILEX * TILECX;

	if (0.f < m_fScrollY)	// �÷��̾ ���� ���� ����� ��
		m_fScrollY = 0.f;

	if (WINCY - TILEY * TILECY > m_fScrollY)	// �÷��̾ �Ʒ��� ���� ����� ��
		m_fScrollY = WINCY - TILEY * TILECY;
}
