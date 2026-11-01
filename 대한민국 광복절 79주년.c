#include <stdio.h>
#include <Windows.h>

HINSTANCE hInstance;

void Init();
void Draw();

int main(void)
{
	Init();
	Draw();
	
	return 0;
}

void Init()
{
	// Setup console window
	system("title 대한민국 광복절 79주년 만세!");
	system("mode con cols=240 lines=80");
	system("color f0");
	
	hInstance = GetModuleHandle(NULL);
	
	// Hide console cursor
	CONSOLE_CURSOR_INFO consoleCursorInfo;
	
	consoleCursorInfo.bVisible = 0;
	consoleCursorInfo.dwSize = 1;
	
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);
}

void Draw()
{
	RECT windowRect;
	HWND consoleWindow = GetConsoleWindow();
	HDC hdc = GetDC(consoleWindow);
	HBITMAP hBitmap;
	HBITMAP hOldBitmap;
	BITMAP bitmap;
	
	GetWindowRect(consoleWindow, &windowRect);
	
	hBitmap = LoadBitmap(hInstnace, MAKEINTRESOURCE(IDB_BITMAP2));
	
	GetObject(hBitmap, sizeof(BITMAP), &bitmap);
	
	
	
	DeleteDC(hBitmap);
	
	ReleaseDC(consoleWindow, hdc);
}
