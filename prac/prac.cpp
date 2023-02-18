// prac.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "prac.h"
#include <vector>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PRAC, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRAC));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PRAC));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PRAC);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}






//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)

{


    



    class Sirkel {
    public:
        POINT position;
        POINT direction;
        COLORREF color;

        Sirkel(POINT pos, POINT dir, COLORREF col) {
            position = pos;
            direction = dir;
            color = col;
           
        }

    };



    static std::vector<Sirkel*> vector;


    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_CREATE:
    {
        SetTimer(hWnd, 0, 100, 0); // vil bruke denne til å oppdatere posisjonen til sirklene
        SetTimer(hWnd, 1, 1000, 0); // vil bruke denne til å pushe ein sirkel til vektoren kvart sekund

    }
    break;


    case WM_TIMER:
    {

        /*
        RECT rect;
        GetClientRect(hWnd, &rect);

        position.x += 1 * direction.x;
        position.y += 2 * direction.y;

        if (position.x <= rect.left || position.x >= rect.right)  //Større enn venstre eller mindre enn høgre(ballen går ut på venstre eller høgre ) så skift retning
        {
            direction.x *= -1;
        }

        if (position.y <= rect.top || position.y >= rect.bottom) {
            direction.y *= -1;
        }
        */
            

        switch (wParam) {
        case 0:
        {
            RECT rect;
            GetClientRect(hWnd, &rect);

            for (Sirkel* s : vector) {
                s->position.x += 5 * s->direction.x;
                s->position.y += 10 * s->direction.y;


                RECT rect;
                GetClientRect(hWnd, &rect);

                if (s->position.x <= rect.left || s->position.x >= rect.right) {
                    s->direction.x *= -1;
                }

                if (s->position.y <= rect.top || s->position.y >= rect.bottom) {
                    s->direction.y *= -1;
                }


            }
          

        }
        break;

        case 1: 
        {
            vector.push_back(new Sirkel({25,25}, {1,1}, RGB(rand() % 255, rand() % 255, rand() % 255)));


        }
        break;



        }
          
         

        InvalidateRect(hWnd, 0, true);

    }
    break;


    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...

            /*
            HBRUSH redBrush = CreateSolidBrush(RGB(255,0,0));
            HGDIOBJ horg = SelectObject(hdc, redBrush);
              Ellipse(hdc, position.x  -10, position.y  -10, position.x + 25, position.y + 25);
              


                SelectObject(hdc, horg);

                DeleteObject(redBrush);
                */

           

            for (Sirkel* s : vector) {

                HBRUSH randomBrush = CreateSolidBrush( s -> color);
                HGDIOBJ horg = SelectObject(hdc, randomBrush);
                Ellipse(hdc, s->position.x - 10, s->position.y - 10, s -> position.x + 25, s -> position.y + 25);
                SelectObject(hdc, horg);
                DeleteObject(randomBrush);

            }

            



            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}





// Message handler for about box.
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
