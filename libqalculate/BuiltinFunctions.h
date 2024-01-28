/*
    Qalculate (library)

    Copyright (C) 2003-2007, 2008, 2016  Hanna Knutsson
   (hanna.knutsson@protonmail.com)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
*/

#ifndef BUILTIN_FUNCTIONS_H
#define BUILTIN_FUNCTIONS_H

#include <libqalculate/Function.h>
#include <libqalculate/MathStructure.h>
#include <libqalculate/includes.h>

#define TEST_NM_S_FUNCTIONS                                                    \
  bool representsNonMatrix(const MathStructure &vargs) const {                 \
    if (vargs.size() == 1)                                                     \
      return vargs[0].representsNonMatrix();                                   \
    bool non_scalar = false;                                                   \
    for (size_t i = 0; i < vargs.size(); i++) {                                \
      if (!vargs[i].representsNonMatrix())                                     \
        return false;                                                          \
      if (!vargs[i].representsScalar()) {                                      \
        if (non_scalar)                                                        \
          return false;                                                        \
        non_scalar = true;                                                     \
      }                                                                        \
    }                                                                          \
    return true;                                                               \
  }                                                                            \
  bool representsScalar(const MathStructure &vargs) const {                    \
    for (size_t i = 0; i < vargs.size(); i++) {                                \
      if (!vargs[i].representsScalar())                                        \
        return false;                                                          \
    }                                                                          \
    return true;                                                               \
  }

#define DECLARE_BUILTIN_FUNCTION(x, i)                                         \
  class x : public MathFunction {                                              \
  public:                                                                      \
    int calculate(MathStructure &mstruct, const MathStructure &vargs,          \
                  const EvaluationOptions &eo);                                \
    x();                                                                       \
    x(const x *function) { set(function); }                                    \
    ExpressionItem *copy() const { return new x(this); }                       \
    int id() const { return i; }                                               \
  };

#define DECLARE_BUILTIN_FUNCTION_M(x, i)                                       \
  class x : public MathFunction {                                              \
  public:                                                                      \
    int calculate(MathStructure &mstruct, const MathStructure &vargs,          \
                  const EvaluationOptions &eo);                                \
    x();                                                                       \
    x(const x *function) { set(function); }                                    \
    ExpressionItem *copy() const { return new x(this); }                       \
    bool representsScalar(const MathStructure &vargs) const;                   \
    bool representsNonMatrix(const MathStructure &vargs) const;                \
    int id() const { return i; }                                               \
  };

#define DECLARE_BUILTIN_FUNCTION_MT(x, i)                                      \
  class x : public MathFunction {                                              \
  public:                                                                      \
    int calculate(MathStructure &mstruct, const MathStructure &vargs,          \
                  const EvaluationOptions &eo);                                \
    x();                                                                       \
    x(const x *function) { set(function); }                                    \
    ExpressionItem *copy() const { return new x(this); }                       \
    TEST_NM_S_FUNCTIONS                                                        \
    int id() const { return i; }                                               \
  };

#define DECLARE_BUILTIN_FUNCTION_B(x, i)                                       \
  class x : public MathFunction {                                              \
  public:                                                                      \
    int calculate(MathStructure &mstruct, const MathStructure &vargs,          \
                  const EvaluationOptions &eo);                                \
    x();                                                                       \
    x(const x *function) { set(function); }                                    \
    ExpressionItem *copy() const { return new x(this); }                       \
    bool representsBoolean(const MathStructure &vargs) const {                 \
      return vargs.size() > 0 && vargs[0].representsScalar();                  \
    }                                                                          \
    int id() const { return i; }                                               \
  };

#define DECLARE_BUILTIN_FUNCTION_PI(x, i)                                      \
  class x : public MathFunction {                                              \
  public:                                                                      \
    int calculate(MathStructure &mstruct, const MathStructure &vargs,          \
                  const EvaluationOptions &eo);                                \
    x();                                                                       \
    x(const x *function) { set(function); }                                    \
    ExpressionItem *copy() const { return new x(this); }                       \
    bool representsInteger(const MathStructure &vargs, bool) const {           \
      return vargs.size() > 0 && vargs[0].representsScalar();                  \
    }                                                                          \
    bool representsPositive(const MathStructure &vargs, bool) const {          \
      return vargs.size() > 0 && vargs[0].representsScalar();                  \
    }                                                                          \
    int id() const { return i; }                                               \
  };

#define DECLARE_BUILTIN_FUNCTION_RPI(x, i)                                     \
  class x : public MathFunction {                                              \
  public:                                                                      \
    int calculate(MathStructure &mstruct, const MathStructure &vargs,          \
                  const EvaluationOptions &eo);                                \
    x();                                                                       \
    x(const x *function) { set(function); }                                    \
    ExpressionItem *copy() const { return new x(this); }                       \
    bool representsReal(const MathStructure &, bool) const;                    \
    bool representsInteger(const MathStructure &, bool) const;                 \
    bool representsNonNegative(const MathStructure &, bool) const;             \
    TEST_NM_S_FUNCTIONS                                                        \
    int id() const { return i; }                                               \
  };

#define DECLARE_BUILTIN_FUNCTION_R(x, i)                                       \
  class x : public MathFunction {                                              \
  public:                                                                      \
    int calculate(MathStructure &mstruct, const MathStructure &vargs,          \
                  const EvaluationOptions &eo);                                \
    x();                                                                       \
    x(const x *function) { set(function); }                                    \
    ExpressionItem *copy() const { return new x(this); }                       \
    bool representsPositive(const MathStructure &vargs,                        \
                            bool allow_units = false) const;                   \
    bool representsNegative(const MathStructure &vargs,                        \
                            bool allow_units = false) const;                   \
    bool representsNonNegative(const MathStructure &vargs,                     \
                               bool allow_units = false) const;                \
    bool representsNonPositive(const MathStructure &vargs,                     \
                               bool allow_units = false) const;                \
    bool representsInteger(const MathStructure &vargs,                         \
                           bool allow_units = false) const;                    \
    bool representsNumber(const MathStructure &vargs,                          \
                          bool allow_units = false) const;                     \
    bool representsRational(const MathStructure &vargs,                        \
                            bool allow_units = false) const;                   \
    bool representsReal(const MathStructure &vargs,                            \
                        bool allow_units = false) const;                       \
    bool representsNonComplex(const MathStructure &vargs,                      \
                              bool allow_units = false) const;                 \
    bool representsComplex(const MathStructure &vargs,                         \
                           bool allow_units = false) const;                    \
    bool representsNonZero(const MathStructure &vargs,                         \
                           bool allow_units = false) const;                    \
    bool representsEven(const MathStructure &vargs,                            \
                        bool allow_units = false) const;                       \
    bool representsOdd(const MathStructure &vargs,                             \
                       bool allow_units = false) const;                        \
    bool representsUndefined(const MathStructure &vargs) const;                \
    TEST_NM_S_FUNCTIONS                                                        \
    int id() const { return i; }                                               \
  };

