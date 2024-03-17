#include "coord_def.h"

namespace oatCoord {
    GeoCoord::GeoCoord(double x, double y, double z)
    {
        this->Lontitude = x;
        this->Latitude = y;
        this->Altitude = z;
    }
} // namespace oatCoord