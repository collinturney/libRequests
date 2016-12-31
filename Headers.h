#pragma once

#include <string>
#include <map>
#include <curl/curl.h>

namespace HTTP {

class Headers
{
   public:

      typedef std::map<std::string, std::string> HeaderMap;
      typedef std::pair<std::string, std::string> StringPair;
      typedef HeaderMap::const_iterator const_iterator;

      enum Type {
         REQUEST=0,
         RESPONSE
      };

      Headers();
      Headers(Type type);
      ~Headers();
      
      bool isSet(const std::string & name);

      std::string get(const std::string & name);
      std::string operator [](const std::string & name);

      void set(const std::string & name, const std::string & value);
      void set(const std::string & name);

      void clear();

      unsigned int size();

      const_iterator begin() const;
      const_iterator end() const;

      const struct curl_slist * getCurlHeaders() const;

   private:

      HeaderMap headers_;
      Type type_;
      struct curl_slist * curlHeaders_;
};

}
