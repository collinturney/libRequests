#include <Request.h>
#include <Response.h>

using HTTP::Request;
using HTTP::Response;
using HTTP::StatusCode;

int main() {

   Request request;
   Response response;

   response = request.get("http://httpbin.org/status/407");

   if (response.ok && response.code == StatusCode::PROXY_AUTHENTICATION_REQUIRED) {
      printf("code        = [%d]\n", response.code);
      printf("codeClass   = [%d]\n", response.codeClass);
      printf("latency     = [%.2f]\n", response.elapsed);
      printf("date header = [%s]\n", response.headers.get("Date").c_str());

      puts("response as json:");
      puts(response.toString());
   }
   else {
      puts("Something went wrong!");
   }

   return 0;
}
