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
#include "orbitmodel.h"

namespace oat
{
    class OrbitModel_SGP4 : public OrbitModel
    {
    public:
        /// @brief Init OrbitModel_SGP4
        /// @param cTleLine1st The first row of TLE data
        /// @param cTleLine2nd The Sencond row of TLE data
        /// @param dBeginTIme calc data start time
        /// @param dEndTime calc data end time
        /// @param dDeltaTime delta time
        OrbitModel_SGP4(const char *cTleLine1st, const char *cTleLine2nd, double dBeginTIme, double dEndTime, double dDeltaTime);
        ~OrbitModel_SGP4();
        
        /**
		* @brief Calculate the world coordinate position of entity at current JD time.
        *        The standard unit of Vec3 depends on the situation, and the celestial body is in kilometers <TODO To be determined>
        * @param jd [in] time , Time is Julian Day (in days <TODO To be determined > )
        * @return position at current JD time;
        */
        Vec3 positionAtJD(double jd);
        /**
		* @brief Calculate the velocity vector of entity at current JD time.
        *        <TODO To be determined unit>
        * @param jd [in] time , Time is Julian Day (in days <TODO To be determined > )
        * @return velocity at current JD time;
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
        // elsetrec: A structure that stores satellite orbital elements and other necessary data 
        // for SGP4 orbit prediction calculations. This includes parameters derived from 
        // Two-Line Element Set (TLE) data, such as inclination, eccentricity, right ascension 
        // of the ascending node, and other data like mean motion and epoch time.
        elsetrec satrec;

        // gravconsttype: An enumeration type representing the gravitational constant model 
        // to be used in SGP4 orbit prediction. Different models correspond to varying Earth 
        // gravitational field parameters, affecting satellite orbit computations. Common models 
        // include WGS-72, WGS-84, etc., each tailored to specific Earth models and satellite orbit calculations.
        gravconsttype whichconst;
    };
}
