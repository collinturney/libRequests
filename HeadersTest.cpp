#include <iostream>
#include <string>
#include <cassert>
#include <Headers.h>

int main() {

   HTTP::Headers headers;   

   assert(headers.size() == 0);
   assert(! headers.isSet("Accept"));
   assert(headers.get("Accept").compare("") == 0);

   headers.set("Accept", "application/json");

   assert(headers.size() == 1);
   assert(headers.isSet("Accept"));
   assert(headers.get("Accept").compare("application/json") == 0);

   headers.set("Proxy-Authorization", "Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ==");
   assert(headers.isSet("Proxy-Authorization"));

   return 0;
}
