#include "arbiter_example.hpp"
#include "BuildInfo.hpp"

#include <arbiter.hpp>
#include <pdal/util/FileUtils.hpp>

using namespace arbiter;

namespace pdal
{
   static PluginInfo const s_info{
         BuildInfo::PDALStageName,
         BuildInfo::PluginDescription,
         BuildInfo::PluginURL
   };

   CREATE_SHARED_STAGE(arbiter_example, s_info)

   std::string arbiter_example::getName() const {
      return s_info.name;
   }

   void arbiter_example::addArgs(ProgramArgs& args) {
      args.add("file", "The file", file);
      args.add("cache", "The file cache", cache, "/tmp");
   }

   PointViewSet arbiter_example::run(PointViewPtr view) {
      std::cout << BuildInfo::PDALStageName << "::run" << std::endl;

      // configure arbiter, this gets moved out
      Json::Value json;
      json["s3"]["endpoint"] = "localhost:9000";
      json["s3"]["access"] = "defaultkey";
      json["s3"]["secret"] = "defaultkey";

      arbiter::Arbiter a(json);

      // get a handle to the file, which will be pulled from the source if not present
      auto h = a.getLocalHandle(file, cache);
      auto p = h->localPath();

      // print the file contents
      std::cout << pdal::FileUtils::readFileIntoString(p) << std::endl;

      PointViewSet viewSet;
      viewSet.insert(view);
      return viewSet;
   }
}
