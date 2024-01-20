#include "SGP4.h"
#include "orbitmodel_sgp4.h"
#include <stdio.h>

namespace oat{
    OrbitModel_SGP4::OrbitModel_SGP4(const char *cTleLine1st, 
        const char *cTleLine2nd, 
        double dBeginTime, 
        double dEndTime, 
        double dDeltaTime)
    {
        float period = 0.0f;
        // sccanf period
        sscanf(cTleLine1st, "%*s %*s %*s %*s %*s %*s %*s %*s %f", &period);


        char longstr1[130], longstr2[130];
        strncpy(longstr1, cTleLine1st, 130);
        strncpy(longstr2, cTleLine2nd, 130);
        // init SGP4
        double startmfe, stopmfe, deltamin;
        // Make sure TLE Data right
        SGP4Funcs::twoline2rv(longstr1, longstr2, 'i', 'e', 'a', whichconst, startmfe, stopmfe, deltamin, satrec);

        // pre calc track
        double tsince = (dBeginTime - satrec.jdsatepoch) * 1440.0; // JD Convert to minutes
        while (tsince <= (dEndTime - satrec.jdsatepoch) * 1440.0) {
            double r[3], v[3];
            SGP4Funcs::sgp4(satrec, tsince, r, v);
            // save result
            OrbitData data;
            data.jd = satrec.jdsatepoch + tsince / 1440.0;
            data.position = Vec3(r[0], r[1], r[2]);
            data.velocity = Vec3(v[0], v[1], v[2]);

            orbitData.push_back(data);

            tsince += dDeltaTime * 1440.0; // add step
        }
    }

    OrbitModel_SGP4::~OrbitModel_SGP4()
    {

    }

    Vec3 OrbitModel_SGP4::positionAtJD(double jd)
    {
        return Vec3();
    }

    Vec3 OrbitModel_SGP4::velocityAtJD(double jd)
    {
        return Vec3();
    }

    Quat OrbitModel_SGP4::quatAtJD(double jd)
    {
        return Quat();
    }
}