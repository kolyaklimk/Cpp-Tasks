#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <process.h>
#include <vector>
#include <mutex>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")

std::vector<SOCKET> clients;
std::mutex clientsMutex;

void ClientHandler(void* socketPtr) {
	SOCKET clientSocket = *((SOCKET*)socketPtr);
	free(socketPtr);

	char buffer[250];
	int bytesRead;

	do {
		bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
		if (bytesRead > 0) {
			buffer[bytesRead] = '\0';
			std::cout << "Message received: " << buffer << '\n';
			{
				std::lock_guard<std::mutex> lock(clientsMutex);
				for (SOCKET& otherClient : clients) {
						send(otherClient, buffer, bytesRead, 0);
				}
			}
		}
		else if (bytesRead == 0) {
			std::cout << "The client disconnected\n";
		}
		else {
			std::cout << "Error when reading a message from a client: " << WSAGetLastError() << '\n';
		}

	} while (bytesRead > 0);

	closesocket(clientSocket);
	{
		std::lock_guard<std::mutex> lock(clientsMutex);
		clients.erase(std::remove(clients.begin(), clients.end(), clientSocket), clients.end());
	}
	_endthread();
}

int main() {
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		std::cout << "Error during Winsock initialization: " << iResult;
		return 1;
	}

	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET) {
		std::cout << "Error when creating a socket: " << WSAGetLastError();
		WSACleanup();
		return 1;
	}

	std::string ip;
	int port;
	sockaddr_in serverAddr;

	while (true) {
		std::cout << "\nPrint IP: ";
		std::cin >> ip;
		std::cout << "\nPrint port: ";
		std::cin >> port;

		serverAddr.sin_family = AF_INET;
		inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr);
		serverAddr.sin_port = htons(port);

		if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
			std::cout << "Error during socket binding: " << WSAGetLastError() << '\n';
			continue;
		}
		break;
	}

	std::cout << "Success!\n";

	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
		std::cout << "Error on socket listening: " << WSAGetLastError();
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}

	while (1) {
		SOCKET clientSocket = accept(serverSocket, NULL, NULL);
		if (clientSocket == INVALID_SOCKET) {
			std::cout << "Error accepting connection: " << WSAGetLastError();
			closesocket(serverSocket);
			WSACleanup();
			return 1;
		}

		std::cout << "New client connected\n";
		{
			std::lock_guard<std::mutex> lock(clientsMutex);
			clients.push_back(clientSocket);
		}
		std::cout << "All clients: " << clients.size() << '\n';

		SOCKET* clientSocketPtr = (SOCKET*)malloc(sizeof(SOCKET));
		*clientSocketPtr = clientSocket;
		_beginthread(ClientHandler, 0, clientSocketPtr);
	}

	closesocket(serverSocket);
	WSACleanup();

	return 0;
}
