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
 * $Id: GFXMath_Test.cpp 5487 2015-01-26 09:14:49Z mshafae $
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
  EXPECT_TRUE(fpEqual(0.2493981133863178f, (*f)[0], precision));
  
  EXPECT_EQ(1u, g->size());
  EXPECT_TRUE(fpEqual(0.4954117880655719f, (*g)[0], precision));
  
  delete g;
  
  g = new Vec1(f);
  
  EXPECT_EQ(1u, g->size());
  EXPECT_TRUE(fpEqual(0.2493981133863178f, (*g)[0], precision));
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


class Vec2Test : public testing::Test{
protected:
  virtual void SetUp( ){
    a = Vec2(0.311614220902166, 0.747756774429607);
    b = Vec2(0.864512059694352, 0.884741010953878);
    c = Vec2(0.366423681042827, 0.673356035859162);
    d = Vec2(0.721620478534571, 0.578209983216220);
    e = new Vec2(0.178987706239355, 0.570434306026590);
    f = new Vec2(0.759776941934895, 0.415749743654568);
    g = new Vec2(0.899931550870371, 0.100554788367090);
    h = new Vec2(0.385096025090437, 0.392850021448233);
  }
  virtual void TearDown( ){
    delete e;
    delete f;
    delete g;
    delete h;
  }
  Vec2 a, b, c, d;
  Vec2 *e, *f, *g, *h;
};

TEST_F(Vec2Test, Constructors) {
  float precision = FP_SP_EPSILON;
  EXPECT_EQ(2u, a.size());
  EXPECT_TRUE(fpEqual(0.311614220902166f, a[0], precision));
  EXPECT_TRUE(fpEqual(0.747756774429607f, a[1], precision));

  EXPECT_EQ(2u, b.size());
  EXPECT_TRUE(fpEqual(0.864512059694352f, b[0], precision));
  EXPECT_TRUE(fpEqual(0.884741010953878f, b[1], precision));

  b = Vec2(a);
  
  EXPECT_EQ(2u, b.size());
  EXPECT_TRUE(fpEqual(0.311614220902166f, b[0], precision));
  EXPECT_TRUE(fpEqual(0.747756774429607f, b[1], precision));
  
  EXPECT_EQ(2u, f->size());
  EXPECT_TRUE(fpEqual(0.759776941934895f, (*f)[0], precision));
  EXPECT_TRUE(fpEqual(0.415749743654568f, (*f)[1], precision));
  
  EXPECT_EQ(2u, g->size());
  EXPECT_TRUE(fpEqual(0.899931550870371f, (*g)[0], precision));
  EXPECT_TRUE(fpEqual(0.100554788367090f, (*g)[1], precision));
  
  delete g;
  
  g = new Vec2(f);
  
  EXPECT_EQ(2u, g->size());
  EXPECT_TRUE(fpEqual(0.759776941934895f, (*g)[0], precision));
  EXPECT_TRUE(fpEqual(0.415749743654568f, (*g)[1], precision));
}

