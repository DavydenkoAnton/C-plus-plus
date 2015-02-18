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
const int field_height = 21;
const int width = 12;



char field[field_height][width + 1] = {
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"************", };

const int number_of_figures = 19;
const int const_figures = 7;
const int figure_height = 4;
const int figure_width = 4;

char figure[number_of_figures][figure_height][figure_width + 1] = {
	{
		"    ",
		"    ",// 1
		"    ",
		"****"
	}, {
		"    ",
		"    ",// 2
		" *  ",
		"*** "
	}
	, {
		"    ",
		"    ",// 3
		"**  ",
		"**  "
	}, {
		"    ",
		"    ",// 4
		"**  ",
		" ** "
	}, {
		"    ",
		"    ",// 5
		" ** ",
		"**  "
	}, {
		"    ",
		"**  ",// 6
		" *  ",
		" *  "
	}, {
		"    ",
		"**  ",// 7
		"*   ",
		"*   "
	}, {
		"  * ",
		"  * ",//8
		"  * ",
		"  * "
	}, {
		"    ",
		"*   ",//9
		"**  ",
		"*   "
	}, {
		"    ",
		"    ",//10
		"*** ",
		" *  "
	}, {
		"    ",
		" *  ",//11
		"**  ",
		" *  "
	}, {
		"    ",
		" *  ",//12
		"**  ",
		"*   "
	}, {
		"    ",
		"*   ",//13
		"**  ",
		" *  "
	}, {
		"    ",
		"    ",//14
		"  * ",
		"*** "
	}, {
		"    ",
		"*   ",//15
		"*   ",
		"**  "
	}, {
		"    ",
		"    ",//16
		"*** ",
		"*   "
	}, {
		"    ",
		"    ",//17
		"*** ",
		"  * "
	}, {
		"    ",
		" *  ",//18
		" *  ",
		"**  "
	}, {
		"    ",
		"    ",//19
		"*   ",
		"*** "
	}
};



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
		700,	// х-координата левого верхнего угла окна
		250,	// y-координата левого верхнего угла окна
		300,	// ширина окна
		500,	// высота окна
		NULL,			// дескриптор родительского окна
		NULL,			// дескриптор меню окна
		hInst,		// идентификатор приложения, создавшего окно
		NULL);		// указатель на область данных приложения



	/* 4. Отображение окна */

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);	// перерисовка окна
	SetTimer(hWnd, 1, 300, NULL);
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


