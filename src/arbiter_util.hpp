//
// from https://github.com/connormanning/entwine/blob/master/entwine/io/ensure.cpp
//

#pragma once

#include <thread>
#include "arbiter.hpp"

namespace
{
   const std::size_t retries(40);
   std::mutex mutex;

   void sleep(std::size_t tried, std::string method, std::string path) {
      std::this_thread::sleep_for(std::chrono::seconds(tried));

      std::lock_guard <std::mutex> lock(mutex);
      std::cout <<
                "\tFailed " << method << " attempt " << tried << ": " << path <<
                std::endl;
   }

   void suicide(std::string method) {
      std::lock_guard <std::mutex> lock(mutex);
      std::cout <<
                "\tFailed to " << method << " data: persistent failure.\n" <<
                "\tThis is a non-recoverable error." <<
                std::endl;

      throw std::runtime_error("Fatal error - could not " + method);
   }
}

namespace
{

   void ensurePut(
         const arbiter::Endpoint& endpoint,
         const std::string& path,
         const std::vector<char>& data) {
      bool done(false);
      std::size_t tried(0);

      while(!done) {
         try {
            endpoint.put(path, data);
            done = true;
         }
         catch(...) {
            if(++tried < retries) {
               sleep(tried, "PUT", endpoint.prefixedRoot() + path);
            }
            else suicide("PUT");
         }
      }
   }
}
