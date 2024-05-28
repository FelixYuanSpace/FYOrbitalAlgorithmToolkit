#ifndef OAT_PHYSICS_CONST_H
#define OAT_PHYSICS_CONST_H


#define LY_UNIT      1
#define METER_UNIT   2
#define AU_UNIT      3

#define SIM_USE_UNIT  METER_UNIT
#include <cmath>

namespace oat {
    #if (SIM_USE_UNIT == LY_UNIT)
    const double phy_locToSimUnit = 1.0;
    const double phy_simToLocUnit = 1.0;
    const double phy_meterToSimUnit = 1.0570008340246154637094605244851e-16;
    const double phy_kmToSimUnit = 1.0570008340246154637094605244851e-13;
    #endif

    #if (SIM_USE_UNIT == METER_UNIT)
    //ly is 9460730472580.8km
    //ly convert to sim unit need plus g_locToSimUnit
    const double phy_locToSimUnit = 9460730472580.8e3;
    //sim convert ly
    const double phy_simToLocUnit = 1.0570008340246154637094605244851e-16;
    //meter convert to sim
    const double phy_meterToSimUnit = 1.0;
    //km convert to sim plus phy_kmToSimUnit
    const double phy_kmToSimUnit = 1000.0;
    #endif

    //Calendar to Julian Date
    double Cal2jd(int year, int month, int day, int hour, int minute, int second)
    {
        int a = (14 - month) / 12;
        int y = year + 4800 - a;
        int m = month + 12 * a - 3;
        double jd = day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
        jd += (hour - 12) / 24.0 + minute / 1440.0 + second / 86400.0;
        return jd;
    }

    //julian date to calendar
    void Jd2Cal(double jd, int& year, int& month, int& day, int& hour, int& minute, double& second)
    {
        // convert JD to date
        const int JGREG = 15 + 31 * (10 + 12 * 1582); // 格里高利历开始日期
        int jalpha, ja, jb, jc, jd1, je;

        // JD转为整数
        double jdf = floor(jd + 0.5);
        double dayfrac = jd + 0.5 - jdf; // 天数的小数部分
        int isecond;

        // 根据儒略日调整日期
        if (jdf >= JGREG)
        {
            jalpha = int((int(jdf - 1867216) - 0.25) / 36524.25);
            ja = int(jdf + 1 + jalpha - int(0.25 * jalpha));
        }
        else
        {
            ja = int(jdf);
        }

        // 计算年月日
        jb = ja + 1524;
        jc = int(6680.0 + ((jb - 2439870) - 122.1) / 365.25);
        jd1 = int(jc * 365.25);
        je = int((jb - jd1) / 30.6001);

        day = jb - jd1 - int(30.6001 * je);
        month = je - 1;
        if (month > 12) month -= 12;
        year = jc - 4715;
        if (month > 2) year--;
        if (year <= 0) year--;

        // 计算时分秒
        dayfrac *= 24.0;  // 转换为小时
        hour = int(dayfrac);
        dayfrac -= hour;
        dayfrac *= 60.0;  // 转换为分钟
        minute = int(dayfrac);
        dayfrac -= minute;
        dayfrac *= 60.0;  // 转换为秒
        second = dayfrac;

        // 调整秒的精度
        isecond = int(second * 1e6);
        second = isecond * 1e-6;
    }

}


#endif