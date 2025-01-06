#include "stdafx.h"
#include "Obj.h"

float CObj::g_fSound = 0.1f;

CObj::CObj()
	: m_fSpeed(0.f), m_bDead(false)
	, m_eDir(DIR(DIR_END)), m_fAngle(0.f)
	, m_pTarget(nullptr)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}


CObj::~CObj()
{
}


void CObj::Update_Rect(void)
{
	m_tRect.left	= long(m_tInfo.fX - (m_tInfo.fCX / 2.f));
	m_tRect.top		= long(m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_tRect.right	= long(m_tInfo.fX + (m_tInfo.fCX / 2.f));
	m_tRect.bottom	= long(m_tInfo.fY + (m_tInfo.fCY / 2.f));
}

void CObj::Move_Frame(void)
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}

void CObj::Set_HP(int _HP)
{
	m_iHP += _HP;
}

void CObj::Set_MaxHP(int _MaxHP)
{
	m_iMaxHP += _MaxHP;
}

void CObj::Set_ATKDMG(float ATKDMG)
{
	m_fATKDMG += ATKDMG;
}

void CObj::Set_ShotSpeed(float _shotspeed)
{
	m_iShotSpeed += _shotspeed;
}

void CObj::Set_Range(float _fRange)
{
	m_fRange += _fRange;
}

void CObj::Set_BulletNum(int _BulletNum)
{
	m_iBulletNum += _BulletNum;
}

void CObj::Set_Speed(float _fSpeed)
{
	m_fSpeed += _fSpeed;
}

void CObj::Set_Check_Hit(bool _Hit)
{
	m_bHit = _Hit;
}

void CObj::Set_Bomb(int _Bomb)
{
	m_iBomb += _Bomb;
}

void CObj::Set_Coin(int _Coin)
{
	m_iCoin += _Coin;
}

void CObj::Set_Key(int _Key)
{
	m_iKey += _Key;
}
