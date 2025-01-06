#pragma once

#include "Obj.h"

// ��� ��ü�� �����ϱ� ���� ������(�޵�����)������ ��� ��
// ��ü ������ �����Ͽ� �ܺο��� ������ �� ��ü �����ͷθ� ��� ������ �̱��� ������ ��� ��

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	CObj*		Get_Player() { return m_ObjList[OBJ_PLAYER].front(); }

	CObj*		Get_Target(OBJID eID, CObj* pObj);

	CObj*		Get_Status(OBJID eID, CObj* pObj);

	list<CObj*>*		Get_List(OBJID eID);
	list<CObj*>&		Get_ListRef(OBJID eID);


public:
	void		AddObject(OBJID eID, CObj* pObj);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	void		Delete_ID(OBJID eID);
	void		Save_Obj(void);
	void		Load_Obj(void);


	
private:
	list<CObj*>			m_ObjList[OBJ_END];
	list<CObj*>			m_RenderSort[RENDER_END];

public:
	static CObjMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CObjMgr;
		}

		return m_pInstance;
	}

	static void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static	CObjMgr*		m_pInstance;
	vector<CObj*>			m_vecObj;
	DWORD					dwCheckTime = GetTickCount();

	bool hit = false;

};

