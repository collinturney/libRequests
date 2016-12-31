#pragma once

namespace HTTP {

class StatusCode
{
   public:

      static const int UNKNOWN_CODE  = 0;
      static const int UNKNOWN_CLASS = 0;

      //////////////////////////////////////////////////////////////////////////
      // 1xx Informational
      static const int INFORMATIONAL_CLASS = 100;

      static const int CONTINUE            = 100;
      static const int SWITCHING_PROTOCOLS = 101;
      static const int PROCESSING          = 102;
      //////////////////////////////////////////////////////////////////////////


      //////////////////////////////////////////////////////////////////////////
      // 2xx Success
      static const int OK_CLASS                      = 200;

      static const int OK                            = 200;
      static const int CREATED                       = 201;
      static const int ACCEPTED                      = 202;
      static const int NON_AUTHORITATIVE_INFORMATION = 203;
      static const int NO_CONTENT                    = 204;
      static const int RESET_CONTENT                 = 205;
      static const int PARTIAL_CONTENT               = 206;
      static const int MULTI_STATUS                  = 207;
      static const int ALREADY_REPORTED              = 208;
      static const int IM_USED                       = 226;
      //////////////////////////////////////////////////////////////////////////


      //////////////////////////////////////////////////////////////////////////
      // 3xx Redirection
      static const int REDIRECTION_CLASS  = 300;

      static const int MULTIPLE_CHOICES   = 300;
      static const int MOVED_PERMANENTLY  = 301;
      static const int MOVED_TEMPORARILY  = 302;
      static const int SEE_OTHER          = 303;
      static const int NOT_MODIFIED       = 304;
      static const int USE_PROXY          = 305;
      static const int SWITCH_PROXY       = 306;
      static const int TEMPORARY_REDIRECT = 307;
      static const int PERMANENT_REDIRECT = 308;
      //////////////////////////////////////////////////////////////////////////


      //////////////////////////////////////////////////////////////////////////
      // 4xx Client Error
      static const int CLIENT_ERROR_CLASS              = 400;

      static const int BAD_REQUEST                     = 400;
      static const int UNAUTHORIZED                    = 401;
      static const int PAYMENT_REQUIRED                = 402;
      static const int FORBIDDEN                       = 403;
      static const int NOT_FOUND                       = 404;
      static const int METHOD_NOT_ALLOWED              = 405;
      static const int NOT_ACCEPTABLE                  = 406;
      static const int PROXY_AUTHENTICATION_REQUIRED   = 407;
      static const int REQUEST_TIMEOUT                 = 408;
      static const int CONFLICT                        = 409;
      static const int GONE                            = 410;
      static const int LENGTH_REQUIRED                 = 411;
      static const int PRECONDITION_FAILED             = 412;
      static const int PAYLOAD_TOO_LARGE               = 413;
      static const int URI_TOO_LONG                    = 414;
      static const int UNSUPPORTED_MEDIA_TYPE          = 415;
      static const int RANGE_NOT_SATISFIABLE           = 416;
      static const int EXPECTATION_FAILED              = 417;
      static const int IM_A_TEAPOT                     = 418;
      static const int MISDIRECT_REQUEST               = 421;
      static const int UNPROCESSABLE_ENTITY            = 422;
      static const int LOCKED                          = 423;
      static const int FAILED_DEPENDENCY               = 424;
      static const int UPGRADE_REQUIRED                = 426;
      static const int PRECONDITION_REQUIRED           = 428;
      static const int TOO_MANY_REQUESTS               = 429;
      static const int REQUEST_HEADER_FIELDS_TOO_LARGE = 431;
      static const int UNAVAILABLE_FOR_LEGAL_REASONS   = 451;
      //////////////////////////////////////////////////////////////////////////
      

      //////////////////////////////////////////////////////////////////////////
      // 5xx Server Error
      static const int SERVER_ERROR_CLASS              = 500;

      static const int INTERNAL_SERVER_ERROR           = 500;
      static const int NOT_IMPLEMENTED                 = 501;
      static const int BAD_GATEWAY                     = 502;
      static const int SERVICE_UNAVAILABLE             = 503;
      static const int GATEWAY_TIMEOUT                 = 504;
      static const int HTTP_VERSION_NOT_SUPPORTED      = 505;
      static const int VARIANT_ALSO_NEGOTIATES         = 506;
      static const int INSUFFICIENT_STORAGE            = 507;
      static const int LOOP_DETECTED                   = 508;
      static const int NOT_EXTENDED                    = 510;
      static const int NETWORK_AUTHENTICATION_REQUIRED = 511;
      //////////////////////////////////////////////////////////////////////////

      
      static inline int getClass(const long & responseCode)
      {
         if (responseCode >= 100 && responseCode < 200)
            return INFORMATIONAL_CLASS;

         if (responseCode >= 200 && responseCode < 300)
            return OK_CLASS;

         if (responseCode >= 300 && responseCode < 400)
            return REDIRECTION_CLASS;

         if (responseCode >= 400 && responseCode < 500)
            return CLIENT_ERROR_CLASS;

         if (responseCode >= 500 && responseCode < 600)
            return SERVER_ERROR_CLASS;
         
         return UNKNOWN_CLASS;
      }
};

}
