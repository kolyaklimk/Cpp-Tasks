#include <windows.h>
#include <vector>
#include <CommCtrl.h> // Для работы с элементами управления из библиотеки Common Controls

struct Shape
{
	RECT rect;
	int selectedShape; // 0 - нет выбора, 1 - круг, 2 - прямоугольник
};

// Глобальные переменные
HINSTANCE hInst;
HWND hwndMain;
HDC hdcBuffer;
HBITMAP hBitmap;
HWND hwndListView; // Дескриптор элемента управления ListView

HWND hwndInput1;
HWND hwndInput2;
HWND hwndInput3;
HWND hwndInput4;
HWND hwndButtonOK;

int selectedItemIndex = -1;
std::vector<Shape> shapes;
RECT currentShape; // Текущая фигура (рисуется во временном буфере)
bool isDrawing = false;
int selectedShape = 1; // 0 - нет выбора, 1 - круг, 2 - прямоугольник

// Прототип функции обработки сообщений окна
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Прототип функции создания кнопки
HWND CreateButton(HWND hwndParent, int x, int y, int width, int height, LPCTSTR text, int id);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Регистрация класса окна
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"MyWindowClass", NULL };
	RegisterClassEx(&wc);

	// Создание главного окна
	hwndMain = CreateWindow(L"MyWindowClass", L"Графический редактор", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
	SetWindowLong(hwndMain, GWL_STYLE, GetWindowLong(hwndMain, GWL_STYLE) & ~WS_THICKFRAME);

	// Создание кнопок
	CreateButton(hwndMain, 10, 10, 80, 30, L"Круг", 1);
	CreateButton(hwndMain, 100, 10, 120, 30, L"Прямоугольник", 2);

	// Создание элемента управления ListView
	hwndListView = CreateWindowEx(WS_EX_CLIENTEDGE, WC_LISTVIEW, L"",
		WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL,
		10, 50, 255, 200, hwndMain, NULL, hInst, NULL);

	// Настройка столбцов в ListView
	LVCOLUMN lvColumn = { 0 };
	lvColumn.mask = LVCF_TEXT | LVCF_WIDTH;
	lvColumn.cx = 100;
	lvColumn.pszText = _wcsdup(L"Круг");
	ListView_InsertColumn(hwndListView, 0, &lvColumn);

	lvColumn.cx = 150;
	lvColumn.pszText = _wcsdup(L"Координаты");
	ListView_InsertColumn(hwndListView, 1, &lvColumn);

	// Создание временного буфера для двойной буферизации
	HDC hdc = GetDC(hwndMain); // Получаем контекст устройства для текущего окна
	hdcBuffer = CreateCompatibleDC(hdc); // Создаем временный контекст устройства
	hBitmap = CreateCompatibleBitmap(hdc, 800, 600);
	SelectObject(hdcBuffer, hBitmap);
	ReleaseDC(hwndMain, hdc); // Освобождение контекста устройства для текущего окна

	// Отображение окна
	ShowWindow(hwndMain, nCmdShow);
	UpdateWindow(hwndMain);

	// Основной цикл сообщений
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Освобождение ресурсов перед выходом
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
		// Обработка уведомления от элемента управления ListView
		NMHDR* pnm = (NMHDR*)lParam;
		if (pnm->code == NM_CLICK) // Проверка, что произошел клик на элементе
		{
			NMLISTVIEW* pNMLV = (NMLISTVIEW*)lParam;
			selectedItemIndex = pNMLV->iItem; // Индекс выбранного элемента

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
			// Удаление четырех полей ввода и кнопки "OK"
			DestroyWindow(hwndInput1);
			DestroyWindow(hwndInput2);
			DestroyWindow(hwndInput3);
			DestroyWindow(hwndInput4);
			DestroyWindow(hwndButtonOK);

			break;
		}

	case WM_PAINT:
	{
		// Рисование текущей фигуры на временном буфере
		if (isDrawing)
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			//Копирование временного буфера на экран
			BitBlt(hdc, 0, 0, 800, 600, hdcBuffer, 0, 0, SRCCOPY);

			//HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255)); // Синий цвет для рисования
			//SelectObject(hdcBuffer, hBrush);

			if (selectedShape == 1) // Рисовать круг
			{
				Ellipse(hdc, currentShape.left, currentShape.top, currentShape.right, currentShape.bottom);
			}
			else if (selectedShape == 2) // Рисовать прямоугольник
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

		// Добавляем информацию о фигуре в ListView
		LVITEM lvItem = { 0 };
		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = ListView_GetItemCount(hwndListView); // Получаем индекс новой строки
		lvItem.iSubItem = 0;
		lvItem.pszText = (selectedShape == 1) ? _wcsdup(L"Круг") : _wcsdup(L"Прямоугольник");
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
