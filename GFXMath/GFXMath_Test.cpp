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
 * $Id: GFXMath_Test.cpp 5509 2015-02-10 10:04:54Z mshafae $
 *
 */

// CC GFXMath_Test.cpp -I ~/local/TitanOpenGLKit_osx/include -L ~/local/TitanOpenGLKit_osx/lib -lgtest -lgtest_main -lstdc++

#include "GFXMath.h"

#include <gtest/gtest.h>

#ifdef __linux__
#ifdef minor
#undef minor
#endif
#endif

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

class Mat2Test : public testing::Test{
protected:
  virtual void SetUp( ){
    a = Mat2(0.880358922885829, 0.682275118878885, 0.353108932573495, 0.883563330818039);
    b = Mat2(0.288146198216614, 0.570632437638512, 0.708673748718465, 0.384173349743281);
    c = Mat2(0.804007112339474, 0.492588975464113, 0.907638188623635, 0.339646591861976);
    d = Mat2(0.899389547287570, 0.090016378915836, 0.999480757114313, 0.784475082365531);

  }
  virtual void TearDown( ){
  }
  Mat2 a, b, c, d;
};

TEST_F(Mat2Test, Constructors) {
  float precision = FP_SP_EPSILON;
  float x[4] = {1.0f, 2.0f, 3.0f, 4.0f};
  Vec2 v = Vec2(1.0f, 2.0f);

  EXPECT_EQ(2u, a.width());
  EXPECT_EQ(2u, a.height());
  EXPECT_EQ(a.width( ), a.height());  
  
  EXPECT_TRUE(fpEqual(0.880358922885829f, a(0, 0), precision));
  EXPECT_TRUE(fpEqual(0.682275118878885f, a(0, 1), precision));
  EXPECT_TRUE(fpEqual(0.353108932573495f, a(1, 0), precision));
  EXPECT_TRUE(fpEqual(0.883563330818039f, a(1, 1), precision));

  EXPECT_EQ(2u, b.width());
  EXPECT_EQ(2u, b.height());
  EXPECT_EQ(b.width( ), b.height());
  EXPECT_TRUE(fpEqual(0.288146198216614f, b(0, 0), precision));
  EXPECT_TRUE(fpEqual(0.570632437638512f, b(0, 1), precision));
  EXPECT_TRUE(fpEqual(0.708673748718465f, b(1, 0), precision));
  EXPECT_TRUE(fpEqual(0.384173349743281f, b(1, 1), precision));

  b = Mat2(a);
  EXPECT_EQ(2u, b.width());
  EXPECT_EQ(2u, b.height());
  EXPECT_TRUE(fpEqual(0.880358922885829f, b(0, 0), precision));
  EXPECT_TRUE(fpEqual(0.682275118878885f, b(0, 1), precision));
  EXPECT_TRUE(fpEqual(0.353108932573495f, b(1, 0), precision));
  EXPECT_TRUE(fpEqual(0.883563330818039f, b(1, 1), precision));
  
  c = Mat2(x);
  EXPECT_EQ(2u, c.width());
  EXPECT_EQ(2u, c.height());
  EXPECT_TRUE(fpEqual(1.0f, c(0, 0), precision));
  EXPECT_TRUE(fpEqual(2.0f, c(0, 1), precision));
  EXPECT_TRUE(fpEqual(3.0f, c(1, 0), precision));
  EXPECT_TRUE(fpEqual(4.0f, c(1, 1), precision));
  
  d = Mat2(v);
  EXPECT_EQ(2u, d.width());
  EXPECT_EQ(2u, d.height());
  EXPECT_TRUE(fpEqual(1.0f, d(0, 0), precision));
  EXPECT_TRUE(fpEqual(2.0f, d(0, 1), precision));
  EXPECT_TRUE(fpEqual(1.0f, d(1, 0), precision));
  EXPECT_TRUE(fpEqual(2.0f, d(1, 1), precision));
}

TEST_F(Mat2Test, Identity) {
  float precision = FP_SP_EPSILON;
  a.identity( );
  EXPECT_TRUE(fpEqual(1.0f, a(0, 0), precision));
  EXPECT_TRUE(fpEqual(0.0f, a(0, 1), precision));
  EXPECT_TRUE(fpEqual(0.0f, a(1, 0), precision));
  EXPECT_TRUE(fpEqual(1.0f, a(1, 1), precision));
}

TEST_F(Mat2Test, BooleanEquals) {
  EXPECT_FALSE(a == b);
  EXPECT_TRUE(a == a);
  a = b;
  EXPECT_TRUE(a == b);
}

TEST_F(Mat2Test, BooleanNotEquals) {
  EXPECT_TRUE(a != b);
  EXPECT_FALSE(a != a);
  a = b;
  EXPECT_FALSE(a != b);
}

TEST_F(Mat2Test, ArithmeticAddition) {
  Mat2 _x = Mat2(1.168505121102443, 1.252907556517397, 1.061782681291960, 1.267736680561320);
  Mat2 x = a + b;
  EXPECT_TRUE(x == _x);
  a += b;
  EXPECT_TRUE(a == _x);
}

TEST_F(Mat2Test, ArithmeticSubtraction) {
  Mat2 _x = Mat2(1.168505121102443, 1.252907556517397, 1.061782681291960, 1.267736680561320);
  Mat2 _y = Mat2(-0.095382434948096, 0.402572596548277, -0.091842568490678, -0.444828490503555);
  Mat2 z = _x - b;
  EXPECT_TRUE(z == a);
  Mat2 y = c - d;
  EXPECT_TRUE(_y == y);
  c -= d;
  EXPECT_TRUE(_y == c);
}

TEST_F(Mat2Test, ArithmeticMultiplication) {
  Mat2 _x = Mat2(0.455167487641971, 0.700784878915439, 0.759542299550285, 0.822951950663933);
  Mat2 _y = Mat2(2.749713059741600, 2.131018106306310, 1.102900440000054, 2.759721707477063);
  Mat2 x = a * b;
  EXPECT_TRUE(x == _x);
  Mat2 y = a * 3.1234f;
  EXPECT_TRUE(y == _y);
  Mat2 z = 3.1234f * a;
  EXPECT_TRUE(z == _y);
  a *= 3.1234f;
  EXPECT_TRUE(a == _y);
}

TEST_F(Mat2Test, ArithmeticDivision) {
  Mat2 _x = Mat2(0.281859167217081, 0.218439879259424, 0.113052741427129, 0.282885103034526);
  Mat2 x = a / 3.1234f;
  EXPECT_TRUE(x == _x);
  a /= 3.1234f;
  EXPECT_TRUE(a == _x);
}

TEST_F(Mat2Test, ArithmeticNegation) {
  Mat2 _x = Mat2(-0.880358922885829, -0.682275118878885, -0.353108932573495, -0.883563330818039);
  Mat2 x = -a;
  EXPECT_TRUE(x == _x);
}

TEST_F(Mat2Test, BracketOperator) {
  Vec2 a0 = Vec2(0.880358922885829, 0.682275118878885);
  Vec2 a1 = Vec2(0.353108932573495, 0.883563330818039);
  EXPECT_TRUE(a[0] == a0);
  EXPECT_TRUE(a[1] == a1);
}

