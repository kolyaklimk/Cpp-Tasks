#include <windows.h>
#include <vector>
#include <CommCtrl.h> // Для работы с элементами управления из библиотеки Common Controls
#include <commdlg.h>
#include <string>

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
	int Thickness;
	COLORREF selectedColorThickness;
	COLORREF selectedColorBrush;
};

struct PaintWindow
{
	int x1 = 150;
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
HWND hwndMain, hwndListView, hwndComboBox, hSlider, hSliderThickness, hwndList, hwndDeleteItem, hwndUpItem, hwndDownItem;
COLORREF customColorsThickness[16]{ 0 };
COLORREF customColorsBrush[16]{ 0 };
CHOOSECOLOR ccThickness, ccBrush;
COLORREF selectedColorThickness, selectedColorBrush;

PaintWindow PW;
int selectedItemIndex = -1;
std::vector<Shape> shapes;
RECT currentShape; // Текущая фигура (рисуется во временном буфере)
bool isDrawing = false;
int selectedShape = 0;
int n = 3;
int Thickness = 1;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void DrawShape(HDC hdc, bool isCorrect);
void FillRectWindow();
void RePaint(bool ctrlZ);

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
	case WM_CREATE:
	{
#pragma region Elements
		hwndComboBox = CreateWindow(L"COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 0, 00, PW.x1, 200, hwnd, NULL, NULL, NULL);

		SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)L"Круг (A)");
		SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)L"N-угольник (B)");
		SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)L"Прямая (C)");

		SendMessage(hwndComboBox, CB_SETCURSEL, 0, 0);
#pragma endregion		

#pragma region SliderN
		hSlider = CreateWindowEx(0, TRACKBAR_CLASS, NULL, TBS_AUTOTICKS | TBS_ENABLESELRANGE | WS_CHILD | WS_VISIBLE, 0, 40, PW.x1, 40, hwnd, NULL, hInst, NULL);
		SendMessage(hSlider, TBM_SETRANGE, TRUE, MAKELPARAM(3, 20));
		SendMessage(hSlider, WM_SETREDRAW, FALSE, 0);
		EnableWindow(hSlider, FALSE);
#pragma endregion

#pragma region Slider Thickness
		hSliderThickness = CreateWindowEx(0, TRACKBAR_CLASS, NULL, TBS_AUTOTICKS | TBS_ENABLESELRANGE | WS_CHILD | WS_VISIBLE, 0, 80, PW.x1, 40, hwnd, NULL, hInst, NULL);
		SendMessage(hSliderThickness, TBM_SETRANGE, TRUE, MAKELPARAM(1, 100));
#pragma endregion

#pragma region Color Choose Thickness
		HWND hButton1 = CreateWindow(L"BUTTON", L"Цвет линии", WS_CHILD | WS_VISIBLE, 0, 120, PW.x1, 40, hwnd, (HMENU)1001, GetModuleHandle(NULL), NULL);
		ZeroMemory(&ccThickness, sizeof(ccThickness));
		ccThickness.lStructSize = sizeof(ccThickness);
		ccThickness.hwndOwner = hwndMain; // Окно-владелец диалога
		ccThickness.lpCustColors = (LPDWORD)customColorsThickness;
		ccThickness.rgbResult = RGB(255, 0, 0);
		ccThickness.Flags = CC_FULLOPEN | CC_RGBINIT; // Флаги диалога (полный выбор цвета и начальное значение)
#pragma endregion

#pragma region Color Choose Brush
		HWND hButton2 = CreateWindow(L"BUTTON", L"Цвет заливки", WS_CHILD | WS_VISIBLE, 0, 160, PW.x1, 40, hwnd, (HMENU)1002, GetModuleHandle(NULL), NULL);
		ZeroMemory(&ccBrush, sizeof(ccBrush));
		ccBrush.lStructSize = sizeof(ccBrush);
		ccBrush.hwndOwner = hwndMain;
		ccBrush.lpCustColors = (LPDWORD)customColorsThickness;
		ccBrush.rgbResult = RGB(255, 0, 0);
		ccBrush.Flags = CC_FULLOPEN | CC_RGBINIT;
