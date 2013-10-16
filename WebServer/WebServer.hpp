#pragma once

#include <string>
#include <list>
#include "ARootElement.h"

class HttpClient;
class AWebPage;

/*!
* This class represents a WebServer, which is
* an entity listening on one network port, and
* will create an HttpClient instance for each client
* in order to respond to them using his RouteMap.
*/
class WebServer
{
public: //public methods
    /*!
    * Create a webserver, listening on given port
    */
    WebServer(unsigned int port = 80);
    /*!
    * Destroy the WebServer, and free all ressources
    */
    virtual ~WebServer();

    /*!
    * set the server maintainer
    */
    WebServer * setWebmaster(const std::string &webMasterEmail);
    /*!
    * get the server maintainer
    */
    std::string getWebmaster() const;

    /*!
    * start listening for new clients
    */
    void start();

    /*!
    * add a route to the map route
    */
    template <class T>
    void registerRoute()
    {
        routes.insert(routes.begin(), new T()); //TODO gestion hosts
    }
    /*!
    * Add a real folder to be mapped
    */
    void registerDirectory(const std::string & path, const std::string & virtualUrl = "/", bool recursive = true);

public: //public nested
    /*!
    * nested clientSocket class
    */
    class ClientSocket
    {
    public:
        /*!
        * create a new client socket
        */
        ClientSocket(void *socket, void *infos);
        /*!
        * copy the other socket inside this one
        */
        ClientSocket(const ClientSocket & o);
        /*!
        * destroy the client socket.
        * If the ClientSocket has not been created by copy,
        * close the socket
        */
        ~ClientSocket();

        /*!
        * return information on client, with syntax
        * `$ip ($port)`
        */
        std::string getInfos() const;
        /*!
        * read one char on the client socket. Use the round-buffer to read
        */
        char readChar();
        /*!
        * read one line on the client socket. Use the round-buffer to read
        */
        std::string readLine();
        /*!
        * Write the given string into the socket
        */
        void write(const std::string &);
        /*!
        * Write the `len` given bytes into the socket
        */
        void write(const char *value, const long long len);
        /*!
        * Write the given string into the socket, and add a EOL (\n) at the end
        */
        void writeLine(const std::string &);
        /*!
        * Get the client-side port
        */
        unsigned short getPort() const;

    private:
        /*!
        * The socket instance. void* because it can differ from systems
        */
        void * socket;
        /*!
        * The client's ip
        */
        std::string ip; //TODO GETTER
        /*!
        * The client's port
        */
        unsigned int port;
        /*!
        * true if has been created using socket, false if created using copy
        */
        bool initial;

        /*!
        * Round buffer for reading data
        */
        char buf[2048];
        /*!
        * Round buffer indexes for reading data
        */
        int bufIndex[2];
    };

private: //private nested
    class Socket
    {
    public:
        /*!
        * Create the server socket and initialize it to liten on given port
        */
        Socket(unsigned int port);
        /*!
        * Destroy the server socket
        */
        ~Socket();

        /*!
        * wait until new client connection
        */
        HttpClient *waitForRequest();
    private:
        /*!
        * Server socket data struct. void* because it can differ from systems.
        */
        void * socket;
    };

    /*!
    * Contains a mapped directory informations
    */
    class MappedDirectory
    {
    public:
        MappedDirectory(const std::string &realPath, const std::string &virtualPath, bool recur);
        ~MappedDirectory();

        /*!
        * return the real file path if the url
        * match the mappedDirectory, or
        * an empty string if it not
        */
        std::string match(const std::string &url);

    private:
        const std::string realPath;
        const std::string virtualPath;
        std::list<std::string> virtualPathPart;
        bool recursive;
    };

    /*!
    * A file about to be sended to the client
    */
    class FileElement : public ARootElement
    {
    public:
        FileElement(const std::string & path);
        ~FileElement();

        const std::string getValue();
        unsigned int length();
        void send(ClientSocket * sock);

    private:
        long long size;
        const std::string path;
        std::ifstream * stream;
    };

private: //private functions
    /*!
    * Called when a new client show up. It
    * 1. Read all the request
    * 2. Execute the request
    */
    void newClient(HttpClient *);
    /*!
    * Called to execute the request. It
    * 1. Analyse the request
    * 2. Check the road
    * 3. Call the AWebPage corresponding to it
    * 4. Send the response
    */
    void execRequest(HttpClient *client);

    /*
    * send the file to the client
    */
    void sendFile(const std::string & path, HttpClient * client);

private: //private attributes
    /*!
    * Webmaster infos
    */
    std::string webMaster;
    /*!
    * current listening port
    */
    const unsigned int listeningPort;
    /*!
    * Server socket
    */
    Socket *socket;
    /*!
    * list of all the routes available
    */
    std::list<AWebPage *>routes;
    /*!
    * list of all the mapped folders
    */
    std::list<MappedDirectory *>mappedDirectories;
};
