#include <windows.h>
#include <vector>
#include <CommCtrl.h> 
#include <commdlg.h>
#include <string>
#include <GdiPlus.h>
#include <iostream>

#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "user32.lib")

#define M_PI 3.141592653589793238462643383279

struct Shape
{
	RECT rect;
	bool isCorrect;
	int n;
	int selectedShape;
	// 1 - круг
	// 2 - n-угольник
	// 3 - Прямая
	// 4 - Карандашь
	int Thickness;
	COLORREF selectedColorThickness;
	COLORREF selectedColorBrush;
	std::vector<POINT> pen;
	int scale = 100;
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
HWND hwndMain, hwndComboBox, hSlider, hSliderThickness, hSliderScale, hwndList, hwndDeleteItem, hwndUpItem, hwndDownItem, hwndSave;
COLORREF customColorsThickness[16]{ 0 };
COLORREF customColorsBrush[16]{ 0 };
CHOOSECOLOR ccThickness, ccBrush;
COLORREF selectedColorThickness, selectedColorBrush;

PaintWindow PW;
int selectedItemIndex = -1;
std::vector<Shape> shapes;
RECT currentShape;
bool isDrawing = false;
bool isMove = false;
int selectedShape = 1;
int n = 3;
int Thickness = 1;
std::vector<POINT> pen;
POINT startPos;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void DrawShape(HDC* hdc, bool isCorrect, int scale = 100);
void FillRectWindow();
void RePaint(bool ctrlZ, bool del);
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);


	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"MyWindowClass", NULL };
	RegisterClassEx(&wc);

	hwndMain = CreateWindow(L"MyWindowClass", L"Графический редактор", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, NULL, NULL, PW.x2, PW.y2, NULL, NULL, hInstance, NULL);
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

	Gdiplus::GdiplusShutdown(gdiplusToken);
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
		hwndComboBox = CreateWindow(L"COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, 0, 00, PW.x1, 200, hwnd, NULL, NULL, NULL);

		SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)L"Перемещение (E)");
		SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)L"Круг (A)");
		SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)L"N-угольник (B)");
		SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)L"Прямая (C)");
		SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)L"Карандашь (D)");

		SendMessage(hwndComboBox, CB_SETCURSEL, 1, 0);
#pragma endregion		

#pragma region SliderN
		hSlider = CreateWindowEx(0, TRACKBAR_CLASS, NULL, TBS_AUTOTICKS | TBS_ENABLESELRANGE | WS_CHILD | WS_VISIBLE, 0, 40, PW.x1, 40, hwnd, NULL, hInst, NULL);
		SendMessage(hSlider, TBM_SETRANGE, TRUE, MAKELPARAM(3, 20));
		SendMessage(hSlider, WM_SETREDRAW, FALSE, 0);
		ShowWindow(hSlider, SW_HIDE);
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

#pragma region Slider Scale
		hSliderScale = CreateWindowEx(0, TRACKBAR_CLASS, NULL, TBS_AUTOTICKS | TBS_ENABLESELRANGE | WS_CHILD | WS_VISIBLE, 0, 200, PW.x1, 40, hwnd, NULL, hInst, NULL);
		SendMessage(hSliderScale, TBM_SETRANGE, TRUE, MAKELPARAM(1, 500));
#pragma endregion

