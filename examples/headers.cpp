#include <Request.h>
#include <Response.h>

int main() {

   HTTP::Request request;
   HTTP::Headers headers;
   HTTP::Response response;

   headers.set("Accept", "application/json");

   response = request.get("http://httpbin.org/headers", headers);

   puts(response.text.c_str());

   return 0;
}