#define DECLARE_BUILTIN_FUNCTION_R2(x, i)                                      \
  class x : public MathFunction {                                              \
  public:                                                                      \
    int calculate(MathStructure &mstruct, const MathStructure &vargs,          \
                  const EvaluationOptions &eo);                                \
    x();                                                                       \
    x(const x *function) { set(function); }                                    \
    ExpressionItem *copy() const { return new x(this); }                       \
    bool representsNumber(const MathStructure &vargs,                          \
                          bool allow_units = false) const;                     \
    bool representsReal(const MathStructure &vargs,                            \
                        bool allow_units = false) const;                       \
    bool representsNonComplex(const MathStructure &vargs,                      \
                              bool allow_units = false) const;                 \
    TEST_NM_S_FUNCTIONS                                                        \
    int id() const { return i; }                                               \
  };

#define DECLARE_BUILTIN_FUNCTION_R3(x, i)                                      \
  class x : public MathFunction {                                              \
  public:                                                                      \
    int calculate(MathStructure &mstruct, const MathStructure &vargs,          \
                  const EvaluationOptions &eo);                                \
    x();                                                                       \
    x(const x *function) { set(function); }                                    \
    ExpressionItem *copy() const { return new x(this); }                       \
    bool representsNumber(const MathStructure &vargs,                          \
                          bool allow_units = false) const;                     \
    bool representsReal(const MathStructure &vargs,                            \
                        bool allow_units = false) const;                       \
    bool representsNonComplex(const MathStructure &vargs,                      \
                              bool allow_units = false) const;                 \
    bool representsComplex(const MathStructure &vargs,                         \
                           bool allow_units = false) const;                    \
    bool representsNonZero(const MathStructure &vargs,                         \
                           bool allow_units = false) const;                    \
    TEST_NM_S_FUNCTIONS                                                        \
    int id() const { return i; }                                               \
  };

#define DECLARE_BUILTIN_FUNCTION_R1(x, i)                                      \
  class x : public MathFunction {                                              \
  public:                                                                      \
    int calculate(MathStructure &mstruct, const MathStructure &vargs,          \
                  const EvaluationOptions &eo);                                \
    x();                                                                       \
    x(const x *function) { set(function); }                                    \
    ExpressionItem *copy() const { return new x(this); }                       \
    bool representsNumber(const MathStructure &vargs,                          \
                          bool allow_units = false) const;                     \
    TEST_NM_S_FUNCTIONS                                                        \
    int id() const { return i; }                                               \
  };

