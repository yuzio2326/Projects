#pragma once

#include "Obj.h"

// 모든 객체를 중재하기 위한 중재자(메디에이터)패턴을 사용 중
// 객체 생성을 제한하여 외부에서 오로지 한 객체 포인터로만 사용 가능한 싱글톤 패턴을 사용 중

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

