#pragma once
#include "Scene.h"
class CEmpty :
	public CScene
{
public:
	CEmpty();
	virtual ~CEmpty();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _DC) override;
	virtual void Release(void) override;

private:
	HWND		m_hVideo;

};

