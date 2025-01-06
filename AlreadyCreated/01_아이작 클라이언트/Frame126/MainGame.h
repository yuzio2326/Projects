#pragma once

#include "Include.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize(void);	// �����͸� �ʱ�ȭ�ϴ� �Լ�
	void		Update(void);		// �� �����Ӹ��� �����ϴ� �Լ�
	void		Late_Update(void);
	void		Render(void);		// �� �����Ӹ��� ����ϴ� �Լ�
	void		Release(void);		// ��ü �ı� �� �޸� ���� �Լ�

private:
	HDC			m_DC;
	CObjMgr*	m_pObjMgr;

private:
	#ifdef _DEBUG
	DWORD		m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[32];
	#endif

};

// 1. ���� �簢�� �ȿ��� ��,���� ���� �ε����� �ݴ� �������� �̵��ϴ� ���� �����ϱ�
// 2. �÷��̾ �߻��ϴ� �̻��ϰ� ���Ͱ� �浹�� ��� �� �� �����ϱ�

/*
��Ʈ: IntersectRect(); // �簢�� �浹 �Լ�
1. ��Ʈ �ּ� : �浹�� �߻����� ���� ����� ��Ʈ�� ���� ����
2. ��Ʈ �ּ� : ù ��° rect�� �ּ�
3. ��Ʈ �ּ� : �� ��° RECT�� �ּ�*/

// 3. ��Ÿ����� ���� ����(�˾ƿ���)