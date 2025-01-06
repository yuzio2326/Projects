#pragma once

class CObj;
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static	void	Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour);
	static	void	Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour);
	static	void	Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour);



	static	void	Collsion_Monster(list<CObj*> _Dest, list<CObj*> _Sour);//dest ����, sour ������-Atk
	static	void	Collsion_Boss(list<CObj*> _Dest, list<CObj*> _Sour);
	static	void	Collsion_Player_Monster(list<CObj*> _Dest, list<CObj*> _Sour);//player �浹 ��Ʈ�� + ������-1
	static	void	Collsion_Meterial(list<CObj*> _Dest, list<CObj*> _Sour);//dest �״�� sour ����
	static	void	Collsion_Explosoin(list<CObj*> _Dest, list<CObj*> _Sour);//player �浹 ��Ʈ�� + ������-10(���� ����)
	static	void	Collsion_Player(list<CObj*> _Dest, list<CObj*> _Sour);//dest ����, sour ������-1
	static	void	Collsion_PlayerHit(list<CObj*> _Dest, list<CObj*> _Sour);//dest -2, (player�� �������� ����)



	//static	void	Colision_Jump(list<CObj*> _Dest);
	static	void	Collision_HitArmor(list<CObj*> _Dest );

	static bool			Check_Sphere(CObj* pDest, CObj* pSour);
	static bool			Check_Rect(CObj* pDest, CObj* pSour, float* _fX, float* _fY);


private:
	DWORD	dwJumpTime;
	DWORD	dwDelay= GetTickCount();

};