#pragma endregion

#pragma region Color Choose Brush
		hwndList = CreateWindowEx(0, L"LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY, 0, 220, PW.x1, 300, hwnd, (HMENU)100, GetModuleHandle(NULL), NULL);
		hwndDeleteItem = CreateWindow(L"BUTTON", L"Удалить", WS_CHILD | WS_VISIBLE, 0, 540, PW.x1, 40, hwnd, (HMENU)101, GetModuleHandle(NULL), NULL);
		hwndUpItem = CreateWindow(L"BUTTON", L"Вверх", WS_CHILD | WS_VISIBLE, 0, 580, PW.x1, 40, hwnd, (HMENU)102, GetModuleHandle(NULL), NULL);
		hwndDownItem = CreateWindow(L"BUTTON", L"Вниз", WS_CHILD | WS_VISIBLE, 0, 620, PW.x1, 40, hwnd, (HMENU)103, GetModuleHandle(NULL), NULL);
		ShowWindow(hwndDeleteItem, SW_HIDE);
		ShowWindow(hwndUpItem, SW_HIDE);
		ShowWindow(hwndDownItem, SW_HIDE);
#pragma endregion
		break;
	}

	case WM_PAINT:
	{
		if (isDrawing)
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			HPEN hPen = CreatePen(PS_SOLID, Thickness, selectedColorThickness);
			HBRUSH hBrush = CreateSolidBrush(selectedColorBrush);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			BitBlt(hdc, PW.x1, PW.y1, PW.Width, PW.Height, hdcBuffer, 0, 0, SRCCOPY);
			if (GetKeyState(VK_SHIFT) & 0x8000)
			{
				DrawShape(hdc, true);
			}
			else
			{
				DrawShape(hdc, false);
			}
			DeleteObject(hPen);
			DeleteObject(hBrush);
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
		if (isDrawing) {
			isDrawing = false;

			if (GetKeyState(VK_SHIFT) & 0x8000) {
				shapes.push_back({ currentShape, true,n,selectedShape, Thickness,selectedColorThickness,selectedColorBrush });
			}
			else {
				shapes.push_back({ currentShape, false,n,selectedShape,Thickness,selectedColorThickness,selectedColorBrush });
			}

			wchar_t buffer[30];
			swprintf(buffer, 30, L"(%d, %d), (%d, %d)", currentShape.left, currentShape.top, currentShape.right, currentShape.bottom);
			SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)buffer);

			currentShape = { 0, 0, 0, 0 };
		}
		break;
	}

	case WM_KEYDOWN:
	{
		int lower = tolower((unsigned char)wParam);
		if (wParam == 'Z' && GetKeyState(VK_CONTROL) < 0) {
			RePaint(true);
			SetFocus(hwnd);
		}
		else if (GetKeyState(VK_SHIFT) < 0)
		{

		}
		else
		{
			switch (lower)
			{
			case L'a':
			case L'c':
				selectedShape = lower - L'a';
				SendMessage(hwndComboBox, CB_SETCURSEL, selectedShape, 0);
				ShowWindow(hSlider, SW_HIDE);
				FillRectWindow();
				break;

			case L'b':
				selectedShape = lower - L'a';
				SendMessage(hwndComboBox, CB_SETCURSEL, selectedShape, 0);
				ShowWindow(hSlider, SW_SHOW);
				break;
			}
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
					ShowWindow(hSlider, SW_SHOW);
				}
				else
				{
					ShowWindow(hSlider, SW_HIDE);
					FillRectWindow();
				}
				selectedShape = selectedIndex;
			}
			SetFocus(hwnd);
		}
		if (LOWORD(wParam) == 1001)
		{
			if (ChooseColor(&ccThickness))
			{
				selectedColorThickness = ccThickness.rgbResult;
			}
		}
		if (LOWORD(wParam) == 1002)
		{
			if (ChooseColor(&ccBrush))
			{
				selectedColorBrush = ccBrush.rgbResult;
			}
		}
		if (LOWORD(wParam) == 100) {
			int ewq = HIWORD(wParam);
			if (ewq == LBN_SELCHANGE) {
				ShowWindow(hwndDeleteItem, SW_SHOW);
				ShowWindow(hwndUpItem, SW_SHOW);
				ShowWindow(hwndDownItem, SW_SHOW);
			}
			else {
				/*SendMessage(hwndList, LB_SETCURSEL, (WPARAM)-1, 0);
				ShowWindow(hwndDeleteItem, SW_HIDE);
				ShowWindow(hwndUpItem, SW_HIDE);
				ShowWindow(hwndDownItem, SW_HIDE);
				FillRectWindow();*/
			}
		}
		if (LOWORD(wParam) == 101)
		{
			RePaint(false);
		}
		break;
	}

	case WM_HSCROLL:
	{
		if (lParam == (LPARAM)hSlider)
			n = SendMessage(hSlider, TBM_GETPOS, 0, 0);

		if (lParam == (LPARAM)hSliderThickness)
			Thickness = SendMessage(hSliderThickness, TBM_GETPOS, 0, 0);

		SetFocus(hwnd);
		break;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void FillRectWindow() {
	HDC hdchwndMain = GetDC(hwndMain);
	RECT rect1{ 0,40,PW.x1,80 };
	RECT rect2{ 0,540,PW.x1,PW.y2 };
	FillRect(hdchwndMain, &rect1, (HBRUSH)(COLOR_WINDOW));
	FillRect(hdchwndMain, &rect2, (HBRUSH)(COLOR_WINDOW));
	ReleaseDC(hwndMain, hdchwndMain);
}

void RePaint(bool ctrlZ)
{
	if (shapes.size() > 0) {
		int indexItem;
		if (ctrlZ)
		{
			shapes.pop_back();
			indexItem = shapes.size();
		}
		else
		{
			indexItem = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
			shapes.erase(shapes.begin() + indexItem);
		}
		SendMessage(hwndList, LB_DELETESTRING, indexItem, 0);

		COLORREF bufSelectedColorThickness = selectedColorThickness;
		COLORREF bufSelectedColorBrush = selectedColorBrush;
		RECT bufCurrentShape = currentShape;
		int bufSelectedShape = selectedShape;
		int bufn = n;
		int bufThickness = Thickness;

		HDC hdc = GetDC(hwndMain);
		RECT rect1{ PW.x1, PW.y1, PW.x2, PW.y2, };
		FillRect(hdc, &rect1, (HBRUSH)(COLOR_WINDOW + 1));

		for (int a = 0; a < shapes.size();a++) {
			HPEN hPen = CreatePen(PS_SOLID, shapes[a].Thickness, shapes[a].selectedColorThickness);
			HBRUSH hBrush = CreateSolidBrush(shapes[a].selectedColorBrush);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			n = shapes[a].n;
			selectedShape = shapes[a].selectedShape;
			currentShape = shapes[a].rect;
			DrawShape(hdc, shapes[a].isCorrect);
			DeleteObject(hPen);
			DeleteObject(hBrush);
		}

		ReleaseDC(hwndMain, hdc);

		selectedColorThickness = bufSelectedColorThickness;
		selectedColorBrush = bufSelectedColorBrush;
		currentShape = bufCurrentShape;
		selectedShape = bufSelectedShape;
		n = bufn;
		Thickness = bufThickness;
	}
}


void DrawShape(HDC hdc, bool isCorrect)
{
	long* x1 = &currentShape.left;
	long* y1 = &currentShape.top;
	long* x2 = &currentShape.right;
	long* y2 = &currentShape.bottom;

	switch (selectedShape) {
		// Круг
	case 0:
		if (isCorrect) {
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
		if (isCorrect)
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