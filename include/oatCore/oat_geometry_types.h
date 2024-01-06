/*
 * @file oat_geometry_types.h
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
 * This file contains modifications based on the OpenSceneGraph (OSG) project.
 * Original OSG source can be found at: https://github.com/openscenegraph/OpenSceneGraph
 * Modifications are licensed under the GNU Lesser General Public License (LGPL).
 * OSG is also licensed under the LGPL.
 *
 */

#include <cmath>

namespace oat {

    class Vec3{

    public:
#ifdef USE_GEOMETRY_FLOAT_TYPE
        typedef float value_type;
#else
        typedef double value_type;
#endif

        value_type _v[3];

        Vec3() { _v[0] = 0.0; _v[1] = 0.0; _v[2] = 0.0; }

        Vec3(value_type x, value_type y, value_type z) { _v[0] = x; _v[1] = y; _v[2] = z; }

        inline bool operator == (const Vec3& v) const { return _v[0] == v._v[0] && _v[1] == v._v[1] && _v[2] == v._v[2]; }

        inline bool operator != (const Vec3& v) const { return _v[0] != v._v[0] || _v[1] != v._v[1] || _v[2] != v._v[2]; }

        inline bool operator <  (const Vec3& v) const
        {
            if (_v[0] < v._v[0]) return true;
            else if (_v[0] > v._v[0]) return false;
            else if (_v[1] < v._v[1]) return true;
            else if (_v[1] > v._v[1]) return false;
            else return (_v[2] < v._v[2]);
        }

        inline value_type* ptr() { return _v; }
        inline const value_type* ptr() const { return _v; }

        inline void set(value_type x, value_type y, value_type z)
        {
            _v[0] = x; _v[1] = y; _v[2] = z;
        }

        inline void set(const Vec3& rhs)
        {
            _v[0] = rhs._v[0]; _v[1] = rhs._v[1]; _v[2] = rhs._v[2];
        }

        inline value_type& operator [] (int i) { return _v[i]; }
        inline value_type operator [] (int i) const { return _v[i]; }

        inline value_type& x() { return _v[0]; }
        inline value_type& y() { return _v[1]; }
        inline value_type& z() { return _v[2]; }

        inline value_type x() const { return _v[0]; }
        inline value_type y() const { return _v[1]; }
        inline value_type z() const { return _v[2]; }

        /** Returns true if all components have values that are not NaN. */
        inline bool valid() const { return !isNaN(); }
        /** Returns true if at least one component has value NaN. */
        inline bool isNaN() const { return isnan(_v[0]) || isnan(_v[1]) || isnan(_v[2]); }

        /** Dot product. right-hand side */
        inline value_type operator * (const Vec3& rhs) const
        {
            return _v[0] * rhs._v[0] + _v[1] * rhs._v[1] + _v[2] * rhs._v[2];
        }

        /** Cross product. right-hand side*/
        inline const Vec3 operator ^ (const Vec3& rhs) const
        {
            return Vec3(_v[1] * rhs._v[2] - _v[2] * rhs._v[1],
                _v[2] * rhs._v[0] - _v[0] * rhs._v[2],
                _v[0] * rhs._v[1] - _v[1] * rhs._v[0]);
        }

        /** Multiply by scalar. right-hand side*/
        inline const Vec3 operator * (value_type rhs) const
        {
            return Vec3(_v[0] * rhs, _v[1] * rhs, _v[2] * rhs);
        }

        /** Unary multiply by scalar. right-hand side*/
        inline Vec3& operator *= (value_type rhs)
        {
            _v[0] *= rhs;
            _v[1] *= rhs;
            _v[2] *= rhs;
            return *this;
        }

        /** Divide by scalar. right-hand side*/
        inline const Vec3 operator / (value_type rhs) const
        {
            return Vec3(_v[0] / rhs, _v[1] / rhs, _v[2] / rhs);
        }

        /** Unary divide by scalar. right-hand side*/
        inline Vec3& operator /= (value_type rhs)
        {
            _v[0] /= rhs;
            _v[1] /= rhs;
            _v[2] /= rhs;
            return *this;
        }

