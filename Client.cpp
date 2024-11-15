#include "initsock.h"
#include <iostream>
#include <thread>
using namespace std;

CInitSock initSock;     // 初始化Winsock库

void client()
{
    // 创建套节字
    SOCKET s = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET)
    {
        cout << " Failed socket()" << endl;
    }

    // 也可以在这里调用bind函数绑定一个本地地址
    // 否则系统将会自动安排
    char address[20] = "127.0.0.1";
    // 填写远程地址信息
    sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(4567);
    // 注意，这里要填写服务器程序（TCPServer程序）所在机器的IP地址
    // 如果你的计算机没有联网，直接使用127.0.0.1即可
    servAddr.sin_addr.S_un.S_addr = inet_addr(address);

    if (::connect(s, (sockaddr*)&servAddr, sizeof(servAddr)) == -1)
    {
        cout << " Failed connect() " << endl;
    }
    else
    {
        cout << "与服务器 " << address << "建立连接" << endl;
    }

    char szText[] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    if (::send(s, szText, strlen(szText), 0) > 0)
    {
        cout << "   发送数据：" << szText << endl;
    }

    // 接收数据
    char buff[256];
    int nRecv = ::recv(s, buff, 256, 0);
    if (nRecv > 0)
    {
        buff[nRecv] = '\0';
        cout << "   接收到数据：" << buff << endl;
    }

    // 关闭套节字
    ::closesocket(s);
}
int main()
{
    for (int i = 0; i < 5; i++)
    {
        std::thread myThread(client);
        //函数形式为void thread_fun
        myThread.join();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return 0;
}