TEST_F(Mat2Test, ParenthesesOperator) {
  float precision = FP_SP_EPSILON;
  float _x[4] = {0.288146198216614, 0.570632437638512, 0.708673748718465, 0.384173349743281};
  for(int i = 0; i < b.width( ); i++){
    for(int j = 0; j < b.height( ); j++){
      EXPECT_TRUE(fpEqual(_x[j + (i*b.height( ))], b(i, j), precision));
    }
  }
}

TEST_F(Mat2Test, ColumnOperator) {
  Vec2 b0 = Vec2(0.288146198216614, 0.570632437638512);
  Vec2 b1 = Vec2(0.708673748718465, 0.384173349743281);
  EXPECT_TRUE(b0 == b.column(0));
  EXPECT_TRUE(b1 == b.column(1));
}

TEST_F(Mat2Test, RowOperator) {
  Vec2 b0 = Vec2(0.288146198216614, 0.708673748718465);
  Vec2 b1 = Vec2(0.570632437638512, 0.384173349743281);
  EXPECT_TRUE(b0 == b.row(0));
  EXPECT_TRUE(b1 == b.row(1));
}

TEST_F(Mat2Test, Transpose) {
  Mat2 _x = Mat2(0.880358922885829, 0.353108932573495, 0.682275118878885, 0.883563330818039);
  Mat2 x = a.transpose( );
  EXPECT_TRUE(x == _x);
}

TEST_F(Mat2Test, Width) {
  EXPECT_EQ(2u, a.width( ));
}

TEST_F(Mat2Test, Height) {
  EXPECT_EQ(2u, a.height( ));
}

TEST_F(Mat2Test, Determinant) {
  float precision = FP_SP_EPSILON;
  float _x = 0.536935423271607;
  float x = a.determinant();
  EXPECT_TRUE(fpEqual(x, _x, precision));
}

TEST_F(Mat2Test, Minor) {
  float precision = FP_SP_EPSILON;
  float _x[4] = {0.384173349743281f, 0.708673748718465f, 0.570632437638512f, 0.288146198216614f};
  for(int i = 0; i < a.width( ); i++){
    for(int j = 0; j < a.width( ); j++){
      EXPECT_TRUE(fpEqual(_x[j + (i*a.width())], b.minor(i, j), precision));
    }
  }
}

TEST_F(Mat2Test, Cofactor) {
  float precision = FP_SP_EPSILON;
  float _x[4] = {0.384173349743281f, -0.708673748718465f, -0.570632437638512f, 0.288146198216614f};
  for(int i = 0; i < a.width( ); i++){
    for(int j = 0; j < a.width( ); j++){
      EXPECT_TRUE(fpEqual(_x[j + (i*a.width())], b.cofactor(i, j), precision));
    }
  }
}

TEST_F(Mat2Test, Adjugate) {
  Mat2 _x = Mat2(0.384173349743281, -0.570632437638512, -0.708673748718465, 0.288146198216614);
  Mat2 x = b.adjugate( );
  EXPECT_TRUE(x == _x);
  Mat2 _y = Mat2(0.883563330818039, -0.682275118878885, -0.353108932573495, 0.880358922885829);
  Mat2 y = a.adjugate( );
  EXPECT_TRUE(y == _y);
}

TEST_F(Mat2Test, Inverse) {
  Mat2 _x = Mat2(1.645567218184990, -1.270683753218789, -0.657637617615099, 1.639599260413300);
  Mat2 x = a.inverse( );
  EXPECT_TRUE(x == _x);
}


class Mat3Test : public testing::Test{
protected:
  virtual void SetUp( ){
    a = Mat3(0.842125654532024, 0.484983535051381, 0.357168713262517, 0.621388576319979, 0.645238963389842, 0.865476516397516, 0.003020818770662, 0.254631742873908, 0.976269230206023);
    b = Mat3(0.060250694944685, 0.685618893674015, 0.301362362334472, 0.919473566712991, 0.872067201822732, 0.024276286344370, 0.790531276275491, 0.882900144234350, 0.682695055616642);
    c = Mat3(0.580860340705153, 0.443140713356973, 0.987578347089206, 0.607372538134053, 0.871410666462068, 0.033782678011061, 0.194380379868822, 0.498305642718305, 0.169561002345617);
    d = Mat3(0.658444399411176, 0.961942289003968, 0.515337739650073, 0.255300884609911, 0.784066981771944, 0.385889075295614, 0.472045538845658, 0.454480055562960, 0.604069486776627);
  }
  virtual void TearDown( ){
  }
  Mat3 a, b, c, d;
};

TEST_F(Mat3Test, Constructors) {
  float precision = FP_SP_EPSILON;
  float x[9] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
  Vec3 v = Vec3(1.0f, 2.0f, 3.0f);

  //a = Mat3(0.842125654532024, 0.484983535051381, 0.357168713262517, 0.621388576319979, 0.645238963389842, 0.865476516397516, 0.003020818770662, 0.254631742873908, 0.976269230206023);
  //b = Mat3(0.060250694944685, 0.685618893674015, 0.301362362334472, 0.919473566712991, 0.872067201822732, 0.024276286344370, 0.790531276275491, 0.882900144234350, 0.682695055616642);

  EXPECT_EQ(3u, a.width());
  EXPECT_EQ(3u, a.height());
  EXPECT_EQ(a.width( ), a.height());  
  
  EXPECT_TRUE(fpEqual(0.842125654532024f, a(0, 0), precision));
  EXPECT_TRUE(fpEqual(0.484983535051381f, a(0, 1), precision));
  EXPECT_TRUE(fpEqual(0.357168713262517f, a(0, 2), precision));
  EXPECT_TRUE(fpEqual(0.621388576319979f, a(1, 0), precision));
  EXPECT_TRUE(fpEqual(0.645238963389842f, a(1, 1), precision));
  EXPECT_TRUE(fpEqual(0.865476516397516f, a(1, 2), precision));
  EXPECT_TRUE(fpEqual(0.003020818770662f, a(2, 0), precision));
  EXPECT_TRUE(fpEqual(0.254631742873908f, a(2, 1), precision));
  EXPECT_TRUE(fpEqual(0.976269230206023f, a(2, 2), precision));

  EXPECT_EQ(3u, b.width());
  EXPECT_EQ(3u, b.height());
  EXPECT_EQ(b.width( ), b.height());
  EXPECT_TRUE(fpEqual(0.060250694944685f, b(0, 0), precision));
  EXPECT_TRUE(fpEqual(0.685618893674015f, b(0, 1), precision));
  EXPECT_TRUE(fpEqual(0.301362362334472f, b(0, 2), precision));
  EXPECT_TRUE(fpEqual(0.919473566712991f, b(1, 0), precision));
  EXPECT_TRUE(fpEqual(0.872067201822732f, b(1, 1), precision));
  EXPECT_TRUE(fpEqual(0.024276286344370f, b(1, 2), precision));
  EXPECT_TRUE(fpEqual(0.790531276275491f, b(2, 0), precision));
  EXPECT_TRUE(fpEqual(0.882900144234350f, b(2, 1), precision));
  EXPECT_TRUE(fpEqual(0.682695055616642f, b(2, 2), precision));

  b = Mat3(a);
  EXPECT_EQ(3u, b.width());
  EXPECT_EQ(3u, b.height());
  EXPECT_TRUE(fpEqual(0.842125654532024f, b(0, 0), precision));
  EXPECT_TRUE(fpEqual(0.484983535051381f, b(0, 1), precision));
  EXPECT_TRUE(fpEqual(0.357168713262517f, b(0, 2), precision));
  EXPECT_TRUE(fpEqual(0.621388576319979f, b(1, 0), precision));
  EXPECT_TRUE(fpEqual(0.645238963389842f, b(1, 1), precision));
  EXPECT_TRUE(fpEqual(0.865476516397516f, b(1, 2), precision));
  EXPECT_TRUE(fpEqual(0.003020818770662f, b(2, 0), precision));
  EXPECT_TRUE(fpEqual(0.254631742873908f, b(2, 1), precision));
  EXPECT_TRUE(fpEqual(0.976269230206023f, b(2, 2), precision));
  
  c = Mat3(x);
  EXPECT_EQ(3u, c.width());
  EXPECT_EQ(3u, c.height());
  EXPECT_TRUE(fpEqual(1.0f, c(0, 0), precision));
  EXPECT_TRUE(fpEqual(2.0f, c(0, 1), precision));
  EXPECT_TRUE(fpEqual(3.0f, c(0, 2), precision));
  EXPECT_TRUE(fpEqual(4.0f, c(1, 0), precision));
  EXPECT_TRUE(fpEqual(5.0f, c(1, 1), precision));
  EXPECT_TRUE(fpEqual(6.0f, c(1, 2), precision));
  EXPECT_TRUE(fpEqual(7.0f, c(2, 0), precision));
  EXPECT_TRUE(fpEqual(8.0f, c(2, 1), precision));
  EXPECT_TRUE(fpEqual(9.0f, c(2, 2), precision));
  
  d = Mat3(v);
  EXPECT_EQ(3u, d.width());
  EXPECT_EQ(3u, d.height());
  EXPECT_TRUE(fpEqual(1.0f, d(0, 0), precision));
  EXPECT_TRUE(fpEqual(2.0f, d(0, 1), precision));
  EXPECT_TRUE(fpEqual(3.0f, d(0, 2), precision));
  EXPECT_TRUE(fpEqual(1.0f, d(1, 0), precision));
  EXPECT_TRUE(fpEqual(2.0f, d(1, 1), precision));
  EXPECT_TRUE(fpEqual(3.0f, d(1, 2), precision));
  EXPECT_TRUE(fpEqual(1.0f, d(2, 0), precision));
  EXPECT_TRUE(fpEqual(2.0f, d(2, 1), precision));
  EXPECT_TRUE(fpEqual(3.0f, d(2, 2), precision));
}

