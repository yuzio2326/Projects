// Frame126.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Frame126.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// ���� ����:
HWND	g_hWnd;
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,			// �޸𸮿� �Ҵ�Ǵ� ��ü, �� ��ü
                     _In_opt_ HINSTANCE hPrevInstance,	// ���� ����Ǿ��� �ν��Ͻ��� �ڵ� ��, ���� ��� NULL
                     _In_ LPWSTR    lpCmdLine,			// �����ڵ�, �ƽ�Ű�ڵ� ��� ȣȯ�ϴ� ���ڿ��� ���� STRING Ŭ����
                     _In_ int       nCmdShow)			// Ctrl + F5�� ���� â ���� ����, ������ â�� ��Ÿ���� �Ű� ���� ���·� �Ѱܹ���
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FRAME126, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FRAME126));

    MSG msg;
	msg.message = WM_NULL;


	CMainGame		MainGame;
	MainGame.Initialize();

	DWORD	dwOldTime = GetTickCount();
	// �ü��(os)�� ������ �������� ���� Ư�� ���� ���� ��ȯ
	// ����ϴ� ���� �뷫 1000������ ���� ���� 1�ʷ� �Ǵ��ϴ� ����
	// GetTickCount ��ȯ���� �뷫 1 / 1000�ʷ� �Ǵ�


    // �⺻ �޽��� �����Դϴ�.
    while (true)
    {
			// PM_REMOVE : �޼����� �о�Ȱ� ���ÿ� �޽��� ť���� ����
			// PM_NOREMOVE : �޼��� ť�� �޽����� �����ϴ����� �Ǵ��Ѵ�.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (dwOldTime + 10 < GetTickCount())
			{
				MainGame.Update();
				MainGame.Late_Update();
				MainGame.Render();

				dwOldTime = GetTickCount();
			}		

			/*MainGame.Update();
			MainGame.Late_Update();
			MainGame.Render();*/
		}       
    }

    return (int) msg.wParam;
}	 



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FRAME126));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   RECT		rc = { 0, 0, WINCX, WINCY };


   // ������ â ũ�⸦ �����ϴ� �Լ�

   // rc = rc + �⺻ ������ â��Ÿ�� + �޴��� ũ��
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
   
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0,		// ������ â�� ����ϴ� ������ â ���� LEFT �� TOP ��ġ 
	  rc.right - rc.left, 
	  rc.bottom - rc.top,	// �����ϰ��� �ϴ� â�� ���λ������, ���� ������
	   nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
//list<RECT>		BulletList;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//static RECT		rc{ 100, 100, 200, 200 };


    switch (message)
    {
	/*case WM_CREATE:

		SetTimer(hWnd, 0 , 0, 0);
		// 1. �ڵ�(� â�� Ÿ�̸Ӹ� ��ġ�� �� �˷��ֱ� ���� ����)
		// 2. Ÿ�̸� id��ȣ, �츮�� Ÿ�̸Ӱ� �� ������ 0���� ���
		// 3. Ÿ�̸� �ֱ�, default ���� 0, 1�ʴ� 1000
		// 4. ���ڰ��� 0 �Ǵ� null�� ��� ������ �ֱ��� �˾Ƽ� WM_TIMER �޼����� �߻���Ŵ

		break;

	case WM_TIMER:
		InvalidateRect(hWnd, NULL, TRUE);
		// ������ ȭ���� �����ϴ� �Լ�
		// �� �Լ��� ȣ��� ��� �ڵ������� WM_PAINT �޽����� �߻�
		// 2���� : ������ â �ȿ��� ������ ������ ����, 0�̰ų� NULL�ΰ�� ������ ��ü ������ ����
		// 3���� : false�� ��� ���� �׸��� �κи� ����, true�� ��� �׷��� ���� �ʴ� �κе� ��� ����

		break;*/

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �޴� ������ ���� �м��մϴ�.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(g_hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
   /* case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.

			// POINT ����ü �ּҰ�

			/ *POINT	Pt{ 100, 100 };

			MoveToEx(hdc, 100, 100, nullptr);
			
		/ *	LineTo(hdc, 200, 100);
			LineTo(hdc, 200, 200);
			LineTo(hdc, 100, 200);
			LineTo(hdc, 100, 100);* /

			// �簢�� �׸��� �Լ�
			Rectangle(hdc, 100, 100, 200, 200);

			// �� �׸��� �Լ�
			Ellipse(hdc, 300, 300, 400, 400);* /
			
			//MoveToEx(hdc, Pt.x, Pt.y, &Pt);
			/ *LineTo(hdc, 200, 200);
			LineTo(hdc, 200, 300);* /

			Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

			for (auto& iter : BulletList)
			{
				Ellipse(hdc, iter.left, iter.top, iter.right, iter.bottom);

				iter.top -= 10;
				iter.bottom -= 10;
			}

            EndPaint(hWnd, &ps);
        }
        break;*/

	case WM_KEYDOWN:

		switch (wParam)
		{
		/*case VK_LEFT:
			rc.left -= 10;
			rc.right -= 10;
			break;

		case VK_RIGHT:
			rc.left += 10;
			rc.right += 10;
			break;

		case VK_UP:
			rc.top -= 10;
			rc.bottom -= 10;
			break;

		case VK_DOWN:
			rc.top	 += 10;
			rc.bottom += 10;
			break;

		case VK_SPACE:
			BulletList.push_back(rc);
			break;*/

		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;		
		}

		break;

    case WM_DESTROY:
		KillTimer(hWnd, 0);		// SetTimer�� ���� ������ Ÿ�̸Ӹ� �����ִ� �Լ� 2���� : 0�� Ÿ�̸� ����
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
