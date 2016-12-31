#include <Request.h>


namespace HTTP {


Request::Request()
{
   curl_ = curl_easy_init();
   curlReset();
}


Request::~Request()
{
   curl_easy_cleanup(curl_);
}


void Request::curlReset()
{
   curl_easy_reset(curl_);
	curl_easy_setopt(curl_, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl_, CURLOPT_TIMEOUT, 10L);
   curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, __curl_write_data);
   curl_easy_setopt(curl_, CURLOPT_HEADERFUNCTION, __curl_write_headers);
}


HTTP::Response
Request::get(const std::string & url)
{
   HTTP::Response response;

   curlReset();
	curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
   curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response.text);
   curl_easy_setopt(curl_, CURLOPT_HEADERDATA, &response.headers);

   perform(response);

   return response;
}


HTTP::Response
Request::get(const std::string & url,
              const HTTP::Headers & headers)
{
   HTTP::Response response;

   curlReset();
	curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
   curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, headers.getCurlHeaders());
   curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response.text);
   curl_easy_setopt(curl_, CURLOPT_HEADERDATA, &response.headers);

   perform(response);

   return response;
}


HTTP::Response
Request::post(const std::string & url,
               const std::string & data)
{
   HTTP::Response response;

   curlReset();
	curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
   curl_easy_setopt(curl_, CURLOPT_POST, 1L);
   curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, data.c_str());
   curl_easy_setopt(curl_, CURLOPT_POSTFIELDSIZE, (long) data.size());
   curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response.text);
   curl_easy_setopt(curl_, CURLOPT_HEADERDATA, &response.headers);

   perform(response);

   return response;
}


HTTP::Response
Request::post(const std::string   & url,
               const HTTP::Headers & headers,
               const std::string   & data)
{
   HTTP::Response response;

   curlReset();
	curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
   curl_easy_setopt(curl_, CURLOPT_POST, 1L);
   curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, headers.getCurlHeaders());
   curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, data.c_str());
   curl_easy_setopt(curl_, CURLOPT_POSTFIELDSIZE, (long) data.size());
   curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response.text);
   curl_easy_setopt(curl_, CURLOPT_HEADERDATA, &response.headers);

   perform(response);

   return response;
}


HTTP::Response
Request::put(const std::string & url,
              const std::string & data)
{
   HTTP::Response response;

   curlReset();
	curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
   curl_easy_setopt(curl_, CURLOPT_CUSTOMREQUEST, "PUT");
   curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, data.c_str());
   curl_easy_setopt(curl_, CURLOPT_POSTFIELDSIZE, (long) data.size());
   curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response.text);
   curl_easy_setopt(curl_, CURLOPT_HEADERDATA, &response.headers);

   perform(response);

   return response;
}


HTTP::Response
Request::put(const std::string & url,
              const HTTP::Headers & headers,
              const std::string & data)
{
   HTTP::Response response;

   curlReset();
	curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
   curl_easy_setopt(curl_, CURLOPT_CUSTOMREQUEST, "PUT");
   curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, headers.getCurlHeaders());
   curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, data.c_str());
   curl_easy_setopt(curl_, CURLOPT_POSTFIELDSIZE, (long) data.size());
   curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response.text);
   curl_easy_setopt(curl_, CURLOPT_HEADERDATA, &response.headers);

   perform(response);

   return response;
}


HTTP::Response
Request::del(const std::string & url)
{
   HTTP::Response response;

   curlReset();
	curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
   curl_easy_setopt(curl_, CURLOPT_CUSTOMREQUEST, "DELETE");
   curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response.text);
   curl_easy_setopt(curl_, CURLOPT_HEADERDATA, &response.headers);

   perform(response);

   return response;
}


HTTP::Response
Request::del(const std::string   & url,
              const HTTP::Headers & headers)
{
   HTTP::Response response;

   curlReset();
	curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
   curl_easy_setopt(curl_, CURLOPT_CUSTOMREQUEST, "DELETE");
   curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, headers.getCurlHeaders());
   curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response.text);
   curl_easy_setopt(curl_, CURLOPT_HEADERDATA, &response.headers);

   perform(response);

   return response;
}


HTTP::Response Request::patch(const std::string & url,
                               const std::string & data)
{
   HTTP::Response response;

   curlReset();
	curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
   curl_easy_setopt(curl_, CURLOPT_CUSTOMREQUEST, "PATCH");
   curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, data.c_str());
   curl_easy_setopt(curl_, CURLOPT_POSTFIELDSIZE, (long) data.size());
   curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response.text);
   curl_easy_setopt(curl_, CURLOPT_HEADERDATA, &response.headers);

   perform(response);

   return response;
}


HTTP::Response Request::patch(const std::string   & url,
                               const HTTP::Headers & headers,
                               const std::string   & data)
{
   HTTP::Response response;

   curlReset();
	curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
   curl_easy_setopt(curl_, CURLOPT_CUSTOMREQUEST, "PATCH");
   curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, headers.getCurlHeaders());
   curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, data.c_str());
   curl_easy_setopt(curl_, CURLOPT_POSTFIELDSIZE, (long) data.size());
   curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response.text);
   curl_easy_setopt(curl_, CURLOPT_HEADERDATA, &response.headers);

   perform(response);

   return response;
}


void
Request::perform(HTTP::Response & response)
{
   struct timeval t1, t2;

   gettimeofday(&t1, NULL);

   CURLcode ret = curl_easy_perform(curl_);

   gettimeofday(&t2, NULL);

   response.elapsed = (t2.tv_sec - t1.tv_sec) * 1000.0;
   response.elapsed += (t2.tv_usec - t1.tv_usec) / 1000.0;

   long responseCode;
   curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &responseCode);

   response.code = (int) responseCode;
   response.codeClass = StatusCode::getClass(responseCode);

   if (ret == CURLE_OK) {
      response.ok = true;
   }
   else {
      response.curlCode = ret;
      response.error.assign(curl_easy_strerror(ret));
   }
}

}
