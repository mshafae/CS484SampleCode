/*
 * Copyright (c) 2015 Michael Shafae
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met: 
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * $Id: GFXMath.h 5487 2015-01-26 09:14:49Z mshafae $
 *
 */

#ifndef _GFXMATH_H_
#define _GFXMATH_H_
#ifdef WIN32
#pragma once
#define _USE_MATH_DEFINES 1
#endif

#include <cmath>
#include <iostream>
#include <iomanip>

#ifndef IOS_FP_PRECISION
#define IOS_FP_PRECISION 5
#endif

#ifndef M_PI
#define M_PI        3.14159265358979323846264338327950288
#endif

#ifndef PI_OVER_ONE_EIGHTY
#define PI_OVER_ONE_EIGHTY 0.01745329251994329547437168059786927188
#endif

#ifndef ONE_EIGHTY_OVER_PI
#define ONE_EIGHTY_OVER_PI 57.29577951308232286464772187173366546631
#endif

template <typename T>
static inline T sqr(T a)
{
    return a * a;
}


#ifndef MSGFX_FP
#define MSGFX_FP

/*
 * One option is to make the Vector and Matrix classes
 * aware of how much precision is really needed. Barring
 * that, let's have a few templated functions that help
 * in determining if two floating point values are equal.
 */

/*
 * These two defines are useful if you want to remember
 * how much precision you'll have with your float or double
 * types. However, 7 decimal places may be overkill for our
 * work. Consider defining your own macro or static variable
 * that defines how much precision you want and need.
 *
 * Single precision floating point numbers have a
 * significand of 24 bits which is about 7 decimal places.
 * Double precision floating point numbers have a
 * significand of 53 bits which is about 16 decimal places.
 */
#define FP_SP_EPSILON 1e-6
#define FP_DP_EPSILON 1e-15

template <typename T>
static bool fpEqual(T a, T b, T epsilon)
{
  return (a == b) || ((a - epsilon) < b && (a + epsilon) > b);
}

template <typename T>
static bool fpNotEqual(T a, T b, T epsilon)
{
  return (a != b) && ((a - epsilon) > b || (a + epsilon) < b);
}

#endif

template <typename T>
static T degreesToRadians(T degrees)
{
  return degrees * static_cast<T>(PI_OVER_ONE_EIGHTY);
}

template <typename T>
static T radiansToDegrees(T radians)
{
  return radians * static_cast<T>(ONE_EIGHTY_OVER_PI);
}

/*
 * See Park & Miller's paper Random Number Generators: Good Ones are 
 * Hard to Find, Communications of the ACM, October 1988, Vol. 31, no. 10
 *
 * In a nutshell, this is Lehmer's parametric multiplicative
 * linear congruential algorithm to generate a series of psuedo random
 * unsigned integers. MS Window's standard library has a broken
 * implementation so it's included here in case someone needs to use
 * it.
 */
// This should be a Singleton but it's not.
class LPMRandom{
public:
  LPMRandom( unsigned int seed = 1 ){
    if(seed < 1 || seed >= m){
      seed = 1234557890;
    }
    this->seed = seed;
  };
  void reseed(unsigned int s){
    seed = s;
  }
  unsigned int operator ()(void){
    return _rand( );
  }
  operator int( ){
    return static_cast<int>(_rand( ));
  }
  operator float( ){
    // invM = 1 / m
    float invM = 0.0000000004656612875245797;
    return _rand( ) * invM;
  }
  operator double( ){
    // invM = 1 / m
    double invM = 0.0000000004656612875245797;
    return _rand( ) * invM;
  }
  float frand( ){
    return static_cast<float>(*this);
  }
  double drand( ){
    return static_cast<double>(*this);
  }
  int irand( ){
    return static_cast<int>(*this);
  }
private:
  unsigned int seed;
  // The multiplier -- 7**5 = 16807
  const static unsigned int a = 16807;
  // The modulo -- a large prime number
  const static unsigned int m = 2147483647;
  // quotient -- m div a
  const static unsigned int q = 127773;
  // remainder -- m mod a
  const static unsigned int r = 2836;
  unsigned int _rand( ){
    unsigned int lo, hi;
    int test;
    hi = seed / q;
    lo = seed % q;
    test = a * lo - r * hi;
    if( test < 0 ){
      test += m;
    }
    seed = test % m;
    return seed;
  }
}; // end class LPMRandom

template <typename T, const int length>
class VecN{
public:
  typedef class VecN<T,length> myType;
  typedef T elementType;

  VecN( ){};

  VecN(const VecN& rhs){
    assign(rhs);
  }
  
