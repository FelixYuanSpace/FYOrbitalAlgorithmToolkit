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
using namespace std;
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

    class Quat;
    class Matrix
    {
    public:

        typedef double value_type;
        typedef float other_value_type;

        inline Matrix() { makeIdentity(); }
        inline Matrix(const Matrix& mat) { set(mat.ptr()); }
        inline explicit Matrix(float const* const ptr) { set(ptr); }
        inline explicit Matrix(double const* const ptr) { set(ptr); }
        inline explicit Matrix(const Quat& quat) { makeRotate(quat); }

        Matrix(value_type a00, value_type a01, value_type a02, value_type a03,
            value_type a10, value_type a11, value_type a12, value_type a13,
            value_type a20, value_type a21, value_type a22, value_type a23,
            value_type a30, value_type a31, value_type a32, value_type a33);

        ~Matrix() {}

        int compare(const Matrix& m) const;

        bool operator < (const Matrix& m) const { return compare(m) < 0; }
        bool operator == (const Matrix& m) const { return compare(m) == 0; }
        bool operator != (const Matrix& m) const { return compare(m) != 0; }

        inline value_type& operator()(int row, int col) { return _mat[row][col]; }
        inline value_type operator()(int row, int col) const { return _mat[row][col]; }

        inline bool valid() const { return !isNaN(); }
        inline bool isNaN() const {
            return isnan(_mat[0][0]) || isnan(_mat[0][1]) || isnan(_mat[0][2]) || isnan(_mat[0][3]) ||
                isnan(_mat[1][0]) || isnan(_mat[1][1]) || isnan(_mat[1][2]) || isnan(_mat[1][3]) ||
                isnan(_mat[2][0]) || isnan(_mat[2][1]) || isnan(_mat[2][2]) || isnan(_mat[2][3]) ||
                isnan(_mat[3][0]) || isnan(_mat[3][1]) || isnan(_mat[3][2]) || isnan(_mat[3][3]);
        }

        inline Matrix& operator = (const Matrix& rhs)
        {
            if (&rhs == this) return *this;
            set(rhs.ptr());
            return *this;
        }

        inline void set(const Matrix& rhs) { set(rhs.ptr()); }

        inline void set(float const* const ptr)
        {
            value_type* local_ptr = (value_type*)_mat;
            for (int i = 0; i < 16; ++i) local_ptr[i] = (value_type)ptr[i];
        }

        inline void set(double const* const ptr)
        {
            value_type* local_ptr = (value_type*)_mat;
            for (int i = 0; i < 16; ++i) local_ptr[i] = (value_type)ptr[i];
        }

        void set(value_type a00, value_type a01, value_type a02, value_type a03,
            value_type a10, value_type a11, value_type a12, value_type a13,
            value_type a20, value_type a21, value_type a22, value_type a23,
            value_type a30, value_type a31, value_type a32, value_type a33);

        value_type* ptr() { return (value_type*)_mat; }
        const value_type* ptr() const { return (const value_type*)_mat; }

        bool isIdentity() const
        {
            return _mat[0][0] == 1.0 && _mat[0][1] == 0.0 && _mat[0][2] == 0.0 && _mat[0][3] == 0.0 &&
                _mat[1][0] == 0.0 && _mat[1][1] == 1.0 && _mat[1][2] == 0.0 && _mat[1][3] == 0.0 &&
                _mat[2][0] == 0.0 && _mat[2][1] == 0.0 && _mat[2][2] == 1.0 && _mat[2][3] == 0.0 &&
                _mat[3][0] == 0.0 && _mat[3][1] == 0.0 && _mat[3][2] == 0.0 && _mat[3][3] == 1.0;
        }

        void makeIdentity();

        void makeScale(const Vec3&);
        void makeScale(value_type, value_type, value_type);

        void makeTranslate(const Vec3&);
        void makeTranslate(value_type, value_type, value_type);

        void makeRotate(const Vec3& from, const Vec3& to);
        void makeRotate(value_type angle, const Vec3& axis);
        void makeRotate(value_type angle, value_type x, value_type y, value_type z);
        void makeRotate(const Quat&);
        void makeRotate(value_type angle1, const Vec3& axis1,
            value_type angle2, const Vec3& axis2,
            value_type angle3, const Vec3& axis3);


        /** decompose the matrix into translation, rotation, scale and scale orientation.*/

        /** decompose the matrix into translation, rotation, scale and scale orientation.*/
        void decompose(Vec3& translation,
            Quat& rotation,
            Vec3& scale,
            Quat& so) const;


        /** Set to an orthographic projection.
         * See glOrtho for further details.
        */
        void makeOrtho(double left, double right,
            double bottom, double top,
            double zNear, double zFar);

        /** Get the orthographic settings of the orthographic projection matrix.
          * Note, if matrix is not an orthographic matrix then invalid values
          * will be returned.
        */
        bool getOrtho(double& left, double& right,
            double& bottom, double& top,
            double& zNear, double& zFar) const;

        /** float version of getOrtho(..) */
        bool getOrtho(float& left, float& right,
            float& bottom, float& top,
            float& zNear, float& zFar) const;


        /** Set to a 2D orthographic projection.
          * See glOrtho2D for further details.
        */
        inline void makeOrtho2D(double left, double right,
            double bottom, double top)
        {
            makeOrtho(left, right, bottom, top, -1.0, 1.0);
        }


        /** Set to a perspective projection.
          * See glFrustum for further details.
        */
        void makeFrustum(double left, double right,
            double bottom, double top,
            double zNear, double zFar);

        /** Get the frustum settings of a perspective projection matrix.
          * Note, if matrix is not a perspective matrix then invalid values
          * will be returned.
        */
        bool getFrustum(double& left, double& right,
            double& bottom, double& top,
            double& zNear, double& zFar) const;

        /** float version of getFrustum(..) */
        bool getFrustum(float& left, float& right,
            float& bottom, float& top,
            float& zNear, float& zFar) const;

        /** Set to a symmetrical perspective projection.
          * See gluPerspective for further details.
          * Aspect ratio is defined as width/height.
        */
        void makePerspective(double fovy, double aspectRatio,
            double zNear, double zFar);

        /** Get the frustum settings of a symmetric perspective projection
          * matrix.
          * Return false if matrix is not a perspective matrix,
          * where parameter values are undefined.
          * Note, if matrix is not a symmetric perspective matrix then the
          * shear will be lost.
          * Asymmetric matrices occur when stereo, power walls, caves and
          * reality center display are used.
          * In these configuration one should use the AsFrustum method instead.
        */
        bool getPerspective(double& fovy, double& aspectRatio,
            double& zNear, double& zFar) const;

        /** float version of getPerspective(..) */
        bool getPerspective(float& fovy, float& aspectRatio,
            float& zNear, float& zFar) const;

        /** Set the position and orientation to be a view matrix,
          * using the same convention as gluLookAt.
        */
        void makeLookAt(const Vec3& eye, const Vec3& center, const Vec3& up);

        /** Get to the position and orientation of a modelview matrix,
          * using the same convention as gluLookAt.
        */
        void getLookAt(Vec3& eye, Vec3& center, Vec3& up,
            value_type lookDistance = 1.0f) const;

        /** invert the matrix rhs, automatically select invert_4x3 or invert_4x4. */
        inline bool invert(const Matrix& rhs)
        {
            bool is_4x3 = (rhs._mat[0][3] == 0.0 && rhs._mat[1][3] == 0.0 && rhs._mat[2][3] == 0.0 && rhs._mat[3][3] == 1.0);
            return is_4x3 ? invert_4x3(rhs) : invert_4x4(rhs);
        }

        /** 4x3 matrix invert, not right hand column is assumed to be 0,0,0,1. */
        bool invert_4x3(const Matrix& rhs);

        /** full 4x4 matrix invert. */
        bool invert_4x4(const Matrix& rhs);

        /** transpose a matrix */
        bool transpose(const Matrix& rhs);

        /** transpose orthogonal part of the matrix **/
        bool transpose3x3(const Matrix& rhs);

        /** ortho-normalize the 3x3 rotation & scale matrix */
        void orthoNormalize(const Matrix& rhs);

        // basic utility functions to create new matrices
        inline static Matrix identity(void);
        inline static Matrix scale(const Vec3& sv);
        inline static Matrix scale(value_type sx, value_type sy, value_type sz);
        inline static Matrix translate(const Vec3& dv);
        inline static Matrix translate(value_type x, value_type y, value_type z);
        inline static Matrix rotate(const Vec3& from, const Vec3& to);
        inline static Matrix rotate(value_type angle, value_type x, value_type y, value_type z);
        inline static Matrix rotate(value_type angle, const Vec3& axis);
        inline static Matrix rotate(value_type angle1, const Vec3& axis1,
            value_type angle2, const Vec3& axis2,
            value_type angle3, const Vec3& axis3);
        inline static Matrix rotate(const Quat& quat);
        inline static Matrix inverse(const Matrix& matrix);
        inline static Matrix orthoNormal(const Matrix& matrix);
        /** Create an orthographic projection matrix.
          * See glOrtho for further details.
        */
        inline static Matrix ortho(double left, double right,
            double bottom, double top,
            double zNear, double zFar);

        /** Create a 2D orthographic projection.
          * See glOrtho for further details.
        */
        inline static Matrix ortho2D(double left, double right,
            double bottom, double top);

        /** Create a perspective projection.
          * See glFrustum for further details.
        */
        inline static Matrix frustum(double left, double right,
            double bottom, double top,
            double zNear, double zFar);

        /** Create a symmetrical perspective projection.
          * See gluPerspective for further details.
          * Aspect ratio is defined as width/height.
        */
        inline static Matrix perspective(double fovy, double aspectRatio,
            double zNear, double zFar);

        /** Create the position and orientation as per a camera,
          * using the same convention as gluLookAt.
        */
        inline static Matrix lookAt(const Vec3& eye,
            const Vec3& center,
            const Vec3& up);


        inline Vec3 preMult(const Vec3& v) const;

        inline Vec3 postMult(const Vec3& v) const;

        inline Vec3 operator* (const Vec3& v) const;

        inline Vec4 preMult(const Vec4& v) const;

        inline Vec4 postMult(const Vec4& v) const;

        inline Vec4 operator* (const Vec4& v) const;

#ifdef OSG_USE_DEPRECATED_API
        inline void set(const Quat& q) { makeRotate(q); }   /// deprecated, replace with makeRotate(q)
        inline void get(Quat& q) const { q = getRotate(); } /// deprecated, replace with getRotate()
#endif

        void setRotate(const Quat& q);
        /** Get the matrix rotation as a Quat. Note that this function
          * assumes a non-scaled matrix and will return incorrect results
          * for scaled matrixces. Consider decompose() instead.
          */
        Quat getRotate() const;

        void setTrans(value_type tx, value_type ty, value_type tz);

        void setTrans(const Vec3& v);

        inline Vec3 getTrans() const { return Vec3(_mat[3][0], _mat[3][1], _mat[3][2]); }

        inline Vec3 getScale() const {
            Vec3 x_vec(_mat[0][0], _mat[1][0], _mat[2][0]);
            Vec3 y_vec(_mat[0][1], _mat[1][1], _mat[2][1]);
            Vec3 z_vec(_mat[0][2], _mat[1][2], _mat[2][2]);
            return Vec3(x_vec.length(), y_vec.length(), z_vec.length());
        }

        /** apply a 3x3 transform of v*M[0..2,0..2]. */
        inline static Vec3 transform3x3(const Vec3& v, const Matrix& m);

        /** apply a 3x3 transform of M[0..2,0..2]*v. */
        inline static Vec3 transform3x3(const Matrix& m, const Vec3& v);

        // basic Matrix multiplication, our workhorse methods.
        void mult(const Matrix&, const Matrix&);
        void preMult(const Matrix&);
        void postMult(const Matrix&);

        /** Optimized version of preMult(translate(v)); */
        inline void preMultTranslate(const Vec3& v);
        /** Optimized version of postMult(translate(v)); */
        inline void postMultTranslate(const Vec3& v);

        /** Optimized version of preMult(scale(v)); */
        inline void preMultScale(const Vec3& v);
        /** Optimized version of postMult(scale(v)); */
        inline void postMultScale(const Vec3& v);

        /** Optimized version of preMult(rotate(q)); */
        inline void preMultRotate(const Quat& q);
        /** Optimized version of postMult(rotate(q)); */
        inline void postMultRotate(const Quat& q);

        inline void operator *= (const Matrix& other)
        {
            if (this == &other) {
                Matrix temp(other);
                postMult(temp);
            }
            else postMult(other);
        }

        inline Matrix operator * (const Matrix& m) const
        {
            Matrix r;
            r.mult(*this, m);
            return  r;
        }

    protected:
        value_type _mat[4][4];

    };


        /** A quaternion class. It can be used to represent an orientation in 3D space.*/
    class Quat
    {

    public:

        /** Data type of vector components.*/
#ifdef OSG_USE_FLOAT_QUAT
        typedef float value_type;
#else
        typedef double value_type;
#endif

        /** Number of vector components. */
        enum { num_components = 4 };

        value_type  _v[4];    // a four-vector

        inline Quat() { _v[0] = 0.0; _v[1] = 0.0; _v[2] = 0.0; _v[3] = 1.0; }

        inline Quat(value_type x, value_type y, value_type z, value_type w)
        {
            _v[0] = x;
            _v[1] = y;
            _v[2] = z;
            _v[3] = w;
        }

        inline Quat(const Vec4& v)
        {
            _v[0] = v.x();
            _v[1] = v.y();
            _v[2] = v.z();
            _v[3] = v.w();
        }

        inline Quat(value_type angle, const Vec3& axis)
        {
            makeRotate(angle, axis);
        }

        inline Quat(value_type angle1, const Vec3& axis1,
            value_type angle2, const Vec3& axis2,
            value_type angle3, const Vec3& axis3)
        {
            makeRotate(angle1, axis1, angle2, axis2, angle3, axis3);
        }

        inline Quat& operator = (const Quat& v) { _v[0] = v._v[0];  _v[1] = v._v[1]; _v[2] = v._v[2]; _v[3] = v._v[3]; return *this; }

        inline bool operator == (const Quat& v) const { return _v[0] == v._v[0] && _v[1] == v._v[1] && _v[2] == v._v[2] && _v[3] == v._v[3]; }

        inline bool operator != (const Quat& v) const { return _v[0] != v._v[0] || _v[1] != v._v[1] || _v[2] != v._v[2] || _v[3] != v._v[3]; }

        inline bool operator <  (const Quat& v) const
        {
            if (_v[0] < v._v[0]) return true;
            else if (_v[0] > v._v[0]) return false;
            else if (_v[1] < v._v[1]) return true;
            else if (_v[1] > v._v[1]) return false;
            else if (_v[2] < v._v[2]) return true;
            else if (_v[2] > v._v[2]) return false;
            else return (_v[3] < v._v[3]);
        }

        /* ----------------------------------
           Methods to access data members
        ---------------------------------- */

        inline Vec4 asVec4() const
        {
            return Vec4(_v[0], _v[1], _v[2], _v[3]);
        }

        inline Vec3 asVec3() const
        {
            return Vec3(_v[0], _v[1], _v[2]);
        }

        inline void set(value_type x, value_type y, value_type z, value_type w)
        {
            _v[0] = x;
            _v[1] = y;
            _v[2] = z;
            _v[3] = w;
        }

        inline void set(const Vec4& v)
        {
            _v[0] = v.x();
            _v[1] = v.y();
            _v[2] = v.z();
            _v[3] = v.w();
        }

        void set(const Matrix& matrix);

        void get(Matrix& matrix) const;


        inline value_type& operator [] (int i) { return _v[i]; }
        inline value_type   operator [] (int i) const { return _v[i]; }

        inline value_type& x() { return _v[0]; }
        inline value_type& y() { return _v[1]; }
        inline value_type& z() { return _v[2]; }
        inline value_type& w() { return _v[3]; }

        inline value_type x() const { return _v[0]; }
        inline value_type y() const { return _v[1]; }
        inline value_type z() const { return _v[2]; }
        inline value_type w() const { return _v[3]; }

        /** return true if the Quat represents a zero rotation, and therefore can be ignored in computations.*/
        bool zeroRotation() const { return _v[0] == 0.0 && _v[1] == 0.0 && _v[2] == 0.0 && _v[3] == 1.0; }


        /* -------------------------------------------------------------
                  BASIC ARITHMETIC METHODS
       Implemented in terms of Vec4s.  Some Vec4 operators, e.g.
       operator* are not appropriate for quaternions (as
       mathematical objects) so they are implemented differently.
       Also define methods for conjugate and the multiplicative inverse.
       ------------------------------------------------------------- */
       /// Multiply by scalar
        inline const Quat operator * (value_type rhs) const
        {
            return Quat(_v[0] * rhs, _v[1] * rhs, _v[2] * rhs, _v[3] * rhs);
        }

        /// Unary multiply by scalar
        inline Quat& operator *= (value_type rhs)
        {
            _v[0] *= rhs;
            _v[1] *= rhs;
            _v[2] *= rhs;
            _v[3] *= rhs;
            return *this;        // enable nesting
        }

        /// Binary multiply
        inline const Quat operator*(const Quat& rhs) const
        {
            return Quat(rhs._v[3] * _v[0] + rhs._v[0] * _v[3] + rhs._v[1] * _v[2] - rhs._v[2] * _v[1],
                rhs._v[3] * _v[1] - rhs._v[0] * _v[2] + rhs._v[1] * _v[3] + rhs._v[2] * _v[0],
                rhs._v[3] * _v[2] + rhs._v[0] * _v[1] - rhs._v[1] * _v[0] + rhs._v[2] * _v[3],
                rhs._v[3] * _v[3] - rhs._v[0] * _v[0] - rhs._v[1] * _v[1] - rhs._v[2] * _v[2]);
        }

        /// Unary multiply
        inline Quat& operator*=(const Quat& rhs)
        {
            value_type x = rhs._v[3] * _v[0] + rhs._v[0] * _v[3] + rhs._v[1] * _v[2] - rhs._v[2] * _v[1];
            value_type y = rhs._v[3] * _v[1] - rhs._v[0] * _v[2] + rhs._v[1] * _v[3] + rhs._v[2] * _v[0];
            value_type z = rhs._v[3] * _v[2] + rhs._v[0] * _v[1] - rhs._v[1] * _v[0] + rhs._v[2] * _v[3];
            _v[3] = rhs._v[3] * _v[3] - rhs._v[0] * _v[0] - rhs._v[1] * _v[1] - rhs._v[2] * _v[2];

            _v[2] = z;
            _v[1] = y;
            _v[0] = x;

            return (*this);            // enable nesting
        }

        /// Divide by scalar
        inline Quat operator / (value_type rhs) const
        {
            value_type div = 1.0 / rhs;
            return Quat(_v[0] * div, _v[1] * div, _v[2] * div, _v[3] * div);
        }

        /// Unary divide by scalar
        inline Quat& operator /= (value_type rhs)
        {
            value_type div = 1.0 / rhs;
            _v[0] *= div;
            _v[1] *= div;
            _v[2] *= div;
            _v[3] *= div;
            return *this;
        }

        /// Binary divide
        inline const Quat operator/(const Quat& denom) const
        {
            return ((*this) * denom.inverse());
        }

        /// Unary divide
        inline Quat& operator/=(const Quat& denom)
        {
            (*this) = (*this) * denom.inverse();
            return (*this);            // enable nesting
        }

        /// Binary addition
        inline const Quat operator + (const Quat& rhs) const
        {
            return Quat(_v[0] + rhs._v[0], _v[1] + rhs._v[1],
                _v[2] + rhs._v[2], _v[3] + rhs._v[3]);
        }

        /// Unary addition
        inline Quat& operator += (const Quat& rhs)
        {
            _v[0] += rhs._v[0];
            _v[1] += rhs._v[1];
            _v[2] += rhs._v[2];
            _v[3] += rhs._v[3];
            return *this;            // enable nesting
        }

        /// Binary subtraction
        inline const Quat operator - (const Quat& rhs) const
        {
            return Quat(_v[0] - rhs._v[0], _v[1] - rhs._v[1],
                _v[2] - rhs._v[2], _v[3] - rhs._v[3]);
        }

        /// Unary subtraction
        inline Quat& operator -= (const Quat& rhs)
        {
            _v[0] -= rhs._v[0];
            _v[1] -= rhs._v[1];
            _v[2] -= rhs._v[2];
            _v[3] -= rhs._v[3];
            return *this;            // enable nesting
        }

        /** Negation operator - returns the negative of the quaternion.
        Basically just calls operator - () on the Vec4 */
        inline const Quat operator - () const
        {
            return Quat(-_v[0], -_v[1], -_v[2], -_v[3]);
        }

        /// Length of the quaternion = sqrt( vec . vec )
        value_type length() const
        {
            return sqrt(_v[0] * _v[0] + _v[1] * _v[1] + _v[2] * _v[2] + _v[3] * _v[3]);
        }

        /// Length of the quaternion = vec . vec
        value_type length2() const
        {
            return _v[0] * _v[0] + _v[1] * _v[1] + _v[2] * _v[2] + _v[3] * _v[3];
        }

        /// Conjugate
        inline Quat conj() const
        {
            return Quat(-_v[0], -_v[1], -_v[2], _v[3]);
        }

        /// Multiplicative inverse method: q^(-1) = q^*/(q.q^*)
        inline const Quat inverse() const
        {
            return conj() / length2();
        }

        /* --------------------------------------------------------
                 METHODS RELATED TO ROTATIONS
          Set a quaternion which will perform a rotation of an
          angle around the axis given by the vector (x,y,z).
          Should be written to also accept an angle and a Vec3?

          Define Spherical Linear interpolation method also

          Not inlined - see the Quat.cpp file for implementation
          -------------------------------------------------------- */
        void makeRotate(value_type  angle,
            value_type  x, value_type  y, value_type  z);
        void makeRotate(value_type  angle, const Vec3& vec);

        void makeRotate(value_type  angle1, const Vec3& axis1,
            value_type  angle2, const Vec3& axis2,
            value_type  angle3, const Vec3& axis3);

        /** Make a rotation Quat which will rotate vec1 to vec2.
            Generally take a dot product to get the angle between these
            and then use a cross product to get the rotation axis
            Watch out for the two special cases of when the vectors
            are co-incident or opposite in direction.*/
        void makeRotate(const Vec3& vec1, const Vec3& vec2);

        void makeRotate_original(const Vec3& vec1, const Vec3& vec2);

        /** Return the angle and vector components represented by the quaternion.*/
        void getRotate(value_type& angle, value_type& x, value_type& y, value_type& z) const;

        /** Return the angle and vector represented by the quaternion.*/
        void getRotate(value_type& angle, Vec3& vec) const;

        /** Spherical Linear Interpolation.
        As t goes from 0 to 1, the Quat object goes from "from" to "to". */
        void slerp(value_type  t, const Quat& from, const Quat& to);

        /** Rotate a vector by this quaternion.*/
        Vec3 operator* (const Vec3& v) const
        {
            // nVidia SDK implementation
            Vec3 uv, uuv;
            Vec3 qvec(_v[0], _v[1], _v[2]);
            uv = qvec ^ v;
            uuv = qvec ^ uv;
            uv *= (2.0f * _v[3]);
            uuv *= 2.0f;
            return v + uv + uuv;
        }

    protected:

    };    // end of class prototype  


}