#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

#include <Request.h>
#include <Response.h>
#include <WorkPile.h>


class ResponseHandler : public WorkPile<HTTP::Response>
{
   public:

      ResponseHandler() :
         WorkPile(1)
      {

      }

      void doWork()
      {
         HTTP::Response response;

         double average = 0;
         unsigned long count = 1;
         unsigned long errors = 0;

         while (! WorkPile::done() || WorkPile::hasWork()) {
            if (! WorkPile::getWork(response)) {
               break;
            }

            if (response.codeClass == 200) {
               average += (response.elapsed - average) / count;
            }
            else {
               errors++;
            }

            count++;
         }

         printf("[processed %ld requests (%ld errors) (%.2f ms avg latency)]\n",
            count-1, errors, average);
      }
};


class RequestPile : public WorkPile<std::string>
{
   public:

      RequestPile(int numWorkers) :
         WorkPile(numWorkers)
      {

      }

      bool init()
      {
         WorkPile::init();
         responseHandler_.init();
      }

      void doWork()
      {
         HTTP::Request request;
         HTTP::Response response;

         std::string url;

         while (! WorkPile::done() || WorkPile::hasWork()) {
            if (! WorkPile::getWork(url)) {
               break;
            }

            response = request.get(url);
            responseHandler_.putWork(response);
         }
      }

      void finishWork()
      {
         WorkPile::finishWork();
         responseHandler_.finishWork();
      }

   protected:

      ResponseHandler responseHandler_;
};


void usage(int argc, char ** argv)
{
   fprintf(stderr, "Usage: %s (-u URL) [-n NUM_REQUESTS] [-t NUM_THREADS]\n",
      argv[0]);

   exit(0);
}


int main(int argc, char ** argv) {

   int c;
   int threads = 0;
   int requests = 0;
   std::string url;

   while ((c = getopt(argc, argv, "hn:t:u:")) != -1) {
      switch (c) {
         case 'h':
            usage(argc, argv);
         break;

         case 'n':
            requests = atoi(optarg);
         break;

         case 't':
            threads = atoi(optarg);
         break;

         case 'u':
            url = optarg;
         break;
      }
   }

   threads = (threads ? threads : 4);
   requests = (requests ? requests : 1000);

   if (url.empty()) {
      printf("URL not specified.\n\n");
      usage(argc, argv);
   }

   printf("[url=%s threads=%d requests=%d]\n", url.c_str(), threads, requests);

   RequestPile pile(threads);
   pile.init();

   for (int i=0; i < requests; ++i) {
      pile.putWork(url);
   }

   pile.finishWork();

   return 0;
}