  VecN(const VecN* rhs){
    assign(rhs);
  }
  
  VecN(T const & s){
    for( int i = 0; i < length; i++ ){
      data[i] = s;
    }
  }
  
  VecN& operator =(const VecN& rhs){
    assign(rhs);
    return *this;
  }

  VecN& operator =(const VecN* rhs){
    assign(rhs);
    return *this;
  }
  
  VecN& operator =(const T& s){
    assign(s);
    return *this;
  }
  
  VecN operator +(const VecN& rhs) const{
    VecN sum;
    // Fill me in!
    return sum;
  }
  
  VecN& operator +=(const VecN& rhs){
    return *this = *this + rhs;
  }

  VecN operator -( ) const{
    VecN rv;
    // Fill me in!
    return rv;
  }
  
  VecN operator -(const VecN& rhs) const{
    VecN difference;
    // Fill me in!
    return difference;
  }
  
  VecN& operator -=(const VecN& rhs){
    return *this = *this - rhs;
  }
  
  VecN operator *(const T& s) const{
    VecN rv;
    // Fill me in!
    return rv;
  }
  
  VecN operator *=(const T& s){
    assign(*this * s);
    return *this;
  }
  
  VecN operator /(const T& s) const{
    VecN rv;
    // Fill me in!
    return rv;
  }
  
  VecN operator /=(const T& s){
    assign(*this / s);
    return *this;
  }
  
  T& operator [](unsigned int i){
    if( i < length ){
      return data[i];
    }else{
      throw( "Index out of range" );
    }
  }
  
  const T& operator [](unsigned int i) const{
    if( i < length ){
      return data[i];
    }else{
      throw( "Index out of range" );
    }
  }
  
  bool operator ==(const VecN& rhs) const{
    bool rv = false;
    // Fill me in!
    return rv;
  }
  
  bool operator !=(const VecN& rhs) const{
    bool rv = false;
    // Fill me in!
    return rv;
  }
  
  static int size( ){
    return length;
  }
  
  operator const T* ( ) const{
    return &data[0];
  }
  
  std::ostream& write( std::ostream &out ) const{
    out.setf( std::ios::fixed );
    out << std::setprecision(IOS_FP_PRECISION)
      << "(";
    for( int i = 0; i < length; i++ ){
      if( i < (length - 1) ){
        out << " " << data[i] << std::endl;
      }else{
        out << " " << data[i] << " )" << std::endl;
      }
    }
    out.unsetf( std::ios::fixed );
    return( out );
  }
  
  std::ostream& write_row( std::ostream &out) const{
    out.setf( std::ios::fixed );
    out << std::setprecision(IOS_FP_PRECISION)
      << "(";
    for( int i = 0; i < length; i++ ){
      if( i < (length - 1) ){
        out << data[i] << ", ";
      }else{
        out << data[i] << ")" << std::endl;
      }
    }
    out.unsetf( std::ios::fixed );
    return( out );
  }
  
  std::ostream& description( std::ostream &out = std::cerr ) const{
    out.setf( std::ios::fixed );
    out << std::setprecision(IOS_FP_PRECISION) <<
      "<Vec"<< length << " " << this << "> ";
    out << "(";
    for( int i = 0; i < length; i++ ){
      if( i < (length - 1) ){
        out << data[i] << ", ";
      }else{
        out << data[i] << ")" << std::endl;
      }
    }
    out.unsetf( std::ios::fixed );
    return( out );
  }
  
  
protected:
  T data[length];

  inline void assign(const VecN& rhs){
    for( int i = 0; i < length; i++ ){
      data[i] = rhs.data[i];
    }
  }

  inline void assign(const T& s){
    for( int i = 0; i < length; i++ ){
      data[i] = s;
    }
  }
  
  inline void assign(const VecN* rhs){
    for( int i = 0; i < length; i++ ){
      data[i] = rhs->data[i];
    }
  }

}; // end class VecN

template <typename T>
class TVec1 : public VecN<T, 1>{
public:
  typedef VecN<T, 1> base;
  TVec1( ) : base( ){ }
  TVec1(const base& v) : base(v){ }
  explicit TVec1(const base* v) : base(v){ }
  explicit TVec1(T x){
    base::data[0] = x;
  }
}; // end class TVec1

template <typename T>
class TVec2 : public VecN<T, 2>{
public:
  typedef VecN<T, 2> base;
  TVec2( ) : base( ){ }
  TVec2(const base& v) : base(v){ }
  explicit TVec2(const base* v) : base(v){ }
  explicit TVec2(T x, T y){
    base::data[0] = x;
    base::data[1] = y;
  }
}; // end class TVec2

