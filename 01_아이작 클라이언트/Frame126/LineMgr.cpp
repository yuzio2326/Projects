#include "stdafx.h"
#include "LineMgr.h"

CLineMgr*		CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
	Load_File();
}

void CLineMgr::Render(HDC _DC)
{
	for (auto& iter : m_LineList)
		iter->Render(_DC);
}

void CLineMgr::Release(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();
}

bool CLineMgr::Collision_Line(float& _fX, float* _fY)
{
	if (m_LineList.empty())
		return false;

	CLine*		pLine = nullptr;

	for (auto& iter : m_LineList)
	{
		if (_fX >= iter->Get_Info().tLPoint.fX &&
			_fX <= iter->Get_Info().tRPoint.fX)
		{
			pLine = iter;
		}
	}

	if (nullptr == pLine)
		return false;

	// Y = ((y2 - y1) / (x2 - x1)) * (X - x1) + y1

	float	x1 = pLine->Get_Info().tLPoint.fX;
	float	x2 = pLine->Get_Info().tRPoint.fX;

	float	y1 = pLine->Get_Info().tLPoint.fY;
	float	y2 = pLine->Get_Info().tRPoint.fY;
	
	*_fY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

	return true;
}

void CLineMgr::Load_File(void)
{
	HANDLE		hFile = CreateFile(L"../Data/Line.dat",		// ������ ������ ��ο� �̸�
		GENERIC_READ,			// ���� ���� ��� (GENERIC_WRITE ���� ���, GENERIC_READ ���� �Է�)
		NULL,					// �������, ������ ���� �ִ� ���¿��� �ٸ� ���α׷����� ������ �� �㰡 �� ���ΰ�(null�� ��� �������� �ʴ´�)
		NULL,					// ���ȼӼ�, null�� �⺻������ ���Ȼ��¸� ����
		OPEN_EXISTING,			// �������, �ش� ������ ��� �۾��� ������ ���� ��������� ����, CREATE_ALWAYS ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISITING ������ ���� ��쿡�� ���� �ɼ�)
		FILE_ATTRIBUTE_NORMAL,	// ���� �Ӽ�����(�б� ����, ���� ��� ���) FILE_ATTRIBUTE_NORMAL �ƹ��� �Ӽ��� ���� �Ϲ����� ������ ����
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����, �츮�� ������� ���� ���̱� ������ null

	if (INVALID_HANDLE_VALUE == hFile)
	{
		// _T : �ƽ�Ű�ڵ� ���ڿ��� �����ڵ�� ��ȯ�����ִ� ��ũ��
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		// 2���� : �˾� â�� ������ �ϴ� �޼���
		// 3���� : �˾� â�� �̸�
	}

	// ���� ���

	DWORD		dwByte = 0;
	LINE		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo));
	}


	// ������ ���� �Ҹ�
	CloseHandle(hFile);
	MessageBox(g_hWnd, _T("Load �Ϸ�"), _T("����"), MB_OK);
}

