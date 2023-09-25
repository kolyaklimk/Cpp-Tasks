#include <windows.h>
#include <vector>
#include <CommCtrl.h> // Для работы с элементами управления из библиотеки Common Controls
#include <commdlg.h>

#define M_PI 3.141592653589793238462643383279
struct Shape
{
	RECT rect;
	bool isCorrect;
	int n;
	int selectedShape;
	// 0 - круг
	// 1 - n-угольник
	// 2 - Прямая
};

struct PaintWindow
{
	int x1 = 130;
	int y1 = 0;
	int x2 = 1000;
	int y2 = 800;
	int Width = x2 - x1;
	int Height = y2 - y1;
};

// Глобальные переменные
HINSTANCE hInst;
HDC hdcBuffer;
HBITMAP hBitmap;
HWND hwndMain, hwndListView, hwndComboBox, hSlider, hSliderThickness;
COLORREF customColors[16]{ 0 }; // Массив для хранения пользовательских цветов
CHOOSECOLOR cc; // Структура для диалога выбора цвета
COLORREF selectedColor;

PaintWindow PW;
int selectedItemIndex = -1;
std::vector<Shape> shapes;
RECT currentShape; // Текущая фигура (рисуется во временном буфере)
bool isDrawing = false;
int selectedShape = 0;
int n = 3;
int Thickness = 1;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void DrawShape(HDC hdc);
void FillRectWindow();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"MyWindowClass", NULL };
	RegisterClassEx(&wc);

	hwndMain = CreateWindow(L"MyWindowClass", L"Графический редактор", WS_OVERLAPPEDWINDOW, NULL, NULL, PW.x2, PW.y2, NULL, NULL, hInstance, NULL);
	SetWindowLong(hwndMain, GWL_STYLE, GetWindowLong(hwndMain, GWL_STYLE) & ~WS_THICKFRAME);

	HDC hdc = GetDC(hwndMain);
	hdcBuffer = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, PW.Width, PW.Height);
	SelectObject(hdcBuffer, hBitmap);
	ShowWindow(hwndMain, nCmdShow);

	RECT rectSlider{ 0,0,PW.x1,PW.y2 };
	FillRect(hdc, &rectSlider, (HBRUSH)(COLOR_WINDOW));
	ReleaseDC(hwndMain, hdc);

	UpdateWindow(hwndMain);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	DeleteObject(hBitmap);
	DeleteDC(hdcBuffer);

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE: {

#pragma region Elements
		hwndComboBox = CreateWindow(
			L"COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
			0, 00, 130, 200, hwnd, NULL, NULL, NULL
		);

		SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)L"Круг (A)");
		SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)L"N-угольник (B)");
		SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)L"Прямая (C)");

		SendMessage(hwndComboBox, CB_SETCURSEL, 0, 0);
#pragma endregion		

#pragma region SliderN
		hSlider = CreateWindowEx(0, TRACKBAR_CLASS, NULL, TBS_AUTOTICKS | TBS_ENABLESELRANGE | WS_CHILD | WS_VISIBLE, 0, 40, 130, 40, hwnd, NULL, hInst, NULL);
		SendMessage(hSlider, TBM_SETRANGE, TRUE, MAKELPARAM(3, 20));
		SendMessage(hSlider, WM_SETREDRAW, FALSE, 0);
		EnableWindow(hSlider, FALSE);
#pragma endregion

#pragma region Slider Thickness
		hSliderThickness = CreateWindowEx(0, TRACKBAR_CLASS, NULL, TBS_AUTOTICKS | TBS_ENABLESELRANGE | WS_CHILD | WS_VISIBLE, 0, 80, 130, 40, hwnd, NULL, hInst, NULL);
		SendMessage(hSliderThickness, TBM_SETRANGE, TRUE, MAKELPARAM(1, 40));
#pragma endregion

#pragma region Color Choose
		HWND hButton = CreateWindow(L"BUTTON", L"Цвет линии", WS_CHILD | WS_VISIBLE, 0, 120, 130, 40, hwnd, (HMENU)1001, GetModuleHandle(NULL), NULL);
		ZeroMemory(&cc, sizeof(cc));
		cc.lStructSize = sizeof(cc);
		cc.hwndOwner = hwndMain; // Окно-владелец диалога
		cc.lpCustColors = (LPDWORD)customColors;
		cc.rgbResult = RGB(255, 0, 0);
		cc.Flags = CC_FULLOPEN | CC_RGBINIT; // Флаги диалога (полный выбор цвета и начальное значение)
