//
// Created by f.wimmer on 12.10.2021.
//

#ifndef ESP32PROROTYPINGLIB_WEBSOCKETSERVER_H
#define ESP32PROROTYPINGLIB_WEBSOCKETSERVER_H

#include <HTTPSServer.hpp>

class WebSocketServer {
public:
    WebSocketServer(httpsserver::WebsocketHandlerCreator creatorFunction);

    void init(httpsserver::HTTPSServer *secureServer);
    void loop();

private:
    httpsserver::WebsocketNode mWebSocketNode;
};


#endif //ESP32PROROTYPINGLIB_WEBSOCKETSERVER_H