TEST_F(Mat3Test, Identity) {
  float precision = FP_SP_EPSILON;
  a.identity( );
  EXPECT_TRUE(fpEqual(1.0f, a(0, 0), precision));
  EXPECT_TRUE(fpEqual(0.0f, a(0, 1), precision));
  EXPECT_TRUE(fpEqual(0.0f, a(0, 2), precision));

  EXPECT_TRUE(fpEqual(0.0f, a(1, 0), precision));
  EXPECT_TRUE(fpEqual(1.0f, a(1, 1), precision));
  EXPECT_TRUE(fpEqual(0.0f, a(1, 2), precision));

  EXPECT_TRUE(fpEqual(0.0f, a(2, 0), precision));
  EXPECT_TRUE(fpEqual(0.0f, a(2, 1), precision));
  EXPECT_TRUE(fpEqual(1.0f, a(2, 2), precision));
}

TEST_F(Mat3Test, BooleanEquals) {
  EXPECT_FALSE(a == b);
  EXPECT_TRUE(a == a);
  a = b;
  EXPECT_TRUE(a == b);
}

TEST_F(Mat3Test, BooleanNotEquals) {
  EXPECT_TRUE(a != b);
  EXPECT_FALSE(a != a);
  a = b;
  EXPECT_FALSE(a != b);
}

TEST_F(Mat3Test, ArithmeticAddition) {
  Mat3 _x = Mat3(0.902376349476709, 1.170602428725396, 0.658531075596988, 1.540862143032969, 1.517306165212573, 0.889752802741887, 0.793552095046153, 1.137531887108258, 1.658964285822664);
  Mat3 x = a + b;
  EXPECT_TRUE(x == _x);
  a += b;
  EXPECT_TRUE(a == _x);
}

TEST_F(Mat3Test, ArithmeticSubtraction) {
  Mat3 _x = Mat3(0.902376349476709, 1.170602428725396, 0.658531075596988, 1.540862143032969, 1.517306165212573, 0.889752802741887, 0.793552095046153, 1.137531887108258, 1.658964285822664);
  Mat3 _y = Mat3(-0.077584058706023, -0.518801575646995, 0.472240607439134, 0.352071653524141, 0.087343684690123, -0.352106397284552, -0.277665158976836, 0.043825587155345, -0.434508484431010);
  Mat3 z = _x - b;
  EXPECT_TRUE(z == a);
  Mat3 y = c - d;
  EXPECT_TRUE(_y == y);
  c -= d;
  EXPECT_TRUE(_y == c);
}

TEST_F(Mat3Test, ArithmeticMultiplication) {
  Mat3 _x = Mat3(0.477684765235388, 0.548345042816112, 0.909117516349214, 1.316278210450517, 1.014802791183521, 1.106861065981523, 1.216413030158666, 1.126912058642347, 1.712976556312219);
  Mat3 _y = Mat3(2.630295269365323, 1.514797573379484, 1.115580759004145, 1.940845079277822, 2.015339378251833, 2.703229351316003, 0.009435225348284, 0.795316785692364, 3.049279313625492);
  Mat3 x = a * b;
  EXPECT_TRUE(x == _x);
  Mat3 y = a * 3.1234f;
  EXPECT_TRUE(y == _y);
  Mat3 z = 3.1234f * a;
  EXPECT_TRUE(z == _y);
  a *= 3.1234f;
  EXPECT_TRUE(a == _y);
}

TEST_F(Mat3Test, ArithmeticDivision) {
  Mat3 _x = Mat3(0.269618253996294, 0.155274231623033, 0.114352536742818, 0.198946204879291, 0.206582238390806, 0.277094357558275, 0.000967157191094, 0.081523897955404, 0.312566187553955);
  Mat3 x = a / 3.1234f;
  EXPECT_TRUE(x == _x);
  a /= 3.1234f;
  EXPECT_TRUE(a == _x);
}

TEST_F(Mat3Test, ArithmeticNegation) {
  Mat3 _x = Mat3(-0.842125654532024, -0.484983535051381, -0.357168713262517, -0.621388576319979, -0.645238963389842, -0.865476516397516, -0.003020818770662, -0.254631742873908, -0.976269230206023);
  Mat3 x = -a;
  EXPECT_TRUE(x == _x);
}

TEST_F(Mat3Test, BracketOperator) {
  Vec3 b0 = Vec3(0.060250694944685, 0.685618893674015, 0.301362362334472);
  Vec3 b1 = Vec3(0.919473566712991, 0.872067201822732, 0.024276286344370);
  Vec3 b2 = Vec3(0.790531276275491, 0.882900144234350, 0.682695055616642);
  EXPECT_TRUE(b[0] == b0);
  EXPECT_TRUE(b[1] == b1);
  EXPECT_TRUE(b[2] == b2);
}

