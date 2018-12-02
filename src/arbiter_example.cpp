#include "arbiter_example.hpp"
#include "BuildInfo.hpp"


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
      std::cout << BuildInfo::PDALStageName << "::addArgs" << std::endl;
   }

   void arbiter_example::ready(PointTableRef table) {
      std::cout << BuildInfo::PDALStageName << "::ready" << std::endl;
   }

   PointViewSet arbiter_example::run(PointViewPtr view) {
      std::cout << BuildInfo::PDALStageName << "::run" << std::endl;

      PointViewSet viewSet;
      viewSet.insert(view);
      return viewSet;
   }

   void arbiter_example::done(PointTableRef) {
      std::cout << BuildInfo::PDALStageName << "::done" << std::endl;
   }
}
