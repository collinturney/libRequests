#include <Response.h>

namespace HTTP {

Response::Response() :
   ok(false),
   code(0),
   codeClass(0),
   elapsed(0),
   curlCode(CURLE_OK),
   headers(Headers::RESPONSE)
{

}


Response::~Response()
{

}


const char *
Response::toString()
{
   if (! this->json.empty()) {
      return this->json.c_str();
   }

   rapidjson::Document doc;
   rapidjson::Document::AllocatorType & alloc = doc.GetAllocator();

   doc.SetObject();
   doc.AddMember("ok", this->ok, alloc);
   doc.AddMember("code", this->code, alloc);
   doc.AddMember("codeClass", this->codeClass, alloc);
   doc.AddMember("curlCode", this->curlCode, alloc);
   doc.AddMember("elapsed", this->elapsed, alloc);

   rapidjson::Value jsonName;
   rapidjson::Value jsonValue;

   rapidjson::Value headers(rapidjson::kObjectType);

   Headers::const_iterator iter;
   for (iter = this->headers.begin(); iter != this->headers.end(); ++iter) {
      const std::string & name = iter->first;
      const std::string & value = iter->second;

      jsonName.SetString(name.data(), name.size(), alloc);
      jsonValue.SetString(value.data(), value.size(), alloc);
      headers.AddMember(jsonName, jsonValue, alloc);
   }

   doc.AddMember("headers", headers, alloc);

   jsonValue.SetString(this->text.data(), this->text.size(), alloc);
   doc.AddMember("text", jsonValue, alloc);

   jsonValue.SetString(this->error.data(), this->error.size(), alloc);
   doc.AddMember("error", jsonValue, alloc);

   rapidjson::StringBuffer buf;
   rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buf);
   doc.Accept(writer);

   this->json = buf.GetString();
   return this->json.c_str();
}

}
