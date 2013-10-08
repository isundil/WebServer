#ifdef _WIN32
# include <WinSock2.h>
# include <WS2tcpip.h>
# include <stdio.h>
# pragma comment(lib, "ws2_32.lib")
#endif
#include <sstream>
#include "WebServer.hpp"
#include "HttpClient.h"
#include "SocketException.h"

WebServer::Socket::Socket(unsigned int port)
{
    /* TODO: WINDOWS CODE */
    WSAData data;
    int errcode;
    SOCKET * sock = new SOCKET();
    sockaddr_in service;

    if ((errcode = WSAStartup(MAKEWORD(2, 2), &data)) != NO_ERROR)
        throw SocketException("WSAStartup()", "", errcode);
    if ((*sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        WSACleanup();
        delete sock;
        throw SocketException("socket()", "", WSAGetLastError());
    }
    service.sin_addr.s_addr = 0;
    service.sin_family = AF_INET;
    service.sin_port = htons(port);
    if ((bind(*sock, (const sockaddr *) &service, sizeof(service))) == SOCKET_ERROR)
    {
        WSACleanup();
        closesocket(*sock);
        delete sock;
        throw SocketException("bind()", "", WSAGetLastError());
    }
    if ((listen(*sock, 0)) == SOCKET_ERROR)
    {
        WSACleanup();
        closesocket(*sock);
        delete sock;
        throw SocketException("listen()", "", WSAGetLastError());
    }
    this->socket = sock;
    /* END TODO */
}

WebServer::Socket::~Socket()
{
    /* TODO: WINDOWS CODE */
    SOCKET sock = *(SOCKET *)(this->socket);
    int closeReturn;

    closeReturn = closesocket(sock);
    WSACleanup();
    delete socket;
    if (closeReturn == SOCKET_ERROR)
        throw SocketException("closesocket()", "", WSAGetLastError());
    /* END TODO */
}

HttpClient * WebServer::Socket::waitForRequest()
{
    /* TODO: WINDOWS CODE */
    SOCKET sock = *(SOCKET *) (this->socket);
    SOCKET client = INVALID_SOCKET;
    sockaddr_in clientInfo;
    int sockSize = sizeof(clientInfo);

    if ((client = accept(sock, (sockaddr *) &clientInfo, &sockSize)) == INVALID_SOCKET) /* END TODO */
        throw SocketException("accept()", "", WSAGetLastError());
    return new HttpClient(new WebServer::ClientSocket((void *) &client, (void *) &clientInfo));
}

WebServer::ClientSocket::ClientSocket(void *socket, void *infos)
{
    /* TODO: WINDOWS CODE */
    this->socket = new SOCKET();
    memcpy(this->socket, socket, sizeof(SOCKET));
    this->ip = std::string(inet_ntoa(((sockaddr_in *) infos)->sin_addr));
    this->port = ntohs(((sockaddr_in *) infos)->sin_port);
    /* END TODO */
    this->initial = true;
    bufIndex[0] = bufIndex[1] = 0;
}

WebServer::ClientSocket::ClientSocket(const WebServer::ClientSocket & o)
{
    socket = o.socket;
    ip = o.ip;
    port = o.port;
    initial = false;
    bufIndex[0] = bufIndex[1] = 0;
}

WebServer::ClientSocket::~ClientSocket()
{
    if (initial == false)
        return;
    /* TODO: WINDOWS CODE */
    SOCKET sock = *(SOCKET *)this->socket;
    closesocket(sock);
    /* END TODO */
}

std::string WebServer::ClientSocket::getInfos() const
{
    std::stringstream ss;
    ss << this->ip << " (" << this->port << ")";
    return ss.str();
}

char WebServer::ClientSocket::readChar()
{
    char c;
    recv(*(SOCKET *)socket, &c, 1, 0);
    return c;
}

void WebServer::ClientSocket::write(const std::string &value)
{
    if ((send(*(SOCKET*) socket, value.c_str(), value.length(), 0)) == SOCKET_ERROR)
        throw SocketException("send()", "", WSAGetLastError());
}

void WebServer::ClientSocket::writeLine(const std::string &value)
{
    this->write(value + "\n");
}


std::string WebServer::ClientSocket::readLine()
{
    if (bufIndex[0] == bufIndex[1])
    {
        int rd = recv(*(SOCKET*)socket, &buf[bufIndex[0]], 2048-bufIndex[0], 0);
        if (rd == -1)
            throw SocketException("recv()", "", WSAGetLastError());
        bufIndex[1] += rd;
        if (rd == 2048 - bufIndex[0])
        {
            rd = recv(*(SOCKET*)socket, &buf[0], bufIndex[0], 0);
            if (rd == -1)
                throw SocketException("recv()", "", WSAGetLastError());
            bufIndex[1] += rd;
            while (bufIndex[1] >= 2048)
                bufIndex[1] -= 2048;
        }
    }
    int lastChar;
    int len = 0;
    for (lastChar = bufIndex[0]; lastChar != bufIndex[1]; lastChar = (lastChar + 1) % 2048, len++)
        if (buf[lastChar] == '\n')
            break;
    int pos = 0;
    char * resultBuf = new char [len +1];
    if (lastChar >= bufIndex[0])
        memcpy(resultBuf, &buf[bufIndex[0]], len);
    else
    {
        memcpy(resultBuf, &buf[bufIndex[0]], 2048 - bufIndex[0]);
        int remainLen = len - (2048 - bufIndex[0]);
        memcpy(&resultBuf[(2048 - bufIndex[0]) % 2048], buf, remainLen);
    }
    bufIndex[0] += len +1;
    while (bufIndex[0] >= 2048)
        bufIndex[0] -= 2048;
    if (len == 2048 - 1)
        bufIndex[0] = bufIndex[1];
    resultBuf[len] = '\0';
    for (int i = 0; i < len; i++)
        if (resultBuf[i] == '\r')
            resultBuf[i] = 0;
    std::string resultStr = std::string(resultBuf);
    delete resultBuf;
    return resultStr;
}