TEST_F(Mat3Test, ParenthesesOperator) {
  float precision = FP_SP_EPSILON;
  float _x[9] = {0.060250694944685, 0.685618893674015, 0.301362362334472, 0.919473566712991, 0.872067201822732, 0.024276286344370, 0.790531276275491, 0.882900144234350, 0.682695055616642};

  for(int i = 0; i < b.width( ); i++){
    for(int j = 0; j < b.height( ); j++){
      EXPECT_TRUE(fpEqual(_x[j + (i*a.height( ))], b(i, j), precision));
    }
  }
}

TEST_F(Mat3Test, ColumnOperator) {
  Vec3 b0 = Vec3(0.060250694944685, 0.685618893674015, 0.301362362334472);
  Vec3 b1 = Vec3(0.919473566712991, 0.872067201822732, 0.024276286344370);
  Vec3 b2 = Vec3(0.790531276275491, 0.882900144234350, 0.682695055616642);
  EXPECT_TRUE(b0 == b.column(0));
  EXPECT_TRUE(b1 == b.column(1));
  EXPECT_TRUE(b2 == b.column(2));
}

TEST_F(Mat3Test, RowOperator) {
  Vec3 b0 = Vec3(0.060250694944685, 0.919473566712991, 0.790531276275491);
  Vec3 b1 = Vec3(0.685618893674015, 0.872067201822732, 0.882900144234350);
  Vec3 b2 = Vec3(0.301362362334472, 0.024276286344370, 0.682695055616642);
  EXPECT_TRUE(b0 == b.row(0));
  EXPECT_TRUE(b1 == b.row(1));
  EXPECT_TRUE(b2 == b.row(2));
}

TEST_F(Mat3Test, Transpose) {
  Mat3 _x = Mat3(0.842125654532024, 0.621388576319979, 0.003020818770662, 0.484983535051381, 0.645238963389842, 0.254631742873908, 0.357168713262517, 0.865476516397516, 0.976269230206023);
  Mat3 x = a.transpose( );
  EXPECT_TRUE(x == _x);
}

TEST_F(Mat3Test, Width) {
  EXPECT_EQ(3u, a.width( ));
}

TEST_F(Mat3Test, Height) {
  EXPECT_EQ(3u, a.height( ));
}

TEST_F(Mat3Test, Determinant) {
  float precision = FP_SP_EPSILON;
  float _x = 0.107765100819701f;
  float x = a.determinant();
  EXPECT_TRUE(fpEqual(x, _x, precision));
}

TEST_F(Mat3Test, Minor) {
  float precision = FP_SP_EPSILON;
  Mat2 minor00 = Mat2(0.872067201822732, 0.024276286344370, 0.882900144234350, 0.682695055616642);
  Mat2 minor11 = Mat2(0.060250694944685, 0.301362362334472, 0.790531276275491, 0.682695055616642);
  Mat2 minor22 = Mat2(0.060250694944685, 0.685618893674015, 0.919473566712991, 0.872067201822732);
  Mat2 minor01 = Mat2(0.919473566712991, 0.024276286344370, 0.790531276275491, 0.682695055616642);
  EXPECT_TRUE(fpEqual(minor00.determinant( ), b.minor(0, 0), precision));
  EXPECT_TRUE(fpEqual(minor11.determinant( ), b.minor(1, 1), precision));
  EXPECT_TRUE(fpEqual(minor22.determinant( ), b.minor(2, 2), precision));
  EXPECT_TRUE(fpEqual(minor01.determinant( ), b.minor(0, 1), precision));
  
}

TEST_F(Mat3Test, Cofactor) {
  float precision = FP_SP_EPSILON;
  Mat3 _x = Mat3(0.409549152300795, -0.604028099356422, 0.156276106218122, -0.382528010469142, 0.821062422533405, -0.212966875766174, 0.189282690125632, -0.506899419613120, 0.242009055990027);
  for(int i = 0; i < a.width( ); i++){
    for(int j = 0; j < a.height( ); j++){
      EXPECT_TRUE(fpEqual(_x(i, j), a.cofactor(i, j), precision));
    }
  }
}

TEST_F(Mat3Test, Adjugate) {
  Mat3 _x = Mat3(0.573922430134900, -0.201995755576692, -0.246163951469770, -0.608528894138113, -0.197103521381464, 0.275632063045805, 0.122406946615652, 0.488807831797827, -0.577865794623974);
  Mat3 x = b.adjugate( );
  EXPECT_TRUE(x == _x);
  Mat3 _y = Mat3(0.409549152300795, -0.382528010469142, 0.189282690125632, -0.604028099356422, 0.821062422533405, -0.506899419613120, 0.156276106218122, -0.212966875766175, 0.242009055990027);
  Mat3 y = a.adjugate( );
  EXPECT_TRUE(y == _y);
}

TEST_F(Mat3Test, Inverse) {
  Mat3 _x = Mat3(3.800387594737184, -3.549646477008712, 1.756437739916519, -5.605043699323430, 7.619001107854946, -4.703743751524887, 1.450155059749660, -1.976213766296039, 2.245708992514422);
  Mat3 x = a.inverse( );
  EXPECT_TRUE(x == _x);
}


class Mat4Test : public testing::Test{
protected:
  virtual void SetUp( ){
    a = Mat4(0.058120829490961, 0.989326706866099, 0.560703439525482, 0.495655370417660, 0.857383152383918, 0.192912345499827, 0.225121529295245, 0.058515863343299, 0.495799431505282, 0.820084041371975, 0.546981316381792, 0.950742413167854, 0.071335749243603, 0.234336617703252, 0.668396486135691, 0.905442111689215);
    b = Mat4(0.921807489334157, 0.435920408953311, 0.310855399051072, 0.594009770536273, 0.469280098873301, 0.046980236441550, 0.165304353089263, 0.576811056008023, 0.426346591318460, 0.503460249877643, 0.421206444174116, 0.581716309800515, 0.071620524912970, 0.696627130178135, 0.514617948719614, 0.456559107903559);
    c = Mat4(0.468089988876607, 0.404029315038635, 0.017100394948367, 0.232886005964266, 0.011703848578218, 0.099984604997189, 0.401446723116248, 0.505336274275201, 0.750913052016802, 0.237974356796178, 0.019381867257071, 0.068233351955908, 0.138316486825267, 0.905442636297074, 0.192798665173080, 0.809313664575976);
    d = Mat4(0.546747808023118, 0.601646209015349, 0.788383461168056, 0.563799476640942, 0.225087220093038, 0.334387220607532, 0.416584609092056, 0.200058565905639, 0.794479984702399, 0.014462212845049, 0.732291954284845, 0.826124979786399, 0.430512776440935, 0.728698208563377, 0.279151498472583, 0.860026431197785);

  }
  virtual void TearDown( ){
  }
  Mat4 a, b, c, d;
};