enum {
  FUNCTION_ID_VECTOR = 1100,
  FUNCTION_ID_LIMITS = 1101,
  FUNCTION_ID_RANK = 1102,
  FUNCTION_ID_SORT = 1103,
  FUNCTION_ID_COMPONENT = 1104,
  FUNCTION_ID_DIMENSION = 1105,
  FUNCTION_ID_MATRIX = 1106,
  FUNCTION_ID_MERGE_VECTORS = 1107,
  FUNCTION_ID_MATRIX_TO_VECTOR = 1108,
  FUNCTION_ID_AREA = 1109,
  FUNCTION_ID_ROWS = 1110,
  FUNCTION_ID_COLUMNS = 1111,
  FUNCTION_ID_ROW = 1112,
  FUNCTION_ID_COLUMN = 1113,
  FUNCTION_ID_ELEMENTS = 1114,
  FUNCTION_ID_ELEMENT = 1115,
  FUNCTION_ID_TRANSPOSE = 1116,
  FUNCTION_ID_IDENTITY = 1117,
  FUNCTION_ID_DETERMINANT = 1118,
  FUNCTION_ID_PERMANENT = 1119,
  FUNCTION_ID_ADJOINT = 1120,
  FUNCTION_ID_COFACTOR = 1121,
  FUNCTION_ID_INVERSE = 1122,
  FUNCTION_ID_MAGNITUDE = 1123,
  FUNCTION_ID_ENTRYWISE = 1125,
  FUNCTION_ID_LOAD = 1126,
  FUNCTION_ID_EXPORT = 1127,
  FUNCTION_ID_GENERATE_VECTOR = 1128,
  FUNCTION_ID_SELECT = 1129,
  FUNCTION_ID_PROCESS = 1130,
  FUNCTION_ID_PROCESS_MATRIX = 1131,
  FUNCTION_ID_RREF = 1132,
  FUNCTION_ID_MATRIX_RANK = 1133,
  FUNCTION_ID_DOT_PRODUCT = 1134,
  FUNCTION_ID_ENTRYWISE_MULTIPLICATION = 1135,
  FUNCTION_ID_ENTRYWISE_DIVISION = 1135,
  FUNCTION_ID_ENTRYWISE_POWER = 1137,
  FUNCTION_ID_NORM = 1138,
  FUNCTION_ID_VERTCAT = 1139,
  FUNCTION_ID_HORZCAT = 1140,
  FUNCTION_ID_KRONECKER_PRODUCT = 1141,
  FUNCTION_ID_SQRT = 1200,
  FUNCTION_ID_CBRT = 1201,
  FUNCTION_ID_ROOT = 1202,
  FUNCTION_ID_SQUARE = 1203,
  FUNCTION_ID_EXP = 1204,
  FUNCTION_ID_LOG = 1205,
  FUNCTION_ID_LOGN = 1206,
  FUNCTION_ID_LAMBERT_W = 1207,
  FUNCTION_ID_CIS = 1208,
  FUNCTION_ID_SIN = 1300,
  FUNCTION_ID_COS = 1301,
  FUNCTION_ID_TAN = 1302,
  FUNCTION_ID_ASIN = 1303,
  FUNCTION_ID_ACOS = 1304,
  FUNCTION_ID_ATAN = 1305,
  FUNCTION_ID_SINH = 1306,
  FUNCTION_ID_COSH = 1307,
  FUNCTION_ID_TANH = 1308,
  FUNCTION_ID_ASINH = 1309,
  FUNCTION_ID_ACOSH = 1310,
  FUNCTION_ID_ATANH = 1311,
  FUNCTION_ID_SINC = 1312,
  FUNCTION_ID_ATAN2 = 1313,
  FUNCTION_ID_RADIANS_TO_DEFAULT_ANGLE_UNIT = 1314,
  FUNCTION_ID_ZETA = 1400,
  FUNCTION_ID_GAMMA = 1401,
  FUNCTION_ID_DIGAMMA = 1402,
  FUNCTION_ID_BETA = 1403,
  FUNCTION_ID_AIRY = 1404,
  FUNCTION_ID_BESSELJ = 1405,
  FUNCTION_ID_BESSELY = 1406,
  FUNCTION_ID_ERF = 1407,
  FUNCTION_ID_ERFI = 1408,
  FUNCTION_ID_ERFC = 1409,
  FUNCTION_ID_POLYLOG = 1410,
  FUNCTION_ID_HEAVISIDE = 1411,
  FUNCTION_ID_DIRAC = 1412,
  FUNCTION_ID_ERFINV = 1413,
  FUNCTION_ID_FACTORIAL = 1500,
  FUNCTION_ID_DOUBLE_FACTORIAL = 1501,
  FUNCTION_ID_MULTI_FACTORIAL = 1502,
  FUNCTION_ID_BINOMIAL = 1503,
  FUNCTION_ID_LOGINT = 1600,
  FUNCTION_ID_FRESNEL_S = 1601,
  FUNCTION_ID_FRESNEL_C = 1602,
  FUNCTION_ID_EXPINT = 1603,
  FUNCTION_ID_SININT = 1604,
  FUNCTION_ID_COSINT = 1605,
  FUNCTION_ID_SINHINT = 1606,
  FUNCTION_ID_COSHINT = 1607,
  FUNCTION_ID_I_GAMMA = 1608,
  FUNCTION_ID_INCOMPLETE_BETA = 1609,
  FUNCTION_ID_INVERSE_INCOMPLETE_BETA = 1610,
  FUNCTION_ID_ABS = 1700,
  FUNCTION_ID_GCD = 1701,
  FUNCTION_ID_LCM = 1702,
  FUNCTION_ID_DIVISORS = 1703,
  FUNCTION_ID_SIGNUM = 1710,
  FUNCTION_ID_ROUND = 1720,
  FUNCTION_ID_FLOOR = 1721,
  FUNCTION_ID_CEIL = 1722,
  FUNCTION_ID_TRUNC = 1723,
  FUNCTION_ID_NUMERATOR = 1730,
  FUNCTION_ID_DENOMINATOR = 1731,
  FUNCTION_ID_INT = 1732,
  FUNCTION_ID_FRAC = 1733,
  FUNCTION_ID_REM = 1734,
  FUNCTION_ID_MOD = 1735,
  FUNCTION_ID_PARALLEL = 1736,
  FUNCTION_ID_POWER_MOD = 1737,
  FUNCTION_ID_BERNOULLI = 1740,
  FUNCTION_ID_TOTIENT = 1745,
  FUNCTION_ID_RE = 1750,
  FUNCTION_ID_IM = 1751,
  FUNCTION_ID_ARG = 1752,
  FUNCTION_ID_PRIME_COUNT = 1760,
  FUNCTION_ID_NTH_PRIME = 1761,
  FUNCTION_ID_PREV_PRIME = 1762,
  FUNCTION_ID_NEXT_PRIME = 1763,
  FUNCTION_ID_PRIMES = 1764,
  FUNCTION_ID_IS_PRIME = 1765,
  FUNCTION_ID_DIFFERENTIATE = 1800,
  FUNCTION_ID_LIMIT = 1810,
  FUNCTION_ID_INTEGRATE = 1820,
  FUNCTION_ID_MONTE_CARLO = 1821,
  FUNCTION_ID_ROMBERG = 1822,
  FUNCTION_ID_SUM = 1830,
  FUNCTION_ID_PRODUCT = 1831,
  FUNCTION_ID_SOLVE = 1840,
  FUNCTION_ID_SOLVE_MULTIPLE = 1841,
  FUNCTION_ID_D_SOLVE = 1842,
  FUNCTION_ID_NEWTON_RAPHSON = 1850,
  FUNCTION_ID_SECANT_METHOD = 1851,
  FUNCTION_ID_BIN = 1900,
  FUNCTION_ID_OCT = 1901,
  FUNCTION_ID_DEC = 1902,
  FUNCTION_ID_HEX = 1903,
  FUNCTION_ID_BASE = 1904,
  FUNCTION_ID_ROMAN = 1905,
  FUNCTION_ID_BIJECTIVE = 1906,
  FUNCTION_ID_BINARY_DECIMAL = 1907,
  FUNCTION_ID_IEEE754_FLOAT = 1910,
  FUNCTION_ID_IEEE754_FLOAT_BITS = 1911,
  FUNCTION_ID_IEEE754_FLOAT_COMPONENTS = 1912,
  FUNCTION_ID_IEEE754_FLOAT_VALUE = 1913,
  FUNCTION_ID_IEEE754_FLOAT_ERROR = 1914,
  FUNCTION_ID_IS_NUMBER = 1920,
  FUNCTION_ID_IS_REAL = 1921,
  FUNCTION_ID_IS_RATIONAL = 1922,
  FUNCTION_ID_IS_INTEGER = 1923,
  FUNCTION_ID_ODD = 1924,
  FUNCTION_ID_EVEN = 1925,
  FUNCTION_ID_POLYNOMIAL_UNIT = 2000,
  FUNCTION_ID_POLYNOMIAL_PRIMPART = 2001,
  FUNCTION_ID_POLYNOMIAL_CONTENT = 2002,
  FUNCTION_ID_COEFF = 2003,
  FUNCTION_ID_L_COEFF = 2004,
  FUNCTION_ID_T_COEFF = 2005,
  FUNCTION_ID_DEGREE = 2006,
  FUNCTION_ID_L_DEGREE = 2007,
  FUNCTION_ID_BIT_XOR = 2100,
  FUNCTION_ID_XOR = 2101,
  FUNCTION_ID_BIT_CMP = 2102,
  FUNCTION_ID_SHIFT = 2103,
  FUNCTION_ID_CIRCULAR_SHIFT = 2104,
  FUNCTION_ID_FOR = 2150,
  FUNCTION_ID_IF = 2151,
  FUNCTION_ID_TOTAL = 2200,
  FUNCTION_ID_PERCENTILE = 2201,
  FUNCTION_ID_MIN = 2202,
  FUNCTION_ID_MAX = 2203,
  FUNCTION_ID_MODE = 2204,
  FUNCTION_ID_RAND = 2220,
  FUNCTION_ID_RANDN = 2221,
  FUNCTION_ID_RAND_POISSON = 2222,
  FUNCTION_ID_DATE = 2300,
  FUNCTION_ID_DATE_TIME = 2301,
  FUNCTION_ID_TIME_VALUE = 2302,
  FUNCTION_ID_TIMESTAMP = 2303,
  FUNCTION_ID_TIMESTAMP_TO_DATE = 2304,
  FUNCTION_ID_DAYS = 2305,
  FUNCTION_ID_YEAR_FRAC = 2306,
  FUNCTION_ID_WEEK = 2307,
  FUNCTION_ID_WEEKDAY = 2308,
  FUNCTION_ID_MONTH = 2309,
  FUNCTION_ID_DAY = 2310,
  FUNCTION_ID_YEAR = 2311,
  FUNCTION_ID_YEARDAY = 2312,
  FUNCTION_ID_TIME = 2313,
  FUNCTION_ID_ADD_DAYS = 2320,
  FUNCTION_ID_ADD_MONTHS = 2321,
  FUNCTION_ID_ADD_YEARS = 2322,
  FUNCTION_ID_LUNAR_PHASE = 2350,
  FUNCTION_ID_NEXT_LUNAR_PHASE = 2351,
  FUNCTION_ID_INTERVAL = 2400,
  FUNCTION_ID_UNCERTAINTY = 2401,
  FUNCTION_ID_LOWER_END_POINT = 2402,
  FUNCTION_ID_UPPER_END_POINT = 2403,
  FUNCTION_ID_MID_POINT = 2404,
  FUNCTION_ID_GET_UNCERTAINTY = 2404,
  FUNCTION_ID_ASCII = 2500,
  FUNCTION_ID_CHAR = 2501,
  FUNCTION_ID_LENGTH = 2502,
  FUNCTION_ID_CONCATENATE = 2503,
  FUNCTION_ID_REPRESENTS_NUMBER = 2600,
  FUNCTION_ID_REPRESENTS_REAL = 2601,
  FUNCTION_ID_REPRESENTS_RATIONAL = 2602,
  FUNCTION_ID_REPRESENTS_INTEGER = 2603,
  FUNCTION_ID_REPLACE = 2610,
  FUNCTION_ID_STRIP_UNITS = 2620,
  FUNCTION_ID_CUSTOM_SUM = 2630,
  FUNCTION_ID_FUNCTION = 2640,
  FUNCTION_ID_TITLE = 2650,
  FUNCTION_ID_ERROR = 2660,
  FUNCTION_ID_WARNING = 2661,
  FUNCTION_ID_MESSAGE = 2662,
  FUNCTION_ID_SAVE = 2670,
  FUNCTION_ID_REGISTER = 2680,
  FUNCTION_ID_STACK = 2681,
  FUNCTION_ID_PLOT = 2690,
  FUNCTION_ID_COMMAND = 2695,
  FUNCTION_ID_GEO_DISTANCE = 2700
};

