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
	if (0.f < m_fScrollX)	// 플레이어가 왼쪽 벽에 닿았을 때
		m_fScrollX = 0.f;

	if (WINCX - TILEX * TILECX > m_fScrollX)	// 플레이어가 오른쪽 벽에 닿았을 때
		m_fScrollX = WINCX - TILEX * TILECX;

	if (0.f < m_fScrollY)	// 플레이어가 위쪽 벽에 닿았을 때
		m_fScrollY = 0.f;

	if (WINCY - TILEY * TILECY > m_fScrollY)	// 플레이어가 아래쪽 벽에 닿았을 때
		m_fScrollY = WINCY - TILEY * TILECY;
}
