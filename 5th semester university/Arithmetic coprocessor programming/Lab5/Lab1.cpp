#include <windows.h>
#include <vector>
#include <CommCtrl.h> 
#include <commdlg.h>
#include <string>
#include <GdiPlus.h>
#include <iostream>
#include <pdh.h>
#include <thread>
#include <deque>
#include <chrono>
#include <Psapi.h>

#pragma comment(lib, "pdh.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "user32.lib")

#define M_PI 3.141592653589793238462643383279
#define WM_PAINT_CP (WM_APP + 1)
#define MYBYTES 1048576

#pragma region const
struct Shape
{
	RECT rect;
	bool isCorrect;
	int n;
	int selectedShape;
	// 1 - ����
	// 2 - n-��������
	// 3 - ������
	// 4 - ���������
	int Thickness;
	COLORREF selectedColorThickness;
	COLORREF selectedColorBrush;
	std::vector<Gdiplus::Point> pen;
	int scale = 100;
	int rotation = 0;
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

// ���������� ����������
HINSTANCE hInst;
HDC hdcBuffer;
HBITMAP hBitmap;
HWND hwndMain, hwndComboBox, hSlider, hSliderCP, hSliderThickness, hSliderScale, hSliderRotation, hwndList, hwndListCP, hwndDeleteItem, hwndUpItem, hwndDownItem, hwndSave, hwndComboBoxCP;
COLORREF customColorsThickness[16]{ 0 };
COLORREF customColorsBrush[16]{ 0 };
CHOOSECOLOR ccThickness, ccBrush;
COLORREF selectedColorThickness, selectedColorBrush;
HHOOK MouseHook;

PaintWindow PW;
int selectedItemIndex = -1;
std::vector<Shape> shapes;
RECT currentShape;
bool isDrawing = false;
bool isMove = false;
bool isTaskManager = false;
int selectedShape = 1;
int n = 3;
int speed = 1000;
int Thickness = 1;
std::vector<Gdiplus::Point> pen;
Gdiplus::Point startPos;
std::vector<float> cpuLoadHistory;
std::vector<float> memoryLoadHistory;
std::vector<std::wstring> StarusCP;
#pragma endregion

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam);
void DrawShape(Gdiplus::Graphics& graphics, Gdiplus::Pen* penPlus, Gdiplus::SolidBrush* brush, bool isCorrect, int scale = 100, int rotation = 0);
void FillRectWindow();
void RePaint(bool ctrlZ, bool del, bool list = false);
void UpdateData();
void DrawGraph(HDC hdc, const std::vector<float>& data, int y, COLORREF color);
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	MouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookProc, NULL, 0);

	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"MyWindowClass", NULL };
	RegisterClassEx(&wc);

	hwndMain = CreateWindow(L"MyWindowClass", L"����������� ��������", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, NULL, NULL, PW.x2 + 200, PW.y2, NULL, NULL, hInstance, NULL);
	SetWindowLong(hwndMain, GWL_STYLE, GetWindowLong(hwndMain, GWL_STYLE) & ~WS_THICKFRAME);

	HDC hdc = GetDC(hwndMain);
	hdcBuffer = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, PW.Width, PW.Height);
	SelectObject(hdcBuffer, hBitmap);
	ShowWindow(hwndMain, nCmdShow);

	RECT rectSlider{ 0,0,PW.x1,PW.y2 };
	FillRect(hdc, &rectSlider, (HBRUSH)(COLOR_WINDOW));
	RECT rectSlider2{ PW.x2,0,PW.x2 + 200,PW.y2 };
	FillRect(hdc, &rectSlider2, (HBRUSH)(COLOR_WINDOW));
	ReleaseDC(hwndMain, hdc);

	UpdateWindow(hwndMain);

	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)UpdateData, NULL, 0, NULL);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(MouseHook);
	Gdiplus::GdiplusShutdown(gdiplusToken);
	DeleteObject(hBitmap);
	DeleteDC(hdcBuffer);

	TerminateThread(hThread, 0);
	CloseHandle(hThread);

	return msg.wParam;
}

LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		// wParam �������� ���������� � ������� ���� (WM_LBUTTONDOWN, WM_LBUTTONUP, WM_MOUSEMOVE � �. �.)
		if (wParam == WM_MOUSEMOVE)
		{
			if (isDrawing || isMove) {
				POINT mousePos;
				GetCursorPos(&mousePos);
				RECT windowRect;
				GetWindowRect(hwndMain, &windowRect);

				if (mousePos.x < windowRect.left + PW.x1 || mousePos.x > windowRect.right - 200 ||
					mousePos.y < windowRect.top || mousePos.y > windowRect.bottom)
				{
					if (isDrawing) {
						isDrawing = false;
						InvalidateRect(hwndMain, NULL, TRUE);
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

							int x = LOWORD(lParam) - startPos.X;
							int y = HIWORD(lParam) - startPos.Y;

							if (shapes[selectedIndex].selectedShape == 4)
							{
								for (long a = 0; a < shapes[selectedIndex].pen.size(); a++)
								{
									shapes[selectedIndex].pen[a].X += x;
									shapes[selectedIndex].pen[a].Y += y;
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
				}
			}
		}
	}

	return CallNextHookEx(MouseHook, nCode, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
#pragma region Elements
		hwndComboBox = CreateWindow(L"COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, 0, 00, PW.x1, 200, hwnd, NULL, NULL, NULL);

		SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)L"����������� (E)");
		SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)L"���� (A)");
		SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)L"N-�������� (B)");
		SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)L"������ (C)");
		SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)L"��������� (D)");

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
		SendMessage(hSliderThickness, TBM_SETRANGE, TRUE, MAKELPARAM(0, 100));
#pragma endregion

#pragma region Color Choose Thickness
		HWND hButton1 = CreateWindow(L"BUTTON", L"���� �����", WS_CHILD | WS_VISIBLE, 0, 120, PW.x1, 40, hwnd, (HMENU)1001, GetModuleHandle(NULL), NULL);
		ZeroMemory(&ccThickness, sizeof(ccThickness));
		ccThickness.lStructSize = sizeof(ccThickness);
		ccThickness.hwndOwner = hwndMain; // ����-�������� �������
		ccThickness.lpCustColors = (LPDWORD)customColorsThickness;
		ccThickness.rgbResult = RGB(255, 0, 0);
		ccThickness.Flags = CC_FULLOPEN | CC_RGBINIT; // ����� ������� (������ ����� ����� � ��������� ��������)
#pragma endregion

#pragma region Color Choose Brush
		HWND hButton2 = CreateWindow(L"BUTTON", L"���� �������", WS_CHILD | WS_VISIBLE, 0, 160, PW.x1, 40, hwnd, (HMENU)1002, GetModuleHandle(NULL), NULL);
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

#pragma region Slider Rotation
		hSliderRotation = CreateWindowEx(0, TRACKBAR_CLASS, NULL, TBS_AUTOTICKS | TBS_ENABLESELRANGE | WS_CHILD | WS_VISIBLE, 0, 240, PW.x1, 40, hwnd, NULL, hInst, NULL);
		SendMessage(hSliderRotation, TBM_SETRANGE, TRUE, MAKELPARAM(0, 360));
#pragma endregion

