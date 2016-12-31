#include <Request.h>
#include <Response.h>

int main() {

   HTTP::Request request;
   HTTP::Response response;

   response = request.get("http://httpbin.org/status/418");

   puts(response.text.c_str());

   return 0;
}
