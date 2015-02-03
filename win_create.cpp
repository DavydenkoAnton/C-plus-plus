// Файл WINDOWS.H содержит определения, макросы, и структуры 
// которые используются при написании приложений под Windows. 
#include <windows.h>
#include <tchar.h>
#include <map>
using namespace std;

//прототип оконной процедуры
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Каркасное приложение"); /* Имя класса окна */

typedef LRESULT CALLBACK EventProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
map<UINT, EventProc*> eventMap;

LRESULT CALLBACK KeyboardHanldler(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam) {
	if (wParam == VK_LEFT){
		MoveWindow(hWnd, CW_USEDEFAULT, 100, 400, 240, true);
	}
	TCHAR str[50];
	wsprintf(str, TEXT("code=%d"), wParam); // текущие координаты курсора мыши
	SetWindowText(hWnd, str);
	return 0;
}



LRESULT CALLBACK MouseMove(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam) {
	TCHAR str[50];
	wsprintf(str, TEXT("X=%d                    Y=%d"), LOWORD(lParam), HIWORD(lParam)); // текущие координаты курсора мыши
	SetWindowText(hWnd, str);	// строка выводится в заголовок окна
	return 0;
}


LRESULT CALLBACK OnDoubleClick(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam){
	MessageBox(0,
		TEXT("Двойной щелчок левой кнопкой мыши"),
		TEXT("WM_LBUTTONDBLCLK"),
		MB_OK | MB_ICONINFORMATION);
	return 0;

}

LRESULT CALLBACK OnExit(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam){
	PostQuitMessage(0);	// посылка сообщения WM_QUIT
	return 0;
}





INT WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG Msg;
	WNDCLASSEX wcl;
	int x,y;

	/* 1. Определение класса окна  */

	wcl.cbSize = sizeof (wcl);	// размер структуры WNDCLASSEX 
	wcl.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;	// окно сможет получать сообщения о двойном щелчке (DBLCLK)
	wcl.lpfnWndProc = WindowProc;	// адрес оконной процедуры
	wcl.cbClsExtra = 0;		// используется Windows 
	wcl.cbWndExtra = 0; 	// используется Windows 
	wcl.hInstance = hInst;	// дескриптор данного приложения
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// загрузка стандартной иконки
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);		// загрузка стандартного курсора
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//заполнение окна белым цветом			
	wcl.lpszMenuName = NULL;	// приложение не содержит меню
	wcl.lpszClassName = szClassWindow;	// имя класса окна
	wcl.hIconSm = NULL;	// отсутствие маленькой иконки для связи с классом окна


	/*  2. Регистрация класса окна  */

	if (!RegisterClassEx(&wcl))
		return 0;	// при неудачной регистрации - выход

	/*  3. Создание окна  */

	// создается окно и  переменной hWnd присваивается дескриптор окна
	hWnd = CreateWindowEx(
		0,		// расширенный стиль окна
		szClassWindow,	// имя класса окна
		TEXT("Каркас  Windows приложения"),	// заголовок окна
		/* Заголовок, рамка, позволяющая менять размеры, системное меню,
		кнопки развёртывания и свёртывания окна  */
		WS_OVERLAPPEDWINDOW,	// стиль окна
		CW_USEDEFAULT,	// х-координата левого верхнего угла окна
		CW_USEDEFAULT,	// y-координата левого верхнего угла окна
		CW_USEDEFAULT,	// ширина окна
		CW_USEDEFAULT,	// высота окна
		NULL,			// дескриптор родительского окна
		NULL,			// дескриптор меню окна
		hInst,		// идентификатор приложения, создавшего окно
		NULL);		// указатель на область данных приложения








	/* 4. Отображение окна */

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);	// перерисовка окна

	/* 4.5 Регистрируем события */

	eventMap[WM_KEYDOWN] = KeyboardHanldler;
	eventMap[WM_LBUTTONDBLCLK] = OnDoubleClick;
	eventMap[WM_MOUSEMOVE] = MouseMove;
	eventMap[WM_DESTROY] = OnExit;
	

	/* 5. Запуск цикла обработки сообщений  */

	// получение очередного сообщения из очереди сообщений
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		//TranslateMessage(&Msg);	// трансляция сообщения
		DispatchMessage(&Msg);	// диспетчеризация сообщений
	}
	return Msg.wParam;
}


// Оконная процедура вызывается операционной системой и получает в качестве 
// параметров сообщения из очереди сообщений данного приложения	




LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{

	if (eventMap.find(uMessage) != eventMap.end())
		return (eventMap[uMessage])  (hWnd, uMessage, wParam, lParam);
	else
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	/*

	switch (uMessage)
	{


	case WM_LBUTTONDOWN:
	MessageBox(
	0,
	TEXT("Нажата левая кнопка мыши"),
	TEXT("WM_LBUTTONDOWN"),
	MB_OK | MB_ICONINFORMATION);
	break;
	case WM_LBUTTONUP:
	MessageBox(
	0,
	TEXT("Отпущена левая кнопка мыши"),
	TEXT("WM_LBUTTONUP"),
	MB_OK | MB_ICONINFORMATION);
	break;
	case WM_RBUTTONDOWN:
	MessageBox(
	0,
	TEXT("Нажата правая кнопка мыши"),
	TEXT("WM_RBUTTONDOWN"),
	MB_OK | MB_ICONINFORMATION);
	break;
	case WM_MOUSEMOVE:
	wsprintf(str, TEXT("X=%d  Y=%d"), LOWORD(lParam), HIWORD(lParam)); // текущие координаты курсора мыши
	SetWindowText(hWnd, str);	// строка выводится в заголовок окна
	break;
	case WM_CHAR:
	wsprintf(str, TEXT("Нажата клавиша %c"), (TCHAR)wParam);	// ASCII-код нажатой клавиши
	MessageBox(0, str, TEXT("WM_CHAR"), MB_OK | MB_ICONINFORMATION);
	break;

	}
	return 0;
	*/
}
