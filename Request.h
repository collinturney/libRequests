#pragma once

#include <string>
#include <curl/curl.h>
#include <boost/algorithm/string.hpp>
#include <sys/time.h>
#include <Headers.h>
#include <Response.h>
#include <StatusCode.h>

namespace HTTP {

static size_t __curl_write_data(void * ptr,
								        size_t size,
								        size_t nmemb,
							           std::string * data)
{
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}


static size_t __curl_write_headers(char * buffer,
                                   size_t size,
                                   size_t nitems,
                                   HTTP::Headers * headers)
{
   if (buffer[0] == '\r' || buffer[0] == '\n')
      return nitems * size;

   std::string header(buffer, size*nitems);
   std::string::size_type index = header.find(':', 0);

   if (index != std::string::npos) {
      headers->set(
         boost::algorithm::trim_copy(header.substr(0, index)), 
         boost::algorithm::trim_copy(header.substr(index + 1))
      );
   }
   else {
      headers->set(header);
   }
   
   return nitems * size;
}


class Request
{
   public:

      Request();
      ~Request();

      HTTP::Response get(const std::string & url);

      HTTP::Response get(const std::string   & url,
                         const HTTP::Headers & headers);

      HTTP::Response post(const std::string & url,
                          const std::string & data);

      HTTP::Response post(const std::string   & url,
                          const HTTP::Headers & headers,
                          const std::string   & data);

      HTTP::Response put(const std::string & url,
                         const std::string & data);

      HTTP::Response put(const std::string   & url,
                         const HTTP::Headers & headers,
                         const std::string   & data);

      HTTP::Response del(const std::string & url);

      HTTP::Response del(const std::string   & url,
                         const HTTP::Headers & headers);

      HTTP::Response patch(const std::string & url,
                           const std::string & data);

      HTTP::Response patch(const std::string   & url,
                           const HTTP::Headers & headers,
                           const std::string   & data);

   private:

      void curlReset();
      void perform(HTTP::Response & response);

      CURL * curl_;
};

}
