/*
 * @file oat_geometry_const.h
 *
 * Created on Sat Jan 06 2024
 * Created by Felix Yuan
 * Email: FelixYuan.space@gmail.com
 *
 *  Copyright (c) 2024 Felix Yuan
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 */
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

    };
}