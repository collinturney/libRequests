#pragma once

#include <boost/thread/thread.hpp>
#include <queue>

template<typename T>
class ConcurrentQueue
{
   public:

      typedef boost::mutex Mutex;
      typedef boost::mutex::scoped_lock ScopedLock;
      typedef boost::condition_variable ConditionVariable;

      ConcurrentQueue() :
         maxSize_(100),
         aborted_(false)
      {

      }

      virtual ~ConcurrentQueue() {}
      
      bool push(T const & item)
      {
         ScopedLock lock(mutex_);

         while (queue_.size() >= maxSize_ && ! aborted_) {
            condVarPop_.wait(lock);
         }

         if (aborted_) {
            return false;
         }

         queue_.push(item);
         lock.unlock();
         condVarPush_.notify_one();
         
         return true;
      }

      bool pop(T & item)
      {
         ScopedLock lock(mutex_);

         while (queue_.empty() && ! aborted_) {
            condVarPush_.wait(lock);
         }

         if (aborted_ && queue_.empty()) {
            return false;
         }

         item = queue_.front();
         queue_.pop();

         condVarPop_.notify_one();
         return true;
      }

      bool empty() const
      {
         ScopedLock lock(mutex_);
         return queue_.empty();
      }

      bool size() const
      {
         ScopedLock lock(mutex_);
         return queue_.size();
      }

      void abort()
      {
         ScopedLock lock(mutex_);
         aborted_ = true;
         condVarPop_.notify_all();
         condVarPush_.notify_all(); 
      }

      unsigned int getMaxSize()
      {
         return maxSize_;
      }

      void setMaxSize(const int & size)
      {
         maxSize_ = size;
      }

   protected:

      bool aborted_;

      unsigned int maxSize_;

      std::queue<T> queue_;
      mutable Mutex mutex_;
      ConditionVariable condVarPush_;
      ConditionVariable condVarPop_;
};
