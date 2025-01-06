#pragma once
#include "Obj.h"
class CScrewBullet :
	public CObj
{
public:
	CScrewBullet();
	virtual ~CScrewBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	POINT		m_tCenter;

	float		m_fRotAngle;	// ��ũ�� �̻����� ȸ�� ����
	float		m_fRotSpeed;	// �̻����� �̵� �ӵ�
	float		m_fRotDistance;	// �������κ��� ������ �Ÿ�

	bool		m_bStart;		// �߽� ���� �� ���� ������ ���� ������ �̵����Ѿ��ؼ� ���� ������ �� �����̶� ������ �ֱ� ���� ����

};

