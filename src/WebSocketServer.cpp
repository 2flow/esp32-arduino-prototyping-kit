//
// Created by f.wimmer on 12.10.2021.
//

#include "WebSocketServer.h"

using namespace httpsserver;

WebSocketServer::WebSocketServer(WebsocketHandlerCreator creatorFunction) :
    mWebSocketNode("/ws", creatorFunction) {
}

void WebSocketServer::init(httpsserver::HTTPSServer *secureServer) {
    secureServer->registerNode(&mWebSocketNode);
}
