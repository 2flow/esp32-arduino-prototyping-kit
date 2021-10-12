//
// Created by f.wimmer on 12.10.2021.
//

#ifndef ESP32PROROTYPINGLIB_FILESERVER_H
#define ESP32PROROTYPINGLIB_FILESERVER_H

#include <HTTPSServer.hpp>
#include "FS.h"
#include <string>
class FileServer {
public:
    /**
     *
     * @param httpServer
     * @param baseURLPath
     * @param fileSystem if nullptr the serviceprovider default filesystem is used
     */
    static void init(httpsserver::HTTPServer* httpServer, std::string const& baseURLPath = "/public", FS* fileSystem = nullptr);

private:
    static FS* sFileSystem;
    static void handleFile(httpsserver::HTTPRequest * req, httpsserver::HTTPResponse * res);
    static void handleFormUpload(httpsserver::HTTPRequest * req, httpsserver::HTTPResponse * res);
    static void handleUploadPage(httpsserver::HTTPRequest * req, httpsserver::HTTPResponse * res);
    static std::string htmlEncode(std::string const & data);
};


#endif //ESP32PROROTYPINGLIB_FILESERVER_H
