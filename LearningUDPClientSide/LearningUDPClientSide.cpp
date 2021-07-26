#include <iostream>
#include <Windows.h>
#include <winsock.h>

using namespace std;

int main() {

	//The WSADATA structure contains information about the Windows Sockets implementation.

	WSADATA WinSocketData;
	int iWsaStartup;
	int iWsaCleanup;

	SOCKET UDPClientSideSocket;

	struct sockaddr_in UDPatServerSide;

	char MessageToBeSent[512] = "This message is typed at the Client Side UDP";
	int iMessageLength = strlen(MessageToBeSent) + 1;



	int iSendToServer;

	int iUDPClientLength = sizeof(UDPClientSideSocket);
	int iCloseClientSideSocket;

	cout << "<-------------------------Client side-------------------------->" << endl;

	//1 initialize WinSocketData (by WSAStartup)

	iWsaStartup = WSAStartup(MAKEWORD(2, 2), &WinSocketData);

	if (iWsaStartup != 0) {
		cout << "WSA Startup Failed" << endl;
	}
	cout << "WSA Startup Succeeded" << endl;

	//2 filling the UDP Server structure;

	UDPatServerSide.sin_family = AF_INET;
	UDPatServerSide.sin_addr.s_addr = inet_addr("127.0.0.1");
	UDPatServerSide.sin_port = 8000;

	//In 127.0.0.1:8000 => Address is 127.0.0.1 , Port is 8000

	//3 UDP Socket creation for client

	UDPClientSideSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (UDPClientSideSocket == INVALID_SOCKET) {
		cout << "UDP Client Side Socket creation failed with error code : " << WSAGetLastError() << endl;
	}
	cout << "UDP Client Side Socket created" << endl;

	//4 Function for sending data to server
	
	iSendToServer = sendto(UDPClientSideSocket, MessageToBeSent, iMessageLength, 0 , (SOCKADDR*)&UDPatServerSide, sizeof(UDPatServerSide));

	if (iSendToServer == SOCKET_ERROR) {
		cout << "UDP Client didnot send data. It failed with error code : " << WSAGetLastError() << endl;
	}
	cout << "UDP Client Socket sent data to UDP Server Socket" << endl;

	
	// 5 closing socket after sending data

	iCloseClientSideSocket = closesocket(UDPClientSideSocket);

	if (iCloseClientSideSocket == SOCKET_ERROR) {
		cout << "UDP Client close connection failed with error code : " << WSAGetLastError() << endl;
	}

	cout << "UDP Client socket closed successfully" << endl;

	//6 WSA Cleanup function for terminating dll
	iWsaCleanup = WSACleanup();

	if (iWsaCleanup == SOCKET_ERROR) {
		cout << "closing socket failed" << WSAGetLastError() << endl;
	}
	cout << "WSA Cleaned up successfully" << endl;


	return 0;
}

// win_32 dll should be added