#include "initsock.h"
#include <iostream>
#include <thread>
using namespace std;

CInitSock initSock;     // ��ʼ��Winsock��

void client()
{
    // �����׽���
    SOCKET s = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET)
    {
        cout << " Failed socket()" << endl;
    }

    // Ҳ�������������bind������һ�����ص�ַ
    // ����ϵͳ�����Զ�����
    char address[20] = "127.0.0.1";
    // ��дԶ�̵�ַ��Ϣ
    sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(4567);
    // ע�⣬����Ҫ��д����������TCPServer�������ڻ�����IP��ַ
    // �����ļ����û��������ֱ��ʹ��127.0.0.1����
    servAddr.sin_addr.S_un.S_addr = inet_addr(address);

    if (::connect(s, (sockaddr*)&servAddr, sizeof(servAddr)) == -1)
    {
        cout << " Failed connect() " << endl;
    }
    else
    {
        cout << "������� " << address << "��������" << endl;
    }

    char szText[] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    if (::send(s, szText, strlen(szText), 0) > 0)
    {
        cout << "   �������ݣ�" << szText << endl;
    }

    // ��������
    char buff[256];
    int nRecv = ::recv(s, buff, 256, 0);
    if (nRecv > 0)
    {
        buff[nRecv] = '\0';
        cout << "   ���յ����ݣ�" << buff << endl;
    }

    // �ر��׽���
    ::closesocket(s);
}
int main()
{
    for (int i = 0; i < 5; i++)
    {
        std::thread myThread(client);
        //������ʽΪvoid thread_fun
        myThread.join();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return 0;
}




