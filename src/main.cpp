#include <windows.h>

#include "resource.h"

HBITMAP hBitmap;
HWND hButton;
bool quit = false;

LRESULT CALLBACK WndProc(HWND hwnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            constexpr int width = 50;
            constexpr int height = 25;

            const auto createStruct = reinterpret_cast<CREATESTRUCTW*>(lParam);

            RECT clientRect;
            GetClientRect(hwnd, &clientRect);
            const int clientWidth = clientRect.right - clientRect.left;
            const int clientHeight = clientRect.bottom - clientRect.top;

            hButton = CreateWindowExW(0,
                L"BUTTON", L"OK",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                (clientWidth - width) / 2, clientHeight - height - 10,
                width, height,
                hwnd,
                reinterpret_cast<HMENU>(IDOK),
                createStruct->hInstance,
                nullptr
            );

            hBitmap = LoadBitmapW(createStruct->hInstance, MAKEINTRESOURCEW(IDB_PETER));
            return 0;
        }
        case WM_PAINT: {
            PAINTSTRUCT ps;
            const HDC hdc = BeginPaint(hwnd, &ps);

            if (hBitmap) {
                const HDC hdcMem = CreateCompatibleDC(hdc);
                const auto hOldBitmap = static_cast<HBITMAP>(SelectObject(hdcMem, hBitmap));

                BITMAP bm;
                GetObjectW(hBitmap, sizeof(bm), &bm);

                RECT rc;
                GetClientRect(hwnd, &rc);

                const int x = (rc.right - bm.bmWidth) / 2;
                const int y = (rc.bottom - bm.bmHeight - 35) / 2;

                BitBlt(hdc, x, y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);

                SelectObject(hdcMem, hOldBitmap);
                DeleteDC(hdcMem);
            }

            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_COMMAND: {
            if (LOWORD(wParam) == IDOK) {
                DestroyWindow(hwnd);
                return 0;
            }
        }
        break;
        case WM_DESTROY: {
            if (hBitmap) {
                DeleteObject(hBitmap);
            }
            PostQuitMessage(0);
            quit = true;
            return 0;
        }
        default: break;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(
    _In_ const HINSTANCE hInstance,
    _In_opt_ HINSTANCE /*hPrevInstance*/,
    _In_ LPSTR /*lpCmdLine*/,
    _In_ const int nShowCmd
) {
    constexpr wchar_t windowClassName[] = L"PeterWC";
    constexpr wchar_t windowName[] = L"";
    constexpr int width = 120;
    constexpr int height = 150;

    WNDCLASSW wc {};
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = windowClassName;
    wc.hInstance = hInstance;

    RegisterClassW(&wc);

    MONITORINFO mi {};
    mi.cbSize = sizeof(MONITORINFO);
    GetMonitorInfoW(MonitorFromPoint({ 0, 0 }, MONITOR_DEFAULTTOPRIMARY), &mi);

    const HWND window = CreateWindowExW(0,
        windowClassName, windowName,
        WS_BORDER,
        (mi.rcWork.right - width) / 2, (mi.rcWork.bottom - height) / 2,
        width, height,
        nullptr, nullptr,
        hInstance, nullptr
    );

    ShowWindow(window, nShowCmd);
    UpdateWindow(window);

    MSG msg;
    while (!quit) {
        while (PeekMessageW(&msg, window, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                return 0;
            }

            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    return 0;
}
