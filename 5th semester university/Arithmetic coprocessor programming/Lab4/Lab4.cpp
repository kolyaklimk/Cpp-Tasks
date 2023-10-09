#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <windows.h>
#include <deque>
#include <pdh.h>

#pragma comment(lib, "pdh.lib")

using namespace std;

// ���������� ����������
HINSTANCE hInst;
vector<float> cpuLoadHistory;
vector<float> memoryLoadHistory;

// ��������� �������
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void UpdateData();
void DrawGraph(HDC hdc, const vector<float>& data, int y, COLORREF color);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	hInst = hInstance;

	// ����������� ������ ����
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"PerfMonitor", NULL };
	RegisterClassEx(&wcex);

	// �������� ����
	HWND hWnd = CreateWindow(L"PerfMonitor", L"Performance Monitor", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		800, 600, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ������ ������ ��� ���������� ������
	thread dataUpdateThread(UpdateData);

	// �������� ���� ��������� ���������
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// �������� ���������� ������
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
		DrawGraph(hdc, cpuLoadHistory, 100, RGB(255, 0, 0)); // ������ �������� ���������� (������� ����)
		DrawGraph(hdc, memoryLoadHistory, 200, RGB(0, 0, 255)); // ������ �������� ������ (����� ����)
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
		PDH_STATUS status;
		PDH_HCOUNTER hCounter;
		PDH_HQUERY hQuery;

		status = PdhOpenQuery(NULL, 0, &hQuery);
		if (status != ERROR_SUCCESS) {
			// ��������� ������
			return;
		}

		// ��������� �������� ������������������ "Processor Time" ��� ���� �����������
		status = PdhAddCounter(hQuery, L"\\Processor Information(_Total)\\% Processor Time", 0, &hCounter);
		if (status != ERROR_SUCCESS) {
			// ��������� ������
			return;
		}
		status = PdhCollectQueryData(hQuery);
		if (status != ERROR_SUCCESS) {
			// ��������� ������
			return;
		}
		Sleep(1000);
		status = PdhCollectQueryData(hQuery);
		if (status != ERROR_SUCCESS) {
			// ��������� ������
			return;
		}

		// ��������� ������ �������� ������������������
		PDH_FMT_COUNTERVALUE counterValue;
		status = PdhGetFormattedCounterValue(hCounter, PDH_FMT_DOUBLE, NULL, &counterValue);
		if (status == ERROR_SUCCESS) {
			// counterValue.doubleValue �������� ������������� CPU � ���������
			printf("������������� CPU: %.2f%%\n", counterValue.doubleValue);
		}
		else {
			// ��������� ������
		}

		// �������� ������� ������������������
		PdhCloseQuery(hQuery);


		// �������� ���������� � ������ (�������� ��� ���������)
		MEMORYSTATUSEX memInfo;
		memInfo.dwLength = sizeof(MEMORYSTATUSEX);
		GlobalMemoryStatusEx(&memInfo);
		float memoryLoad = (float)(memInfo.ullTotalPhys - memInfo.ullAvailPhys) / (float)memInfo.ullTotalPhys * 100.0f;

		// ��������� ������ � ������� 
		cpuLoadHistory.push_back(counterValue.doubleValue);
		memoryLoadHistory.push_back(memoryLoad);

		// ������������ ������� � 100 ������ (����� ��������� �� ������ ����������)
		if (cpuLoadHistory.size() > 300)
		{
			cpuLoadHistory.erase(cpuLoadHistory.begin());
			memoryLoadHistory.erase(memoryLoadHistory.begin());
		}

		// ��������� ����
		InvalidateRect(NULL, NULL, TRUE);
		// ���� ��������� ����� ����� ����������� ������ (�������� �� �������� ����������)
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
		step = max(10, width / dataSize*10);
	}
	step = 10;

	for (int i = 0; i < dataSize; i++)
	{
		int x = i * step;
		int value = data[i];
		int barHeight = (int)((float)value / 100.0 * height);
		Rectangle(hdc, x, y, x + step, y - barHeight);
	}

	DeleteObject(hBrush);
}
