/*
 * @file coord_def.h
 *
 * Created on Tue Feb 13 2024
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

namespace oatCoord {

    /**
     * Represents a geographical coordinate using the WGS-84 datum.
     * This structure stores latitude and longitude values,
     * which are essential for specifying locations on the Earth's surface.
     * The WGS-84 (World Geodetic System 1984) is the reference coordinate system
     * used by the Global Positioning System (GPS) and is widely adopted for
     * global mapping and navigation purposes.
     *
     * Latitude is measured in degrees north or south of the equator,
     * ranging from -90° to 90°. Longitude is measured in degrees east or west
     * of the Prime Meridian, ranging from -180° to 180°.
     */
    struct GeoCoord
	{
        /// @brief Lontitude | unit: deg | range [-180, 180]
		double Lontitude; 
        /// @brief Latitude | unit: deg | range [-90, 90]
		double Latitude;
		/// @brief Altitude | unit: meter
		double Altitude; 
		GeoCoord(double x = 0, double y = 0, double z = 0)
		{
			this->Lontitude = x;
			this->Latitude = y;
			this->Altitude = z;
		}
	};

    /**
     * Represents a point in the Earth-Centered, Earth-Fixed (ECEF) coordinate system.
     * This system uses a 3D Cartesian coordinate system to describe positions on the Earth's surface,
     * with the origin at the center of the Earth. The ECEF coordinate system is fixed to the Earth,
     * with the X, Y, and Z axes defined as follows:
     *
     * - X axis points towards the intersection of the Equator and the Prime Meridian (0° longitude),
     *   with its positive direction extending from the Earth's center towards this point.
     * - Y axis follows the right-hand rule, orthogonal to the X and Z axes, with its positive direction
     *   pointing towards 90° east longitude on the Equator.
     * - Z axis points towards the North Pole, orthogonal to the plane of the Equator,
     *   with its positive direction extending from the Earth's center towards the North Pole.
     */
    struct ECEFCoord
    {
        /// @brief X axis points to the Prime Meridian at the Equator | unit: meter
        double x; 
        /// @brief Y axis complies with the right-hand rule | unit: meter
		double y; 
		/// @brief Z axis points to the North Pole | unit: meter
		double z; 

        ECEFCoord(double x = 0, double y = 0, double z = 0)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

        /// @brief operator+
        /// @param other 
        /// @return 
        ECEFCoord operator+(const ECEFCoord& other) const
		{
			ECEFCoord result(*this);
			result.x = result.x + other.x;
			result.y = result.y + other.y;
			result.z = result.z + other.z;

			return result;
		}

        /// @brief operator-
        /// @param other 
        /// @return 
        ECEFCoord operator-(const ECEFCoord& other) const
		{
			ECEFCoord result(*this);
			result.x = result.x - other.x;
			result.y = result.y - other.y;
			result.z = result.z - other.z;

			return result;
		}
    };

    /**
     * Represents a point in a local North-East-Up (NEU) coordinate system, 
     * which is commonly used for representing positions relative to a specific reference point on the Earth's surface.
     * This system is oriented with respect to the Earth's surface, with the axes defined as follows:
     *
     * - X axis points towards the true north direction from the reference point, parallel to the Earth's surface.
     * - Y axis points towards the zenith, perpendicular to the Earth's surface at the reference point, indicating height or depth.
     * - Z axis points towards the east, orthogonal to both the X and Y axes, parallel to the Earth's surface.
     *
     * This coordinate system is particularly useful for applications involving local area mapping, aerial and ground navigation, 
     * and in any context where it's necessary to express positions in a localized three-dimensional space relative to the Earth's surface.
     */

    struct ENUCoord
    {
        /// @brief X axis component, pointing northward | unit: meter
        double x; 
        /// @brief Y axis component, pointing upward to the zenith | unit: meter
        double y; 
        /// @brief Z axis component, pointing eastward | unit: meter
        double z; 

        ENUCoord(double x = 0, double y = 0, double z = 0)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
    };
    
    
}