#pragma region Color Choose Brush
		hwndList = CreateWindowEx(0, L"LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | WS_VSCROLL, 0, 280, PW.x1, 250, hwnd, (HMENU)100, GetModuleHandle(NULL), NULL);
		hwndDeleteItem = CreateWindow(L"BUTTON", L"��������", WS_CHILD | WS_VISIBLE, 0, 520, PW.x1 / 2, 40, hwnd, (HMENU)99, GetModuleHandle(NULL), NULL);
		hwndDeleteItem = CreateWindow(L"BUTTON", L"�������", WS_CHILD | WS_VISIBLE, PW.x1 / 2, 520, PW.x1 / 2, 40, hwnd, (HMENU)101, GetModuleHandle(NULL), NULL);
		hwndUpItem = CreateWindow(L"BUTTON", L"�����", WS_CHILD | WS_VISIBLE, 0, 560, PW.x1 / 2, 40, hwnd, (HMENU)102, GetModuleHandle(NULL), NULL);
		hwndDownItem = CreateWindow(L"BUTTON", L"����", WS_CHILD | WS_VISIBLE, PW.x1 / 2, 560, PW.x1 / 2, 40, hwnd, (HMENU)103, GetModuleHandle(NULL), NULL);
#pragma endregion

#pragma region Open/Save
		hwndSave = CreateWindow(L"BUTTON", L"������� ������", WS_CHILD | WS_VISIBLE, 0, PW.y2 - 160, PW.x1, 40, hwnd, (HMENU)104, GetModuleHandle(NULL), NULL);
		hwndSave = CreateWindow(L"BUTTON", L"��������� ������", WS_CHILD | WS_VISIBLE, 0, PW.y2 - 120, PW.x1, 40, hwnd, (HMENU)105, GetModuleHandle(NULL), NULL);
		hwndSave = CreateWindow(L"BUTTON", L"��������� png", WS_CHILD | WS_VISIBLE, 0, PW.y2 - 80, PW.x1, 40, hwnd, (HMENU)106, GetModuleHandle(NULL), NULL);
#pragma endregion

#pragma region Select CP
		hwndComboBoxCP = CreateWindow(L"COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, PW.x2, 0, 180, 200, hwnd, NULL, NULL, NULL);
		hwndListCP = CreateWindowEx(0, L"LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | WS_VSCROLL, PW.x2, 500, 180, 220, hwnd, NULL, GetModuleHandle(NULL), NULL);

		hSliderCP = CreateWindowEx(0, TRACKBAR_CLASS, NULL, TBS_AUTOTICKS | TBS_ENABLESELRANGE | WS_CHILD | WS_VISIBLE, PW.x2, 50, 180, 40, hwnd, NULL, hInst, NULL);
		SendMessage(hSliderCP, TBM_SETRANGE, TRUE, MAKELPARAM(50, 2000));
		SendMessage(hSliderCP, TBM_SETPOS, TRUE, 1000);

		SYSTEM_INFO sysInfo;
		GetSystemInfo(&sysInfo);

		int numCores = sysInfo.dwNumberOfProcessors;
		SendMessage(hwndComboBoxCP, CB_ADDSTRING, 0, (LPARAM)L"_Total");
		for (int a = 0; a < sysInfo.dwNumberOfProcessors; a++)
		{
			SendMessage(hwndComboBoxCP, CB_ADDSTRING, 0, (LPARAM)(L"0," + std::to_wstring(a)).c_str());
		}

		SendMessage(hwndComboBoxCP, CB_SETCURSEL, 0, 0);
#pragma endregion
		break;
	}

	case WM_PAINT:
	{
		if (isDrawing)
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			Gdiplus::Graphics graphics(hdc);
			Gdiplus::Pen pen(Gdiplus::Color({ GetRValue(selectedColorThickness),GetGValue(selectedColorThickness),GetBValue(selectedColorThickness) }));
			pen.SetWidth(Thickness);
			Gdiplus::SolidBrush brush(Gdiplus::Color({ GetRValue(selectedColorBrush),GetGValue(selectedColorBrush),GetBValue(selectedColorBrush) }));
			BitBlt(hdc, PW.x1, PW.y1, PW.Width, PW.Height, hdcBuffer, 0, 0, SRCCOPY);
			DrawShape(graphics, &pen, &brush, GetKeyState(VK_SHIFT) & 0x8000);
			EndPaint(hwnd, &ps);
		}
		if (isTaskManager) {
			isTaskManager = false;

			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			if (cpuLoadHistory.size() == 1)
			{
				RECT rectSlider2{ PW.x2,0,PW.x2 + 200,PW.y2 };
				RECT rectSlider3{ PW.x2,100,PW.x2 + 200,300 };
				RECT rectSlider4{ PW.x2,300,PW.x2 + 200,500 };
				FillRect(hdc, &rectSlider2, (HBRUSH)(COLOR_WINDOW));
				FillRect(hdc, &rectSlider3, (HBRUSH)(COLOR_WINDOW + 2));
				FillRect(hdc, &rectSlider4, (HBRUSH)(COLOR_WINDOW + 4));
			}
			SendMessage(hwndListCP, LB_RESETCONTENT, 0, 0);
			for (const std::wstring& item : StarusCP)
			{
				// �������� ������� � ������
				SendMessage(hwndListCP, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(item.c_str()));
			}

			DrawGraph(hdc, cpuLoadHistory, 300, RGB(255, 0, 0));
			DrawGraph(hdc, memoryLoadHistory, 500, RGB(0, 0, 255));
			EndPaint(hwnd, &ps);
		}
		break;
	}

	case WM_LBUTTONDOWN:
	{
		if (LOWORD(lParam) >= PW.x1 && LOWORD(lParam) <= PW.x2 + 200 && selectedShape != 0) {
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
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (selectedShape == 0)
		{
			isMove = true;
			startPos = { LOWORD(lParam), HIWORD(lParam) };
			InvalidateRect(hwnd, NULL, TRUE);
		}
		break;
	}

	case WM_MOUSEMOVE:
	{
		if (isDrawing)
		{
			currentShape.right = LOWORD(lParam);
			currentShape.bottom = HIWORD(lParam);

			if (selectedShape == 4) {
				pen.push_back({ LOWORD(lParam) ,HIWORD(lParam) });
			}
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (isMove)
		{
			int selectedIndex = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
			if (selectedIndex != LB_ERR) {
				selectedIndex = shapes.size() - selectedIndex - 1;

				int x = LOWORD(lParam) - startPos.X;
				int y = HIWORD(lParam) - startPos.Y;

				if (shapes[selectedIndex].selectedShape == 4)
				{
					std::vector<Gdiplus::Point> bufpoints = shapes[selectedIndex].pen;
					for (long a = 0; a < shapes[selectedIndex].pen.size(); a++)
					{
						shapes[selectedIndex].pen[a].X += x;
						shapes[selectedIndex].pen[a].Y += y;
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
			InvalidateRect(hwnd, NULL, TRUE);
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

				int x = LOWORD(lParam) - startPos.X;
				int y = HIWORD(lParam) - startPos.Y;

				if (shapes[selectedIndex].selectedShape == 4)
				{
					for (long a = 0; a < shapes[selectedIndex].pen.size(); a++)
					{
						shapes[selectedIndex].pen[a].X += x;
						shapes[selectedIndex].pen[a].Y += y;
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
				int selectedIndex = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
				if (selectedIndex != LB_ERR)
				{
					shapes[shapes.size() - selectedIndex - 1].selectedColorThickness = ccThickness.rgbResult;
					RePaint(false, false);
				}
			}
		}
		if (LOWORD(wParam) == 1002)
		{
			if (ChooseColor(&ccBrush))
			{
				selectedColorBrush = ccBrush.rgbResult;
				int selectedIndex = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
				if (selectedIndex != LB_ERR)
				{
					shapes[shapes.size() - selectedIndex - 1].selectedColorBrush = ccBrush.rgbResult;
					RePaint(false, false);
				}
			}
		}
		if (LOWORD(wParam) == 100) {
			if (HIWORD(wParam) == LBN_SELCHANGE)
			{
				int selectedIndex = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
				SetFocus(hwndMain);
				SendMessage(hwndList, LB_SETSEL, selectedIndex, 0);
				SendMessage(hSliderScale, TBM_SETPOS, TRUE, shapes[shapes.size() - selectedIndex - 1].scale);
				SendMessage(hSliderRotation, TBM_SETPOS, TRUE, shapes[shapes.size() - selectedIndex - 1].rotation);
				SendMessage(hSliderThickness, TBM_SETPOS, TRUE, shapes[shapes.size() - selectedIndex - 1].Thickness);
				SendMessage(hSlider, TBM_SETPOS, TRUE, shapes[shapes.size() - selectedIndex - 1].n);
			}
		}
		if (LOWORD(wParam) == 99)
		{
			int selectedIndex = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
			if (selectedIndex != LB_ERR) {
				SetFocus(hwndMain);
				SendMessage(hwndList, LB_SETCURSEL, -1, 0);
			}
			else
			{
				MessageBox(NULL, L"�� ������ ������� � ������!", L"������", MB_ICONERROR | MB_OK);
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
				MessageBox(NULL, L"�� ������ ������� � ������!", L"������", MB_ICONERROR | MB_OK);
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
				MessageBox(NULL, L"�� ������ ������� � ������!", L"������", MB_ICONERROR | MB_OK);
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
				MessageBox(NULL, L"�� ������ ������� � ������!", L"������", MB_ICONERROR | MB_OK);
			}
			SetFocus(hwndMain);
		}
		if (LOWORD(wParam) == 104)
		{
			// ��������� ���� ��� ������ � �������� ������
			HANDLE fileHandle = CreateFile(L"shapes.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (fileHandle == INVALID_HANDLE_VALUE) {
				MessageBox(NULL, L"Error 1: �� ������� ������� ���� ��� ������!", L"������", MB_ICONERROR | MB_OK);
				return 1;
			}

			// �������� ������ �����
			DWORD fileSize = GetFileSize(fileHandle, NULL);

			// ������� memory-mapped ���� ��� ������
			HANDLE mapHandle = CreateFileMapping(fileHandle, NULL, PAGE_READONLY, 0, fileSize, NULL);
			if (mapHandle == NULL) {
				CloseHandle(fileHandle);
				MessageBox(NULL, L"Error 2: �� ������� ������� memory-mapped ���� ��� ������!", L"������", MB_ICONERROR | MB_OK);
				return 1;
			}
			CloseHandle(fileHandle);

			// ���������� ���� � ������ ��� ������
			LPVOID mapView = MapViewOfFile(mapHandle, FILE_MAP_READ, 0, 0, 0);
			if (mapView == NULL) {
				CloseHandle(mapHandle);
				MessageBox(NULL, L"Error 3: �� ������� ���������� ���� � ������ ��� ������!", L"������", MB_ICONERROR | MB_OK);
				return 1;
			}
			CloseHandle(mapHandle);

			// ���������� ���������� ��������� (Shapes) � �����
			size_t numShapes = fileSize / sizeof(Shape);

			// ������� ������, ���� �� ��� �������� ������
			shapes.clear();

			// �������� ������ �� memory-mapped ����� � ������
			for (size_t i = 0; i < numShapes; ++i) {
				shapes.push_back(*(reinterpret_cast<const Shape*>(static_cast<const char*>(mapView) + i * sizeof(Shape))));
			}

			// ��������� memory-mapped ���� � ���� �� �����
			UnmapViewOfFile(mapView);
			RePaint(false, false, true);

			MessageBox(NULL, L"������ ������!", L"�����", MB_ICONINFORMATION | MB_OK);
		}
		if (LOWORD(wParam) == 105)
		{
			// ������� memory-mapped ����
			HANDLE mapHandle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(Shape) * shapes.size(), L"MyMappedFile");
			if (mapHandle == NULL) {
				MessageBox(NULL, L"Error 1. �� ������� ������� memory-mapped ����!", L"������", MB_ICONERROR | MB_OK);
				return 1;
			}

			// ���������� ���� � ������ 
			LPVOID mapView = MapViewOfFile(mapHandle, FILE_MAP_WRITE, 0, 0, 0);
			if (mapView == NULL) {
				CloseHandle(mapHandle);
				MessageBox(NULL, L"Error 2. �� ������� ���������� ���� � ������!", L"������", MB_ICONERROR | MB_OK);
				return 1;
			}

			// ��������� memory-mapped ����
			CloseHandle(mapHandle);

			// �������� ������ �� ������� � memory-mapped ���� 
			memcpy(mapView, &shapes[0], sizeof(Shape) * shapes.size());

			// ��������� ���� ��� ������ �� ���� � �������� ������ 
			HANDLE fileHandle = CreateFile(L"shapes.dat", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (fileHandle == INVALID_HANDLE_VALUE) {
				MessageBox(NULL, L"Error 3. �� ������� ������� ���� ��� ������!", L"������", MB_ICONERROR | MB_OK);
				return 1;
			}

			// ������ ������ �� memory-mapped ����� � ���������� �� �� ����
			OVERLAPPED overlapped;
			memset(&overlapped, 0, sizeof(OVERLAPPED));
			DWORD bytesWritten;
			WriteFile(fileHandle, mapView, sizeof(Shape) * shapes.size(), NULL, &overlapped);
			if (!GetOverlappedResult(fileHandle, &overlapped, &bytesWritten, TRUE)) {
				MessageBox(NULL, L"Error 4. �� ������� �������� ������ �� ����!", L"������", MB_ICONERROR | MB_OK);
				return 1;
			}

			MessageBox(NULL, L"������ ��������!", L"�����", MB_ICONINFORMATION | MB_OK);
			// ��������� memory-mapped ���� � ���� �� �����
			UnmapViewOfFile(mapView);
			CloseHandle(fileHandle);
		}
		if (LOWORD(wParam) == 106)
		{
			HDC screenDC = GetDC(hwndMain);
			RECT windowRect;
			GetWindowRect(hwndMain, &windowRect);

			HBITMAP hBitmap = CreateCompatibleBitmap(screenDC, PW.Width - 16, PW.Height - 35);

			HDC memDC = CreateCompatibleDC(screenDC);
			SelectObject(memDC, hBitmap);
			BitBlt(memDC, 0, 0, windowRect.right - windowRect.left + PW.x1, windowRect.bottom - windowRect.top, screenDC, PW.x1, PW.y1, SRCCOPY);

			Gdiplus::Bitmap bitmap(hBitmap, NULL);

			CLSID pngClsid;
			GetEncoderClsid(L"image/png", &pngClsid);

			bitmap.Save(L"paint.png", &pngClsid, NULL);

			MessageBox(NULL, L"Png ���������!", L"�����", MB_ICONERROR | MB_OK);
			DeleteObject(hBitmap);
			DeleteDC(memDC);
		}
		break;
	}

	case WM_HSCROLL:
	{
		int selectedIndex = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
		if (lParam == (LPARAM)hSlider)
		{
			n = SendMessage(hSlider, TBM_GETPOS, 0, 0); selectedColorThickness = ccThickness.rgbResult;
			if (selectedIndex != LB_ERR)
			{
				shapes[shapes.size() - selectedIndex - 1].n = n;
				RePaint(false, false);
			}
		}

		if (lParam == (LPARAM)hSliderCP)
		{
			speed = SendMessage(hSliderCP, TBM_GETPOS, 0, 0);
		}

		if (lParam == (LPARAM)hSliderThickness)
		{
			Thickness = SendMessage(hSliderThickness, TBM_GETPOS, 0, 0);
			if (selectedIndex != LB_ERR)
			{
				shapes[shapes.size() - selectedIndex - 1].Thickness = Thickness;
				RePaint(false, false);
			}
		}

		if (lParam == (LPARAM)hSliderScale) {
			if (selectedIndex != LB_ERR)
			{
				shapes[shapes.size() - selectedIndex - 1].scale = SendMessage(hSliderScale, TBM_GETPOS, 0, 0);
				RePaint(false, false);
			}
		}

		if (lParam == (LPARAM)hSliderRotation) {
			if (selectedIndex != LB_ERR)
			{
				shapes[shapes.size() - selectedIndex - 1].rotation = SendMessage(hSliderRotation, TBM_GETPOS, 0, 0);
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

void RePaint(bool ctrlZ, bool del, bool list)
{
	if (list) {
		SendMessage(hwndList, LB_RESETCONTENT, 0, 0);
		for (int a = 0; a < shapes.size(); a++)
		{
			wchar_t buffer[30];
			swprintf(buffer, 30, L"(%d, %d), (%d, %d)", shapes[a].rect.left, shapes[a].rect.top, shapes[a].rect.right, shapes[a].rect.bottom);
			SendMessage(hwndList, LB_INSERTSTRING, (WPARAM)0, (LPARAM)buffer);
		}
	}
	if (shapes.size() > 0)
	{
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

		COLORREF bufSCT = selectedColorThickness;
		COLORREF bufSCB = selectedColorBrush;
		RECT bufCurrentShape = currentShape;
		int bufSelectedShape = selectedShape;
		int bufn = n;
		std::vector<Gdiplus::Point> bufpen = pen;

		HDC hdc = GetDC(hwndMain);
		RECT rect1{ PW.x1, PW.y1, PW.x2, PW.y2, };
		FillRect(hdc, &rect1, (HBRUSH)(COLOR_WINDOW + 1));

		for (int a = 0; a < shapes.size(); a++) {
			n = shapes[a].n;
			selectedShape = shapes[a].selectedShape;
			pen = shapes[a].pen;
			selectedColorThickness = shapes[a].selectedColorThickness;
			selectedColorBrush = shapes[a].selectedColorBrush;
			currentShape = shapes[a].rect;
			Gdiplus::Graphics graphics(hdc);
			Gdiplus::Pen pen(Gdiplus::Color({ GetRValue(selectedColorThickness),GetGValue(selectedColorThickness),GetBValue(selectedColorThickness) }));
			pen.SetWidth(shapes[a].Thickness);
			Gdiplus::SolidBrush brush(Gdiplus::Color({ GetRValue(selectedColorBrush),GetGValue(selectedColorBrush),GetBValue(selectedColorBrush) }));
			DrawShape(graphics, &pen, &brush, shapes[a].isCorrect, shapes[a].scale, shapes[a].rotation);
		}

		ReleaseDC(hwndMain, hdc);

		selectedColorThickness = bufSCT;
		selectedColorBrush = bufSCB;
		currentShape = bufCurrentShape;
		selectedShape = bufSelectedShape;
		n = bufn;
		pen = bufpen;
		bufpen.clear();
	}
}

void DrawShape(Gdiplus::Graphics& graphics, Gdiplus::Pen* penPlus, Gdiplus::SolidBrush* brush, bool isCorrect, int scale, int rotation)
{
	long x1 = currentShape.left;
	long y1 = currentShape.top;
	long x2 = currentShape.right;
	long y2 = currentShape.bottom;

	float s = scale / 100.0;
	graphics.TranslateTransform((x2 + x1) / 2, (y2 + y1) / 2);
	graphics.ScaleTransform(s, s);
	graphics.RotateTransform(rotation);
	graphics.TranslateTransform(-(x2 + x1) / 2, -(y2 + y1) / 2);

	switch (selectedShape) {
		// ����
	case 1:
	{
		if (isCorrect) {
			int centerX = (x1 + x2) / 2;
			int centerY = (y1 + y2) / 2;
			int radius = (x2 - x1) / 2;
			x1 = centerX - radius;
			x2 = centerX + radius;
			y1 = centerY - radius;
			y2 = centerY + radius;

			Gdiplus::Rect ellipseRect(x1, y1, x2 - x1, y2 - y1);

			graphics.FillEllipse(brush, ellipseRect);
			graphics.DrawEllipse(penPlus, ellipseRect);
		}
		else {
			Gdiplus::Rect ellipseRect(x1, y1, x2 - x1, y2 - y1);

			graphics.FillEllipse(brush, ellipseRect);
			graphics.DrawEllipse(penPlus, ellipseRect);
		}
		break;
	}
	// N-��������
	case 2: {
		if (isCorrect)
		{
			double angle = 2 * M_PI / n;
			int radius, x;
			int y = y1;
			std::vector<Gdiplus::Point> vertices;

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
			graphics.FillPolygon(brush, &vertices[0], vertices.size());
			graphics.DrawPolygon(penPlus, &vertices[0], vertices.size());
		}
		else
		{
			int width = x2 - x1;
			int height = y2 - y1;
			int centerX = (x1 + x2) / 2;
			int centerY = (y1 + y2) / 2;
			double angle = 2 * M_PI / n;
			std::vector<Gdiplus::Point> vertices;

			for (int i = 0; i < n; i++)
			{
				int x = static_cast<int>(centerX + width / 2 * cos(i * angle));
				int y = static_cast<int>(centerY + height / 2 * sin(i * angle));
				vertices.push_back({ x, y });
			}

			graphics.FillPolygon(brush, &vertices[0], vertices.size());
			graphics.DrawPolygon(penPlus, &vertices[0], vertices.size());
		}
		break;
	}
		  // ������
	case 3: {
		Gdiplus::Point startPoint(x1, y1);
		Gdiplus::Point endPoint(x2, y2);
		graphics.DrawLine(penPlus, startPoint, endPoint);
		break;
	}

		  // ��������
	case 4:
	{
		graphics.DrawCurve(penPlus, &pen[0], pen.size());
		break;
	}
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

void UpdateData()
{
	while (true)
	{
		int selectedIndex = SendMessage(hwndComboBoxCP, CB_GETCURSEL, 0, 0);
		int textLength = SendMessage(hwndComboBoxCP, CB_GETLBTEXTLEN, selectedIndex, 0);
		std::wstring buffer(textLength, L'2');
		SendMessage(hwndComboBoxCP, CB_GETLBTEXT, selectedIndex, (LPARAM)buffer.c_str());

		PDH_STATUS status;
		PDH_HCOUNTER hCounter[10];
		PDH_HQUERY hQuery;
		const LPCWSTR counterPaths[] = {
		L"\\System\\Processes",
		L"\\System\\Threads",
		L"\\Process(_Total)\\Handle Count",
		L"\\System\\System Up Time",
		L"\\Memory\\Available Bytes",
		L"\\Memory\\Committed Bytes",
		L"\\Memory\\Pool Nonpaged Bytes",
		L"\\Memory\\Pool Paged Bytes",
		};

		status = PdhOpenQuery(NULL, 0, &hQuery);

		status = PdhAddCounter(hQuery, (L"\\Processor Information(" + buffer + L")\\% Processor Utility").c_str(), 0, &hCounter[0]);

		for (int i = 0; i < 8; ++i)
		{
			status = PdhAddCounter(hQuery, counterPaths[i], NULL, &hCounter[i + 1]);
		}

		status = PdhCollectQueryData(hQuery);

		std::this_thread::sleep_for(std::chrono::milliseconds(speed));

		status = PdhCollectQueryData(hQuery);

		PDH_FMT_COUNTERVALUE counterValue;
		status = PdhGetFormattedCounterValue(hCounter[0], PDH_FMT_DOUBLE, NULL, &counterValue);

		if (cpuLoadHistory.size() == 25)
		{
			cpuLoadHistory.clear();
			memoryLoadHistory.clear();
		}
		cpuLoadHistory.push_back(counterValue.doubleValue);
		StarusCP.clear();
		StarusCP.push_back(L"CPU: " + std::to_wstring(counterValue.doubleValue) + L"%");
		for (int i = 1; i < 5; ++i)
		{
			status = PdhGetFormattedCounterValue(hCounter[i], PDH_FMT_LONG, NULL, &counterValue);
			if (status == ERROR_SUCCESS)
			{
				if (i == 1)
					StarusCP.push_back(L"Processes: " + std::to_wstring(counterValue.longValue));
				else if (i == 2)
					StarusCP.push_back(L"Threads: " + std::to_wstring(counterValue.longValue));
				else if (i == 3)
					StarusCP.push_back(L"Handles: " + std::to_wstring(counterValue.longValue));
				else if (i == 4)
					StarusCP.push_back(L"Up time: " + std::to_wstring(counterValue.longValue));
			}
		}

		StarusCP.push_back(L"");

		MEMORYSTATUSEX memInfo;
		memInfo.dwLength = sizeof(MEMORYSTATUSEX);
		GlobalMemoryStatusEx(&memInfo);

		float memoryLoad = (float)(memInfo.ullTotalPhys - memInfo.ullAvailPhys) / (float)memInfo.ullTotalPhys * 100.0f;
		StarusCP.push_back(L"Memory: " + std::to_wstring(memoryLoad) + L"%");
		StarusCP.push_back(L"Total: " + std::to_wstring(memInfo.ullTotalPhys / MYBYTES) + L" MB");
		StarusCP.push_back(L"In Use: " + std::to_wstring((memInfo.ullTotalPhys - memInfo.ullAvailPhys) / MYBYTES) + L" MB");
		for (int i = 5; i < 9; ++i)
		{
			status = PdhGetFormattedCounterValue(hCounter[i], PDH_FMT_DOUBLE, NULL, &counterValue);
			if (status == ERROR_SUCCESS)
			{
				if (i == 5)
					StarusCP.push_back(L"Available: " + std::to_wstring(long long(counterValue.doubleValue / MYBYTES)));
				else if (i == 6)
					StarusCP.push_back(L"Committed: " + std::to_wstring(long long(counterValue.doubleValue / MYBYTES)));
				else if (i == 7)
					StarusCP.push_back(L"Pool Nonpaged: " + std::to_wstring(long long(counterValue.doubleValue / MYBYTES)));
				else if (i == 8)
					StarusCP.push_back(L"Pool Paged: " + std::to_wstring(long long(counterValue.doubleValue / MYBYTES)));
			}
		}
		memoryLoadHistory.push_back(memoryLoad);

		PdhCloseQuery(hQuery);
		isTaskManager = true;
		InvalidateRect(hwndMain, NULL, TRUE);
	}
}

void DrawGraph(HDC hdc, const std::vector<float>& data, int y, COLORREF color)
{
	int width = 800;
	int height = 200;

	HBRUSH hBrush = CreateSolidBrush(color);
	SelectObject(hdc, hBrush);

	MoveToEx(hdc, 0, y, NULL);

	int dataSize = data.size();
	int step;
	if (dataSize)
	{
		step = max(5, width / dataSize * 5);
	}
	step = 5;

	int x = (dataSize - 1) * step + PW.x2;
	int value = data[dataSize - 1];
	int barHeight = min((int)((float)value / 100.0 * height), height);
	Rectangle(hdc, x, y, x + step, y - barHeight);

	DeleteObject(hBrush);
}