DECLARE_BUILTIN_FUNCTION(VectorFunction, FUNCTION_ID_VECTOR)
DECLARE_BUILTIN_FUNCTION(LimitsFunction, FUNCTION_ID_LIMITS)
DECLARE_BUILTIN_FUNCTION(RankFunction, FUNCTION_ID_RANK)
DECLARE_BUILTIN_FUNCTION(SortFunction, FUNCTION_ID_SORT)
DECLARE_BUILTIN_FUNCTION_M(ComponentFunction, FUNCTION_ID_COMPONENT)
DECLARE_BUILTIN_FUNCTION_PI(DimensionFunction, FUNCTION_ID_DIMENSION)
DECLARE_BUILTIN_FUNCTION(MatrixFunction, FUNCTION_ID_MATRIX)
DECLARE_BUILTIN_FUNCTION(VertCatFunction, FUNCTION_ID_VERTCAT)
DECLARE_BUILTIN_FUNCTION_M(HorzCatFunction, FUNCTION_ID_HORZCAT)
DECLARE_BUILTIN_FUNCTION(MergeVectorsFunction, FUNCTION_ID_MERGE_VECTORS)
DECLARE_BUILTIN_FUNCTION(MatrixToVectorFunction, FUNCTION_ID_MATRIX_TO_VECTOR)
DECLARE_BUILTIN_FUNCTION(AreaFunction, FUNCTION_ID_AREA)
DECLARE_BUILTIN_FUNCTION_PI(RowsFunction, FUNCTION_ID_ROWS)
DECLARE_BUILTIN_FUNCTION_PI(ColumnsFunction, FUNCTION_ID_COLUMNS)
DECLARE_BUILTIN_FUNCTION(RowFunction, FUNCTION_ID_ROW)
DECLARE_BUILTIN_FUNCTION(ColumnFunction, FUNCTION_ID_COLUMN)
DECLARE_BUILTIN_FUNCTION_PI(ElementsFunction, FUNCTION_ID_ELEMENTS)
DECLARE_BUILTIN_FUNCTION_M(ElementFunction, FUNCTION_ID_ELEMENT)
DECLARE_BUILTIN_FUNCTION(TransposeFunction, FUNCTION_ID_TRANSPOSE)
DECLARE_BUILTIN_FUNCTION(IdentityMatrixFunction, FUNCTION_ID_IDENTITY)
DECLARE_BUILTIN_FUNCTION(DeterminantFunction, FUNCTION_ID_DETERMINANT)
DECLARE_BUILTIN_FUNCTION(PermanentFunction, FUNCTION_ID_PERMANENT)
DECLARE_BUILTIN_FUNCTION(AdjointFunction, FUNCTION_ID_ADJOINT)
DECLARE_BUILTIN_FUNCTION(CofactorFunction, FUNCTION_ID_COFACTOR)
DECLARE_BUILTIN_FUNCTION(InverseFunction, FUNCTION_ID_INVERSE)
DECLARE_BUILTIN_FUNCTION(MagnitudeFunction, FUNCTION_ID_MAGNITUDE)
DECLARE_BUILTIN_FUNCTION(EntrywiseFunction, FUNCTION_ID_ENTRYWISE)
DECLARE_BUILTIN_FUNCTION(LoadFunction, FUNCTION_ID_LOAD)
DECLARE_BUILTIN_FUNCTION(ExportFunction, FUNCTION_ID_EXPORT)
DECLARE_BUILTIN_FUNCTION(GenerateVectorFunction, FUNCTION_ID_GENERATE_VECTOR)
DECLARE_BUILTIN_FUNCTION(SelectFunction, FUNCTION_ID_SELECT)
DECLARE_BUILTIN_FUNCTION(ProcessFunction, FUNCTION_ID_PROCESS)
DECLARE_BUILTIN_FUNCTION(ProcessMatrixFunction, FUNCTION_ID_PROCESS_MATRIX)
DECLARE_BUILTIN_FUNCTION(RRefFunction, FUNCTION_ID_RREF)
DECLARE_BUILTIN_FUNCTION(MatrixRankFunction, FUNCTION_ID_MATRIX_RANK)
DECLARE_BUILTIN_FUNCTION(DotProductFunction, FUNCTION_ID_DOT_PRODUCT)
DECLARE_BUILTIN_FUNCTION(EntrywiseMultiplicationFunction,
                         FUNCTION_ID_ENTRYWISE_MULTIPLICATION)