TEST_F(Vec2Test, BooleanEquals) {
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

TEST_F(Vec2Test, BooleanNotEquals) {
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

TEST_F(Vec2Test, ArithmeticAddition) {
  Vec2 _x = Vec2(1.176126280596518, 1.632497785383486);
  Vec2 x = a + b;
  EXPECT_TRUE(x == _x);
  
  Vec2 _y = Vec2(0.623228441804331, 1.495513548859215);
  a += a;
  EXPECT_TRUE(a == _y);
}

TEST_F(Vec2Test, ArithmeticSubtraction) {
  Vec2 _x = Vec2(-0.552897838792186, -0.136984236524271);
  Vec2 x = a - b;
  EXPECT_TRUE(x == _x);
  
  Vec2 _y = Vec2(0.0, 0.0);
  a -= a;
  EXPECT_TRUE(a == _y);
  
  Vec2 _z = Vec2(0.498088378651525, 0.211384975094717);
  b -= c;
  EXPECT_TRUE(b == _z);
  
}

TEST_F(Vec2Test, ArithmeticMultiplication) {
  Vec2 _x = Vec2(0.349942770073132, 0.839730857684449);
  Vec2 x = a * 1.123;
  EXPECT_TRUE(x == _x);
  Vec2 y = 1.123f * a;
  EXPECT_TRUE(y == _x);
  a *= 1.123;
  EXPECT_TRUE(a == _x);
}

TEST_F(Vec2Test, ArithmeticDivision) {
  Vec2 _x = Vec2(0.146780132313785, 0.352217039297978);
  Vec2 _y = Vec2(6.812911149733879, 2.839158497252579);
  Vec2 x = a / 2.123f;
  EXPECT_TRUE(x == _x);
  Vec2 y = 2.123f / a;
  EXPECT_TRUE(y == _y);
  a /= 2.123;
  EXPECT_TRUE(_x == a);
}

TEST_F(Vec2Test, ArithmeticNegation) {
  Vec2 _x = Vec2(-0.311614220902166, -0.747756774429607);
  EXPECT_TRUE(_x == -a);
  Vec2 x = -a;
  EXPECT_TRUE(_x == x);
  x = -x;
  EXPECT_TRUE(a == x);
}

TEST_F(Vec2Test, BracketOperator) {
  float precision = FP_SP_EPSILON;
  float a1 = 0.311614220902166;
  float a2 = 0.747756774429607;
  float y = 1.123;
  EXPECT_TRUE(fpEqual(a[0], a1, precision));
  EXPECT_TRUE(fpEqual(a[1], a2, precision));
  a[0] = y;
  a[1] = y;
  EXPECT_TRUE(fpEqual(a[0], y, precision));
  EXPECT_TRUE(fpEqual(a[1], y, precision));
}

TEST_F(Vec2Test, DotProduct) {
  float precision = FP_SP_EPSILON;
  float _x = 0.930965336498644;
  float _y = 0.656243616373835;
  float x = dot(a, b);
  EXPECT_TRUE(fpEqual(x, _x, precision));
  float y = dot(a, a);
  EXPECT_TRUE(fpEqual(y, _y, precision));  
}

TEST_F(Vec2Test, SquaredLength) {
  float precision = FP_SP_EPSILON;
  float _x = 0.656243616373835;
  float x = squaredLength(a);
  EXPECT_TRUE(fpEqual(x, _x, precision));
}

TEST_F(Vec2Test, Length) {
  float precision = FP_SP_EPSILON;
  float _x = 0.810088647231792;
  float x = length(a);
  EXPECT_TRUE(fpEqual(x, _x, precision));
}

TEST_F(Vec2Test, Normalize) {
  Vec2 _x = Vec2(0.384666816362633, 0.923055491500612);
  Vec2 x = normalize(a);
  EXPECT_TRUE(x == _x);
}

TEST_F(Vec2Test, Distance) {
  float precision = FP_SP_EPSILON;
  float _x = 0.569614519826529;
  Vec2 v = b - a;
  float x = length(v);
  EXPECT_TRUE(fpEqual(x, _x, precision));
}

TEST_F(Vec2Test, Angle) {
  float precision = FP_SP_EPSILON;
  float _x = 0.378987504225326;
  float x = angleInRadians(a, b);
  EXPECT_TRUE(fpEqual(x, _x, precision));
}


class Vec3Test : public testing::Test{
protected:
  virtual void SetUp( ){
    a = Vec3(0.577030653156837, 0.464016202534924, 0.679106087611341);
    b = Vec3(0.738149043232649, 0.926337063215633, 0.714927181933456);
    c = Vec3(0.491486045834997, 0.018638374076204, 0.410554052105320);
    d = Vec3(0.063211644914916, 0.979947129362498, 0.656295868900335);
    e = new Vec3(0.482925842360389, 0.998345440877571, 0.300338709028279);
    f = new Vec3(0.709536553526954, 0.177644222044825, 0.651760642123328);
    g = new Vec3(0.136851337218809, 0.421710455193275, 0.640287931935240);
    h = new Vec3(0.811179570994577, 0.373749323570861, 0.194826096099051);
  }
  virtual void TearDown( ){
    delete e;
    delete f;
    delete g;
    delete h;
  }
  Vec3 a, b, c, d;
  Vec3 *e, *f, *g, *h;
};

TEST_F(Vec3Test, Constructors) {
  float precision = FP_SP_EPSILON;
  EXPECT_EQ(3u, a.size());
  EXPECT_TRUE(fpEqual(0.577030653156837f, a[0], precision));
  EXPECT_TRUE(fpEqual(0.464016202534924f, a[1], precision));
  EXPECT_TRUE(fpEqual(0.679106087611341f, a[2], precision));

  EXPECT_EQ(3u, b.size());
  EXPECT_TRUE(fpEqual(0.738149043232649f, b[0], precision));
  EXPECT_TRUE(fpEqual(0.926337063215633f, b[1], precision));
  EXPECT_TRUE(fpEqual(0.714927181933456f, b[2], precision));

  b = Vec3(a);
  
  EXPECT_EQ(3u, b.size());
  EXPECT_TRUE(fpEqual(0.577030653156837f, b[0], precision));
  EXPECT_TRUE(fpEqual(0.464016202534924f, b[1], precision));
  EXPECT_TRUE(fpEqual(0.679106087611341f, b[2], precision));
  
  EXPECT_EQ(3u, f->size());
  EXPECT_TRUE(fpEqual(0.709536553526954f, (*f)[0], precision));
  EXPECT_TRUE(fpEqual(0.177644222044825f, (*f)[1], precision));
  EXPECT_TRUE(fpEqual(0.651760642123328f, (*f)[2], precision));
  
  EXPECT_EQ(3u, g->size());
  EXPECT_TRUE(fpEqual(0.136851337218809f, (*g)[0], precision));
  EXPECT_TRUE(fpEqual(0.421710455193275f, (*g)[1], precision));
  EXPECT_TRUE(fpEqual(0.640287931935240f, (*g)[2], precision));
  
  delete g;
  
  g = new Vec3(f);
  
  EXPECT_EQ(3u, g->size());
  EXPECT_TRUE(fpEqual(0.709536553526954f, (*g)[0], precision));
  EXPECT_TRUE(fpEqual(0.177644222044825f, (*g)[1], precision));
  EXPECT_TRUE(fpEqual(0.651760642123328f, (*g)[2], precision));
}

TEST_F(Vec3Test, BooleanEquals) {
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

TEST_F(Vec3Test, BooleanNotEquals) {
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

TEST_F(Vec3Test, ArithmeticAddition) {
  Vec3 _x = Vec3(1.315179696389486, 1.390353265750557, 1.394033269544797);
  Vec3 x = a + b;
  EXPECT_TRUE(x == _x);
  
  Vec3 _y = Vec3(1.154061306313675, 0.928032405069848, 1.358212175222682);
  a += a;
  EXPECT_TRUE(a == _y);
}

TEST_F(Vec3Test, ArithmeticSubtraction) {
  Vec3 _x = Vec3(-0.161118390075811, -0.462320860680710, -0.035821094322115);
  Vec3 x = a - b;
  EXPECT_TRUE(x == _x);
  
  Vec3 _y = Vec3(0.0, 0.0, 0.0);
  a -= a;
  EXPECT_TRUE(a == _y);
  
  Vec3 _z = Vec3(0.246662997397651, 0.907698689139429, 0.304373129828136);
  b -= c;
  EXPECT_TRUE(b == _z);
  
}

TEST_F(Vec3Test, ArithmeticMultiplication) {
  Vec3 _x = Vec3(0.648005423495128, 0.521090195446719, 0.762636136387536);
  Vec3 x = a * 1.123;
  EXPECT_TRUE(x == _x);
  Vec3 y = 1.123f * a;
  EXPECT_TRUE(y == _x);
  a *= 1.123;
  EXPECT_TRUE(a == _x);
}

TEST_F(Vec3Test, ArithmeticDivision) {
  Vec3 _x = Vec3(0.271799648213301, 0.218566275334396, 0.319880399251691);
  Vec3 _y = Vec3(3.679180626515117, 4.575271269412655, 3.126168412754700);
  Vec3 x = a / 2.123f;
  EXPECT_TRUE(x == _x);
  Vec3 y = 2.123f / a;
  EXPECT_TRUE(y == _y);
  a /= 2.123;
  EXPECT_TRUE(_x == a);
}

TEST_F(Vec3Test, ArithmeticNegation) {
  Vec3 _x = Vec3(-0.577030653156837, -0.464016202534924, -0.679106087611341);
  EXPECT_TRUE(_x == -a);
  Vec3 x = -a;
  EXPECT_TRUE(_x == x);
  x = -x;
  EXPECT_TRUE(a == x);
}

TEST_F(Vec3Test, BracketOperator) {
  float precision = FP_SP_EPSILON;
  float a1 = 0.577030653156837;
  float a2 = 0.464016202534924;
  float a3 = 0.679106087611341;
  float y = 1.123;
  EXPECT_TRUE(fpEqual(a[0], a1, precision));
  EXPECT_TRUE(fpEqual(a[1], a2, precision));
  EXPECT_TRUE(fpEqual(a[2], a3, precision));
  a[0] = y;
  a[1] = y;
  a[2] = y;
  EXPECT_TRUE(fpEqual(a[0], y, precision));
  EXPECT_TRUE(fpEqual(a[1], y, precision));
  EXPECT_TRUE(fpEqual(a[2], y, precision));
}

TEST_F(Vec3Test, DotProduct) {
  float precision = FP_SP_EPSILON;
  float _x = 1.341281432334132;
  float _y = 1.009460489128320;
  float x = dot(a, b);
  EXPECT_TRUE(fpEqual(x, _x, precision));
  float y = dot(a, a);
  EXPECT_TRUE(fpEqual(y, _y, precision));  
}

TEST_F(Vec3Test, CrossProduct) {
  Vec3 _x = Vec3(-0.297343342759991, 0.088746610073140, 0.192011764685103);
  Vec3 _y = Vec3(0.297343342759991, -0.088746610073140, -0.192011764685103);
  Vec3 _z = Vec3(0.0, 0.0, 0.0);
  Vec3 x = cross(a, b);
  EXPECT_TRUE(x == _x);
  Vec3 y = cross(b, a);
  EXPECT_TRUE(y == _y);
  Vec3 z = cross(a, a);
  EXPECT_TRUE(z == _z);
}

TEST_F(Vec3Test, SquaredLength) {
  float precision = FP_SP_EPSILON;
  float _x = 1.009460489128320;
  float x = squaredLength(a);
  EXPECT_TRUE(fpEqual(x, _x, precision));
}

TEST_F(Vec3Test, Length) {
  float precision = FP_SP_EPSILON;
  float _x = 1.004719109566609;
  float x = length(a);
  EXPECT_TRUE(fpEqual(x, _x, precision));
}

TEST_F(Vec3Test, Normalize) {
  Vec3 _x = Vec3(0.574320372393178, 0.461836744336514, 0.675916364230672);
  Vec3 x = normalize(a);
  EXPECT_TRUE(x == _x);
}

TEST_F(Vec3Test, Distance) {
  float precision = FP_SP_EPSILON;
  float _x = 0.490900055652479;
  Vec3 v = b - a;
  float x = length(v);
  EXPECT_TRUE(fpEqual(x, _x, precision));
}

TEST_F(Vec3Test, Angle) {
  float precision = FP_SP_EPSILON;
  float _x = 0.265629863091071;
  float x = angleInRadians(a, b);
  EXPECT_TRUE(fpEqual(x, _x, precision));
}


class Vec4Test : public testing::Test{
protected:
  virtual void SetUp( ){
    a = Vec4(0.834624519997676, 0.050843905697752, 0.580656945524675, 0.209013864371992);
    b = Vec4(0.503136976949202, 0.502166404115286, 0.587205537155695, 0.750357447413078);
    c = Vec4(0.374022704953088, 0.204014819459926, 0.066809844479659, 0.466645746933968);
    d = Vec4(0.071401439320448, 0.793561052805261, 0.527665575465877, 0.225434676269768);
    e = new Vec4(0.589475414960220, 0.712903374137218, 0.097413994806303, 0.630330254130685);
    f = new Vec4(0.974145840503622, 0.981361844791386, 0.992332408791040, 0.659029395257233);
    g = new Vec4(0.260844623846239, 0.483605055383677, 0.206742305179194, 0.883800600069613);

    h = new Vec4(0.119199077335388, 0.357274934153236, 0.622028386236251, 0.653843755003646);
  }
  virtual void TearDown( ){
    delete e;
    delete f;
    delete g;
    delete h;
  }
  Vec4 a, b, c, d;
  Vec4 *e, *f, *g, *h;
};

TEST_F(Vec4Test, Constructors) {
  float precision = FP_SP_EPSILON;
  EXPECT_EQ(4u, a.size());
  EXPECT_TRUE(fpEqual(0.834624519997676f, a[0], precision));
  EXPECT_TRUE(fpEqual(0.050843905697752f, a[1], precision));
  EXPECT_TRUE(fpEqual(0.580656945524675f, a[2], precision));
  EXPECT_TRUE(fpEqual(0.209013864371992f, a[3], precision));

  EXPECT_EQ(4u, b.size());
  EXPECT_TRUE(fpEqual(0.503136976949202f, b[0], precision));
  EXPECT_TRUE(fpEqual(0.502166404115286f, b[1], precision));
  EXPECT_TRUE(fpEqual(0.587205537155695f, b[2], precision));
  EXPECT_TRUE(fpEqual(0.750357447413078f, b[3], precision));

  b = Vec4(a);
  
  EXPECT_EQ(4u, b.size());
  EXPECT_TRUE(fpEqual(0.834624519997676f, b[0], precision));
  EXPECT_TRUE(fpEqual(0.050843905697752f, b[1], precision));
  EXPECT_TRUE(fpEqual(0.580656945524675f, b[2], precision));
  EXPECT_TRUE(fpEqual(0.209013864371992f, b[3], precision));
  
  EXPECT_EQ(4u, f->size());
  EXPECT_TRUE(fpEqual(0.974145840503622f, (*f)[0], precision));
  EXPECT_TRUE(fpEqual(0.981361844791386f, (*f)[1], precision));
  EXPECT_TRUE(fpEqual(0.992332408791040f, (*f)[2], precision));
  EXPECT_TRUE(fpEqual(0.659029395257233f, (*f)[3], precision));
  
  EXPECT_EQ(4u, g->size());
  EXPECT_TRUE(fpEqual(0.260844623846239f, (*g)[0], precision));
  EXPECT_TRUE(fpEqual(0.483605055383677f, (*g)[1], precision));
  EXPECT_TRUE(fpEqual(0.206742305179194f, (*g)[2], precision));
  EXPECT_TRUE(fpEqual(0.883800600069613f, (*g)[3], precision));
  
  delete g;
  
  g = new Vec4(f);
  
  EXPECT_EQ(4u, g->size());
  EXPECT_TRUE(fpEqual(0.974145840503622f, (*g)[0], precision));
  EXPECT_TRUE(fpEqual(0.981361844791386f, (*g)[1], precision));
  EXPECT_TRUE(fpEqual(0.992332408791040f, (*g)[2], precision));
  EXPECT_TRUE(fpEqual(0.659029395257233f, (*g)[3], precision));
}


TEST_F(Vec4Test, BooleanEquals) {
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

TEST_F(Vec4Test, BooleanNotEquals) {
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

TEST_F(Vec4Test, ArithmeticAddition) {
  Vec4 _x = Vec4(1.337761496946878, 0.553010309813038, 1.167862482680371, 0.959371311785071);
  Vec4 x = a + b;
  EXPECT_TRUE(x == _x);
  
  Vec4 _y = Vec4(1.669249039995352, 0.101687811395504, 1.161313891049351, 0.418027728743985);
  a += a;
  EXPECT_TRUE(a == _y);
}

TEST_F(Vec4Test, ArithmeticSubtraction) {
  Vec4 _x = Vec4(0.331487543048474, -0.451322498417534, -0.006548591631020, -0.541343583041086);
  Vec4 x = a - b;
  EXPECT_TRUE(x == _x);
  
  Vec4 _y = Vec4(0.0, 0.0, 0.0, 0.0);
  a -= a;
  EXPECT_TRUE(a == _y);
  
  Vec4 _z = Vec4(0.129114271996114, 0.298151584655360, 0.520395692676037, 0.283711700479110);
  b -= c;
  EXPECT_TRUE(b == _z);
  
}

TEST_F(Vec4Test, ArithmeticMultiplication) {
  Vec4 _x = Vec4(0.937283335957390, 0.057097706098576, 0.652077749824210, 0.234722569689747);
  Vec4 x = a * 1.123;
  EXPECT_TRUE(x == _x);
  Vec4 y = 1.123f * a;
  EXPECT_TRUE(y == _x);
  a *= 1.123;
  EXPECT_TRUE(a == _x);
}

TEST_F(Vec4Test, ArithmeticDivision) {
  Vec4 _x = Vec4(0.393134488929664, 0.023949084172281, 0.273507746361128, 0.098452126411678);
  Vec4 _y = Vec4(2.543658794023823, 41.755250130083141, 3.656203574869290, 10.157220940241512);
  Vec4 x = a / 2.123f;
  EXPECT_TRUE(x == _x);
  Vec4 y = 2.123f / a;
  EXPECT_TRUE(y == _y);
  a /= 2.123;
  EXPECT_TRUE(_x == a);
}

TEST_F(Vec4Test, ArithmeticNegation) {
  Vec4 _x = Vec4(-0.834624519997676, -0.050843905697752, -0.580656945524675, -0.209013864371992);
  EXPECT_TRUE(_x == -a);
  Vec4 x = -a;
  EXPECT_TRUE(_x == x);
  x = -x;
  EXPECT_TRUE(a == x);
}

TEST_F(Vec4Test, BracketOperator) {
  float precision = FP_SP_EPSILON;
  float a1 = 0.834624519997676;
  float a2 = 0.050843905697752;
  float a3 = 0.580656945524675;
  float a4 = 0.209013864371992;
  float y = 1.123;
  EXPECT_TRUE(fpEqual(a[0], a1, precision));
  EXPECT_TRUE(fpEqual(a[1], a2, precision));
  EXPECT_TRUE(fpEqual(a[2], a3, precision));
  EXPECT_TRUE(fpEqual(a[3], a4, precision));
  a[0] = y;
  a[1] = y;
  a[2] = y;
  a[3] = y;
  EXPECT_TRUE(fpEqual(a[0], y, precision));
  EXPECT_TRUE(fpEqual(a[1], y, precision));
  EXPECT_TRUE(fpEqual(a[2], y, precision));
  EXPECT_TRUE(fpEqual(a[3], y, precision));
}

TEST_F(Vec4Test, DotProduct) {
  float precision = FP_SP_EPSILON;
  float _x = 0.943262642518840;
  float _y = 1.080032476013712;
  float x = dot(a, b);
  EXPECT_TRUE(fpEqual(x, _x, precision));
  float y = dot(a, a);
  EXPECT_TRUE(fpEqual(y, _y, precision));  
}

TEST_F(Vec4Test, SquaredLength) {
  float precision = FP_SP_EPSILON;
  float _x = 1.080032476013712;
  float x = squaredLength(a);
  EXPECT_TRUE(fpEqual(x, _x, precision));
}

TEST_F(Vec4Test, Length) {
  float precision = FP_SP_EPSILON;
  float _x = 1.039246109453248;
  float x = length(a);
  EXPECT_TRUE(fpEqual(x, _x, precision));
}

TEST_F(Vec4Test, Normalize) {
  Vec4 _x = Vec4(0.803105744063623, 0.048923835495041, 0.558729005808029, 0.201120660900964);
  Vec4 x = normalize(a);
  EXPECT_TRUE(x == _x);
}

TEST_F(Vec4Test, Distance) {
  float precision = FP_SP_EPSILON;
  float _x = 0.778891358102187;
  Vec4 v = b - a;
  float x = length(v);
  EXPECT_TRUE(fpEqual(x, _x, precision));
}

