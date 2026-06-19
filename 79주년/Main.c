#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "resource.h"

static HWND hWnd;
static HINSTANCE hInst;

void Init();
void Render();

int main(void)
{
    Init();

    while (1)
    {
        Render();
    }

    return 0;
}

void Init()
{
    // Full screen
    SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

    // Setup console window
    system("title 대한민국 광복절 79주년 만세!");
    system("mode con cols=192 lines=65");

    // Hide console cursor
    CONSOLE_CURSOR_INFO consoleCursorInfo;

    consoleCursorInfo.bVisible = 0;
    consoleCursorInfo.dwSize = 1;

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);

    // Get handle window and handle instance
    hWnd = GetConsoleWindow();
    hInst = GetModuleHandle(NULL);
}

void Render()
{
    int x, y;

    HDC hDC;
    HDC hMemDC;

    static HDC hBackDC;

    HBITMAP hBitmap;
    HBITMAP hOldBitmap;
    HBITMAP hBackBitmap;
    BITMAP bitmap;
    RECT windowRect;

    GetWindowRect(hWnd, &windowRect);

    hDC = GetDC(hWnd);
    hBackDC = CreateCompatibleDC(hDC);
    hMemDC = CreateCompatibleDC(hDC);
    hBackBitmap = CreateCompatibleBitmap(hDC, windowRect.right, windowRect.bottom);
    hOldBitmap = (HBITMAP)SelectObject(hBackDC, hBackBitmap);
    hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));

    GetObject(hBitmap, sizeof(BITMAP), &bitmap);

    x = (windowRect.right >> 1) - (bitmap.bmWidth >> 1);
    y = (windowRect.bottom >> 1) - (bitmap.bmHeight >> 1);

    SelectObject(hMemDC, hBitmap);
    BitBlt(hBackDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hMemDC, 0, 0, SRCCOPY);
    BitBlt(hDC, x, y, x + bitmap.bmWidth, y + bitmap.bmHeight, hBackDC, 0, 0, SRCCOPY);
    DeleteObject(SelectObject(hBackDC, hBackBitmap));
    DeleteObject(hBitmap);
    DeleteDC(hBackDC);
    DeleteDC(hMemDC);
    ReleaseDC(hWnd, hDC);
}