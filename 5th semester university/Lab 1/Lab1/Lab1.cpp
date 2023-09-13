#include <windows.h>
#include <vector>
#include <CommCtrl.h> // ��� ������ � ���������� ���������� �� ���������� Common Controls

struct Shape
{
	RECT rect;
	int selectedShape; // 0 - ��� ������, 1 - ����, 2 - �������������
};

// ���������� ����������
HINSTANCE hInst;
HWND hwndMain;
HDC hdcBuffer;
HBITMAP hBitmap;
HWND hwndListView; // ���������� �������� ���������� ListView

HWND hwndInput1;
HWND hwndInput2;
HWND hwndInput3;
HWND hwndInput4;
HWND hwndButtonOK;

int selectedItemIndex = -1;
std::vector<Shape> shapes;
RECT currentShape; // ������� ������ (�������� �� ��������� ������)
bool isDrawing = false;
int selectedShape = 1; // 0 - ��� ������, 1 - ����, 2 - �������������

// �������� ������� ��������� ��������� ����
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// �������� ������� �������� ������
HWND CreateButton(HWND hwndParent, int x, int y, int width, int height, LPCTSTR text, int id);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ����������� ������ ����
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"MyWindowClass", NULL };
	RegisterClassEx(&wc);

	// �������� �������� ����
	hwndMain = CreateWindow(L"MyWindowClass", L"����������� ��������", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
	SetWindowLong(hwndMain, GWL_STYLE, GetWindowLong(hwndMain, GWL_STYLE) & ~WS_THICKFRAME);

	// �������� ������
	CreateButton(hwndMain, 10, 10, 80, 30, L"����", 1);
	CreateButton(hwndMain, 100, 10, 120, 30, L"�������������", 2);

	// �������� �������� ���������� ListView
	hwndListView = CreateWindowEx(WS_EX_CLIENTEDGE, WC_LISTVIEW, L"",
		WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL,
		10, 50, 255, 200, hwndMain, NULL, hInst, NULL);

	// ��������� �������� � ListView
	LVCOLUMN lvColumn = { 0 };
	lvColumn.mask = LVCF_TEXT | LVCF_WIDTH;
	lvColumn.cx = 100;
	lvColumn.pszText = _wcsdup(L"����");
	ListView_InsertColumn(hwndListView, 0, &lvColumn);

	lvColumn.cx = 150;
	lvColumn.pszText = _wcsdup(L"����������");
	ListView_InsertColumn(hwndListView, 1, &lvColumn);

	// �������� ���������� ������ ��� ������� �����������
	HDC hdc = GetDC(hwndMain); // �������� �������� ���������� ��� �������� ����
	hdcBuffer = CreateCompatibleDC(hdc); // ������� ��������� �������� ����������
	hBitmap = CreateCompatibleBitmap(hdc, 800, 600);
	SelectObject(hdcBuffer, hBitmap);
	ReleaseDC(hwndMain, hdc); // ������������ ��������� ���������� ��� �������� ����

	// ����������� ����
	ShowWindow(hwndMain, nCmdShow);
	UpdateWindow(hwndMain);

	// �������� ���� ���������
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// ������������ �������� ����� �������
	DeleteObject(hBitmap);
	DeleteDC(hdcBuffer);


	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		break;

	case WM_NOTIFY:
	{
		// ��������� ����������� �� �������� ���������� ListView
		NMHDR* pnm = (NMHDR*)lParam;
		if (pnm->code == NM_CLICK) // ��������, ��� ��������� ���� �� ��������
		{
			NMLISTVIEW* pNMLV = (NMLISTVIEW*)lParam;
			selectedItemIndex = pNMLV->iItem; // ������ ���������� ��������

			HWND hwndInput1 = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
				100, 10, 100, 25, hwndMain, NULL, hInst, NULL);
			HWND hwndInput2 = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
				100, 40, 100, 25, hwndMain, NULL, hInst, NULL);
			HWND hwndInput3 = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
				100, 70, 100, 25, hwndMain, NULL, hInst, NULL);
			HWND hwndInput4 = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
				100, 100, 100, 25, hwndMain, NULL, hInst, NULL);
			HWND hwndButtonOK = CreateWindowEx(0, L"BUTTON", L"OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				100, 130, 100, 25, hwndMain, NULL, hInst, NULL);
		}
		break;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_REMOVE_CONTROLS:
		{
			// �������� ������� ����� ����� � ������ "OK"
			DestroyWindow(hwndInput1);
			DestroyWindow(hwndInput2);
			DestroyWindow(hwndInput3);
			DestroyWindow(hwndInput4);
			DestroyWindow(hwndButtonOK);

			break;
		}

	case WM_PAINT:
	{
		// ��������� ������� ������ �� ��������� ������
		if (isDrawing)
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			//����������� ���������� ������ �� �����
			BitBlt(hdc, 0, 0, 800, 600, hdcBuffer, 0, 0, SRCCOPY);

			//HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255)); // ����� ���� ��� ���������
			//SelectObject(hdcBuffer, hBrush);

			if (selectedShape == 1) // �������� ����
			{
				Ellipse(hdc, currentShape.left, currentShape.top, currentShape.right, currentShape.bottom);
			}
			else if (selectedShape == 2) // �������� �������������
			{
				Rectangle(hdc, currentShape.left, currentShape.top, currentShape.right, currentShape.bottom);
			}

			//DeleteObject(hBrush);
			EndPaint(hwnd, &ps);
		}
		break;
	}

	case WM_LBUTTONDOWN:
	{
		isDrawing = true;
		currentShape.left = LOWORD(lParam);
		currentShape.top = HIWORD(lParam);
		currentShape.right = LOWORD(lParam);
		currentShape.bottom = HIWORD(lParam);

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		BitBlt(hdcBuffer, 0, 0, 800, 600, hdc, 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);
		break;
	}

	case WM_MOUSEMOVE:
	{
		if (isDrawing)
		{
			currentShape.right = LOWORD(lParam);
			currentShape.bottom = HIWORD(lParam);

			InvalidateRect(hwnd, NULL, TRUE);
		}
		break;
	}

	case WM_LBUTTONUP:
	{
		isDrawing = false;

		// ��������� ���������� � ������ � ListView
		LVITEM lvItem = { 0 };
		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = ListView_GetItemCount(hwndListView); // �������� ������ ����� ������
		lvItem.iSubItem = 0;
		lvItem.pszText = (selectedShape == 1) ? _wcsdup(L"����") : _wcsdup(L"�������������");
		ListView_InsertItem(hwndListView, &lvItem);

		lvItem.iSubItem = 1;
		WCHAR coords[64];
		swprintf_s(coords, 64, L"(%d, %d, %d, %d)", currentShape.left, currentShape.top, currentShape.right, currentShape.bottom);
		lvItem.pszText = coords;
		ListView_SetItem(hwndListView, &lvItem);

		shapes.push_back({ currentShape,selectedShape });
		currentShape = { 0, 0, 0, 0 };

		InvalidateRect(hwndListView, NULL, TRUE);
		break;
	}

	case WM_COMMAND:
		if (LOWORD(wParam) == 1)
		{
			selectedShape = 1;
		}
		else if (LOWORD(wParam) == 2)
		{
			selectedShape = 2;
		}
		else
		{
			selectedShape = 0;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

HWND CreateButton(HWND hwndParent, int x, int y, int width, int height, LPCTSTR text, int id)
{
	return CreateWindow(L"BUTTON", text, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, x, y, width, height, hwndParent, (HMENU)id, hInst, NULL);
}
