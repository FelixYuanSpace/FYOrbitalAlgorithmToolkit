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

    Vec3 OrbitModel_SGP4::positionAtJD(double jd) {
        // check jd is in precalc range
        if (orbitData.empty() || jd < orbitData.front().jd || jd > orbitData.back().jd) {
            // if not in range return zero
            return Vec3(); 
        }

        // find data in orbitData and interpolation(if needed) 
        for (size_t i = 0; i < orbitData.size() - 1; ++i) {
            if (jd >= orbitData[i].jd && jd <= orbitData[i + 1].jd) {
                // Linear interpolation 
                double factor = (jd - orbitData[i].jd) / (orbitData[i + 1].jd - orbitData[i].jd);
                return Vec3(
                    orbitData[i].position.x() + factor * (orbitData[i + 1].position.x() - orbitData[i].position.x()),
                    orbitData[i].position.y() + factor * (orbitData[i + 1].position.y() - orbitData[i].position.y()),
                    orbitData[i].position.z() + factor * (orbitData[i + 1].position.z() - orbitData[i].position.z())
                );
            }
        }

        // if can't find point, return nearest point
        return orbitData.back().position;
    }


    Vec3 OrbitModel_SGP4::velocityAtJD(double jd)
    {
        // check jd is in precalc range
        if (orbitData.empty() || jd < orbitData.front().jd || jd > orbitData.back().jd) {
            // if not in range return zero
            return Vec3(); 
        }

        // find data in orbitData and interpolation(if needed) 
        for (size_t i = 0; i < orbitData.size() - 1; ++i) {
            if (jd >= orbitData[i].jd && jd <= orbitData[i + 1].jd) {
                // Linear interpolation 
                double factor = (jd - orbitData[i].jd) / (orbitData[i + 1].jd - orbitData[i].jd);
                return Vec3(
                    orbitData[i].velocity.x() + factor * (orbitData[i + 1].velocity.x() - orbitData[i].velocity.x()),
                    orbitData[i].velocity.y() + factor * (orbitData[i + 1].velocity.y() - orbitData[i].velocity.y()),
                    orbitData[i].velocity.z() + factor * (orbitData[i + 1].velocity.z() - orbitData[i].velocity.z())
                );
            }
        }

        // 
        return orbitData.back().velocity;
    }

    Quat OrbitModel_SGP4::quatAtJD(double jd)
    {
        return Quat();
    }
}