template <typename T>
class TVec3 : public VecN<T, 3>{
public:
  typedef VecN<T, 3> base;
  TVec3( ) : base( ){ }
  TVec3(const base& v) : base(v){ }
  explicit TVec3(const base* v) : base(v){ }
  explicit TVec3(T x, T y, T z){
    base::data[0] = x;
    base::data[1] = y;
    base::data[2] = z;
  }
  
  explicit TVec3(const TVec2<T>& v, T z){
    base::data[0] = v[0];
    base::data[1] = v[1];
    base::data[2] = z;
  }
}; // end class TVec3

template <typename T>
class TVec4 : public VecN<T, 4>{
public:
  typedef VecN<T, 4> base;
  TVec4( ) : base( ){ }
  TVec4(const base& v) : base(v){ }
  explicit TVec4(const base* v) : base(v){ }
  explicit TVec4(T x, T y, T z, T w){
    base::data[0] = x;
    base::data[1] = y;
    base::data[2] = z;
    base::data[3] = w;
  }
  
  explicit TVec4(const TVec2<T>& v, T z, T w){
    base::data[0] = v[0];
    base::data[1] = v[1];
    base::data[2] = z;
    base::data[3] = w;
  }
  
  explicit TVec4(const TVec3<T>& v, T w){
    base::data[0] = v[0];
    base::data[1] = v[1];
    base::data[2] = v[2];
    base::data[3] = w;
  }
}; // end class TVec4

template <typename T, int length>
static const VecN<T, length> operator *(T lhs, const VecN<T, length>& rhs){
  return rhs * lhs;
}

template <typename T>
static const TVec1<T> operator /(T lhs, const TVec1<T>& rhs){
  return TVec1<T>(lhs / rhs[0]);
}

template <typename T>
static const TVec2<T> operator /(T lhs, const TVec2<T>& rhs){
  return TVec2<T>(lhs / rhs[0], lhs / rhs[1]);
}

template <typename T>
static const TVec3<T> operator /(T lhs, const TVec3<T>& rhs){
  return TVec3<T>(lhs / rhs[0], lhs / rhs[1], lhs / rhs[2]);
}

template <typename T>
static const TVec4<T> operator /(T lhs, const TVec4<T>& rhs){
  return TVec4<T>(lhs / rhs[0], lhs / rhs[1], lhs / rhs[2], lhs / rhs[3]);
}

template <typename T, int length>
static T dot(const VecN<T, length>& a, const VecN<T, length>& b){
  T rv(0);
  // Fill me in!
  return rv;
}

template <typename T, int length>
static T squaredLength(const VecN<T, length>& v){
  T rv(0);
  // Fill me in!
  return rv;
}

template <typename T, int length>
static T length(const VecN<T, length>& v){
  return sqrt(squaredLength(v));
}

template <typename T, int _length>
static VecN<T, _length> normalize(const VecN<T, _length>& v){
  VecN<T, _length> rv;
  // Fill me in!
  return rv;
}

template <typename T, int length>
static T distance(const VecN<T, length>& a, const VecN<T, length>& b){
  T rv;
  // Fill me in!
  return rv;
}

template <typename T>
static T angleInRadians(const TVec2<T>& a, const TVec2<T>& b){
  T rv(0);
  // Fill me in!
  return rv;
}

template <typename T>
static T angleInRadians(const TVec3<T>& a, const TVec3<T>& b){
  T rv(0);
  // Fill me in!
  return rv;
}

template <typename T>
static T angle(const TVec2<T>& a, const TVec2<T>& b){
  // In degrees!
  return radiansToDegrees(angleInRadians(a, b));
}

template <typename T>
static T angle(const TVec3<T>& a, const TVec3<T>& b){
  // In degrees!
  return radiansToDegrees(angleInRadians(a, b));
}


template <typename T>
static VecN<T, 3> cross(const VecN<T, 3>& a, const VecN<T, 3>& b){
  // Fill me in!
  return TVec3<T>(0, 0, 0);
}

template <typename T, int length>
std::ostream& operator <<( std::ostream &out, const VecN<T, length> &v ){
  return(v.write_row( out ));
}

typedef TVec1<float> Vec1;
typedef TVec1<double> Vec1d;
typedef TVec1<int> Vec1i;

typedef TVec2<float> Vec2;
typedef TVec2<double> Vec2d;
typedef TVec2<int> Vec2i;

typedef TVec3<float> Vec3;
typedef TVec3<double> Vec3d;
typedef TVec3<int> Vec3i;

typedef TVec4<float> Vec4;
typedef TVec4<double> Vec4d;
typedef TVec4<int> Vec4i;

#endif
