#pragma once

#include <ConcurrentQueue.h>
#include <boost/thread/thread.hpp>

template<typename T>
class WorkPile
{
   public:

      WorkPile(int workerCount) :
         init_(false),
         done_(false),
         workerCount_(workerCount) {}

      virtual ~WorkPile() {};

      bool init() {
         assert(! init_);

         for (int i=0; i < workerCount_; ++i) {
            workers_.create_thread(boost::bind(&WorkPile::doWork, this));
         }

         init_ = true;
      }

      virtual void doWork() = 0;

      bool getWork(T & item) {
         return queue_.pop(item);
      }

      bool putWork(const T & item) {
         assert(init_);
         return queue_.push(item);
      }

      bool hasWork() {
         return ! queue_.empty();
      }

      void finishWork() {
         done_ = true;
         queue_.abort();
         workers_.join_all();
      }

      bool done() {
         return done_;
      }

      unsigned int size() {
         return queue_.size();
      }

      unsigned int getMaxPileSize() {
         return queue_.getMaxSize();
      }

      void setMaxPileSize(const unsigned int & size) {
         queue_.setMaxSize(size);
      }

   protected:

      bool init_;
      bool done_;

      unsigned int workerCount_;
      boost::thread_group workers_;

      ConcurrentQueue<T> queue_;
};
