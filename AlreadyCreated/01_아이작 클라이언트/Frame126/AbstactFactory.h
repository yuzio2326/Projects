#pragma once

#include "Obj.h"

// �߻� ���丮 ���� : ���� ������ �� ������� �ν��Ͻ��� ����� ������ �߻�ȭ�Ͽ����Ͽ� �߻� ���丮 �����̶� �θ���.
// ��, ��ü ���� �� ���ݵǴ� �������� �۾��� �߻�ȭ�ϴ� �����̶� ���� �� �ִ�.

template<typename T>
class CAbstactFactory
{
public:
	CAbstactFactory() {}
	~CAbstactFactory() {}

public:
	static		CObj*		Create(void)
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static		CObj*		Create(float fX, float fY)
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		pObj->Set_Pos(fX, fY);

		return pObj;
	}

	/*static		CObj*		Create(float fX, float fY, DIR eDir = DIR_END)
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		pObj->Set_Pos(fX, fY);
		pObj->Set_Direction(eDir);		

		return pObj;
	}*/

	static		CObj*		Create(float fX, float fY, float _fAngle)
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		pObj->Set_Pos(fX, fY);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}

};

