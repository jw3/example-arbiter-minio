#include "arbiter_writer.hpp"
#include "BuildInfo.hpp"

#include <arbiter.hpp>
#include <arbiter_util.hpp>
#include <pdal/util/FileUtils.hpp>

using namespace arbiter;

namespace pdal
{
   static PluginInfo const s_info{
         "filters.arbiter_writer",
         BuildInfo::PluginDescription,
         BuildInfo::PluginURL
   };

   CREATE_SHARED_STAGE(arbiter_writer, s_info)

   std::string arbiter_writer::getName() const {
      return s_info.name;
   }

   void arbiter_writer::addArgs(ProgramArgs& args) {
      args.add("file", "The file", file);
      args.add("arbiter", "The arbiter config", ajson, "");
   }

   PointViewSet arbiter_writer::run(PointViewPtr view) {
      std::cout << "filters.arbiter_writer::run" << std::endl;

      std::shared_ptr<arbiter::Arbiter> a;
      if(!ajson.empty()) {
         if(pdal::FileUtils::isAbsolutePath(ajson)) {
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

      /**
       * calculate the local file for writing and translate that to the s3 path
       * https://github.com/connormanning/entwine/blob/c880482e12119843ad2af76ed24135c4c1f2097e/entwine/io/laszip.cpp#L30-L35
       */

      auto out = a->getEndpoint(pdal::FileUtils::getDirectory(file));
      auto tmp = a->getEndpoint(arbiter::fs::getTempPath());

      const bool local(out.isLocal());
      const std::string localDir(local ? out.prefixedRoot() : pdal::FileUtils::getDirectory(file));
      const std::string localFile(pdal::FileUtils::getFilename(file));
      const std::string filename = localDir + localFile;

      std::stringstream ss;
      ss << "current time is " << std::chrono::system_clock::now().time_since_epoch().count() << std::endl;
      tmp.put(localFile, ss.str());
      std::cout << "wrote to file: " << ss.str();

      if(!local) {
         std::cout << "uploading file to " << file << std::endl << std::endl;
         ensurePut(out, localFile, tmp.getBinary(localFile));
         arbiter::fs::remove(tmp.prefixedRoot() + localFile);
      }
      else {
         std::cout << "wrote local file: " << file << std::endl << std::endl;
      }

      PointViewSet viewSet;
      viewSet.insert(view);
      return viewSet;
   }
}