        /** Binary vector add. right-hand side*/
        inline const Vec3 operator + (const Vec3& rhs) const
        {
            return Vec3(_v[0] + rhs._v[0], _v[1] + rhs._v[1], _v[2] + rhs._v[2]);
        }

        /** Unary vector add. Slightly more efficient because no temporary
         * intermediate object.
         * right-hand side
        */
        inline Vec3& operator += (const Vec3& rhs)
        {
            _v[0] += rhs._v[0];
            _v[1] += rhs._v[1];
            _v[2] += rhs._v[2];
            return *this;
        }

        /** Binary vector subtract. right-hand side*/
        inline const Vec3 operator - (const Vec3& rhs) const
        {
            return Vec3(_v[0] - rhs._v[0], _v[1] - rhs._v[1], _v[2] - rhs._v[2]);
        }

        /** Unary vector subtract. right-hand side*/
        inline Vec3& operator -= (const Vec3& rhs)
        {
            _v[0] -= rhs._v[0];
            _v[1] -= rhs._v[1];
            _v[2] -= rhs._v[2];
            return *this;
        }

        /** Negation operator. Returns the negative of the Vec3. */
        inline const Vec3 operator - () const
        {
            return Vec3(-_v[0], -_v[1], -_v[2]);
        }

        /** Length of the vector = sqrt( vec . vec ) */
        inline value_type length() const
        {
            return sqrt(_v[0] * _v[0] + _v[1] * _v[1] + _v[2] * _v[2]);
        }

        /** Length squared of the vector = vec . vec */
        inline value_type length2() const
        {
            return _v[0] * _v[0] + _v[1] * _v[1] + _v[2] * _v[2];
        }

        /** Normalize the vector so that it has length unity.
         * Returns the previous length of the vector.
         * If the vector is zero length, it is left unchanged and zero is returned.
        */
        inline value_type normalize()
        {
            value_type norm = Vec3::length();
            if (norm > 0.0)
            {
                value_type inv = 1.0 / norm;
                _v[0] *= inv;
                _v[1] *= inv;
                _v[2] *= inv;
            }
            return(norm);
        }
    };

    class Vec4
    {
    public:

#ifdef USE_GEOMETRY_FLOAT_TYPE
        typedef float value_type;
#else
        typedef double value_type;
#endif

        enum { num_components = 4 };

        value_type _v[4];

        /** Constructor that sets all components of the vector to zero */
        Vec4() { _v[0] = 0.0; _v[1] = 0.0; _v[2] = 0.0; _v[3] = 0.0; }

        Vec4(value_type x, value_type y, value_type z, value_type w)
        {
            _v[0] = x;
            _v[1] = y;
            _v[2] = z;
            _v[3] = w;
        }

        Vec4(const Vec3& v3, value_type w)
        {
            _v[0] = v3[0];
            _v[1] = v3[1];
            _v[2] = v3[2];
            _v[3] = w;
        }


        inline bool operator == (const Vec4& v) const { return _v[0] == v._v[0] && _v[1] == v._v[1] && _v[2] == v._v[2] && _v[3] == v._v[3]; }

        inline bool operator != (const Vec4& v) const { return _v[0] != v._v[0] || _v[1] != v._v[1] || _v[2] != v._v[2] || _v[3] != v._v[3]; }

        inline bool operator <  (const Vec4& v) const
        {
            if (_v[0] < v._v[0]) return true;
            else if (_v[0] > v._v[0]) return false;
            else if (_v[1] < v._v[1]) return true;
            else if (_v[1] > v._v[1]) return false;
            else if (_v[2] < v._v[2]) return true;
            else if (_v[2] > v._v[2]) return false;
            else return (_v[3] < v._v[3]);
        }

        inline value_type* ptr() { return _v; }
        inline const value_type* ptr() const { return _v; }

        inline void set(value_type x, value_type y, value_type z, value_type w)
        {
            _v[0] = x; _v[1] = y; _v[2] = z; _v[3] = w;
        }

        inline value_type& operator [] (unsigned int i) { return _v[i]; }
        inline value_type  operator [] (unsigned int i) const { return _v[i]; }

