#include "arbiter_reader.hpp"
#include "BuildInfo.hpp"

#include <arbiter.hpp>
#include <pdal/util/FileUtils.hpp>

using namespace arbiter;

namespace pdal
{
   static PluginInfo const s_info{
         "filters.arbiter_reader",
         BuildInfo::PluginDescription,
         BuildInfo::PluginURL
   };

   CREATE_SHARED_STAGE(arbiter_reader, s_info)

   std::string arbiter_reader::getName() const {
      return s_info.name;
   }

   void arbiter_reader::addArgs(ProgramArgs& args) {
      args.add("file", "The file", file);
      args.add("cache", "The file cache", cache, "/tmp");
      args.add("arbiter", "The arbiter config", ajson, "");
   }

   PointViewSet arbiter_reader::run(PointViewPtr view) {
      std::cout << "filters.arbiter_reader::run" << std::endl;

      std::shared_ptr<arbiter::Arbiter> a;
      if(!ajson.empty()) {
         if(pdal::FileUtils::isAbsolutePath(ajson)){
            std::cout << "using json file from pipeline" << std::endl;
            ajson = pdal::FileUtils::readFileIntoString(ajson);
         }
         else
            std::cout << "using json from pipeline" << std::endl;

         Json::Reader jsonReader;
         Json::Value aconf(Json::objectValue);
         jsonReader.parse(ajson, aconf);

         a = std::make_shared<arbiter::Arbiter>(aconf);
      }
      else {
         std::cout << "using config file from env" << std::endl;
         a = std::make_shared<arbiter::Arbiter>();
      }

      // get a handle to the file, which will be pulled from the source if not present
      auto h = a->getLocalHandle(file, cache);
      auto p = h->localPath();

      // print the file contents
      std::cout << pdal::FileUtils::readFileIntoString(p) << std::endl;

      PointViewSet viewSet;
      viewSet.insert(view);
      return viewSet;
   }
}