TEST_F(Mat4Test, Constructors) {
  float precision = FP_SP_EPSILON;
  float x[16] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
  Vec4 v = Vec4(1.0f, 2.0f, 3.0f, 4.0f);

  EXPECT_EQ(4u, a.width());
  EXPECT_EQ(4u, a.height());
  EXPECT_EQ(a.width( ), a.height());  
  
  a = Mat4(0.058120829490961, 0.989326706866099, 0.560703439525482, 0.495655370417660, 0.857383152383918, 0.192912345499827, 0.225121529295245, 0.058515863343299, 0.495799431505282, 0.820084041371975, 0.546981316381792, 0.950742413167854, 0.071335749243603, 0.234336617703252, 0.668396486135691, 0.905442111689215);
  
  EXPECT_TRUE(fpEqual(0.058120829490961f, a(0, 0), precision));
  EXPECT_TRUE(fpEqual(0.989326706866099f, a(0, 1), precision));
  EXPECT_TRUE(fpEqual(0.560703439525482f, a(0, 2), precision));
  EXPECT_TRUE(fpEqual(0.495655370417660f, a(0, 3), precision));
  EXPECT_TRUE(fpEqual(0.857383152383918f, a(1, 0), precision));
  EXPECT_TRUE(fpEqual(0.192912345499827f, a(1, 1), precision));
  EXPECT_TRUE(fpEqual(0.225121529295245f, a(1, 2), precision));
  EXPECT_TRUE(fpEqual(0.058515863343299f, a(1, 3), precision));
  EXPECT_TRUE(fpEqual(0.495799431505282f, a(2, 0), precision));
  EXPECT_TRUE(fpEqual(0.820084041371975f, a(2, 1), precision));
  EXPECT_TRUE(fpEqual(0.546981316381792f, a(2, 2), precision));
  EXPECT_TRUE(fpEqual(0.950742413167854f, a(2, 3), precision));
  EXPECT_TRUE(fpEqual(0.071335749243603f, a(3, 0), precision));
  EXPECT_TRUE(fpEqual(0.234336617703252f, a(3, 1), precision));
  EXPECT_TRUE(fpEqual(0.668396486135691f, a(3, 2), precision));
  EXPECT_TRUE(fpEqual(0.905442111689215f, a(3, 3), precision));

  //b = Mat4(0.921807489334157, 0.435920408953311, 0.310855399051072, 0.594009770536273, 
  // 0.469280098873301, 0.046980236441550, 0.165304353089263, 0.576811056008023, 
  // 0.426346591318460, 0.503460249877643, 0.421206444174116, 0.581716309800515, 
  // 0.071620524912970, 0.696627130178135, 0.514617948719614, 0.456559107903559);

  EXPECT_EQ(4u, b.width());
  EXPECT_EQ(4u, b.height());
  EXPECT_EQ(b.width( ), b.height());
  EXPECT_TRUE(fpEqual(0.921807489334157f, b(0, 0), precision));
  EXPECT_TRUE(fpEqual(0.435920408953311f, b(0, 1), precision));
  EXPECT_TRUE(fpEqual(0.310855399051072f, b(0, 2), precision));
  EXPECT_TRUE(fpEqual(0.594009770536273f, b(0, 3), precision));
  EXPECT_TRUE(fpEqual(0.469280098873301f, b(1, 0), precision));
  EXPECT_TRUE(fpEqual(0.046980236441550f, b(1, 1), precision));
  EXPECT_TRUE(fpEqual(0.165304353089263f, b(1, 2), precision));
  EXPECT_TRUE(fpEqual(0.576811056008023f, b(1, 3), precision));
  EXPECT_TRUE(fpEqual(0.426346591318460f, b(2, 0), precision));
  EXPECT_TRUE(fpEqual(0.503460249877643f, b(2, 1), precision));
  EXPECT_TRUE(fpEqual(0.421206444174116f, b(2, 2), precision));
  EXPECT_TRUE(fpEqual(0.581716309800515f, b(2, 3), precision));
  EXPECT_TRUE(fpEqual(0.071620524912970f, b(3, 0), precision));
  EXPECT_TRUE(fpEqual(0.696627130178135f, b(3, 1), precision));
  EXPECT_TRUE(fpEqual(0.514617948719614f, b(3, 2), precision));
  EXPECT_TRUE(fpEqual(0.456559107903559f, b(3, 3), precision));

  b = Mat4(a);
  EXPECT_EQ(4u, b.width());
  EXPECT_EQ(4u, b.height());
  EXPECT_TRUE(fpEqual(0.058120829490961f, b(0, 0), precision));
  EXPECT_TRUE(fpEqual(0.989326706866099f, b(0, 1), precision));
  EXPECT_TRUE(fpEqual(0.560703439525482f, b(0, 2), precision));
  EXPECT_TRUE(fpEqual(0.495655370417660f, b(0, 3), precision));
  EXPECT_TRUE(fpEqual(0.857383152383918f, b(1, 0), precision));
  EXPECT_TRUE(fpEqual(0.192912345499827f, b(1, 1), precision));
  EXPECT_TRUE(fpEqual(0.225121529295245f, b(1, 2), precision));
  EXPECT_TRUE(fpEqual(0.058515863343299f, b(1, 3), precision));
  EXPECT_TRUE(fpEqual(0.495799431505282f, b(2, 0), precision));
  EXPECT_TRUE(fpEqual(0.820084041371975f, b(2, 1), precision));
  EXPECT_TRUE(fpEqual(0.546981316381792f, b(2, 2), precision));
  EXPECT_TRUE(fpEqual(0.950742413167854f, b(2, 3), precision));
  EXPECT_TRUE(fpEqual(0.071335749243603f, b(3, 0), precision));
  EXPECT_TRUE(fpEqual(0.234336617703252f, b(3, 1), precision));
  EXPECT_TRUE(fpEqual(0.668396486135691f, b(3, 2), precision));
  EXPECT_TRUE(fpEqual(0.905442111689215f, b(3, 3), precision));

  c = Mat4(x);
  EXPECT_EQ(4u, c.width());
  EXPECT_EQ(4u, c.height());
  EXPECT_TRUE(fpEqual(1.0f, c(0, 0), precision));
  EXPECT_TRUE(fpEqual(2.0f, c(0, 1), precision));
  EXPECT_TRUE(fpEqual(3.0f, c(0, 2), precision));
  EXPECT_TRUE(fpEqual(4.0f, c(0, 3), precision));
  EXPECT_TRUE(fpEqual(5.0f, c(1, 0), precision));
  EXPECT_TRUE(fpEqual(6.0f, c(1, 1), precision));
  EXPECT_TRUE(fpEqual(7.0f, c(1, 2), precision));
  EXPECT_TRUE(fpEqual(8.0f, c(1, 3), precision));
  EXPECT_TRUE(fpEqual(9.0f, c(2, 0), precision));
  EXPECT_TRUE(fpEqual(10.0f, c(2, 1), precision));
  EXPECT_TRUE(fpEqual(11.0f, c(2, 2), precision));
  EXPECT_TRUE(fpEqual(12.0f, c(2, 3), precision));
  EXPECT_TRUE(fpEqual(13.0f, c(3, 0), precision));
  EXPECT_TRUE(fpEqual(14.0f, c(3, 1), precision));
  EXPECT_TRUE(fpEqual(15.0f, c(3, 2), precision));
  EXPECT_TRUE(fpEqual(16.0f, c(3, 3), precision));

  d = Mat4(v);
  EXPECT_EQ(4u, d.width());
  EXPECT_EQ(4u, d.height());
  EXPECT_TRUE(fpEqual(1.0f, d(0, 0), precision));
  EXPECT_TRUE(fpEqual(2.0f, d(0, 1), precision));
  EXPECT_TRUE(fpEqual(3.0f, d(0, 2), precision));
  EXPECT_TRUE(fpEqual(4.0f, d(0, 3), precision));
  EXPECT_TRUE(fpEqual(1.0f, d(1, 0), precision));
  EXPECT_TRUE(fpEqual(2.0f, d(1, 1), precision));
  EXPECT_TRUE(fpEqual(3.0f, d(1, 2), precision));
  EXPECT_TRUE(fpEqual(4.0f, d(1, 3), precision));
  EXPECT_TRUE(fpEqual(1.0f, d(2, 0), precision));
  EXPECT_TRUE(fpEqual(2.0f, d(2, 1), precision));
  EXPECT_TRUE(fpEqual(3.0f, d(2, 2), precision));
  EXPECT_TRUE(fpEqual(4.0f, d(3, 3), precision));
  EXPECT_TRUE(fpEqual(1.0f, d(3, 0), precision));
  EXPECT_TRUE(fpEqual(2.0f, d(3, 1), precision));
  EXPECT_TRUE(fpEqual(3.0f, d(3, 2), precision));
  EXPECT_TRUE(fpEqual(4.0f, d(3, 3), precision));
}

