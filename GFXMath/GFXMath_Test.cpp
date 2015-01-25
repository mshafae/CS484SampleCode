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
 * $Id: GFXMath_Test.cpp 5479 2015-01-25 01:23:30Z mshafae $
 *
 */

// CC GFXMath_Test.cpp -I ~/local/TitanOpenGLKit_osx/include -L ~/local/TitanOpenGLKit_osx/lib -lgtest -lgtest_main -lstdc++

#include "GFXMath.h"

#include <gtest/gtest.h>

TEST(GFXMath_FP_Test, fpEqual) {
  float precision_1 = FP_SP_EPSILON;
  float precision_2 = 1e-5;
  float a = 0.52120106552957357;
  float b = 0.71392779691972863;
  float c = 0.71392;
  EXPECT_TRUE(fpEqual(a, a, precision_1));
  EXPECT_FALSE(fpEqual(a, b, 0.01f));
  EXPECT_FALSE(fpEqual(b, c, precision_1));
  EXPECT_TRUE(fpEqual(b, c, precision_2));
}

TEST(GFXMath_FP_Test, fpNotEqual) {
  float precision_1 = FP_SP_EPSILON;
  float precision_2 = 1e-5;
  float a = 0.52120106552957357;
  float b = 0.71392779691972863;
  float c = 0.71392;
  EXPECT_FALSE(fpNotEqual(a, a, precision_1));
  EXPECT_TRUE(fpNotEqual(a, b, precision_1));
  EXPECT_TRUE(fpNotEqual(b, c, precision_1));
  EXPECT_FALSE(fpNotEqual(b, c, precision_2));
}

TEST(GFXMath_Angles, degreesToRadians) {
  float d1 = 45.0;
  float r1 = 0.785398163397448;
  float r2 = 1.0;
  float d2 = 57.295779513082323;
  EXPECT_EQ(degreesToRadians(d1), r1);
  EXPECT_EQ(degreesToRadians(d2), r2);
}

TEST(GFXMath_Angles, radiansToDegrees) {
  float d1 = 45.0;
  float r1 = 0.785398163397448;
  float r2 = 1.0;
  float d2 = 57.295779513082323;
  EXPECT_EQ(radiansToDegrees(r1), d1);
  EXPECT_EQ(radiansToDegrees(r2), d2);
}

const static unsigned int _seed_of_1[] = {16807, 282475249, 1622650073, 984943658, 1144108930, 470211272, 101027544, 1457850878, 1458777923, 2007237709, 823564440};
const static unsigned int _seed_of_0[] = {227459916, 397916552, 519412706, 248324687, 1032288288, 148872303, 278347766, 971519996, 1018404631, 881966627};
const static float _f_seed_of_1[] = {0.00000782636925578, 0.13153779506683350, 0.75560534000396729, 0.45865014195442200, 0.53276723623275757, 0.21895918250083923, 0.04704461619257927, 0.67886471748352051, 0.67929643392562866, 0.93469291925430298};
const static float _f_seed_of_0[] = {0.10591927915811539, 0.18529433012008667, 0.24187038838863373, 0.11563519388437271, 0.48069667816162109, 0.06932406872510910, 0.12961578369140625, 0.45239925384521484, 0.47423160076141357, 0.41069772839546204};
const static double _d_seed_of_1[] = {0.00000782636925578, 0.13153779506683350, 0.75560534000396729, 0.45865014195442200, 0.53276723623275757, 0.21895918250083923, 0.04704461619257927, 0.67886471748352051, 0.67929643392562866, 0.93469291925430298};
const static double _d_seed_of_0[] = {0.10591927915811539, 0.18529433012008667, 0.24187038838863373, 0.11563519388437271, 0.48069667816162109, 0.06932406872510910, 0.12961578369140625, 0.45239925384521484, 0.47423160076141357, 0.41069772839546204};

class LPMRandomTest : public testing::Test{
protected:
  virtual void SetUp( ){
    seed_of_1 = _seed_of_1;
    seed_of_0 = _seed_of_0;
    f_seed_of_1 = _f_seed_of_1;
    f_seed_of_0 = _f_seed_of_0;
    d_seed_of_1 = _d_seed_of_1;
    d_seed_of_0 = _d_seed_of_0;
  }
  LPMRandom r;
  const unsigned int *seed_of_1;
  const unsigned int *seed_of_0;
  const float *f_seed_of_1;
  const float *f_seed_of_0;
  const double *d_seed_of_1;
  const double *d_seed_of_0;
  
};