#pragma endregion
		break;
	}

	case WM_PAINT:
	{
		if (isDrawing)
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			HPEN hPen = CreatePen(PS_SOLID, Thickness, selectedColor);
			SelectObject(hdc, hPen);
			BitBlt(hdc, PW.x1, PW.y1, PW.Width, PW.Height, hdcBuffer, 0, 0, SRCCOPY);
			DrawShape(hdc);
			DeleteObject(hPen);
			EndPaint(hwnd, &ps);
		}
		break;
	}

	case WM_LBUTTONDOWN:
	{
		if (LOWORD(lParam) >= PW.x1) {
			isDrawing = true;
			currentShape.left = LOWORD(lParam);
			currentShape.top = HIWORD(lParam);
			currentShape.right = LOWORD(lParam);
			currentShape.bottom = HIWORD(lParam);

			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			BitBlt(hdcBuffer, 0, 0, PW.Width, PW.Height, hdc, PW.x1, PW.y1, SRCCOPY);
			EndPaint(hwnd, &ps);
		}
		break;
	}

	case WM_MOUSEMOVE:
	{
		if (isDrawing)
		{
			if (LOWORD(lParam) >= PW.x1) {
				currentShape.right = LOWORD(lParam);
				currentShape.bottom = HIWORD(lParam);

				InvalidateRect(hwnd, NULL, TRUE);
			}
		}
		break;
	}

	case WM_LBUTTONUP:
	{
		isDrawing = false;

		if (GetKeyState(VK_SHIFT) & 0x8000) {
			shapes.push_back({ currentShape, true,n,selectedShape });
		}
		else {
			shapes.push_back({ currentShape, false,n,selectedShape });
		}
		currentShape = { 0, 0, 0, 0 };
		break;
	}

	case WM_CHAR:
	{
		selectedShape = tolower((unsigned char)wParam) - L'a';
		SendMessage(hwndComboBox, CB_SETCURSEL, selectedShape, 0);
		if (selectedShape == 1)
		{
			SendMessage(hSlider, WM_SETREDRAW, TRUE, 0);
			EnableWindow(hSlider, TRUE);
			UpdateWindow(hSlider);
		}
		else
		{
			SendMessage(hSlider, WM_SETREDRAW, FALSE, 0);
			EnableWindow(hSlider, FALSE);
			FillRectWindow();
		}
		break;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == 0 && HIWORD(wParam) == CBN_SELCHANGE) {
			int selectedIndex = SendMessage(hwndComboBox, CB_GETCURSEL, 0, 0);
			if (selectedIndex != CB_ERR) {
				if (selectedIndex == 1)
				{
					SendMessage(hSlider, WM_SETREDRAW, TRUE, 0);
					EnableWindow(hSlider, TRUE);
					UpdateWindow(hSlider);
				}
				else
				{
					SendMessage(hSlider, WM_SETREDRAW, FALSE, 0);
					EnableWindow(hSlider, FALSE);
					FillRectWindow();
				}
				selectedShape = selectedIndex;
			}
			SetFocus(hwnd);
		}
		if (LOWORD(wParam) == 1001)
		{
			if (ChooseColor(&cc))
			{
				selectedColor = cc.rgbResult;
			}
		}
		break;
	}

	case WM_HSCROLL:
		if (lParam == (LPARAM)hSlider)
			n = SendMessage(hSlider, TBM_GETPOS, 0, 0);

		if (lParam == (LPARAM)hSliderThickness)
			Thickness = SendMessage(hSliderThickness, TBM_GETPOS, 0, 0);

		SetFocus(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

void FillRectWindow() {
	HDC hdchwndMain = GetDC(hwndMain);
	RECT rect1{ 0,40,130,80 };
	FillRect(hdchwndMain, &rect1, (HBRUSH)(COLOR_WINDOW));
	ReleaseDC(hwndMain, hdchwndMain);
}

void DrawShape(HDC hdc)
{
	long* x1 = &currentShape.left;
	long* y1 = &currentShape.top;
	long* x2 = &currentShape.right;
	long* y2 = &currentShape.bottom;

	switch (selectedShape) {
		// Круг
	case 0:
		if (GetKeyState(VK_SHIFT) & 0x8000) {
			int centerX = (*x1 + *x2) / 2;
			int centerY = (*y1 + *y2) / 2;
			int radius = (*x2 - *x1) / 2;
			Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
		}
		else {
			Ellipse(hdc, *x1, *y1, *x2, *y2);
		}
		break;

		// N-угольник
	case 1:
		if (GetKeyState(VK_SHIFT) & 0x8000)
		{
			double angle = 2 * M_PI / n;
			int radius, x;
			int y = *y1;
			std::vector<POINT> vertices;

			if (*x2 >= *x1)
			{
				if (*y2 >= *y1)
				{
					radius = (*x2 - *x1) / 2;
				}
				else
				{
					radius = (*x1 - *x2) / 2;
				}
				x = *x1 + (*x2 - *x1) / 2 - radius * tan(M_PI / n);
			}
			else
			{
				if (*y2 >= *y1)
				{
					radius = (*x1 - *x2) / 2;
				}
				else
				{
					radius = (*x2 - *x1) / 2;
				}
				x = *x1 - abs(*x2 - *x1) / 2 - radius * tan(M_PI / n);
			}

			for (int i = 0; i < n; i++) {
				vertices.push_back({ x,y });
				x += static_cast<int>(radius * 2 * cos(angle * i));
				y += static_cast<int>(radius * 2 * sin(angle * i));
			}

			Polygon(hdc, vertices.data(), n);
		}
		else
		{
			int width = *x2 - *x1;
			int height = *y2 - *y1;
			int centerX = (*x1 + *x2) / 2;
			int centerY = (*y1 + *y2) / 2;
			double angle = 2 * M_PI / n;
			std::vector<POINT> vertices;

			for (int i = 0; i < n; i++)
			{
				int x = static_cast<int>(centerX + width / 2 * cos(i * angle));
				int y = static_cast<int>(centerY + height / 2 * sin(i * angle));
				vertices.push_back({ x, y });
			}

			if (!vertices.empty())
			{
				Polygon(hdc, vertices.data(), static_cast<int>(vertices.size()));
			}
		}
		break;

		// Прямая
	case 2:
		MoveToEx(hdc, *x1, *y1, NULL);
		LineTo(hdc, *x2, *y2);
		break;
	}
}