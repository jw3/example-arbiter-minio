#pragma once

#include <pdal/Filter.hpp>

namespace pdal
{
    class PDAL_DLL arbiter_example : public Filter
    {
    public:
        std::string getName() const override;

    private:
        void addArgs(ProgramArgs&) override;
        void ready(PointTableRef) override;
        PointViewSet run(PointViewPtr) override;
        void done(PointTableRef) override;
    };
}