#pragma region Color Choose Brush
		hwndList = CreateWindowEx(0, L"LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | WS_VSCROLL, 0, 240, PW.x1, 300, hwnd, (HMENU)100, GetModuleHandle(NULL), NULL);
		hwndDeleteItem = CreateWindow(L"BUTTON", L"Удалить", WS_CHILD | WS_VISIBLE, 0, 530, PW.x1, 40, hwnd, (HMENU)101, GetModuleHandle(NULL), NULL);
		hwndUpItem = CreateWindow(L"BUTTON", L"Вверх", WS_CHILD | WS_VISIBLE, 0, 570, PW.x1 / 2, 40, hwnd, (HMENU)102, GetModuleHandle(NULL), NULL);
		hwndDownItem = CreateWindow(L"BUTTON", L"Вниз", WS_CHILD | WS_VISIBLE, PW.x1 / 2, 570, PW.x1 / 2, 40, hwnd, (HMENU)103, GetModuleHandle(NULL), NULL);
#pragma endregion

#pragma region Color Choose Brush
		hwndSave = CreateWindow(L"BUTTON", L"Сохранить", WS_CHILD | WS_VISIBLE, 0, PW.y2 - 80, PW.x1, 40, hwnd, (HMENU)104, GetModuleHandle(NULL), NULL);
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
			DrawShape(&hdc, GetKeyState(VK_SHIFT) & 0x8000);
			DeleteObject(hPen);
			DeleteObject(hBrush);
			EndPaint(hwnd, &ps);
		}
		break;
	}

	case WM_LBUTTONDOWN:
	{
		if (LOWORD(lParam) >= PW.x1 && selectedShape != 0) {
			isDrawing = true;
			currentShape.left = LOWORD(lParam);
			currentShape.top = HIWORD(lParam);
			currentShape.right = LOWORD(lParam);
			currentShape.bottom = HIWORD(lParam);

			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			BitBlt(hdcBuffer, 0, 0, PW.Width, PW.Height, hdc, PW.x1, PW.y1, SRCCOPY);
			EndPaint(hwnd, &ps);

			if (selectedShape == 4) {
				pen.push_back({ LOWORD(lParam) ,HIWORD(lParam) });
			}
		}
		if (selectedShape == 0)
		{
			isMove = true;
			startPos = { LOWORD(lParam), HIWORD(lParam) };
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

				if (selectedShape == 4) {
					pen.push_back({ LOWORD(lParam) ,HIWORD(lParam) });
				}
				InvalidateRect(hwnd, NULL, TRUE);
			}
		}
		if (isMove)
		{
			int selectedIndex = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
			if (selectedIndex != LB_ERR) {
				selectedIndex = shapes.size() - selectedIndex - 1;

				int x = LOWORD(lParam) - startPos.x;
				int y = HIWORD(lParam) - startPos.y;

				if (shapes[selectedIndex].selectedShape == 4)
				{
					std::vector<POINT> bufpoints = shapes[selectedIndex].pen;
					for (long a = 0;a < shapes[selectedIndex].pen.size();a++)
					{
						shapes[selectedIndex].pen[a].x += x;
						shapes[selectedIndex].pen[a].y += y;
					}
					RePaint(false, false);
					shapes[selectedIndex].pen = bufpoints;
					bufpoints.clear();
				}
				else
				{
					RECT bufrect = shapes[selectedIndex].rect;
					shapes[selectedIndex].rect.left += x;
					shapes[selectedIndex].rect.right += x;
					shapes[selectedIndex].rect.top += y;
					shapes[selectedIndex].rect.bottom += y;
					RePaint(false, false);
					shapes[selectedIndex].rect = bufrect;
				}
			}
		}
		break;
	}

	case WM_LBUTTONUP:
	{
		if (isDrawing) {
			isDrawing = false;
			if (selectedShape == 4) {
				pen.push_back({ LOWORD(lParam) ,HIWORD(lParam) });
			}
			shapes.push_back({ currentShape, bool(GetKeyState(VK_SHIFT) & 0x8000),n,selectedShape, Thickness,selectedColorThickness,selectedColorBrush,pen });
			pen.clear();

			wchar_t buffer[30];
			swprintf(buffer, 30, L"(%d, %d), (%d, %d)", currentShape.left, currentShape.top, currentShape.right, currentShape.bottom);
			SendMessage(hwndList, LB_INSERTSTRING, (WPARAM)0, (LPARAM)buffer);

			currentShape = { 0, 0, 0, 0 };
		}
		if (isMove) {
			isMove = false;

			int selectedIndex = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
			if (selectedIndex != LB_ERR) {
				selectedIndex = shapes.size() - selectedIndex - 1;

				int x = LOWORD(lParam) - startPos.x;
				int y = HIWORD(lParam) - startPos.y;

				if (shapes[selectedIndex].selectedShape == 4)
				{
					for (long a = 0;a < shapes[selectedIndex].pen.size();a++)
					{
						shapes[selectedIndex].pen[a].x += x;
						shapes[selectedIndex].pen[a].y += y;
					}
					RePaint(false, false);
				}
				else
				{
					shapes[selectedIndex].rect.left += x;
					shapes[selectedIndex].rect.right += x;
					shapes[selectedIndex].rect.top += y;
					shapes[selectedIndex].rect.bottom += y;
					RePaint(false, false);
				}
			}
			SetFocus(hwndMain);
		}
		break;
	}

	case WM_KEYDOWN:
	{
		int lower = tolower((unsigned char)wParam);
		if (wParam == 'Z' && GetKeyState(VK_CONTROL) < 0) {
			RePaint(true, true);
			SetFocus(hwnd);
		}
		else
		{
			switch (lower)
			{
			case L'a':
			case L'c':
			case L'd':
				selectedShape = lower - L'a' + 1;
				SendMessage(hwndComboBox, CB_SETCURSEL, selectedShape, 0);
				ShowWindow(hSlider, SW_HIDE);
				FillRectWindow();
				break;

			case L'b':
				selectedShape = lower - L'a' + 1;
				SendMessage(hwndComboBox, CB_SETCURSEL, selectedShape, 0);
				ShowWindow(hSlider, SW_SHOW);
				break;

			case L'e':
				selectedShape = 0;
				SendMessage(hwndComboBox, CB_SETCURSEL, selectedShape, 0);
				ShowWindow(hSlider, SW_HIDE);
				FillRectWindow();
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
				if (selectedIndex == 2)
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
			if (HIWORD(wParam) == LBN_SELCHANGE)
			{
				int selectedIndex = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
				SetFocus(hwndMain);
				SendMessage(hwndList, LB_SETSEL, selectedIndex, 0);
				SendMessage(hSliderScale, TBM_SETPOS, TRUE, 100);
			}
		}
		if (LOWORD(wParam) == 101)
		{
			int selectedIndex = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
			if (selectedIndex != LB_ERR) {
				RePaint(false, true);
			}
			else
			{
				MessageBox(NULL, L"Не выбран элемент в списке!", L"Ошибка", MB_ICONERROR | MB_OK);
			}
			SetFocus(hwndMain);
		}
		if (LOWORD(wParam) == 102)
		{
			int selectedIndex = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
			if (selectedIndex != LB_ERR) {
				if (selectedIndex > 0)
				{
					Shape buf = shapes[shapes.size() - selectedIndex];
					shapes[shapes.size() - selectedIndex] = shapes[shapes.size() - selectedIndex - 1];
					shapes[shapes.size() - selectedIndex - 1] = buf;

					wchar_t buffer1[30];
					wchar_t buffer2[30];
					SendMessage(hwndList, LB_GETTEXT, selectedIndex - 1, (LPARAM)buffer1);
					SendMessage(hwndList, LB_GETTEXT, selectedIndex, (LPARAM)buffer2);
					SendMessage(hwndList, LB_DELETESTRING, selectedIndex - 1, 0);
					SendMessage(hwndList, LB_DELETESTRING, selectedIndex - 1, 0);
					SendMessage(hwndList, LB_INSERTSTRING, selectedIndex - 1, (LPARAM)buffer1);
					SendMessage(hwndList, LB_INSERTSTRING, selectedIndex - 1, (LPARAM)buffer2);
					SendMessage(hwndList, LB_SETCURSEL, selectedIndex - 1, 0);
					RePaint(false, false);
				}
			}
			else
			{
				MessageBox(NULL, L"Не выбран элемент в списке!", L"Ошибка", MB_ICONERROR | MB_OK);
			}
			SetFocus(hwndMain);
		}
		if (LOWORD(wParam) == 103)
		{
			int selectedIndex = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
			if (selectedIndex != LB_ERR) {
				if (selectedIndex < shapes.size() - 1)
				{
					Shape buf = shapes[shapes.size() - selectedIndex - 1];
					shapes[shapes.size() - selectedIndex - 1] = shapes[shapes.size() - selectedIndex - 2];
					shapes[shapes.size() - selectedIndex - 2] = buf;

					wchar_t buffer1[30];
					wchar_t buffer2[30];
					SendMessage(hwndList, LB_GETTEXT, selectedIndex + 1, (LPARAM)buffer1);
					SendMessage(hwndList, LB_GETTEXT, selectedIndex, (LPARAM)buffer2);
					SendMessage(hwndList, LB_DELETESTRING, selectedIndex, 0);
					SendMessage(hwndList, LB_DELETESTRING, selectedIndex, 0);
					SendMessage(hwndList, LB_INSERTSTRING, selectedIndex, (LPARAM)buffer2);
					SendMessage(hwndList, LB_INSERTSTRING, selectedIndex, (LPARAM)buffer1);
					SendMessage(hwndList, LB_SETCURSEL, selectedIndex + 1, 0);
					RePaint(false, false);
				}
			}
			else
			{
				MessageBox(NULL, L"Не выбран элемент в списке!", L"Ошибка", MB_ICONERROR | MB_OK);
			}
			SetFocus(hwndMain);
		}
		if (LOWORD(wParam) == 104)
		{
			HWND desktop = GetDesktopWindow();
			HDC screenDC = GetDC(hwndMain);

			HBITMAP hBitmap = CreateCompatibleBitmap(screenDC, PW.Width - 16, PW.Height - 35);

			HDC memDC = CreateCompatibleDC(screenDC);
			SelectObject(memDC, hBitmap);
			BitBlt(memDC, 0, 0, PW.Width - 16, PW.Height - 35, screenDC, PW.x1, PW.y1, SRCCOPY);

			Gdiplus::Bitmap bitmap(hBitmap, NULL);

			CLSID pngClsid;
			int rez = GetEncoderClsid(L"image/png", &pngClsid);

			bitmap.Save(L"paint.png", &pngClsid, NULL);

			DeleteObject(hBitmap);
			DeleteDC(memDC);
			ReleaseDC(desktop, screenDC);
		}
		break;
	}

	case WM_HSCROLL:
	{
		if (lParam == (LPARAM)hSlider)
			n = SendMessage(hSlider, TBM_GETPOS, 0, 0);

		if (lParam == (LPARAM)hSliderThickness)
			Thickness = SendMessage(hSliderThickness, TBM_GETPOS, 0, 0);

		if (lParam == (LPARAM)hSliderScale) {
			int selectedIndex = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
			if (selectedIndex != LB_ERR)
			{
				shapes[shapes.size() - selectedIndex - 1].scale = SendMessage(hSliderScale, TBM_GETPOS, 0, 0);
				RePaint(false, false);
			}
		}

		SetFocus(hwnd);
		break;
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void FillRectWindow() {
	HDC hdchwndMain = GetDC(hwndMain);
	RECT rect1{ 0,0,PW.x1,PW.y2 };
	FillRect(hdchwndMain, &rect1, (HBRUSH)(COLOR_WINDOW));
	ReleaseDC(hwndMain, hdchwndMain);
}

void RePaint(bool ctrlZ, bool del)
{
	if (shapes.size() > 0) {
		int indexItem;
		if (del) {
			if (ctrlZ)
			{
				shapes.pop_back();
				indexItem = 0;
			}
			else
			{

				indexItem = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
				shapes.erase(shapes.begin() + shapes.size() - indexItem - 1);
			}
			SendMessage(hwndList, LB_DELETESTRING, indexItem, 0);
		}

		COLORREF bufSelectedColorThickness = selectedColorThickness;
		COLORREF bufSelectedColorBrush = selectedColorBrush;
		RECT bufCurrentShape = currentShape;
		int bufSelectedShape = selectedShape;
		int bufn = n;
		std::vector<POINT> bufpen = pen;

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
			pen = shapes[a].pen;
			currentShape = shapes[a].rect;
			DrawShape(&hdc, shapes[a].isCorrect, shapes[a].scale);
			DeleteObject(hPen);
			DeleteObject(hBrush);
		}

		ReleaseDC(hwndMain, hdc);

		selectedColorThickness = bufSelectedColorThickness;
		selectedColorBrush = bufSelectedColorBrush;
		currentShape = bufCurrentShape;
		selectedShape = bufSelectedShape;
		n = bufn;
		pen = bufpen;
		bufpen.clear();
	}
}

void DrawShape(HDC* hdc, bool isCorrect, int scale)
{
	long x1 = currentShape.left;
	long y1 = currentShape.top;
	long x2 = currentShape.right;
	long y2 = currentShape.bottom;

	if (scale != 100 && selectedShape != 4)
	{
		float s = scale / 100.0;
		int newWidth = static_cast<int>((x2 - x1) * s);
		int newHeight = static_cast<int>((y2 - y1) * s);
		x1 = (x1 + x2) / 2 - newWidth / 2;
		y1 = (y1 + y2) / 2 - newHeight / 2;
		x2 = x1 + newWidth;
		y2 = y1 + newHeight;
	}

	switch (selectedShape) {
		// Круг
	case 1:
		if (isCorrect) {
			int centerX = (x1 + x2) / 2;
			int centerY = (y1 + y2) / 2;
			int radius = (x2 - x1) / 2;
			Ellipse(*hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
		}
		else {
			Ellipse(*hdc, x1, y1, x2, y2);
		}
		break;

		// N-угольник
	case 2:
		if (isCorrect)
		{
			double angle = 2 * M_PI / n;
			int radius, x;
			int y = y1;
			std::vector<POINT> vertices;

			if (x2 >= x1)
			{
				if (y2 >= y1)
				{
					radius = (x2 - x1) / 2;
				}
				else
				{
					radius = (x1 - x2) / 2;
				}
				x = x1 + (x2 - x1) / 2 - radius * tan(M_PI / n);
			}
			else
			{
				if (y2 >= y1)
				{
					radius = (x1 - x2) / 2;
				}
				else
				{
					radius = (x2 - x1) / 2;
				}
				x = x1 - abs(x2 - x1) / 2 - radius * tan(M_PI / n);
			}

			for (int i = 0; i < n; i++) {
				vertices.push_back({ x,y });
				x += static_cast<int>(radius * 2 * cos(angle * i));
				y += static_cast<int>(radius * 2 * sin(angle * i));
			}

			Polygon(*hdc, vertices.data(), n);
		}
		else
		{
			int width = x2 - x1;
			int height = y2 - y1;
			int centerX = (x1 + x2) / 2;
			int centerY = (y1 + y2) / 2;
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
				Polygon(*hdc, vertices.data(), static_cast<int>(vertices.size()));
			}
		}
		break;

		// Прямая
	case 3:
		MoveToEx(*hdc, x1, y1, NULL);
		LineTo(*hdc, x2, y2);
		break;

		// Карандаш
	case 4:
		if (scale != 100)
		{
			std::vector<POINT> bufpen = pen;
			float s = scale / 100.0;
			POINT center = { 0, 0 };
			for (int i = 0; i < bufpen.size(); i++) {
				center.x += bufpen[i].x;
				center.y += bufpen[i].y;
			}
			center.x /= bufpen.size();
			center.y /= bufpen.size();
			for (int i = 0; i < pen.size(); i++) {
				int deltaX = bufpen[i].x - center.x;
				int deltaY = bufpen[i].y - center.y;
				bufpen[i].x = center.x + static_cast<int>(deltaX * s);
				bufpen[i].y = center.y + static_cast<int>(deltaY * s);
			}
			Polyline(*hdc, (POINT*)&bufpen[0], pen.size());
			bufpen.clear();
		}
		else
		{
			Polyline(*hdc, (POINT*)&pen[0], pen.size());
		}
		break;
	}

	FillRectWindow();
}

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

	Gdiplus::GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;  // Failure

	pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}

	free(pImageCodecInfo);
	return -1;  // Failure
}