#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <Windows.h>
#include <deque>
#include <pdh.h>

#pragma comment(lib, "pdh.lib")

using namespace std;

// Глобальные переменные
HINSTANCE hInst;
vector<float> cpuLoadHistory;
vector<float> memoryLoadHistory;

// Прототипы функций
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void UpdateData();
void DrawGraph(HDC hdc, const vector<float>& data, int y, COLORREF color);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	hInst = hInstance;

	// Регистрация класса окна
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"PerfMonitor", NULL };
	RegisterClassEx(&wcex);

	// Создание окна
	HWND hWnd = CreateWindow(L"PerfMonitor", L"Performance Monitor", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		800, 600, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Запуск потока для обновления данных
	thread dataUpdateThread(UpdateData);

	// Основной цикл обработки сообщений
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Ожидание завершения потока
	dataUpdateThread.join();

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		DrawGraph(hdc, cpuLoadHistory, 100, RGB(255, 0, 0)); // График загрузки процессора (красный цвет)
		DrawGraph(hdc, memoryLoadHistory, 200, RGB(0, 0, 255)); // График загрузки памяти (синий цвет)
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void UpdateData()
{
	while (true)
	{
		PDH_HQUERY query;
		PDH_HCOUNTER counter;
		PDH_FMT_COUNTERVALUE value;

		// Инициализация библиотеки PDH
		bool ewq = PdhOpenQuery(L"\\NIKOLAY", 0, &query);
		bool few = PdhAddCounter(query, L"\\Processor Information(_Total)\\% Processor Time", 0, &counter);
		bool gfds = PdhCollectQueryData(query);

		this_thread::sleep_for(chrono::milliseconds(1000));

		bool vgfdas = PdhCollectQueryData(query);
		bool vgfsd = PdhGetFormattedCounterValue(counter, PDH_FMT_DOUBLE, NULL, &value);  \

			// Закрываем библиотеку PDH
		PdhCloseQuery(query);







		// Получаем информацию о памяти (остается без изменений)
		MEMORYSTATUSEX memInfo;
		memInfo.dwLength = sizeof(MEMORYSTATUSEX);
		GlobalMemoryStatusEx(&memInfo);
		float memoryLoad = (float)(memInfo.ullTotalPhys - memInfo.ullAvailPhys) / (float)memInfo.ullTotalPhys * 100.0f;

		// Добавляем данные в историю 
		cpuLoadHistory.push_back(value.doubleValue);
		memoryLoadHistory.push_back(memoryLoad);

		// Ограничиваем историю в 100 точках (можно настроить по своему усмотрению)
		if (cpuLoadHistory.size() > 300)
		{
			cpuLoadHistory.erase(cpuLoadHistory.begin());
			memoryLoadHistory.erase(memoryLoadHistory.begin());
		}

		// Обновляем окно
		InvalidateRect(NULL, NULL, TRUE);

		// Ждем некоторое время перед обновлением данных (замените на реальный мониторинг)
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

void DrawGraph(HDC hdc, const vector<float>& data, int y, COLORREF color)
{
	int width = 800;
	int height = 100;

	HBRUSH hBrush = CreateSolidBrush(color);
	SelectObject(hdc, hBrush);

	MoveToEx(hdc, 0, y, NULL);

	int dataSize = data.size();
	int step;
	if (dataSize)
	{
		step = max(1, width / dataSize);
	}
	step = 1;

	for (int i = 0; i < dataSize; i++)
	{
		int x = i * step;
		int value = data[i];
		int barHeight = (int)((float)value / 100.0 * height);
		Rectangle(hdc, x, y, x + step, y - barHeight);
	}

	DeleteObject(hBrush);
}