        inline value_type& x() { return _v[0]; }
        inline value_type& y() { return _v[1]; }
        inline value_type& z() { return _v[2]; }
        inline value_type& w() { return _v[3]; }

        inline value_type x() const { return _v[0]; }
        inline value_type y() const { return _v[1]; }
        inline value_type z() const { return _v[2]; }
        inline value_type w() const { return _v[3]; }

        /** Returns true if all components have values that are not NaN. */
        inline bool valid() const { return !isNaN(); }
        /** Returns true if at least one component has value NaN. */
        inline bool isNaN() const { return isnan(_v[0]) || isnan(_v[1]) || isnan(_v[2]) || isnan(_v[3]); }

        /** Dot product. */
        inline value_type operator * (const Vec4& rhs) const
        {
            return _v[0] * rhs._v[0] +
                _v[1] * rhs._v[1] +
                _v[2] * rhs._v[2] +
                _v[3] * rhs._v[3];
        }

        /** Multiply by scalar. */
        inline Vec4 operator * (value_type rhs) const
        {
            return Vec4(_v[0] * rhs, _v[1] * rhs, _v[2] * rhs, _v[3] * rhs);
        }

        /** Unary multiply by scalar. */
        inline Vec4& operator *= (value_type rhs)
        {
            _v[0] *= rhs;
            _v[1] *= rhs;
            _v[2] *= rhs;
            _v[3] *= rhs;
            return *this;
        }

        /** Divide by scalar. */
        inline Vec4 operator / (value_type rhs) const
        {
            return Vec4(_v[0] / rhs, _v[1] / rhs, _v[2] / rhs, _v[3] / rhs);
        }

        /** Unary divide by scalar. */
        inline Vec4& operator /= (value_type rhs)
        {
            _v[0] /= rhs;
            _v[1] /= rhs;
            _v[2] /= rhs;
            _v[3] /= rhs;
            return *this;
        }

        /** Binary vector add. */
        inline Vec4 operator + (const Vec4& rhs) const
        {
            return Vec4(_v[0] + rhs._v[0], _v[1] + rhs._v[1],
                _v[2] + rhs._v[2], _v[3] + rhs._v[3]);
        }

        /** Unary vector add. Slightly more efficient because no temporary
         * intermediate object.
        */
        inline Vec4& operator += (const Vec4& rhs)
        {
            _v[0] += rhs._v[0];
            _v[1] += rhs._v[1];
            _v[2] += rhs._v[2];
            _v[3] += rhs._v[3];
            return *this;
        }

        /** Binary vector subtract. */
        inline Vec4 operator - (const Vec4& rhs) const
        {
            return Vec4(_v[0] - rhs._v[0], _v[1] - rhs._v[1],
                _v[2] - rhs._v[2], _v[3] - rhs._v[3]);
        }

        /** Unary vector subtract. */
        inline Vec4& operator -= (const Vec4& rhs)
        {
            _v[0] -= rhs._v[0];
            _v[1] -= rhs._v[1];
            _v[2] -= rhs._v[2];
            _v[3] -= rhs._v[3];
            return *this;
        }

        /** Negation operator. Returns the negative of the Vec4. */
        inline const Vec4 operator - () const
        {
            return Vec4(-_v[0], -_v[1], -_v[2], -_v[3]);
        }

        /** Length of the vector = sqrt( vec . vec ) */
        inline value_type length() const
        {
            return sqrt(_v[0] * _v[0] + _v[1] * _v[1] + _v[2] * _v[2] + _v[3] * _v[3]);
        }

        /** Length squared of the vector = vec . vec */
        inline value_type length2() const
        {
            return _v[0] * _v[0] + _v[1] * _v[1] + _v[2] * _v[2] + _v[3] * _v[3];
        }

        /** Normalize the vector so that it has length unity.
         * Returns the previous length of the vector.
        */
        inline value_type normalize()
        {
            value_type norm = Vec4::length();
            if (norm > 0.0f)
            {
                value_type inv = 1.0 / norm;
                _v[0] *= inv;
                _v[1] *= inv;
                _v[2] *= inv;
                _v[3] *= inv;
            }
            return(norm);
        }

    };    // end of class Vec4
}