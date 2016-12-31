#pragma once

#include <string>
#include <curl/curl.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <Headers.h>

namespace HTTP {

class Response
{
   public:

      Response();
      ~Response();

      bool ok;

      // Response metadata
      HTTP::Headers headers;
      int code;               // HTTP status code
      int codeClass;          // HTTP status code class
      CURLcode curlCode;      // CURL response code
      float elapsed;          // latency in milliseconds

      // Response body
      std::string text;
      std::string error;

      // string Response encoding
      const char * toString();
      std::string json;
};

}
