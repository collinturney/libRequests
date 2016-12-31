#include <Headers.h>

namespace HTTP {

Headers::Headers() :
   type_(REQUEST),
   curlHeaders_(NULL)
{
  
}


Headers::Headers(Headers::Type type) :
   type_(type),
   curlHeaders_(NULL)
{

}


Headers::~Headers()
{
   clear();
}


bool
Headers::isSet(const std::string & name)
{
   HeaderMap::iterator iter = headers_.find(name);
   return iter != headers_.end();
}


std::string
Headers::get(const std::string & name)
{
   HeaderMap::iterator iter = headers_.find(name);

   if (iter != headers_.end()) {
      return iter->second;
   }
   else {
      return "";
   }
}


std::string
Headers::operator[](const std::string & name)
{
   return get(name);
}


void
Headers::set(const std::string & name, const std::string & value)
{
   headers_.insert( StringPair(name, value) );

   std::string nameValue = name;
   nameValue += ": ";
   nameValue += value;

   if (type_ == REQUEST) {
      curlHeaders_ = curl_slist_append(curlHeaders_, nameValue.c_str());
   }
}


void
Headers::set(const std::string & name)
{
   headers_.insert( StringPair(name, "") );

   if (type_ == REQUEST) {
      curlHeaders_ = curl_slist_append(curlHeaders_, (name + ";").c_str());
   }
}


void
Headers::clear()
{
   if (curlHeaders_) {
      curl_slist_free_all(curlHeaders_);
      curlHeaders_ = NULL;
   }

   headers_.clear();
}


unsigned int
Headers::size()
{
   return headers_.size();
}


Headers::const_iterator
Headers::begin() const
{
   return headers_.begin();
}


Headers::const_iterator
Headers::end() const
{
   return headers_.end();
}


const struct curl_slist * Headers::getCurlHeaders() const
{
   return curlHeaders_;
}

}
