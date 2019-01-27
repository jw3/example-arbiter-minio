#pragma once

#include <pdal/Filter.hpp>

namespace pdal
{
   class PDAL_DLL arbiter_writer : public Filter
   {
   public:
      std::string getName() const override;

      void addArgs(ProgramArgs&) override;
      PointViewSet run(PointViewPtr) override;

      std::string file;
      std::string ajson;
   };
}
