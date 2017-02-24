#ifndef SERVER_MONITOR_H
#define SERVER_MONITOR_H

#include <iostream>
#include <vector> 
#include <string>
#include "request_handler.h"

using namespace std;

namespace http {
namespace server {
class ServerMonitor
{
public:
    static ServerMonitor* getInstance();
    void method();
    ~ServerMonitor()
    {
        instanceFlag = false;
    }
    std::vector<std::pair<std::string, Response::ResponseCode>> getRequests(); 
    std::vector<std::pair<std::string, std::string>> getHandlers(); 

    void addRequest(std::string url, Response::ResponseCode responseCode); 
    void addHandler(std::string handlerName, std::string path);  

private:
    static bool instanceFlag;
    static ServerMonitor *single;
    ServerMonitor()
    {
        //private constructor
    }
    
    std::vector<std::pair<std::string, Response::ResponseCode>> mRequests;
    std::vector<std::pair<std::string, std::string>> mHandlers;
};
}
}
#endif 