DECLARE_BUILTIN_FUNCTION(EntrywiseDivisionFunction,
                         FUNCTION_ID_ENTRYWISE_DIVISION)
DECLARE_BUILTIN_FUNCTION(EntrywisePowerFunction, FUNCTION_ID_ENTRYWISE_POWER)
DECLARE_BUILTIN_FUNCTION(NormFunction, FUNCTION_ID_NORM)
DECLARE_BUILTIN_FUNCTION_MT(KroneckerProductFunction,
                            FUNCTION_ID_KRONECKER_PRODUCT)

DECLARE_BUILTIN_FUNCTION_R(SqrtFunction, FUNCTION_ID_SQRT)
DECLARE_BUILTIN_FUNCTION(CbrtFunction, FUNCTION_ID_CBRT)
DECLARE_BUILTIN_FUNCTION_R(RootFunction, FUNCTION_ID_ROOT)
DECLARE_BUILTIN_FUNCTION(SquareFunction, FUNCTION_ID_SQUARE)
DECLARE_BUILTIN_FUNCTION(ExpFunction, FUNCTION_ID_EXP)
DECLARE_BUILTIN_FUNCTION_R(LogFunction, FUNCTION_ID_LOG)
DECLARE_BUILTIN_FUNCTION_MT(LognFunction, FUNCTION_ID_LOGN)
DECLARE_BUILTIN_FUNCTION_R3(LambertWFunction, FUNCTION_ID_LAMBERT_W)
DECLARE_BUILTIN_FUNCTION_MT(CisFunction, FUNCTION_ID_CIS)

DECLARE_BUILTIN_FUNCTION_R2(SinFunction, FUNCTION_ID_SIN)
DECLARE_BUILTIN_FUNCTION_R2(CosFunction, FUNCTION_ID_COS)
DECLARE_BUILTIN_FUNCTION_R2(TanFunction, FUNCTION_ID_TAN)
DECLARE_BUILTIN_FUNCTION_R1(AsinFunction, FUNCTION_ID_ASIN)
DECLARE_BUILTIN_FUNCTION_R1(AcosFunction, FUNCTION_ID_ACOS)
DECLARE_BUILTIN_FUNCTION_R2(AtanFunction, FUNCTION_ID_ATAN)
DECLARE_BUILTIN_FUNCTION_R2(SinhFunction, FUNCTION_ID_SINH)
DECLARE_BUILTIN_FUNCTION_R2(CoshFunction, FUNCTION_ID_COSH)
DECLARE_BUILTIN_FUNCTION_R2(TanhFunction, FUNCTION_ID_TANH)
DECLARE_BUILTIN_FUNCTION_R2(AsinhFunction, FUNCTION_ID_ASINH)
DECLARE_BUILTIN_FUNCTION_R1(AcoshFunction, FUNCTION_ID_ACOSH)
DECLARE_BUILTIN_FUNCTION(AtanhFunction, FUNCTION_ID_ATANH)
DECLARE_BUILTIN_FUNCTION_R2(SincFunction, FUNCTION_ID_SINC)
DECLARE_BUILTIN_FUNCTION_R1(Atan2Function, FUNCTION_ID_ATAN2)
DECLARE_BUILTIN_FUNCTION(RadiansToDefaultAngleUnitFunction,
                         FUNCTION_ID_RADIANS_TO_DEFAULT_ANGLE_UNIT)