TEST_F(Mat4Test, Identity) {
  float precision = FP_SP_EPSILON;
  a.identity( );
  EXPECT_TRUE(fpEqual(1.0f, a(0, 0), precision));
  EXPECT_TRUE(fpEqual(0.0f, a(0, 1), precision));
  EXPECT_TRUE(fpEqual(0.0f, a(0, 2), precision));
  EXPECT_TRUE(fpEqual(0.0f, a(0, 3), precision));

  EXPECT_TRUE(fpEqual(0.0f, a(1, 0), precision));
  EXPECT_TRUE(fpEqual(1.0f, a(1, 1), precision));
  EXPECT_TRUE(fpEqual(0.0f, a(1, 2), precision));
  EXPECT_TRUE(fpEqual(0.0f, a(1, 3), precision));

  EXPECT_TRUE(fpEqual(0.0f, a(2, 0), precision));
  EXPECT_TRUE(fpEqual(0.0f, a(2, 1), precision));
  EXPECT_TRUE(fpEqual(1.0f, a(2, 2), precision));
  EXPECT_TRUE(fpEqual(0.0f, a(2, 3), precision));

  EXPECT_TRUE(fpEqual(0.0f, a(3, 0), precision));
  EXPECT_TRUE(fpEqual(0.0f, a(3, 1), precision));
  EXPECT_TRUE(fpEqual(0.0f, a(3, 2), precision));
  EXPECT_TRUE(fpEqual(1.0f, a(3, 3), precision));
}

TEST_F(Mat4Test, BooleanEquals) {
  EXPECT_FALSE(a == b);
  EXPECT_TRUE(a == a);
  a = b;
  EXPECT_TRUE(a == b);
}

TEST_F(Mat4Test, BooleanNotEquals) {
  EXPECT_TRUE(a != b);
  EXPECT_FALSE(a != a);
  a = b;
  EXPECT_FALSE(a != b);
}

TEST_F(Mat4Test, ArithmeticAddition) {
  Mat4 _x = Mat4(0.979928318825118, 1.425247115819410, 0.871558838576553, 1.089665140953934, 1.326663251257219, 0.239892581941377, 0.390425882384509, 0.635326919351322, 0.922146022823742, 1.323544291249618, 0.968187760555908, 1.532458722968369, 0.142956274156573, 0.930963747881387, 1.183014434855305, 1.362001219592774);
  Mat4 x = a + b;
  EXPECT_TRUE(x == _x);
  a += b;
  EXPECT_TRUE(a == _x);
}

TEST_F(Mat4Test, ArithmeticSubtraction) {
  Mat4 _x = Mat4(0.979928318825118, 1.425247115819410, 0.871558838576553, 1.089665140953934, 1.326663251257219, 0.239892581941377, 0.390425882384509, 0.635326919351322, 0.922146022823742, 1.323544291249618, 0.968187760555908, 1.532458722968369, 0.142956274156573, 0.930963747881387, 1.183014434855305, 1.362001219592774);
  Mat4 _y = Mat4(-0.078657819146511, -0.197616893976715, -0.771283066219689, -0.330913470676677, -0.213383371514821, -0.234402615610342, -0.015137885975808, 0.305277708369562, -0.043566932685597, 0.223512143951129, -0.712910087027774, -0.757891627830491, -0.292196289615669, 0.176744427733697, -0.086352833299503, -0.050712766621810);
  Mat4 z = _x - b;
  EXPECT_TRUE(z == a);
  Mat4 y = c - d;
  EXPECT_TRUE(_y == y);
  c -= d;
  EXPECT_TRUE(_y == c);
}

TEST_F(Mat4Test, ArithmeticMultiplication) {
  Mat4 _x = Mat4(0.623823092497053, 1.390188988776151, 1.182061837698644, 1.315791964897023, 0.190660064969446, 0.744065816276781, 0.749660103869878, 0.914781170492959, 0.706769038052893, 1.000661882334202, 0.971602934275384, 1.167950663952667, 0.889155281678702, 0.734262555953918, 0.783632546013919, 0.978919788952303);
  Mat4 _y = Mat4(0.181534598832067, 3.090063036225575, 1.751301123013890, 1.548129983962520, 2.677950538155930, 0.602542419934158, 0.703144584600769, 0.182768447566460, 1.548579944363598, 2.561450494821226, 1.708441443586890, 2.969548853288476, 0.222810079187470, 0.731926991734338, 2.087669584796218, 2.828057891650094);
  Mat4 x = a * b;
  EXPECT_TRUE(x == _x);
  Mat4 y = a * 3.1234f;
  EXPECT_TRUE(y == _y);
  Mat4 z = 3.1234f * a;
  EXPECT_TRUE(z == _y);
  a *= 3.1234f;
  EXPECT_TRUE(a == _y);
}

TEST_F(Mat4Test, ArithmeticDivision) {
  Mat4 _x = Mat4(0.018608192831837, 0.316746720518057, 0.179517013358994, 0.158690968309426, 0.274503154377895, 0.061763573509581, 0.072075792180075, 0.018734668420087, 0.158737091472524, 0.262561324637246, 0.175123684568673, 0.304393421645596, 0.022839133394251, 0.075026131044135, 0.213996441741593, 0.289889899369026);
  Mat4 x = a / 3.1234f;
  EXPECT_TRUE(x == _x);
  a /= 3.1234f;
  EXPECT_TRUE(a == _x);
}

TEST_F(Mat4Test, ArithmeticNegation) {
  Mat4 _x = Mat4(-0.058120829490961, -0.989326706866099, -0.560703439525482, -0.495655370417660, -0.857383152383918, -0.192912345499827, -0.225121529295245, -0.058515863343299, -0.495799431505282, -0.820084041371975, -0.546981316381792, -0.950742413167854, -0.071335749243603, -0.234336617703252, -0.668396486135691, -0.905442111689215);
  Mat4 x = -a;
  EXPECT_TRUE(x == _x);
}