TEST_F(LPMRandomTest, Constructor){
  r = LPMRandom(1);
  for(int i = 0; i < 10; i++ ){
    unsigned int rn = r( );
    EXPECT_EQ(rn, seed_of_1[i]);
  }
  r = LPMRandom(0);
  for(int i = 0; i < 10; i++ ){
    unsigned int rn = r( );
    EXPECT_EQ(rn, seed_of_0[i]);
  }
  r = LPMRandom(2147483647 + 1);
  for(int i = 0; i < 10; i++ ){
    unsigned int rn = r( );
    EXPECT_EQ(rn, seed_of_0[i]);
  }
}

TEST_F(LPMRandomTest, IntegerRand){
  r = LPMRandom(1);
  for(int i = 0; i < 10; i++ ){
    int rn = r.irand( );
    EXPECT_EQ(rn, static_cast<int>(seed_of_1[i]));
  }
}

TEST_F(LPMRandomTest, FloatRand){
  float precision = FP_SP_EPSILON;
  r = LPMRandom(1);
  for(int i = 0; i < 10; i++ ){
    float rn = r.frand( );
    EXPECT_TRUE(fpEqual(rn, _f_seed_of_1[i], precision));
  }
  r = LPMRandom(0);
  for(int i = 0; i < 10; i++ ){
    float rn = r.frand( );
    EXPECT_TRUE(fpEqual(rn, _f_seed_of_0[i], precision));
  }
  r = LPMRandom(2147483647 + 1);
  for(int i = 0; i < 10; i++ ){
    float rn = r.frand( );
    EXPECT_TRUE(fpEqual(rn, _f_seed_of_0[i], precision));
  }
}

TEST_F(LPMRandomTest, DoubleRand){
  double precision = FP_SP_EPSILON;
  r = LPMRandom(1);
  for(int i = 0; i < 10; i++ ){
    double rn = r.drand( );
    EXPECT_TRUE(fpEqual(rn, _d_seed_of_1[i], precision));
  }
  r = LPMRandom(0);
  for(int i = 0; i < 10; i++ ){
    double rn = r.drand( );
    EXPECT_TRUE(fpEqual(rn, _d_seed_of_0[i], precision));
  }
  r = LPMRandom(2147483647 + 1);
  for(int i = 0; i < 10; i++ ){
    double rn = r.drand( );
    EXPECT_TRUE(fpEqual(rn, _d_seed_of_0[i], precision));
  }
}



class Vec1Test : public testing::Test{
protected:
  virtual void SetUp( ){
    a = Vec1(0.5374693001147223);
    b = Vec1(0.2577439204835488);
    c = Vec1(0.6503827885914889);
    d = Vec1(0.07631174006296397);
    e = Vec1(0.2754099415250377);
    
    f = new Vec1(0.2493981133863178);
    g = new Vec1(0.4954117880655719);
  }
  virtual void TearDown() {
    delete f;
    delete g;
  }
  
  Vec1 a, b, c, d, e;
  Vec1 *f, *g;
};

TEST_F(Vec1Test, Constructors) {
  float precision = FP_SP_EPSILON;
  EXPECT_EQ(1u, a.size());
  EXPECT_TRUE(fpEqual(0.5374693001147223f, a[0], precision));

  EXPECT_EQ(1u, b.size());
  EXPECT_TRUE(fpEqual(0.2577439204835488f, b[0], precision));

  b = Vec1(a);
  
  EXPECT_EQ(1u, b.size());
  EXPECT_TRUE(fpEqual(0.5374693001147223f, b[0], precision));
  
  EXPECT_EQ(1u, f->size());
  EXPECT_TRUE(fpEqual(0.2493981133863178f, *f[0], precision));
  
  EXPECT_EQ(1u, g->size());
  EXPECT_TRUE(fpEqual(0.4954117880655719f, *g[0], precision));
  
  delete g;
  
  g = new Vec1(f);
  
  EXPECT_EQ(1u, g->size());
  EXPECT_TRUE(fpEqual(0.2493981133863178f, *g[0], precision));
}

TEST_F(Vec1Test, BooleanEquals) {
  EXPECT_FALSE(a == b);
  EXPECT_FALSE(b == c);
  b = a;
  EXPECT_TRUE(a == b);
  EXPECT_TRUE(a == a);
  
  EXPECT_FALSE(*f == *g);
  EXPECT_TRUE(*f == *f);
  *f = *g;
  EXPECT_TRUE(*f == *g);
  
}

