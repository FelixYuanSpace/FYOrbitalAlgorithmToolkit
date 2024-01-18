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

namespace oat
{

    class OrbitModel
    {
    public:
        OrbitModel();
        virtual ~OrbitModel();
        /**
		* @brief Calculate the world coordinate position of entity based on time.
        *        The standard unit of Vec3 depends on the situation, and the celestial body is in kilometers <TODO To be determined>
        * @param jd [in] time , Time is Julian Day (in days <TODO To be determined > )
        * 
        */
        virtual Vec3 positionAtJD(double jd);


    };

}