DECLARE_BUILTIN_FUNCTION_MT(ZetaFunction, FUNCTION_ID_ZETA)
DECLARE_BUILTIN_FUNCTION_MT(GammaFunction, FUNCTION_ID_GAMMA)
DECLARE_BUILTIN_FUNCTION_MT(DigammaFunction, FUNCTION_ID_DIGAMMA)
DECLARE_BUILTIN_FUNCTION_MT(BetaFunction, FUNCTION_ID_BETA)
DECLARE_BUILTIN_FUNCTION_MT(AiryFunction, FUNCTION_ID_AIRY)
DECLARE_BUILTIN_FUNCTION_MT(BesseljFunction, FUNCTION_ID_BESSELJ)
DECLARE_BUILTIN_FUNCTION_MT(BesselyFunction, FUNCTION_ID_BESSELY)
DECLARE_BUILTIN_FUNCTION_R(ErfFunction, FUNCTION_ID_ERF)
DECLARE_BUILTIN_FUNCTION_R(ErfiFunction, FUNCTION_ID_ERFI)
DECLARE_BUILTIN_FUNCTION_R(ErfcFunction, FUNCTION_ID_ERFC)
DECLARE_BUILTIN_FUNCTION_MT(ErfinvFunction, FUNCTION_ID_ERFINV)
DECLARE_BUILTIN_FUNCTION_R2(LiFunction, FUNCTION_ID_POLYLOG)

DECLARE_BUILTIN_FUNCTION_R(HeavisideFunction, FUNCTION_ID_HEAVISIDE)
DECLARE_BUILTIN_FUNCTION_R(DiracFunction, FUNCTION_ID_DIRAC)

DECLARE_BUILTIN_FUNCTION_R2(liFunction, FUNCTION_ID_LOGINT)
DECLARE_BUILTIN_FUNCTION_R(FresnelSFunction, FUNCTION_ID_FRESNEL_S)
DECLARE_BUILTIN_FUNCTION_R(FresnelCFunction, FUNCTION_ID_FRESNEL_C)
DECLARE_BUILTIN_FUNCTION_R2(EiFunction, FUNCTION_ID_EXPINT)
DECLARE_BUILTIN_FUNCTION_R2(SiFunction, FUNCTION_ID_SININT)
DECLARE_BUILTIN_FUNCTION_R2(CiFunction, FUNCTION_ID_COSINT)
DECLARE_BUILTIN_FUNCTION_R2(ShiFunction, FUNCTION_ID_SINHINT)
DECLARE_BUILTIN_FUNCTION_R2(ChiFunction, FUNCTION_ID_COSHINT)
DECLARE_BUILTIN_FUNCTION_R2(IGammaFunction, FUNCTION_ID_I_GAMMA)
DECLARE_BUILTIN_FUNCTION(IncompleteBetaFunction, FUNCTION_ID_INCOMPLETE_BETA)
DECLARE_BUILTIN_FUNCTION(InverseIncompleteBetaFunction,
                         FUNCTION_ID_INVERSE_INCOMPLETE_BETA)

DECLARE_BUILTIN_FUNCTION_MT(DeriveFunction, FUNCTION_ID_DIFFERENTIATE)
DECLARE_BUILTIN_FUNCTION_MT(IntegrateFunction, FUNCTION_ID_INTEGRATE)
DECLARE_BUILTIN_FUNCTION_MT(LimitFunction, FUNCTION_ID_LIMIT)
DECLARE_BUILTIN_FUNCTION_MT(MonteCarloFunction, FUNCTION_ID_MONTE_CARLO)
DECLARE_BUILTIN_FUNCTION_MT(RombergFunction, FUNCTION_ID_ROMBERG)

DECLARE_BUILTIN_FUNCTION_MT(SumFunction, FUNCTION_ID_SUM)
DECLARE_BUILTIN_FUNCTION_MT(ProductFunction, FUNCTION_ID_PRODUCT)
DECLARE_BUILTIN_FUNCTION_MT(SolveFunction, FUNCTION_ID_SOLVE)
DECLARE_BUILTIN_FUNCTION_MT(SolveMultipleFunction, FUNCTION_ID_SOLVE_MULTIPLE)
DECLARE_BUILTIN_FUNCTION_MT(DSolveFunction, FUNCTION_ID_D_SOLVE)
DECLARE_BUILTIN_FUNCTION_MT(NewtonRaphsonFunction, FUNCTION_ID_NEWTON_RAPHSON)
DECLARE_BUILTIN_FUNCTION_MT(SecantMethodFunction, FUNCTION_ID_SECANT_METHOD)

DECLARE_BUILTIN_FUNCTION_R(FactorialFunction, FUNCTION_ID_FACTORIAL)
DECLARE_BUILTIN_FUNCTION_R(DoubleFactorialFunction,
                           FUNCTION_ID_DOUBLE_FACTORIAL)
DECLARE_BUILTIN_FUNCTION_R(MultiFactorialFunction, FUNCTION_ID_MULTI_FACTORIAL)
DECLARE_BUILTIN_FUNCTION(BinomialFunction, FUNCTION_ID_BINOMIAL)

DECLARE_BUILTIN_FUNCTION_R(ReFunction, FUNCTION_ID_RE)
DECLARE_BUILTIN_FUNCTION_R(ImFunction, FUNCTION_ID_IM)
DECLARE_BUILTIN_FUNCTION_R2(ArgFunction, FUNCTION_ID_ARG)