TEST_F(Mat4Test, BracketOperator) {
  Vec4 b0 = Vec4(0.921807489334157, 0.435920408953311, 0.310855399051072, 0.594009770536273);
  Vec4 b1 = Vec4(0.469280098873301, 0.046980236441550, 0.165304353089263, 0.576811056008023);
  Vec4 b2 = Vec4(0.426346591318460, 0.503460249877643, 0.421206444174116, 0.581716309800515);
  Vec4 b3 = Vec4(0.071620524912970, 0.696627130178135, 0.514617948719614, 0.456559107903559);
  EXPECT_TRUE(b[0] == b0);
  EXPECT_TRUE(b[1] == b1);
  EXPECT_TRUE(b[2] == b2);
  EXPECT_TRUE(b[3] == b3);
}

TEST_F(Mat4Test, ParenthesesOperator) {
  float precision = FP_SP_EPSILON;  
  float _x[16] = {0.921807489334157, 0.435920408953311, 0.310855399051072, 0.594009770536273, 0.469280098873301, 0.046980236441550, 0.165304353089263, 0.576811056008023, 0.426346591318460, 0.503460249877643, 0.421206444174116, 0.581716309800515, 0.071620524912970, 0.696627130178135, 0.514617948719614, 0.456559107903559};
  for(int i = 0; i < b.width( ); i++){
    for(int j = 0; j < b.height( ); j++){
      EXPECT_TRUE(fpEqual(_x[j + (i*a.height( ))], b(i, j), precision));
    }
  }
}

TEST_F(Mat4Test, ColumnOperator) {
  Vec4 b0 = Vec4(0.921807489334157, 0.435920408953311, 0.310855399051072, 0.594009770536273);
  Vec4 b1 = Vec4(0.469280098873301, 0.046980236441550, 0.165304353089263, 0.576811056008023);
  Vec4 b2 = Vec4(0.426346591318460, 0.503460249877643, 0.421206444174116, 0.581716309800515);
  Vec4 b3 = Vec4(0.071620524912970, 0.696627130178135, 0.514617948719614, 0.456559107903559);
  EXPECT_TRUE(b0 == b.column(0));
  EXPECT_TRUE(b1 == b.column(1));
  EXPECT_TRUE(b2 == b.column(2));
  EXPECT_TRUE(b3 == b.column(3));
}

TEST_F(Mat4Test, RowOperator) {
  Vec4 b0 = Vec4(0.921807489334157, 0.469280098873301, 0.426346591318460, 0.071620524912970);
  Vec4 b1 = Vec4(0.435920408953311, 0.046980236441550, 0.503460249877643, 0.696627130178135);
  Vec4 b2 = Vec4(0.310855399051072, 0.165304353089263, 0.421206444174116, 0.514617948719614);
  Vec4 b3 = Vec4(0.594009770536273, 0.576811056008023, 0.581716309800515, 0.456559107903559);
  EXPECT_TRUE(b0 == b.row(0));
  EXPECT_TRUE(b1 == b.row(1));
  EXPECT_TRUE(b2 == b.row(2));
  EXPECT_TRUE(b3 == b.row(3));
}

TEST_F(Mat4Test, Transpose) {
  Mat4 _x = Mat4(0.058120829490961, 0.857383152383918, 0.495799431505282, 0.071335749243603, 0.989326706866099, 0.192912345499827, 0.820084041371975, 0.234336617703252, 0.560703439525482, 0.225121529295245, 0.546981316381792, 0.668396486135691, 0.495655370417660, 0.058515863343299, 0.950742413167854, 0.905442111689215);
  Mat4 x = a.transpose( );
  EXPECT_TRUE(x == _x);
}

TEST_F(Mat4Test, Width) {
  EXPECT_EQ(4u, a.width( ));
}

TEST_F(Mat4Test, Height) {
  EXPECT_EQ(4u, a.height( ));
}

TEST_F(Mat4Test, Determinant) {
  float precision = FP_SP_EPSILON;
  float _x = 0.233521062628353f;
  float x = a.determinant();
  EXPECT_TRUE(fpEqual(x, _x, precision));
}

TEST_F(Mat4Test, Minor) {  
  float precision = FP_SP_EPSILON;
  Mat3 minor00 = Mat3(0.046980236441550, 0.165304353089263, 0.576811056008023, 0.503460249877643, 0.421206444174116, 0.581716309800515, 0.696627130178135, 0.514617948719614, 0.456559107903559);
  Mat3 minor11 = Mat3(0.921807489334157, 0.310855399051072, 0.594009770536273, 0.426346591318460, 0.421206444174116, 0.581716309800515, 0.071620524912970, 0.514617948719614, 0.456559107903559);
  Mat3 minor22 = Mat3(0.921807489334157, 0.435920408953311, 0.594009770536273, 0.469280098873301, 0.046980236441550, 0.576811056008023, 0.071620524912970, 0.696627130178135, 0.456559107903559);
  Mat3 minor01 = Mat3(0.469280098873301, 0.165304353089263, 0.576811056008023, 0.426346591318460, 0.421206444174116, 0.581716309800515, 0.071620524912970, 0.514617948719614, 0.456559107903559);
  EXPECT_TRUE(fpEqual(minor00.determinant( ), b.minor(0, 0), precision));
  EXPECT_TRUE(fpEqual(minor11.determinant( ), b.minor(1, 1), precision));
  EXPECT_TRUE(fpEqual(minor22.determinant( ), b.minor(2, 2), precision));
  EXPECT_TRUE(fpEqual(minor01.determinant( ), b.minor(0, 1), precision));
}

TEST_F(Mat4Test, Cofactor) {
  float precision = FP_SP_EPSILON;
  Mat4 _x = Mat4(-0.119480042604160, 0.188900741338274, 0.375477763514944, -0.316653242103577, 0.221981985284991, -0.076915605568049, 0.318229496018283, -0.232499220642703, 0.110477418538022, 0.147279469438711, -0.661776012179504, 0.441701124605566, -0.064945190292525, -0.253084895303282, 0.468775942334813, -0.017524210153140);
  for(int i = 0; i < a.width( ); i++){
    for(int j = 0; j < a.height( ); j++){
      EXPECT_TRUE(fpEqual(_x(i, j), a.cofactor(i, j), precision));
    }
  }
}

TEST_F(Mat4Test, Adjugate) {
  Mat4 _x = Mat4(0.004157240255617, 0.012544905716867, -0.032299205655067, 0.019895546757337, -0.033625802960818, -0.033833111236516, 0.121396335224407, -0.068181445709759, 0.061027003503540, 0.073353104313885, -0.233828893683897, 0.125855693721607, -0.018132785720291, -0.033025808400140, 0.083401799244785, -0.046701424082839);
  Mat4 x = b.adjugate( );
  EXPECT_TRUE(x == _x);
  Mat4 _y = Mat4(-0.119480042604160, 0.221981985284991, 0.110477418538021, -0.064945190292525, 0.188900741338274, -0.076915605568049, 0.147279469438711, -0.253084895303281, 0.375477763514944, 0.318229496018283, -0.661776012179504, 0.468775942334812, -0.316653242103577, -0.232499220642703, 0.441701124605566, -0.017524210153140);
  Mat4 y = a.adjugate( );
  EXPECT_TRUE(y == _y);
}

