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



	static	void	Collsion_Monster(list<CObj*> _Dest, list<CObj*> _Sour);//dest 삭제, sour 데미지-Atk
	static	void	Collsion_Boss(list<CObj*> _Dest, list<CObj*> _Sour);
	static	void	Collsion_Player_Monster(list<CObj*> _Dest, list<CObj*> _Sour);//player 충돌 히트백 + 데미지-1
	static	void	Collsion_Meterial(list<CObj*> _Dest, list<CObj*> _Sour);//dest 그대로 sour 삭제
	static	void	Collsion_Explosoin(list<CObj*> _Dest, list<CObj*> _Sour);//player 충돌 히트백 + 데미지-10(몬스터 전용)
	static	void	Collsion_Player(list<CObj*> _Dest, list<CObj*> _Sour);//dest 삭제, sour 데미지-1
	static	void	Collsion_PlayerHit(list<CObj*> _Dest, list<CObj*> _Sour);//dest -2, (player만 데미지를 입음)



	//static	void	Colision_Jump(list<CObj*> _Dest);
	static	void	Collision_HitArmor(list<CObj*> _Dest );

	static bool			Check_Sphere(CObj* pDest, CObj* pSour);
	static bool			Check_Rect(CObj* pDest, CObj* pSour, float* _fX, float* _fY);


private:
	DWORD	dwJumpTime;
	DWORD	dwDelay= GetTickCount();

};

