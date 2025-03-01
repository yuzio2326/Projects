// Frame126.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Frame126.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HWND	g_hWnd;
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,			// 메모리에 할당되는 실체, 즉 객체
                     _In_opt_ HINSTANCE hPrevInstance,	// 전에 실행되었던 인스턴스의 핸들 값, 없을 경우 NULL
                     _In_ LPWSTR    lpCmdLine,			// 유니코드, 아스키코드 모두 호환하는 문자열을 만든 STRING 클래스
                     _In_ int       nCmdShow)			// Ctrl + F5를 통해 창 실행 가능, 실행한 창의 스타일을 매개 변수 형태로 넘겨받음
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FRAME126, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
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
	// 운영체제(os)가 구동된 시점으로 부터 특정 정수 값을 반환
	// 상승하던 값이 대략 1000정도가 됐을 때를 1초로 판단하는 개념
	// GetTickCount 반환값을 대략 1 / 1000초로 판단


    // 기본 메시지 루프입니다.
    while (true)
    {
			// PM_REMOVE : 메세지를 읽어옴과 동시에 메시지 큐에서 제거
			// PM_NOREMOVE : 메세지 큐에 메시지가 존재하는지만 판단한다.
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
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
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
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   RECT		rc = { 0, 0, WINCX, WINCY };


   // 윈도우 창 크기를 조절하는 함수

   // rc = rc + 기본 윈도우 창스타일 + 메뉴바 크기
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
   
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0,		// 생성된 창을 출력하는 윈도우 창 기준 LEFT 와 TOP 위치 
	  rc.right - rc.left, 
	  rc.bottom - rc.top,	// 생성하고자 하는 창의 가로사이즈와, 세로 사이즈
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
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
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
		// 1. 핸들(어떤 창에 타이머를 설치할 지 알려주기 위한 변수)
		// 2. 타이머 id번호, 우리는 타이머가 한 개여서 0번만 사용
		// 3. 타이머 주기, default 값은 0, 1초당 1000
		// 4. 인자값이 0 또는 null인 경우 설정한 주기대로 알아서 WM_TIMER 메세지를 발생시킴

		break;

	case WM_TIMER:
		InvalidateRect(hWnd, NULL, TRUE);
		// 윈도우 화면을 갱신하는 함수
		// 이 함수가 호출될 경우 자동적으로 WM_PAINT 메시지가 발생
		// 2인자 : 윈도우 창 안에서 갱신할 범위를 지정, 0이거나 NULL인경우 윈도우 전체 영역에 적용
		// 3인자 : false인 경우 새로 그리는 부분만 갱신, true인 경우 그려져 있지 않는 부분도 모두 갱신

		break;*/

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
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
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.

			// POINT 구조체 주소값

			/ *POINT	Pt{ 100, 100 };

			MoveToEx(hdc, 100, 100, nullptr);
			
		/ *	LineTo(hdc, 200, 100);
			LineTo(hdc, 200, 200);
			LineTo(hdc, 100, 200);
			LineTo(hdc, 100, 100);* /

			// 사각형 그리기 함수
			Rectangle(hdc, 100, 100, 200, 200);

			// 원 그리기 함수
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
		KillTimer(hWnd, 0);		// SetTimer를 통해 생성한 타이머를 지워주는 함수 2인자 : 0번 타이머 삭제
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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
