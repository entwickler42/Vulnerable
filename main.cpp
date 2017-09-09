#include <winsock2.h>
#include <iostream>

using namespace std;

//-----------------------------------------------------------------------------
int readClient(int cs)
{
	char buf[512];
	unsigned int size = 0;	
	recv(cs,(char*)&size,4,0);
	recv(cs,buf,size,0);
	return 0;
}

//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	if(MessageBox(NULL,"Press [OK] to start the vulnerable server !","Message",0x01)!=IDOK) return 0;

	WSAData data;	
	int ss=0, cs=0;	
	struct sockaddr_in server;

	server.sin_family				= AF_INET;
	server.sin_port					= htons(31000);
	server.sin_addr.S_un.S_addr		= INADDR_ANY;
	memset(&server.sin_zero,0,8);

	WSAStartup(MAKEWORD(1,1),&data);

	if((ss = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		cout << "Can't get a socket !\n";
		return 0;
	}

	if(bind(ss,(struct sockaddr*)&server,sizeof(struct sockaddr_in)) != 0)
	{
		cout << "Can't bin port 31000 !\n";
		closesocket(ss);
		return 0;
	}

	if(listen(ss,10) != 0)		 
	{
		cout << "Can't listen on port 31000 !\n";
		closesocket(ss);
		return 0;
	}

	cout << "Server online - waition for connections...\n";

	while((cs = accept(ss,NULL,NULL)) != INVALID_SOCKET )
	{		
		readClient(cs);		
		closesocket(cs);

		cout << "Connection closed !\n";

	}
	
	closesocket(ss);
	WSACleanup();
	return 0;
}
