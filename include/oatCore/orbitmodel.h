/*
 * @file orbit_model.h
 *
 * Created on Sat Jan 06 2024
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
 */
#include "oat_geometry_types.h"
#include <map>
#include <vector>

namespace oat
{
    struct OrbitData {
        // julian date
        double jd; 
        // position 
        Vec3 position; 
        // velocity
        Vec3 velocity; 
    };
    class OrbitModel
    {
    public:
        OrbitModel();
        virtual ~OrbitModel();

        /**
		* @brief Calculate the world coordinate position of entity at current JD time.
        *        The standard unit of Vec3 depends on the situation, and the celestial body is in kilometers <TODO To be determined>
        * @param jd [in] time , Time is Julian Day (in days <TODO To be determined > )
        * @return position at current JD time;
        */
        virtual Vec3 positionAtJD(double jd);

        /**
		* @brief Calculate the velocity vector of entity at current JD time.
        *        <TODO To be determined unit>
        * @param jd [in] time , Time is Julian Day (in days <TODO To be determined > )
        * @return velocity at current JD time;
        */
        virtual Vec3 velocityAtJD(double jd);

        /**
		* @brief Calculate the quaternion of entity at current JD time.
        *        <TODO To be determined unit>
        * @param jd [in] time , Time is Julian Day (in days <TODO To be determined > )
        * @return quatertion at current JD time;
        */
        virtual Quat quatAtJD(double jd);

        //Get Period
        virtual double getPeriod() const {return m_period;};
        //Get enclosing sphere radius
        virtual double getBoundingRadius() const {return m_boundingRadius;};
        
        /// @brief Orbital interpolation sample, Calculate a fixed number of equal point sets in a period
        /// @param curJD current JD (Angle interpolation, time invalid)
        /// @param ptNum interpolation number
        /// @param mapTime2Position interpolation map
        virtual void sample(double curJD, int ptNum, std::map<double, Vec3>& mapTime2Position);
    protected:
        //orbit period
        double m_period;
        //Orbital enclosing sphere radius
        double m_boundingRadius;
        //calc data start time
        double m_beginTime;
        //calc data end time;
        double m_endTime;
        //orbit data cache;
        std::vector<OrbitData> orbitData;

    };

}