TEST_F(Vec1Test, BooleanNotEquals) {
  EXPECT_TRUE(a != b);
  EXPECT_TRUE(b != c);
  b = a;
  EXPECT_FALSE(a != b);
  EXPECT_FALSE(a != a);
  
  EXPECT_TRUE(*f != *g);
  EXPECT_FALSE(*f != *f);
  *f = *g;
  EXPECT_FALSE(*f != *g);
}

TEST_F(Vec1Test, ArithmeticAddition) {
  Vec1 _x = Vec1(0.795213220598271);
  Vec1 x = a + b;
  EXPECT_TRUE(x == _x);
  
  Vec1 _y = Vec1(1.074938600229445);
  a += a;
  EXPECT_TRUE(a == _y);
}

TEST_F(Vec1Test, ArithmeticSubtraction) {
  Vec1 _x = Vec1(0.279725379631173);
  Vec1 x = a - b;
  EXPECT_TRUE(x == _x);
  
  Vec1 _y = Vec1(0.0);
  a -= a;
  EXPECT_TRUE(a == _y);
  
  Vec1 _z = Vec1(-0.392638868107940);
  b -= c;
  EXPECT_TRUE(b == _z);
  
}

TEST_F(Vec1Test, ArithmeticMultiplication) {
  Vec1 _x = Vec1(0.603578024028833);
  Vec1 x = a * 1.123;
  EXPECT_TRUE(x == _x);
  Vec1 y = 1.123f * a;
  EXPECT_TRUE(y == _x);
  a *= 1.123;
  EXPECT_TRUE(a == _x);
}

TEST_F(Vec1Test, ArithmeticDivision) {
  Vec1 _x = Vec1(0.253165002409196);
  Vec1 _y = Vec1(3.949993049922755);
  Vec1 x = a / 2.123f;
  EXPECT_TRUE(x == _x);
  Vec1 y = 2.123f / a;
  EXPECT_TRUE(y == _y);
  a /= 2.123;
  EXPECT_TRUE(_x == a);
}

TEST_F(Vec1Test, ArithmeticNegation) {
  Vec1 _x = Vec1(-0.537469300114722);
  EXPECT_TRUE(_x == -a);
  Vec1 x = -a;
  EXPECT_TRUE(_x == x);
  x = -x;
  EXPECT_TRUE(a == x);
}


TEST_F(Vec1Test, BracketOperator) {
  float precision = FP_SP_EPSILON;
  float x = 0.5374693001147223;
  float y = 1.123;
  EXPECT_TRUE(fpEqual(a[0], x, precision));
  a[0] = y;
  EXPECT_TRUE(fpEqual(a[0], y, precision));
}

TEST_F(Vec1Test, DotProduct) {
  float precision = FP_SP_EPSILON;
  float _x = 0.138529444551118;
  float _y = 0.288873248565809;
  float x = dot(a, b);
  EXPECT_TRUE(fpEqual(x, _x, precision));
  float y = dot(a, a);
  EXPECT_TRUE(fpEqual(y, _y, precision));  
}

TEST_F(Vec1Test, SquaredLength) {
  float precision = FP_SP_EPSILON;
  float _x = 0.288873248565809;
  float x = squaredLength(a);
  EXPECT_TRUE(fpEqual(x, _x, precision));
}

TEST_F(Vec1Test, Length) {
  float precision = FP_SP_EPSILON;
  float _x = 0.537469300114722;
  float x = length(a);
  EXPECT_TRUE(fpEqual(x, _x, precision));
}

TEST_F(Vec1Test, Normalize) {
  Vec1 _x = Vec1(1.0);
  Vec1 x = normalize(a);
  EXPECT_TRUE(x == _x);
}

TEST_F(Vec1Test, Distance) {
  float precision = FP_SP_EPSILON;
  float _x = 0.279725379631173;
  Vec1 v = b - a;
  float x = length(v);
  EXPECT_TRUE(fpEqual(x, _x, precision));
}

TEST_F(Vec1Test, Angle) {
  float precision = FP_SP_EPSILON;
  float _x = 0.0f;
  float x = angle(a, b);
  EXPECT_TRUE(fpEqual(x, _x, precision));
}