DECLARE_BUILTIN_FUNCTION_R(AbsFunction, FUNCTION_ID_ABS)
DECLARE_BUILTIN_FUNCTION_MT(GcdFunction, FUNCTION_ID_GCD)
DECLARE_BUILTIN_FUNCTION_MT(LcmFunction, FUNCTION_ID_LCM)
DECLARE_BUILTIN_FUNCTION(DivisorsFunction, FUNCTION_ID_DIVISORS)
DECLARE_BUILTIN_FUNCTION_MT(PrimeCountFunction, FUNCTION_ID_PRIME_COUNT)
DECLARE_BUILTIN_FUNCTION_MT(IsPrimeFunction, FUNCTION_ID_IS_PRIME)
DECLARE_BUILTIN_FUNCTION_MT(NthPrimeFunction, FUNCTION_ID_NTH_PRIME)
DECLARE_BUILTIN_FUNCTION_MT(PrimesFunction, FUNCTION_ID_PRIMES)
DECLARE_BUILTIN_FUNCTION_MT(PrevPrimeFunction, FUNCTION_ID_PREV_PRIME)
DECLARE_BUILTIN_FUNCTION_MT(NextPrimeFunction, FUNCTION_ID_NEXT_PRIME)
DECLARE_BUILTIN_FUNCTION_R(SignumFunction, FUNCTION_ID_SIGNUM)
DECLARE_BUILTIN_FUNCTION_R(RoundFunction, FUNCTION_ID_ROUND)
DECLARE_BUILTIN_FUNCTION_R(FloorFunction, FUNCTION_ID_FLOOR)
DECLARE_BUILTIN_FUNCTION_R(CeilFunction, FUNCTION_ID_CEIL)
DECLARE_BUILTIN_FUNCTION_R(TruncFunction, FUNCTION_ID_TRUNC)
DECLARE_BUILTIN_FUNCTION_MT(NumeratorFunction, FUNCTION_ID_NUMERATOR)
DECLARE_BUILTIN_FUNCTION_MT(DenominatorFunction, FUNCTION_ID_DENOMINATOR)
DECLARE_BUILTIN_FUNCTION_MT(IntFunction, FUNCTION_ID_INT)
DECLARE_BUILTIN_FUNCTION_MT(FracFunction, FUNCTION_ID_FRAC)
DECLARE_BUILTIN_FUNCTION_MT(RemFunction, FUNCTION_ID_REM)
DECLARE_BUILTIN_FUNCTION_MT(ModFunction, FUNCTION_ID_MOD)
DECLARE_BUILTIN_FUNCTION_MT(PowerModFunction, FUNCTION_ID_POWER_MOD)
DECLARE_BUILTIN_FUNCTION_MT(BernoulliFunction, FUNCTION_ID_BERNOULLI)
DECLARE_BUILTIN_FUNCTION_MT(TotientFunction, FUNCTION_ID_TOTIENT)
DECLARE_BUILTIN_FUNCTION(ParallelFunction, FUNCTION_ID_PARALLEL)
DECLARE_BUILTIN_FUNCTION_MT(LowerEndPointFunction, FUNCTION_ID_LOWER_END_POINT)
DECLARE_BUILTIN_FUNCTION_MT(UpperEndPointFunction, FUNCTION_ID_UPPER_END_POINT)
DECLARE_BUILTIN_FUNCTION_MT(MidPointFunction, FUNCTION_ID_MID_POINT)
DECLARE_BUILTIN_FUNCTION_MT(GetUncertaintyFunction, FUNCTION_ID_GET_UNCERTAINTY)

DECLARE_BUILTIN_FUNCTION(BinFunction, FUNCTION_ID_BIN)
DECLARE_BUILTIN_FUNCTION(OctFunction, FUNCTION_ID_OCT)
DECLARE_BUILTIN_FUNCTION(DecFunction, FUNCTION_ID_DEC)
DECLARE_BUILTIN_FUNCTION(HexFunction, FUNCTION_ID_HEX)
DECLARE_BUILTIN_FUNCTION(BaseFunction, FUNCTION_ID_BASE)
DECLARE_BUILTIN_FUNCTION(RomanFunction, FUNCTION_ID_ROMAN)
DECLARE_BUILTIN_FUNCTION(BijectiveFunction, FUNCTION_ID_BIJECTIVE)
DECLARE_BUILTIN_FUNCTION(BinaryDecimalFunction, FUNCTION_ID_BINARY_DECIMAL)

DECLARE_BUILTIN_FUNCTION(IEEE754FloatFunction, FUNCTION_ID_IEEE754_FLOAT)
DECLARE_BUILTIN_FUNCTION(IEEE754FloatBitsFunction,
                         FUNCTION_ID_IEEE754_FLOAT_BITS)
DECLARE_BUILTIN_FUNCTION(IEEE754FloatComponentsFunction,
                         FUNCTION_ID_IEEE754_FLOAT_COMPONENTS)
DECLARE_BUILTIN_FUNCTION(IEEE754FloatValueFunction,
                         FUNCTION_ID_IEEE754_FLOAT_VALUE)
DECLARE_BUILTIN_FUNCTION(IEEE754FloatErrorFunction,
                         FUNCTION_ID_IEEE754_FLOAT_ERROR)

DECLARE_BUILTIN_FUNCTION_B(IsNumberFunction, FUNCTION_ID_IS_NUMBER)
DECLARE_BUILTIN_FUNCTION_B(IsRealFunction, FUNCTION_ID_IS_REAL)
DECLARE_BUILTIN_FUNCTION_B(IsRationalFunction, FUNCTION_ID_IS_RATIONAL)
DECLARE_BUILTIN_FUNCTION_B(IsIntegerFunction, FUNCTION_ID_IS_INTEGER)
DECLARE_BUILTIN_FUNCTION_B(OddFunction, FUNCTION_ID_ODD)
DECLARE_BUILTIN_FUNCTION_B(EvenFunction, FUNCTION_ID_EVEN)

DECLARE_BUILTIN_FUNCTION(PolynomialUnitFunction, FUNCTION_ID_POLYNOMIAL_UNIT)
DECLARE_BUILTIN_FUNCTION(PolynomialPrimpartFunction,
                         FUNCTION_ID_POLYNOMIAL_PRIMPART)
DECLARE_BUILTIN_FUNCTION(PolynomialContentFunction,
                         FUNCTION_ID_POLYNOMIAL_CONTENT)
DECLARE_BUILTIN_FUNCTION(CoeffFunction, FUNCTION_ID_COEFF)
DECLARE_BUILTIN_FUNCTION(LCoeffFunction, FUNCTION_ID_L_COEFF)
DECLARE_BUILTIN_FUNCTION(TCoeffFunction, FUNCTION_ID_T_COEFF)
DECLARE_BUILTIN_FUNCTION(DegreeFunction, FUNCTION_ID_DEGREE)
DECLARE_BUILTIN_FUNCTION(LDegreeFunction, FUNCTION_ID_L_DEGREE)

DECLARE_BUILTIN_FUNCTION(BitXorFunction, FUNCTION_ID_BIT_XOR)
DECLARE_BUILTIN_FUNCTION_B(XorFunction, FUNCTION_ID_XOR)
DECLARE_BUILTIN_FUNCTION(BitCmpFunction, FUNCTION_ID_BIT_CMP)
DECLARE_BUILTIN_FUNCTION(ShiftFunction, FUNCTION_ID_SHIFT)
DECLARE_BUILTIN_FUNCTION(CircularShiftFunction, FUNCTION_ID_CIRCULAR_SHIFT)

