#pragma once

#include <string>
#include <list>

class HttpClient;
class AWebPage;

class WebServer
{
public: //public methods
    WebServer(unsigned int port = 80);
    virtual ~WebServer();

    WebServer * setWebmaster(const std::string &webMasterEmail);
    std::string getWebmaster() const;

    void start();

    template <class T>void registerRoute()
    {
        routes.insert(routes.begin(), new T());
    }

public: //public nested
    class ClientSocket
    {
    public:
        ClientSocket(void *socket, void *infos);
        ClientSocket(const ClientSocket & o);
        ~ClientSocket();

        std::string getInfos() const;
        char readChar();
        std::string readLine();
        void write(const std::string &);
        void writeLine(const std::string &);

    private:
        void * socket;
        std::string ip;
        unsigned int port;
        bool initial;

        char buf[2048];
        int bufIndex[2];
    };

private: //private nested
    class Socket
    {
    public:
        Socket(unsigned int port);
        ~Socket();

        HttpClient *waitForRequest();
    private:
        void * socket;
    };

private: //private functions
    void newClient(HttpClient *);

private: //private attributes
    std::string webMaster;
    const unsigned int listeningPort;
    Socket *socket;
    void execRequest(HttpClient *client);
    std::list<AWebPage *>routes;
};
