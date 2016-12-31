#include <Headers.h>
#include <Request.h>
#include <Response.h>

using HTTP::Headers;
using HTTP::Request;
using HTTP::Response;

void loadTest(const std::string & url)
{
   Request request;
   Response response;

   for (int i=0; i <= 1000; ++i) {
      response = request.get(url);

      if (! response.ok || response.code != 200) {
         break;
      }

      if (i && i % 100 == 0) {
         printf("Processed %d requests\n", i);
      }
   }
}

int main() {

   Headers headers;
   Request request;
   Response response;

   response = request.get("http://httpbin.org/get");
   puts(response.toString());

   headers.set("Content-Type", "text/plain");
   response = request.post("http://httpbin.org/post",
                           headers,
                           "i has post data");
   puts(response.toString());
   
   //loadTest("http://127.0.0.1:8000/");

   return 0;
}
