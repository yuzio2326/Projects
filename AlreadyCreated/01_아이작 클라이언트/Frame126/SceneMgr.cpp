#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr)//, m_eCurScene(SCENE_END), m_ePreScene(SCENE_LOGO)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eScene)
{
	// state 패턴(상태 패턴) : FSM을 기반으로 하는 객체의 상태를 표현(Finite State Machine : 유한 상태 기계)
	// 자신이 취할 수 있는 유한한 개수의 상태를 의미, 그리고 그 중 반드시 단 하나만 상태를 취한다. 
	// 현재 상태에서 특정 조건이 완료되면 다른 상태로 변할 수 있다.
	m_eCurScene = eScene;
	
	/*if (m_pScene)
	{
		// 저장을 하던지 아니면 씬 전환 때마다 삭제하지 말고 특정 조건이 벌어지면 이전 씬을 삭제해라
		//Safe_Delete(m_pScene);
		Release();
	}*/

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SCENE_LOGO:
			m_pScene = new CLogo;
			break;

		case SCENE_MENU:
			m_pScene = new CMyMenu;
			break;

		case SCENE_EDIT:
			m_pScene = new CMyEdit;
			break;

		case SCENE_STAGE:
			m_pScene = new CStage;
			break;

		//shop이 만들어지면
		//case SCENE_SHOP:
		//	m_pScene = new CShop;
		//	break;


		case SCENE_CREDIT:
			m_pScene = new CCredit;
			break;
		}

		m_pScene->Initialize();
		m_ePreScene = m_eCurScene;
	}	

}

void CSceneMgr::Update(void)
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update(void)
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC _DC)
{
	m_pScene->Render(_DC);
}

void CSceneMgr::Release(void)
{
	Safe_Delete(m_pScene);
}
