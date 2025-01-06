#pragma once

#include "Include.h"

class CObj abstract
{
public:
	CObj();
	virtual ~CObj();

public:
	void			Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

	void		Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void		Set_PosY(float _fY) { m_tInfo.fY += _fY; }

	void		Set_Direction(DIR eDir) { m_eDir = eDir; }
	void		Set_Dead(void) { m_bDead = true; }
	bool		Get_Dead(void) { return m_bDead; }
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void		Set_Target(CObj* pTarget) { m_pTarget = pTarget; }
	void		Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }

	void		Set_HP(int _HP);
	void		Set_MaxHP(int _MaxHP);
	void		Set_ATKDMG(float ATKDMG);
	void		Set_ShotSpeed(float _shotspeed);
	void		Set_Range(float _fRange);
	void		Set_BulletNum(int _BulletNum);
	void		Set_Speed(float _fSpeed);
	void		Set_Check_Hit(bool _Hit);

	void		Set_Bomb(int _Bomb);
	void		Set_Coin(int _Coin);
	void		Set_Key(int _Key);




	const RENDERID		Get_RenderID(void)const { return m_eGroup; }
	const INFO&			Get_Info(void) const { return m_tInfo; }
	const RECT&			Get_Rect(void) const { return m_tRect; }
	
	const int			Get_HP(void) const { return m_iHP; }
	const int			Get_MAXHP(void) const { return m_iMaxHP; }
	const float			Get_Speed(void) const { return m_fSpeed; }
	const float			Get_Range(void) const { return m_fRange; }
	const float			Get_ATKDMG(void) const { return m_fATKDMG; }
	const int			Get_ShotSpeed(void) const { return m_iShotSpeed; }
	const int			Get_BulletNum(void) const { return m_iBulletNum; }
	const int			Get_CheckHP(void) const { return m_iCheckHP; }


	const int			Get_Bomb(void) const { return m_iBomb; }
	const int			Get_Coin(void) const { return m_iCoin; }
	const int			Get_Key(void) const { return m_iKey; }
	const bool			Get_Check_Hit(void) const { return m_bHit; }

public:
	virtual void		Initialize(void)PURE;
	virtual int			Update(void)PURE;
	virtual void		Late_Update(void)PURE;
	virtual void		Render(HDC hDC)PURE;
	virtual void		Release(void)PURE;

public:
	void			Update_Rect(void);
	void			Move_Frame(void);

protected:
	INFO			m_tInfo;
	RECT			m_tRect;	
	FRAME			m_tFrame;
	RENDERID		m_eGroup;

	DIR				m_eDir;
	float			m_fSpeed;
	bool			m_bDead;
	float			m_fAngle;
	bool			m_bHit;

	//status นื ui ฐüทร
	int				m_iHP;
	int				m_iCheckHP;
	int				m_iMaxHP;
	float			m_fATKDMG;
	float			m_fRange;
	int				m_iShotSpeed;
	int				m_iBulletNum;
	int				m_iBomb;
	int				m_iKey;
	int				m_iCoin;




	CObj*			m_pTarget;
	CObj*			m_pTargetStatus;

	TCHAR*			m_pFrameKey = nullptr;

	static			float g_fSound;
};