DECLARE_BUILTIN_FUNCTION(ForFunction, FUNCTION_ID_FOR)
DECLARE_BUILTIN_FUNCTION_M(IFFunction, FUNCTION_ID_IF)

DECLARE_BUILTIN_FUNCTION(TotalFunction, FUNCTION_ID_TOTAL)
DECLARE_BUILTIN_FUNCTION(PercentileFunction, FUNCTION_ID_PERCENTILE)
DECLARE_BUILTIN_FUNCTION(MinFunction, FUNCTION_ID_MIN)
DECLARE_BUILTIN_FUNCTION(MaxFunction, FUNCTION_ID_MAX)
DECLARE_BUILTIN_FUNCTION(ModeFunction, FUNCTION_ID_MODE)
DECLARE_BUILTIN_FUNCTION_RPI(RandFunction, FUNCTION_ID_RAND)
DECLARE_BUILTIN_FUNCTION_R2(RandnFunction, FUNCTION_ID_RANDN)
DECLARE_BUILTIN_FUNCTION_RPI(RandPoissonFunction, FUNCTION_ID_RAND_POISSON)

DECLARE_BUILTIN_FUNCTION(DateFunction, FUNCTION_ID_DATE)
DECLARE_BUILTIN_FUNCTION(DateTimeFunction, FUNCTION_ID_DATE_TIME)
DECLARE_BUILTIN_FUNCTION(TimeValueFunction, FUNCTION_ID_TIME_VALUE)
DECLARE_BUILTIN_FUNCTION(TimestampFunction, FUNCTION_ID_TIMESTAMP)
DECLARE_BUILTIN_FUNCTION(TimestampToDateFunction, FUNCTION_ID_TIMESTAMP_TO_DATE)
DECLARE_BUILTIN_FUNCTION(DaysFunction, FUNCTION_ID_DAYS)
DECLARE_BUILTIN_FUNCTION(YearFracFunction, FUNCTION_ID_YEAR_FRAC)
DECLARE_BUILTIN_FUNCTION(WeekFunction, FUNCTION_ID_WEEK)
DECLARE_BUILTIN_FUNCTION(WeekdayFunction, FUNCTION_ID_WEEKDAY)
DECLARE_BUILTIN_FUNCTION(MonthFunction, FUNCTION_ID_MONTH)
DECLARE_BUILTIN_FUNCTION(DayFunction, FUNCTION_ID_DAY)
DECLARE_BUILTIN_FUNCTION(YearFunction, FUNCTION_ID_YEAR)
DECLARE_BUILTIN_FUNCTION(YeardayFunction, FUNCTION_ID_YEARDAY)
DECLARE_BUILTIN_FUNCTION(TimeFunction, FUNCTION_ID_TIME)
DECLARE_BUILTIN_FUNCTION(AddDaysFunction, FUNCTION_ID_ADD_DAYS)
DECLARE_BUILTIN_FUNCTION(AddMonthsFunction, FUNCTION_ID_ADD_MONTHS)
DECLARE_BUILTIN_FUNCTION(AddYearsFunction, FUNCTION_ID_ADD_YEARS)
DECLARE_BUILTIN_FUNCTION(LunarPhaseFunction, FUNCTION_ID_LUNAR_PHASE)
DECLARE_BUILTIN_FUNCTION(NextLunarPhaseFunction, FUNCTION_ID_NEXT_LUNAR_PHASE)

DECLARE_BUILTIN_FUNCTION_PI(AsciiFunction, FUNCTION_ID_ASCII)
DECLARE_BUILTIN_FUNCTION(CharFunction, FUNCTION_ID_CHAR)
DECLARE_BUILTIN_FUNCTION_PI(LengthFunction, FUNCTION_ID_LENGTH)
DECLARE_BUILTIN_FUNCTION(ConcatenateFunction, FUNCTION_ID_CONCATENATE)
DECLARE_BUILTIN_FUNCTION(ReplaceFunction, FUNCTION_ID_REPLACE)
DECLARE_BUILTIN_FUNCTION(StripUnitsFunction, FUNCTION_ID_STRIP_UNITS)
DECLARE_BUILTIN_FUNCTION(CustomSumFunction, FUNCTION_ID_CUSTOM_SUM)
DECLARE_BUILTIN_FUNCTION(FunctionFunction, FUNCTION_ID_FUNCTION)
DECLARE_BUILTIN_FUNCTION(TitleFunction, FUNCTION_ID_TITLE)
DECLARE_BUILTIN_FUNCTION(RepresentsNumberFunction,
                         FUNCTION_ID_REPRESENTS_NUMBER)
DECLARE_BUILTIN_FUNCTION(RepresentsRealFunction, FUNCTION_ID_REPRESENTS_REAL)
DECLARE_BUILTIN_FUNCTION(RepresentsRationalFunction,
                         FUNCTION_ID_REPRESENTS_RATIONAL)
DECLARE_BUILTIN_FUNCTION(RepresentsIntegerFunction,
                         FUNCTION_ID_REPRESENTS_INTEGER)
DECLARE_BUILTIN_FUNCTION(ErrorFunction, FUNCTION_ID_ERROR)
DECLARE_BUILTIN_FUNCTION(WarningFunction, FUNCTION_ID_WARNING)
DECLARE_BUILTIN_FUNCTION(MessageFunction, FUNCTION_ID_MESSAGE)
DECLARE_BUILTIN_FUNCTION(SaveFunction, FUNCTION_ID_SAVE)
DECLARE_BUILTIN_FUNCTION(RegisterFunction, FUNCTION_ID_REGISTER)
DECLARE_BUILTIN_FUNCTION(StackFunction, FUNCTION_ID_STACK)
DECLARE_BUILTIN_FUNCTION(CommandFunction, FUNCTION_ID_COMMAND)
DECLARE_BUILTIN_FUNCTION(PlotFunction, FUNCTION_ID_PLOT)
DECLARE_BUILTIN_FUNCTION_R(IntervalFunction, FUNCTION_ID_INTERVAL)
DECLARE_BUILTIN_FUNCTION(UncertaintyFunction, FUNCTION_ID_UNCERTAINTY)
DECLARE_BUILTIN_FUNCTION(GeographicDistanceFunction, FUNCTION_ID_GEO_DISTANCE)

#endif
