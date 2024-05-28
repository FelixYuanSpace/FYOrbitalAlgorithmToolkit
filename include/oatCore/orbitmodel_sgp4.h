/*
 * @file orbitmodel_sgp4.h
 *
 * Created on Sat Jan 20 2024
 * Created by Felix Yuan
 * Email: FelixYuan.space@gmail.com
 *
 *  Copyright (c) 2024 Felix Yuan
 *
 * This program is free software: you can redistribute it and/or modify it under the terms of the 
 * GNU Lesser General Public License as published by the Free Software Foundation, either version 3 
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without 
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along with this program. 
 * If not, see <https://www.gnu.org/licenses/>.
 *
 * This part is Orbit Model with SGP4
 *  
 */

#pragma once
//增加导出宏
#ifdef oatCore_EXPORTS
#define OATCORE_API __declspec(dllexport)
#else
#define OATCORE_API __declspec(dllimport)
#endif
#include "orbitmodel.h"
namespace oat
{
    class OATCORE_API OrbitModel_SGP4 : public OrbitModel
    {
    public:
        /// @brief Init OrbitModel_SGP4
        /// @param cTleLine1st The first row of TLE data
        /// @param cTleLine2nd The Sencond row of TLE data
        /// @param dBeginTIme calc data start time JD time 此值位儒略日
        /// @param dEndTime calc data end time JD time 此值位儒略日
        /// @param dDeltaTime delta time 此值x1440为分钟
        OrbitModel_SGP4(const char *cTleLine1st, const char *cTleLine2nd, double dBeginTIme, double dEndTime, 
            double dDeltaTime, char opsmode = 'a', char typerun = 'c', char typeinput = 'e');
        ~OrbitModel_SGP4();
        
        /**
		* @brief Calculate the world coordinate position of entity at current JD time.
        *        The standard unit of Vec3 depends on the situation, and the celestial body is in kilometers <TODO To be determined>
        * @param jd [in] time , Time is Julian Day (in days <TODO To be determined > )
        * @return position at current JD time; 三个分量的单位位千米
        * 位置数据表示卫星相对于地心的三维坐标。例如，6054.819833 -2700.602360 1496.441942 表示在三个空间坐标轴上（通常是地心惯性坐标系，即ECI），
        * 卫星位于地心东方6054.819833千米，北方-2700.602360千米，垂直方向1496.441942千米的位置。
        */
        Vec3 positionAtJD(double jd);
        /**
		* @brief Calculate the velocity vector of entity at current JD time.
        *        <TODO To be determined unit>
        * @param jd [in] time , Time is Julian Day (in days <TODO To be determined > )
        * @return velocity at current JD time; 这个三分量的单位为千米/每秒
        * 速度数据表示卫星在这三个坐标轴上的瞬时速度。例如，3.181021 3.915930 -5.765891 表示卫星在地心惯性坐标系中，
        * 沿东方轴的速度为3.181021千米/秒，沿北方轴的速度为3.915930千米/秒，垂直向下方向的速度为-5.765891千米/秒。
        */
        Vec3 velocityAtJD(double jd);
        /**
		* @brief Calculate the quaternion of entity at current JD time.
        *        <TODO To be determined unit>
        * @param jd [in] time , Time is Julian Day (in days <TODO To be determined > )
        * @return quatertion at current JD time;
        */
        Quat quatAtJD(double jd);
    private:
        // a or i 
        // 操作模式
        // a : best understanding of how afspc code works
        // a : 这代表使用 AFSPC（Air Force Space Command，美国空军空间司令部）的代码的最佳理解方式。这是默认的操作模式，用于更准确地模拟 AFSPC 的行为。
        // i : improved sgp4 resulting in smoother behavior
        // i : 这代表改进的 SGP4 模型，旨在提供更平滑的轨道计算结果。这种模式经过优化，能在一些情况下提供更精确的计算。
        char m_opsmode;
        // c or v or m
        // c : compare 1 year of full satcat data
        // c : 比较一年的完整 satcat 数据,
        //     该模式用于将当前数据与过去一年的完整卫星目录数据进行比较，可能用于验证轨道计算的准确性。
        // v : verification run, requires modified elm file with  start, stop, and delta times 
        // v : 验证运行，需要修改的 elm 文件，其中包含开始、结束和时间间隔。
        //     该模式用于验证轨道计算的准确性，需要一个特定格式的输入文件。
        // m : manual operation- either mfe, epoch, or day of yr
        // m : 手动操作，可以使用三种时间格式之一：mfe（minutes from epoch，距历元的分钟数）、epoch（历元时间）、或 day of year（年内天数）。
        //     该模式允许用户手动输入时间参数，以更灵活地控制轨道计算。
        char m_typerun;

        // m : input start stop mfe
        //     输入开始和结束时间，以 mfe（距历元的分钟数，minutes from epoch）格式。
        //     该模式下，用户需要输入的是从某个参考时间（历元）开始计算的分钟数，表示相对时间。
        // e : input start stop ymd hms
        //     输入开始和结束时间，以 ymd hms（年-月-日 时:分:秒）格式。
        //     该模式下，用户需要输入的是具体的年月日和时分秒，表示绝对时间。
        // d : input start stop yr dayofyr
        //     输入开始和结束时间，以 yr dayofyr（年-年内天数）格式。
        //     该模式下，用户需要输入的是年份和该年中的某一天，表示绝对时间，但以年内天数为基准。
        char m_typeinput;

        //gravconsttype  whichconst;

    };
}
