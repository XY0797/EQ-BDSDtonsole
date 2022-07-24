#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include "Base64.h"
#pragma comment (lib,"WS2_32.lib")
int main(int argc, char** argv)
 {
    if (argc == 4)
    {
        if (strcmp(argv[1], "-be") == 0)
        {
            //初始化
            WSADATA wsaData;
            WSAStartup(MAKEWORD(2, 2), &wsaData);
            //创建接收数据报的socket
            SOCKET UDPClientSocket;
            UDPClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
            //目的地址
            sockaddr_in RecvAddr;
            RecvAddr.sin_family = AF_INET;
            //设置IP
            RecvAddr.sin_addr.s_addr = inet_addr(argv[2]);
            //端口
            RecvAddr.sin_port = htons(atoi(argv[3]));
            //--------------------
            //取启动时间
            long long temp_tickcounttime_longlong = (long long)GetTickCount();
            char temp_tickcounttime_char[8];
            memcpy(temp_tickcounttime_char, &temp_tickcounttime_longlong, 8);
            //--------------------
            //发送数据的缓冲区
            char SendBuf[33] = { 0 };
            //生成数据包
            SendBuf[0] = 1;
            int temp_i = 0;
            while (temp_i != 8)
            {
                SendBuf[temp_i + 1] = temp_tickcounttime_char[7 - temp_i];
                temp_i++;
            }
            char temp_data1[16] = { char(0), char(255), char(255), char(0), char(254), char(254), char(254), char(254), char(253), char(253), char(253), char(253), char(18), char(52), char(86), char(120) };
            temp_i = 0;
            while (temp_i != 16)
            {
                SendBuf[temp_i + 9] = temp_data1[temp_i];
                temp_i++;
            }
            GUID guid;
            CoCreateGuid(&guid);
            temp_i = 0;
            while (temp_i != 8)
            {
                SendBuf[temp_i + 25] = guid.Data4[temp_i];
                temp_i++;
            }
            //设置超时时间
            DWORD temp_setsockopt = 5000;
            setsockopt(UDPClientSocket, SOL_SOCKET, SO_SNDTIMEO, (char*)&temp_setsockopt, sizeof(temp_setsockopt));
            setsockopt(UDPClientSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&temp_setsockopt, sizeof(temp_setsockopt));
            //发送数据
            temp_i = sendto(UDPClientSocket, SendBuf, 33, 0, (SOCKADDR*)&RecvAddr, sizeof(RecvAddr));
            if (temp_i == -1) { std::cout << "=="; closesocket(UDPClientSocket); WSACleanup(); return 0; }
            //接收数据
            //接收缓冲区
            char RecvBuf[1024] = { 0 };
            //缓冲区长度
            int BufLen = 1024;
            temp_i = recvfrom(UDPClientSocket, RecvBuf, BufLen, 0, NULL, NULL);
            if (temp_i == -1) { std::cout << "=="; closesocket(UDPClientSocket); WSACleanup(); return 0; }
            //关闭socket，结束接收数据
            closesocket(UDPClientSocket);
            //释放资源
            WSACleanup();
            //返回数据
            std::cout << base64_encode(RecvBuf, temp_i);
            return 0;
        }
        else
        {
            //初始化
            WSADATA wsaData;
            WSAStartup(MAKEWORD(2, 2), &wsaData);
            //socket描述符
            SOCKET TCPClientSocket;
            TCPClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            //目的地址
            sockaddr_in RecvAddr;
            RecvAddr.sin_family = AF_INET;
            //设置IP
            RecvAddr.sin_addr.s_addr = inet_addr(argv[2]);
            //设置端口
            RecvAddr.sin_port = htons(atoi(argv[3]));
            //设置超时时间
            DWORD temp_setsockopt = 5000;
            setsockopt(TCPClientSocket, SOL_SOCKET, SO_SNDTIMEO, (char*)&temp_setsockopt, sizeof(temp_setsockopt));
            setsockopt(TCPClientSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&temp_setsockopt, sizeof(temp_setsockopt));
            //非零允许非阻塞
            u_long temp_u_i = 1;
            ioctlsocket(TCPClientSocket, FIONBIO, &temp_u_i);
            fd_set temp_fd_set;
            temp_fd_set.fd_count = 1;
            temp_fd_set.fd_array[0] = TCPClientSocket;
            timeval temp_timeval;
            temp_timeval.tv_sec = 5;
            connect(TCPClientSocket, (SOCKADDR*)&RecvAddr, sizeof(RecvAddr));
            int temp_i = 0;
            temp_i = select(TCPClientSocket, NULL, &temp_fd_set, NULL, &temp_timeval);
            if (temp_i == 1)
            {
                //设置零禁止非阻塞
                u_long temp_u_i = 0;
                ioctlsocket(TCPClientSocket, FIONBIO, &temp_u_i);
                //发送数据的缓冲区
                char SendBuf[2] = { char(254),char(1) };
                temp_i = send(TCPClientSocket, SendBuf, 2, 0);
                if (temp_i == -1) { std::cout << "=="; closesocket(TCPClientSocket); WSACleanup(); return 0; }//发送失败
                //接收数据
                //接收缓冲区
                char RecvBuf[2048] = { 0 };
                //缓冲区长度
                int BufLen = 2048;
                temp_i = recv(TCPClientSocket, RecvBuf, BufLen, 0);
                if (temp_i == -1) { std::cout << "=="; closesocket(TCPClientSocket); WSACleanup(); return 0; }//接收失败
                //关闭socket，结束接收数据
                closesocket(TCPClientSocket);
                //释放资源
                WSACleanup();
                //返回数据
                std::cout << base64_encode(RecvBuf, temp_i);
                return 0;
            }else{ std::cout << "=="; closesocket(TCPClientSocket); WSACleanup(); return 0; }
        }
    }
    else
    {
        return 0;
    }
 }