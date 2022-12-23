#include <iostream>
#include <WS2tcpip.h>
#include <windows.h>
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

#include <Ws2tcpip.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <thread>
#include <locale>
#include <fstream>
#include <Windows.h>
#include <string>
#include <map>
#include <conio.h>

#pragma comment (lib, "ws2_32.lib")
#pragma warning(disable: 4996)


#define IP_ADDRESS ""

using namespace std;

bool bEnd = false;



SOCKET MakeSocket(WORD wSrcPort, const char* p1)
{


	SOCKET sock = (SOCKET)NULL;
	SOCKADDR_IN Addr = { 0 };
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET)
	{
		return (SOCKET)NULL;
	}

	Addr.sin_family = AF_INET;
	Addr.sin_port = htons(wSrcPort);
	Addr.sin_addr.s_addr = inet_addr(p1);

	if (bind(sock, (SOCKADDR*)&Addr, sizeof(Addr)) == SOCKET_ERROR)
	{
		closesocket(sock);
		return (SOCKET)NULL;

	}

	return sock;
}

bool SendData(SOCKET sock, WORD wDstPort, const char* p2)
{
	SOCKADDR_IN SendAddr = { 0 };
	string msg;

	SendAddr.sin_family = AF_INET;
	SendAddr.sin_port = htons(wDstPort);
	SendAddr.sin_addr.s_addr = inet_addr(p2);

	while (true) {
		getline(cin, msg);
		cout << "\nНаписать сообщение: " << "\n";
		int msg_size = msg.size();
		sendto(sock, (char*)&msg_size, sizeof(int), 0, (sockaddr*)&SendAddr, sizeof(SendAddr));
		sendto(sock, msg.c_str(), msg.length(), 0, (sockaddr*)&SendAddr, sizeof(SendAddr));
		Sleep(500);
	}
	return true;
}




DWORD WINAPI RecvThread(LPVOID pParam)
{
	SOCKET sock = (SOCKET)pParam;
	SOCKADDR_IN RecvAddr = { 0 };
	int iRet, iRecvSize;

	int msg_size;
	string msg;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	time_t t = time(0);
	struct tm* now = localtime(&t);
	char buffer[80];
	strftime(buffer, 80, "%d.%m.%Y-%H.%M.%S", now);
	string r = string(buffer);

	while (!bEnd)
	{
		iRecvSize = sizeof(RecvAddr);

		int msg_size = msg.size();
		recvfrom(sock, (char*)&msg_size, sizeof(int), 0, (sockaddr*)&RecvAddr, &iRecvSize);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recvfrom(sock, msg, msg_size, 0, (sockaddr*)&RecvAddr, &iRecvSize);

		cout << "\n-> " << string(msg, msg_size) << endl;
		if (msg_size > 1) {
			map< char, unsigned char > mp;
			mp['а'] = 193;
			mp['б'] = 194;
			mp['ц'] = 195;
			mp['д'] = 196;
			mp['е'] = 197;
			mp['ф'] = 198;
			mp['г'] = 199;
			mp['х'] = 200;
			mp['и'] = 201;
			mp['й'] = 202;
			mp['к'] = 203;
			mp['л'] = 204;
			mp['м'] = 205;
			mp['н'] = 206;
			mp['о'] = 207;
			mp['п'] = 208;
			mp['я'] = 209;
			mp['р'] = 210;
			mp['с'] = 211;
			mp['т'] = 212;
			mp['у'] = 213;
			mp['ж'] = 214;
			mp['в'] = 215;
			mp['ь'] = 216;
			mp['ы'] = 217;
			mp['з'] = 218;
			mp['ш'] = 219;
			mp['э'] = 220;
			mp['щ'] = 221;
			mp['ч'] = 222;
			mp['ъ'] = 223;
			mp['ё'] = 163;
			mp['!'] = 33;
			mp['.'] = 46;
			mp['?'] = 63;
			mp[','] = 44;
			mp[' '] = 32;
			mp['Ю'] = 224;
			mp['А'] = 225;
			mp['Б'] = 226;
			mp['Ц'] = 227;
			mp['Д'] = 228;
			mp['Е'] = 229;
			mp['Ф'] = 230;
			mp['Г'] = 231;
			mp['Х'] = 232;
			mp['И'] = 233;
			mp['Й'] = 234;
			mp['К'] = 235;
			mp['Л'] = 236;
			mp['М'] = 237;
			mp['Н'] = 238;
			mp['О'] = 239;
			mp['П'] = 240;
			mp['Я'] = 241;
			mp['Р'] = 242;
			mp['С'] = 243;
			mp['Т'] = 244;
			mp['У'] = 245;
			mp['Ж'] = 246;
			mp['В'] = 247;
			mp['Ь'] = 248;
			mp['Ы'] = 249;
			mp['З'] = 250;
			mp['Ш'] = 251;
			mp['Э'] = 252;
			mp['Щ'] = 253;
			mp['Ч'] = 254;
			mp['Ъ'] = 255;
			mp['Ё'] = 179;
			mp['ю'] = 192;
			fstream file;

			string gg = ".txt";
			string ras = "G:\\";
			ofstream fout(ras + r.c_str() + gg, ios::app);
			file.open(ras + r.c_str() + gg);
			cout << "Шифрование: \n";
			int b[255];
			for (int i = 0; msg[i]; i++)
			{
				auto d = mp.find(msg[i]);
				fout << d->second;
				cout << d->second;
			}
			cout << "\nДешифровка: \n";
			for (int i = 0; msg[i]; i++)
			{
				auto d = mp.find(msg[i]);
				cout << d->first;
			}
			cout << "\nКодировка: " << "\n";
			for (int i = 0; msg[i]; i++)
			{
				auto d = mp.find(msg[i]);
				cout << (int)(d->second) << " ";
				b[i] = d->second;
			}
			cout << "\nДвоичный вид:" << "\n";
			for (int i = 0; msg[i]; i++)
			{
				int m = 0;
				while (b[i])
				{
					b[i] = b[i] / 2;
					m = b[i] % 2;
					cout << m;
				}
				fout << " " << "\n";
				cout << " " << "\n";
			}
			cout << "\nНаписать сообщение: " << "\n";
			file.close();
		}
		delete[] msg;
	}
	cout << "Связь оборвалась\n";
	return 0;
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	SetConsoleTitleA("Клиент_UDP_Чат");
	WSADATA wsaData = { 0 };
	WORD wSrcPort, wDstPort;
	SOCKET sock;
	string str;
	const char* p1 = { str.c_str() };
	cout << "Введите свой IP-адрес : ";
	cin >> str;
	string str1;
	const char* p2 = { str1.c_str() };
	cout << "Введите IP-адрес собеседника : ";
	cin >> str1;
	char in[256];
	cout << "Введите порт для прослушивания : ";
	cin >> in;
	cout << "Введите порт для подключения : ";
	char tr[256];
	cin >> tr;


	wSrcPort = (WORD)atoi(in);
	wDstPort = (WORD)atoi(tr);

	WORD DLLVersion = MAKEWORD(2, 2);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {

		exit(1);
	}

	sock = MakeSocket(wSrcPort, p1);

	if (sock)
	{
		HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RecvThread, (PVOID)sock, 0, NULL);

		while (1) {
			if (!SendData(sock, wDstPort, p2))
				break;
		}

		bEnd = true;
		closesocket(sock);

		if (WaitForSingleObject(hThread, 3000) == WAIT_TIMEOUT)
		{
			cout << "Ошибка : нет связи\n";
			TerminateThread(hThread, 0);
		}


	}

	WSACleanup();

	return 0;
}
