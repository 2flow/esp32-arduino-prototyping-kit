//
// Created by f.wimmer on 12.10.2021.
//

#include "FileServer.h"
#include <functional>
// We will use SPIFFS and FS
#include <FS.h>
#include <HTTPBodyParser.hpp>
#include <HTTPMultipartBodyParser.hpp>
#include "ServiceProvider.h"
using namespace httpsserver;

FS* FileServer::sFileSystem = nullptr;

static char contentTypes[][2][32] = {
        {".html", "text/html"},
        {".css",  "text/css"},
        {".js",   "application/javascript"},
        {".json", "application/json"},
        {".png",  "image/png"},
        {".jpg",  "image/jpg"},
        {"", ""}
};

std::string FileServer::htmlEncode(std::string const & data) {
    // Quick and dirty: doesn't handle control chars and such.
    const char *p = data.c_str();
    std::string rv = "";
    while(p && *p) {
        char escapeChar = *p++;
        switch(escapeChar) {
            case '&': rv += "&amp;"; break;
            case '<': rv += "&lt;"; break;
            case '>': rv += "&gt;"; break;
            case '"': rv += "&quot;"; break;
            case '\'': rv += "&#x27;"; break;
            case '/': rv += "&#x2F;"; break;
            default: rv += escapeChar; break;
        }
    }
    return rv;
}

void FileServer::init(httpsserver::HTTPServer *httpServer, std::string const& baseURLPath, FS* fileSystem) {
    if(httpServer != nullptr){
        auto *nodeFormUpload = new ResourceNode(baseURLPath+"/upload", "POST", &FileServer::handleFormUpload);
        auto *nodeRoot = new ResourceNode(baseURLPath+"/upload", "GET", &FileServer::handleUploadPage);
        auto *nodeFile = new ResourceNode(baseURLPath+"/*", "GET", &FileServer::handleFile);

        httpServer->registerNode(nodeFormUpload);
        httpServer->registerNode(nodeRoot);
        httpServer->registerNode(nodeFile);
    }

    if(fileSystem == nullptr) {
        sFileSystem = ServiceProvider<FS>::getGlobalService();
    }else{
        sFileSystem = fileSystem;
    }
}

void FileServer::handleFile(httpsserver::HTTPRequest *req, httpsserver::HTTPResponse *res) {
    std::string filename = req->getRequestString();
    // Check if the file exists
    if ((sFileSystem == nullptr) || !sFileSystem->exists(filename.c_str())) {
        // Send "404 Not Found" as response, as the file doesn't seem to exist
        res->setStatusCode(404);
        res->setStatusText("Not found");
        res->println("404 Not Found");
        return;
    }

    File file = sFileSystem->open(filename.c_str());

    // Set length
    res->setHeader("Content-Length", httpsserver::intToString(file.size()));

    // Content-Type is guessed using the definition of the contentTypes-table defined above
    int cTypeIdx = 0;
    do {
        if(filename.rfind(contentTypes[cTypeIdx][0])!=std::string::npos) {
            res->setHeader("Content-Type", contentTypes[cTypeIdx][1]);
            break;
        }
        cTypeIdx+=1;
    } while(strlen(contentTypes[cTypeIdx][0])>0);

    // Read the file and write it to the response
    uint8_t buffer[256];
    size_t length = 0;
    do {
        length = file.read(buffer, 256);
        res->write(buffer, length);
    } while (length > 0);

    file.close();
}

void FileServer::handleUploadPage(httpsserver::HTTPRequest *req, httpsserver::HTTPResponse *res) {
    // Status code is 200 OK by default.
    // We want to deliver a simple HTML page, so we send a corresponding content type:
    res->setHeader("Content-Type", "text/html");

    // The response implements the Print interface, so you can use it just like
    // you would write to Serial etc.
    res->println("<!DOCTYPE html>");
    res->println("<html>");
    res->println("<head><title>Very simple file server</title></head>");
    res->println("<body>");
    res->println("<h1>Very simple file server</h1>");
    res->println("<p>This is a very simple file server to demonstrate the use of POST forms. </p>");
    res->println("<h2>List existing files</h2>");
    res->println("<p>See <a href=\"/public\">/public</a> to list existing files and retrieve or edit them.</p>");
    res->println("<h2>Upload new file</h2>");
    res->println("<p>This form allows you to upload files (text, jpg and png supported best). It demonstrates multipart/form-data.</p>");
    res->println(R"(<form method="POST" action="/upload" enctype="multipart/form-data">)");
    res->println(R"(file: <input type="file" name="file"><br>)");
    res->println(R"(<input type="submit" value="Upload">)");
    res->println("</form>");
    res->println("</body>");
    res->println("</html>");
}

void FileServer::handleFormUpload(httpsserver::HTTPRequest *req, httpsserver::HTTPResponse *res) {
// First, we need to check the encoding of the form that we have received.
    // The browser will set the Content-Type request header, so we can use it for that purpose.
    // Then we select the body parser based on the encoding.
    // Actually we do this only for documentary purposes, we know the form is going
    // to be multipart/form-data.
    HTTPBodyParser *parser;
    std::string contentType = req->getHeader("Content-Type");
    size_t semicolonPos = contentType.find(";");
    if (semicolonPos != std::string::npos) {
        contentType = contentType.substr(0, semicolonPos);
    }
    if (contentType == "multipart/form-data") {
        parser = new HTTPMultipartBodyParser(req);
    } else {
        Serial.printf("Unknown POST Content-Type: %s\n", contentType.c_str());
        return;
    }
    // We iterate over the fields. Any field with a filename is uploaded
    res->println("<html><head><title>File Upload</title></head><body><h1>File Upload</h1>");
    bool didwrite = false;
    while(parser->nextField()) {
        std::string name = parser->getFieldName();
        std::string filename = parser->getFieldFilename();
        std::string mimeType = parser->getFieldMimeType();
        Serial.printf("handleFormUpload: field name='%s', filename='%s', mimetype='%s'\n", name.c_str(), filename.c_str(), mimeType.c_str());
        // Double check that it is what we expect
        if (name != "file") {
            Serial.println("Skipping unexpected field");
            break;
        }


        if(sFileSystem != nullptr) {
            // Should check file name validity and all that, but we skip that.
            std::string pathname = "/public/" + filename;
            File file = sFileSystem->open(pathname.c_str(), "w");
            size_t fileLength = 0;
            didwrite = true;
            while (!parser->endOfField()) {
                byte buf[512];
                size_t readLength = parser->read(buf, 512);
                file.write(buf, readLength);
                fileLength += readLength;
            }
            file.close();
            res->printf("<p>Saved %d bytes to %s</p>", (int) fileLength, pathname.c_str());
        }
    }
    if (!didwrite) {
        res->println("<p>Did not write any file</p>");
    }
    res->println("</body></html>");
    delete parser;
}
