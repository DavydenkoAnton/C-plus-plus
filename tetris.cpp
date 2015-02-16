// Файл WINDOWS.H содержит определения, макросы, и структуры 
// которые используются при написании приложений под Windows. 
#include <windows.h>
#include <tchar.h>
#include <vector>
#include <map>

#define IDM_RECTANGLE  1200

using namespace std;

//прототип оконной процедуры
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Tetris"); /* Имя класса окна */

typedef LRESULT CALLBACK EventProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
map<UINT, EventProc*> eventMap;

char field[20][11] = {
	"**********",
	"**********",
	"**********",
	"**********",
	"**********",
	"**********",
	"**********",
	"**********",
	"**********",
	"**********",
	"**********",
	"**********",
	"**********",
	"**********",
	"**********",
	"**********",
	"**********",
	"**********",
	"**********",
	"**********" };

char figure[2][2][5] = {
	{
		"****",
		"    "
	}, {
		" *  ",
		"*** "
	}
};

void figure_down(){
	int rand_f = rand() % 2;

}

int cell_size = 20;

int x(int i){
	return i = 20 + i*cell_size;
}

int y(int j){
	return j = 20 + j*cell_size;
}

LRESULT CALLBACK KeyboardHanldler(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam) {
	if (wParam == VK_LEFT){
		MoveWindow(hWnd, CW_USEDEFAULT, CW_USEDEFAULT, 400, 240, true);
	}
	TCHAR str[50];
	wsprintf(str, TEXT("code=%d"), wParam); // текущие координаты курсора мыши
	SetWindowText(hWnd, str);
	return 0;
}



INT WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG Msg;
	WNDCLASSEX wcl;

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
		TEXT("Tetris"),	// заголовок окна
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
	SetTimer(hWnd, 1, 500, NULL);
	/* 4.5 Регистрируем события */

	eventMap[WM_KEYDOWN] = KeyboardHanldler;



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


int figure_i = 3;
int figure_j = 0;
int rand_f = rand() % 2;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;   // paint data for Begin/EndPaint  

	
	


	switch (uMessage)
	{

	case WM_TIMER:
		
			figure_j++;

			InvalidateRgn(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);

			
		
		



		break;
	case WM_PAINT:

		BeginPaint(hWnd, &ps);
		for (int j = 0; j < 20; j++){
			for (int i = 0; i < 10; i++){
				if (field[j][i] == '*'){
					Rectangle(ps.hdc, x(i), y(j), x(i) + 21, y(j) + 21);
				}
			}
		}


		SelectObject(ps.hdc, GetStockObject(GRAY_BRUSH));
		for (int h = 0; h < 20; h++){
			for (int j = 0; j < 2; j++){
				for (int i = 0; i < 4; i++){
					
					if (figure[rand_f][j][i] == '*'){
						
						Rectangle(ps.hdc, 20 + (i + figure_i) * 20, 20 + (j + figure_j) * 20, 20 + (i + figure_i) * 20 + 21, 20 + (j + figure_j) * 20 + 21);
					}
				}
			}
		}

		EndPaint(hWnd, &ps);
		break;

		//---------------------------------------------------------------------


		/*
		if (eventMap.find(uMessage) != eventMap.end())
		return (eventMap[uMessage])  (hWnd, uMessage, wParam, lParam);
		else
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
		*/
	case WM_DESTROY:

		// Destroy the background brush, compatible bitmap,  
		// and bitmap.  

		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);



	}
	return 0;

}
