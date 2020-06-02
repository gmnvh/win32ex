#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>

/* Globals variables */
HWND hLabel;


/* Local prototypes */
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void createLabels(HWND hwnd);
void createButtons(HWND hwnd);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Button_Example_01";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Button Example 01",            // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position - X, Y, nWidth, nHeight
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 300,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_CREATE:
        createLabels(hwnd);
        createButtons(hwnd);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        EndPaint(hwnd, &ps);
    }
    return 0;

    case WM_COMMAND:
        switch (wParam)
        {
        case 1: /* Button was pressed */

            /* Change the main window title */
            SetWindowTextW(hwnd, L"How to change window title");

            /* Change the label title */
            SetWindowTextW(hLabel, L"How to change label title");
            break;
        }

        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void createLabels(HWND hwnd)
{
    /* Label 1 */
    hLabel = CreateWindowW(L"Static",
                           L"My First Label",
                           WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
                           110, 10, 100, 50, hwnd,
                           NULL, NULL, NULL);
}

void createButtons(HWND hwnd)
{
    CreateWindowW(L"Button", L"Change Title",
                  WS_VISIBLE | WS_CHILD,
                  10, 10, 100, 50, hwnd,
                  (HMENU)1, NULL, NULL);
}