TEST_F(Mat4Test, Inverse) {
  Mat4 _x = Mat4(-0.511645678806762, 0.950586567166633, 0.473094021132669, -0.278112773047305, 0.808923782772041, -0.329373310922533, 0.630690301684284, -1.083777593570066, 1.607896775086679, 1.362744295681554, -2.833902881097773, 2.007424671070742, -1.355994352456027, -0.995624197774073, 1.891483019279206, -0.075043381337422);
  Mat4 x = a.inverse( );
  EXPECT_TRUE(x == _x);
}

TEST(HelperFunctions, SQR) {
  float precision = FP_SP_EPSILON;
  float x = 0.404006351202407f;
  float x2 = 0.163221131811882f;
  EXPECT_EQ(4, sqr(2));
  EXPECT_EQ(0, sqr(0));
  EXPECT_TRUE(fpEqual(x2, sqr(x), precision));
}

TEST(HelperFunctions, POW) {
  float precision = FP_SP_EPSILON;
  float x = 1267650600228229401496703205376.0f;
  EXPECT_EQ(1, _pow(4, 0));
  EXPECT_EQ(4, _pow(2, 2));
  EXPECT_TRUE(fpEqual(x, _pow(4.0f, 50.0f), precision));
}

TEST(HelperFunctions, DegreesToRadians) {
  float precision = FP_SP_EPSILON;
  EXPECT_TRUE(fpEqual(float(M_PI), degreesToRadians(180.0f), precision));
  EXPECT_TRUE(fpEqual((2.0f * float(M_PI)), degreesToRadians(360.0f), precision));
}

TEST(HelperFunctions, RadiansToDegrees) {
  float precision = FP_SP_EPSILON;
  EXPECT_TRUE(fpEqual(180.0f, radiansToDegrees(float(M_PI)), precision));
  EXPECT_TRUE(fpEqual(360.0f, radiansToDegrees((2.0f * float(M_PI))), precision));
}

TEST(HelperFunctions, Frustum) {
  Mat4 _x = Mat4(1.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 1.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, -1.500000000000000, -1.000000000000000, 0.000000000000000, 0.000000000000000, -2.500000000000000, 0.000000000000000);
  Mat4 _y = Mat4(0.050000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.050000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, -1.105263157894737, -1.000000000000000, 0.000000000000000, 0.000000000000000, -0.210526315789474, 0.000000000000000);
  Mat4 x = frustum( -1.0, 1.0, -1.0, 1.0, 1.0, 5.0 );
  Mat4 y = frustum( -2.0, 2.0, -2.0, 2.0, 0.1, 2.0 );
  EXPECT_TRUE(x == _x);
  EXPECT_TRUE(y == _y);
}

TEST(HelperFunctions, Perspective) {
  Mat4 _x = Mat4(3.218951416497460, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 2.414213562373095, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, -1.105263157894737, -1.000000000000000, 0.000000000000000, 0.000000000000000, -2.105263157894737, 0.000000000000000);
  Mat4 _y = Mat4(0.974278579257494, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 1.732050807568878, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, -1.083333333333333, -1.000000000000000, 0.000000000000000, 0.000000000000000, -2.083333333333333, 0.000000000000000);
  Mat4 x = perspective(45.0, .75, 1.0, 20.0);
  Mat4 y = perspective(60.0, (16.0/9.0), 1.0, 25.0);
  EXPECT_TRUE(x == _x);
  EXPECT_TRUE(y == _y);
}

TEST(HelperFunctions, Ortho) {
  Mat4 _x = Mat4(1.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 1.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, -0.105263157894737, 0.000000000000000, -0.000000000000000, -0.000000000000000, -1.105263157894737, 1.000000000000000);
  Mat4 x = ortho(-1.0, 1.0, -1.0, 1.0, 1.0, 20.0);
  EXPECT_TRUE(x == _x);
}

TEST(HelperFunctions, Rotate) {
  Mat4 _x = Mat4(1.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.866025403784439, 0.500000000000000, 0.000000000000000, 0.000000000000000, -0.500000000000000, 0.866025403784439, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 1.000000000000000);
  Mat4 _y = Mat4(0.918844752434809, 0.384105281322154, -0.090484549970936, 0.000000000000000, -0.383127913853368, 0.923251456628801, 0.028631267159575, 0.000000000000000, 0.094537413490007, 0.008359467281191, 0.995486211234186, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 1.000000000000000);
  Mat4 _z = Mat4(0.966039426759060, 0.138117286100694, -0.218383701835110, 0.000000000000000, -0.125921916623972, 0.989646184247291, 0.068877434029745, 0.000000000000000, 0.225635761484683, -0.039039022592215, 0.973429225909245, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 1.000000000000000);
  Vec3 v = Vec3(0.204485559696454, 0.841350534618938, 0.500314834651197);
  Mat4 x = rotate(30.0, 1.0, 0.0, 0.0);
  Mat4 y = rotate(23.25, 0.025677156908873, 0.234356989309077, 0.971811445278899);
  Mat4 z = rotate(15.3, v);
  EXPECT_TRUE(x == _x);
  EXPECT_TRUE(y == _y);
  EXPECT_TRUE(z == _z);  
}

TEST(HelperFunctions, Scale) {
  Mat4 _x = Mat4(0.204485559696454, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.841350534618938, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.500314834651197, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 1.000000000000000);
  Mat4 _y = Mat4(1.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 2.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 3.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 1.000000000000000);
  Mat4 _z = Mat4(3.400000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 3.400000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 3.400000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 1.000000000000000);
  Vec3 v = Vec3(0.204485559696454, 0.841350534618938, 0.500314834651197);
  Mat4 x = scale(v);
  Mat4 y = scale(1.0, 2.0, 3.0);
  Mat4 z = scale(3.4);
  EXPECT_TRUE(x == _x);
  EXPECT_TRUE(y == _y);
  EXPECT_TRUE(z == _z);  
}

TEST(HelperFunctions, Translate) {
  Mat4 _x = Mat4(1.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 1.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000, 1.000000000000000, 0.000000000000000, 0.204485559696454, 0.841350534618938, 0.500314834651197, 1.000000000000000);
  Vec3 v = Vec3(0.204485559696454, 0.841350534618938, 0.500314834651197);
  Mat4 x = translate(v);
  Mat4 y = translate(0.204485559696454, 0.841350534618938, 0.500314834651197);
  EXPECT_TRUE(x == _x);
  EXPECT_TRUE(y == _x);
}

TEST(HelperFunctions, LookAt) {
  Mat4 _x = Mat4(-0.115581170756122, 0.597653236354744, 0.391667560447679, 0.000000000000000, 0.102612058656748, 0.276586504500920, -0.895077098447604, 0.000000000000000, -0.643275686144851, -0.063264244268964, -0.213151377963133, 0.000000000000000, 0.352138611336373, -0.513400951582086, -0.166250171546251, 1.000000000000000);
  Vec3 eye = Vec3(0.859135371411426, 0.093066886406494, 0.407894359648632);
  Vec3 center = Vec3(0.530621853973708, 0.843818175721528, 0.586676357425850);
  Vec3 up = Vec3(0.306191887077451, 0.954762142338091, 0.097283471948774);
  Mat4 x = lookat(eye, center, up);
  EXPECT_TRUE(x == _x);
}

/*
TEST(HelperFunctions, Project) {
  EXPECT_TRUE(false);
}

TEST(HelperFunctions, UnProject) {
  EXPECT_TRUE(false);
}
*/