int figure_x = 3;
int figure_y = 0;
int figure_num = 0;


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;   // paint data for Begin/EndPaint  

	switch (uMessage){

	case WM_TIMER:

		figure_y++;

		//МЫ переберем всю фигуру
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				if (field[figure_y + j + 1][figure_x + i] == figure[figure_num][j][i] && figure[figure_num][j][i] != ' '){
					//пройтись по всей фигуре и записать в массив поля
					for (int q = 0; q < 4; q++){
						for (int w = 0; w < 4; w++){
							if (figure[figure_num][w][q] != ' ')
								field[figure_y + w][figure_x + q] = figure[figure_num][w][q];
						}
					}
					//сбрасываем координату Y фигуры
					figure_y = 0;
					//сбрасываем координату X фигуры
					figure_x = 3;
					//следующая рандомная фигура
					figure_num = rand() % const_figures;
				}
			}
		}




		InvalidateRgn(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);

		break;
	case WM_PAINT:
		//отрисовка поля
		BeginPaint(hWnd, &ps);
		for (int j = 0; j < field_height; j++){
			for (int i = 0; i < width; i++){
				if (field[j][i] == ' '){
					Rectangle(ps.hdc, x(i), y(j), x(i) + 21, y(j) + 21);
				}
				else if (field[j][i] == '*') {
					SelectObject(ps.hdc, GetStockObject(GRAY_BRUSH));
					Rectangle(ps.hdc, x(i), y(j), x(i) + 21, y(j) + 21);
					SelectObject(ps.hdc, GetStockObject(WHITE_BRUSH));
				}
			}
		}

		//стирание строки

		//проверяем полна ли она
		for (int j = 0; j < field_height - 1; j++){
			bool full_string = true;//допускаем что эта строка полна
			for (int i = 0; i < width; i++){
				if (field[j][i] != '*'){
					full_string = false;
					break;
				}
			}
			//если полна. сдвигаем вниз строки на один
			if (full_string){
				for (int q = j; q >0; q--){
					for (int i = 0; i < width; i++){
						field[q][i] = field[q - 1][i];
					}
				}
			}
		}


		//отрисовка фигуры
		SelectObject(ps.hdc, GetStockObject(GRAY_BRUSH));
		for (int h = 0; h < field_height; h++){
			for (int j = 0; j < figure_height; j++){
				for (int i = 0; i < figure_width; i++){

					if (figure[figure_num][j][i] == '*'){

						Rectangle(ps.hdc, 20 + (i + figure_x) * 20, 20 + (j + figure_y) * 20,
							20 + (i + figure_x) * 20 + 21, 20 + (j + figure_y) * 20 + 21);
					}
				}
			}
		}

		EndPaint(hWnd, &ps);
		break;

	case WM_KEYDOWN:

		//реакция на движение влево
		if (wParam == VK_LEFT){
			if (figure_num == 7){
				if (figure_x >= 0){
					figure_x--;
				}
			}
			if (figure_num == 0  || figure_num == 1  || figure_num == 2  || figure_num == 3  ||
				figure_num == 4  || figure_num == 5  || figure_num == 6  || figure_num == 9  ||
				figure_num == 10 || figure_num == 11 || figure_num == 12 || figure_num == 13 ||
				figure_num == 14 || figure_num == 15 || figure_num == 16 || figure_num == 17 ||
				figure_num == 18 || figure_num == 19){
				if (figure_x >= 2){
					figure_x--;
				}
			}
		}

		//реакция на движение вправо
		if (wParam == VK_RIGHT){
			if (figure_num == 0){
				if (figure_x <= 6){
					figure_x++;
				}
			}
			if (figure_num == 7){
				if (figure_x <= 7){
					figure_x++;
				}
			}
			if (figure_num == 1 || figure_num == 3 || figure_num == 4 || figure_num == 9 ||
				figure_num == 13 || figure_num == 15 || figure_num == 16 || figure_num == 18){
				if (figure_x <= 7){
					figure_x++;
				}
			}
			if (figure_num == 2 || figure_num == 5 || figure_num == 6 || figure_num == 8 ||
				figure_num == 10 || figure_num == 11 || figure_num == 12 || figure_num == 14 ||
				figure_num == 17){
				if (figure_x <= 8){
					figure_x++;
				}
			}
		}

		//реакция на поворот фигуры

		
		if (wParam == VK_SPACE){
			//поворот палки
			if (figure_num == 0){
				figure_num = 7;
				break;
			}
			if (figure_num == 7){
				figure_num = 0;
				break;
			}
			//поворот короны
			if (figure_num == 1){
				figure_num = 8;
				break;
			}
			if (figure_num == 8){
				figure_num = 9;
				break;
			}
			if (figure_num == 9){
				figure_num = 10;
				break;
			}
			if (figure_num == 10){
				figure_num = 1;
				break;
			}
			//поворот кубика
			//  LOL
			//поворот z
			if (figure_num == 3){
				figure_num = 11;
				break;
			}
			if (figure_num ==11){
				figure_num =3;
				break;
			}
			//поворот z зеркальной
			if (figure_num == 4){
				figure_num = 12;
				break;
			}
			if (figure_num == 12){
				figure_num = 4;
				break;
			}
			//поворот Г зеркальной
			if (figure_num == 5){
				figure_num = 13;
				break;
			}
			if (figure_num == 13){
				figure_num = 14;
				break;
			}
			if (figure_num == 14){
				figure_num = 15;
				break;
			}
			if (figure_num == 15){
				figure_num = 5;
				break;
			}
			//поворот Г 
			if (figure_num == 6){
				figure_num = 16;
				break;
			}
			if (figure_num == 16){
				figure_num = 17;
				break;
			}
			if (figure_num == 17){
				figure_num = 18;
				break;
			}
			if (figure_num == 18){
				figure_num = 6;
				break;
			}



		}break;



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
