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
	// state ����(���� ����) : FSM�� ������� �ϴ� ��ü�� ���¸� ǥ��(Finite State Machine : ���� ���� ���)
	// �ڽ��� ���� �� �ִ� ������ ������ ���¸� �ǹ�, �׸��� �� �� �ݵ�� �� �ϳ��� ���¸� ���Ѵ�. 
	// ���� ���¿��� Ư�� ������ �Ϸ�Ǹ� �ٸ� ���·� ���� �� �ִ�.
	m_eCurScene = eScene;
	
	/*if (m_pScene)
	{
		// ������ �ϴ��� �ƴϸ� �� ��ȯ ������ �������� ���� Ư�� ������ �������� ���� ���� �����ض�
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

		//shop�� ���������
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
