#include "server_monitor.h" 

//Our singleton class that helps monitor the status of our server

namespace http {
namespace server {

bool ServerMonitor::instanceFlag = false;
ServerMonitor* ServerMonitor::single = NULL;

ServerMonitor* ServerMonitor::getInstance()
{
    if(!instanceFlag)
    {
        single = new ServerMonitor();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}

void ServerMonitor::method()
{
    cout << "Method of the singleton class" << endl;
}

std::vector<std::pair<std::string, Response::ResponseCode>> ServerMonitor::getRequests(){
    return mRequests;
} 

std::vector<std::pair<std::string, std::string>> ServerMonitor::getHandlers(){
    return mHandlers; 
}

void ServerMonitor::addRequest(std::string url, Response::ResponseCode responseCode){
    std::pair<std::string, Response::ResponseCode> requestInfo = std::make_pair(url, responseCode);
    mRequests.push_back(requestInfo);
}

void ServerMonitor::addHandler(std::string path, std::string handlerName){
    std::pair<std::string, std::string> handlerInfo = std::make_pair(path, handlerName);
    mHandlers.push_back(handlerInfo);
}

// int ServerMonitor::getNumRequests(){
//     return numRequests;
// }

// void ServerMonitor::incrementRequests(){
//     numRequests++; 
// }

}
}
