#include <windows.h>
#include <tchar.h>
#include "resource1.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	hInst = hInstance;
	// создаём главное окно приложения на основе модального диалога
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	

}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	static HWND hImage;
	switch (message)
	{
	case WM_INITDIALOG: {
					
							HBITMAP hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
							hImage = CreateWindowEx(0, TEXT("STATIC"), 0,
								WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE,
								100, 100,48, 48, hWnd, 0, hInst, 0);
							SendMessage(hImage, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
							UpdateWindow(hImage);
							return TRUE;


	}
	case WM_CLOSE:
		EndDialog(hWnd, 0); // закрываем модальный диалог
		return TRUE;
	}
	return FALSE;
}
