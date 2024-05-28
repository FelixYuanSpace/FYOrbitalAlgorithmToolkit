#include "SGP4.h"
#include "orbitmodel_sgp4.h"
#include "oat_math_const.h"
#include <stdio.h>

namespace oat
{
    OrbitModel_SGP4::OrbitModel_SGP4(const char *cTleLine1st,
                                     const char *cTleLine2nd,
                                     double dBeginTime,
                                     double dEndTime,
                                     double dDeltaTime,
                                     char opsmode,
                                     char typerun,
                                     char typeinput)
    {
        float period = 0.0f;
        // sccanf period
        sscanf(cTleLine1st, "%*s %*s %*s %*s %*s %*s %*s %*s %f", &period);

        char longstr1[130], longstr2[130];
        strncpy(longstr1, cTleLine1st, 130);
        strncpy(longstr2, cTleLine2nd, 130);

        char str[2];
        double ro[3];
        double vo[3];

        double p, a, ecc, incl, node, argp, nu, m, arglat, truelon, lonper;
        double sec, jd, jdFrac, rad, tsince, startmfe, stopmfe, deltamin;
        int year;
        int mon;
        int day;
        int hr;
        int min;
        typedef char str3[4];
        // month string
        char monstr[13][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                              "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        //str3 monstr[13];
        char outname[64];
        elsetrec satrec;

        rad = 180.0 / PI;

        printf("%s\n", SGP4Version);

        m_opsmode = opsmode;
        m_typerun = typerun;
        m_typeinput = typeinput;
        

        gravconsttype whichconst = wgs84;

        satrec.classification = 'U';
        strncpy_s(satrec.intldesg, "          ", 11 * sizeof(char));
        satrec.ephtype = 0;
        satrec.elnum = 0;
        satrec.revnum = 0;
        
        SGP4Funcs::twoline2rv(longstr1, longstr2, m_typerun, m_typeinput, m_opsmode, whichconst,
                              startmfe, stopmfe, deltamin, satrec);

        tsince = (dBeginTime - satrec.jdsatepoch) * 1440.0; // JD Convert to minutes
        while (tsince <= (dEndTime - satrec.jdsatepoch) * 1440.0)
        {
            double r[3], v[3];
            SGP4Funcs::sgp4(satrec, tsince, r, v);
            // save result
            OrbitData data;
            data.jd = satrec.jdsatepoch + tsince / 1440.0;
            data.position = Vec3(r[0], r[1], r[2]);
            data.velocity = Vec3(v[0], v[1], v[2]);

            orbitData.push_back(data);
            //打印data
            //把JD转换成年月日时分秒
            double jd = data.jd;
            double jdFrac = jd - floor(jd);
            SGP4Funcs::invjday_SGP4(jd, jdFrac, year, mon, day, hr, min, sec);

            //打印data.jd
            //printf("jd: %f\n", jd);
            //打印年月日时分秒与相应的data数据
            //printf("%4d %2d %2d %2d %2d %8.6f %14.6f %14.6f %14.6f %14.6f %14.6f\n",
            //    				year, mon, day, hr, min, sec, data.position.x(), data.position.y(), data.position.z(), data.velocity.x(), data.velocity.y(), data.velocity.z());
            

            tsince += dDeltaTime * 1440.0; // add step
        }


        int ttt = 0;

        /*SGP4Funcs::sgp4(satrec, 0.0, ro, vo);

        double rteme[3];
        double vteme[3];
        double ateme[3];

        double rpef[3];
        double vpef[3];
        double apef[3];

        for (int i = 0; i < 3; i++)
        {
            rteme[i] = ro[i];
            vteme[i] = vo[i];
        }

        // calculate ateme
        double ateme_unit_vector[3];
        double magnitude_of_rteme = sqrt(pow(rteme[0], 2) + pow(rteme[1], 2) + pow(rteme[2], 2));
        for (int i = 0; i < 3; i++)
        {
            ateme_unit_vector[i] = -1 * rteme[i] / magnitude_of_rteme;
            ateme[i] = 9.81 * ateme_unit_vector[i];
        }

        jd = satrec.jdsatepoch;
        jdFrac = satrec.jdsatepochF;
        SGP4Funcs::invjday_SGP4(jd, jdFrac, year, mon, day, hr, min, sec);
        // delta UT1 = UT1 - UTC; on 9/12/2016 delta UT1 = -0.3811866 seconds
        // UTC = UT1 - delta UT1 => UT1 = UTC + delta UT1
        double day_jdut1 = (jd + jdFrac + (-0.3811899)) / 86400;
        double jdut1 = (day_jdut1 - 2451545) / 36525;*/




        /*// init SGP4
        double startmfe, stopmfe, deltamin;
        elsetrec satrec;
        gravconsttype whichconst;
        // Make sure TLE Data right
        SGP4Funcs::twoline2rv(longstr1, longstr2, 'i', 'e', 'a', whichconst, startmfe, stopmfe, deltamin, satrec);

        // pre calc track
        double tsince = (dBeginTime - satrec.jdsatepoch) * 1440.0; // JD Convert to minutes
        while (tsince <= (dEndTime - satrec.jdsatepoch) * 1440.0)
        {
            double r[3], v[3];
            SGP4Funcs::sgp4(satrec, tsince, r, v);
            // save result
            OrbitData data;
            data.jd = satrec.jdsatepoch + tsince / 1440.0;
            data.position = Vec3(r[0], r[1], r[2]);
            data.velocity = Vec3(v[0], v[1], v[2]);

            orbitData.push_back(data);

            tsince += dDeltaTime * 1440.0; // add step
        }*/
    }

    OrbitModel_SGP4::~OrbitModel_SGP4()
    {
    }

    Vec3 OrbitModel_SGP4::positionAtJD(double jd)
    {
        // check jd is in precalc range
        if (orbitData.empty() || jd < orbitData.front().jd || jd > orbitData.back().jd)
        {
            // if not in range return zero
            return Vec3();
        }

        // find data in orbitData and interpolation(if needed)
        for (size_t i = 0; i < orbitData.size() - 1; ++i)
        {
            if (jd >= orbitData[i].jd && jd <= orbitData[i + 1].jd)
            {
                // Linear interpolation
                double factor = (jd - orbitData[i].jd) / (orbitData[i + 1].jd - orbitData[i].jd);
                return Vec3(
                    orbitData[i].position.x() + factor * (orbitData[i + 1].position.x() - orbitData[i].position.x()),
                    orbitData[i].position.y() + factor * (orbitData[i + 1].position.y() - orbitData[i].position.y()),
                    orbitData[i].position.z() + factor * (orbitData[i + 1].position.z() - orbitData[i].position.z()));
            }
        }

        // if can't find point, return nearest point
        return orbitData.back().position;
    }

    Vec3 OrbitModel_SGP4::velocityAtJD(double jd)
    {
        // check jd is in precalc range
        if (orbitData.empty() || jd < orbitData.front().jd || jd > orbitData.back().jd)
        {
            // if not in range return zero
            return Vec3();
        }

        // find data in orbitData and interpolation(if needed)
        for (size_t i = 0; i < orbitData.size() - 1; ++i)
        {
            if (jd >= orbitData[i].jd && jd <= orbitData[i + 1].jd)
            {
                // Linear interpolation
                double factor = (jd - orbitData[i].jd) / (orbitData[i + 1].jd - orbitData[i].jd);
                return Vec3(
                    orbitData[i].velocity.x() + factor * (orbitData[i + 1].velocity.x() - orbitData[i].velocity.x()),
                    orbitData[i].velocity.y() + factor * (orbitData[i + 1].velocity.y() - orbitData[i].velocity.y()),
                    orbitData[i].velocity.z() + factor * (orbitData[i + 1].velocity.z() - orbitData[i].velocity.z()));
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