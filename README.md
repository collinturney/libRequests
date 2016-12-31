#libRequests

This library provides a simple means for making HTTP requests from C++ code without much boilerplate. It was designed to match the usage patterns of the popular [requests](http://docs.python-requests.org) library for Python.

##Dependencies

- libcurl-dev
- libboost-dev
- rapidjson-dev

##Building

First, install the required dependencies. For Ubuntu 16.04 or Linux Mint 18:

    $ sudo apt install libboost-dev libcurl-dev rapidjson-dev

The included Makefile will build the library as well as the included examples.

    $ make
    g++ -O2 -g -I. -o headersTest HeadersTest.cpp  -L. -lRequests -lcurl -lboost_system -lboost_thread
    g++ -O2 -g -I. -o requestTest RequestTest.cpp  -L. -lRequests -lcurl -lboost_system -lboost_thread
    g++ -O2 -g -I. -o loadTest    LoadTest.cpp     -L. -lRequests -lcurl -lboost_system -lboost_thread
    make -C examples all
    make[1]: Entering directory '/home/collin/libRequests/examples'
    g++ -O2 -g -I.. -o requestExample  request.cpp -L.. -lRequests -lcurl -lboost_system -lboost_thread
    g++ -O2 -g -I.. -o responseExample response.cpp -L.. -lRequests -lcurl -lboost_system -lboost_thread
    g++ -O2 -g -I.. -o headersExample  headers.cpp -L.. -lRequests -lcurl -lboost_system -lboost_thread
    make[1]: Leaving directory '/home/collin/libRequests/examples'

##Examples

A simple HTTP request:

    #include <Request.h>
    #include <Response.h>

    int main() {
       HTTP::Request request;
       HTTP::Response response;

       response = request.get("http://httpbin.org/status/418");

       puts(response.text.c_str());

       return 0;
    }

HTTP request with modified headers:

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

Here is another example that includes examining response metadata. The response object also includes the parsed HTTP response headers and the response as JSON for logging or downstream parsing.

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

Finally, the included LoadTest client serves as an 'Apache Benchmark'-like example of how threading can easily be done with the library and the included utility classes for managing concurrency. The library is fairly lightweight and is easily capable of generating thousands of requests per second.

    $ ./loadTest -u http://newton:8080 -t 16 -n 10000
    [url=http://newton:8080 threads=16 requests=10000]
    [processed 10000 requests (0 errors) (31.91 ms avg latency)]

