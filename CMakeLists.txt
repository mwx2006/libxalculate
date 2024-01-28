cmake_minimum_required(VERSION 3.12)
project(libqalculate VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

if(NOT DEFINED DATA_DIR)
    set(DATA_DIR "data")
endif()

if(NOT DEFINED LOCALE_DIR)
    set(LOCALE_DIR "locale")
endif()

option(ENABLE_GNUPLOT "ENABLE_GNUPLOT" OFF)

find_package(LibXml2 REQUIRED)
find_package(CURL)
find_package(Intl REQUIRED)
find_package(ICU COMPONENTS uc i18n)
find_package(PkgConfig REQUIRED)
find_package(Iconv)
pkg_check_modules(mpfr REQUIRED IMPORTED_TARGET mpfr)
pkg_check_modules(gmp REQUIRED IMPORTED_TARGET gmp)
pkg_check_modules(readline IMPORTED_TARGET readline)

add_library(libqalculate STATIC libqalculate/BuiltinFunctions-algebra.cc
    libqalculate/BuiltinFunctions-calculus.cc
    libqalculate/BuiltinFunctions-combinatorics.cc
    libqalculate/BuiltinFunctions-datetime.cc
    libqalculate/BuiltinFunctions-explog.cc
    libqalculate/BuiltinFunctions-logical.cc
    libqalculate/BuiltinFunctions-matrixvector.cc
    libqalculate/BuiltinFunctions-number.cc
    libqalculate/BuiltinFunctions-special.cc
    libqalculate/BuiltinFunctions-statistics.cc
    libqalculate/BuiltinFunctions-trigonometry.cc
    libqalculate/BuiltinFunctions-util.cc
    libqalculate/Calculator-calculate.cc
    libqalculate/Calculator-convert.cc
    libqalculate/Calculator-definitions.cc
    libqalculate/Calculator-parse.cc
    libqalculate/Calculator-plot.cc
    libqalculate/Calculator.cc
    libqalculate/DataSet.cc
    libqalculate/ExpressionItem.cc
    libqalculate/Function.cc
    libqalculate/MathStructure-calculate.cc
    libqalculate/MathStructure-convert.cc
    libqalculate/MathStructure-decompose.cc
    libqalculate/MathStructure-differentiate.cc
    libqalculate/MathStructure-eval.cc
    libqalculate/MathStructure-factor.cc
    libqalculate/MathStructure-gcd.cc
    libqalculate/MathStructure-integrate.cc
    libqalculate/MathStructure-isolatex.cc
    libqalculate/MathStructure-limit.cc
    libqalculate/MathStructure-matrixvector.cc
    libqalculate/MathStructure-polynomial.cc
    libqalculate/MathStructure-print.cc
    libqalculate/MathStructure.cc
    libqalculate/Number.cc
    libqalculate/Prefix.cc
    libqalculate/QalculateDateTime.cc
    libqalculate/Unit.cc
    libqalculate/util.cc
    libqalculate/Variable.cc)

target_link_libraries(libqalculate PRIVATE PkgConfig::mpfr PkgConfig::gmp LibXml2::LibXml2)

if(${readline_FOUND})
    target_link_libraries(libqalculate PRIVATE PkgConfig::readline)
    add_compile_definitions(HAVE_LIBREADLINE)
endif()

if(${Iconv_FOUND})
    target_link_libraries(libqalculate PRIVATE Iconv::Iconv)
    add_compile_definitions(HAVE_ICONV ICONV_CONST=)
endif()

if(${CURL_FOUND})
    add_compile_definitions(HAVE_LIBCURL)
    target_link_libraries(libqalculate PRIVATE CURL::libcurl)
endif()

if(${ICU_FOUND})
    add_compile_definitions(HAVE_ICU)
    target_link_libraries(libqalculate PRIVATE ICU::uc ICU::i18n)
endif()

if(${Intl_FOUND})
    add_compile_definitions(ENABLE_NLS)
    target_link_libraries(libqalculate PRIVATE Intl::Intl)
endif()

if(${ENABLE_GNUPLOT})
    add_compile_definitions(HAVE_GNUPLOT_CALL)
endif()

include_directories(${Intl_INCLUDE_DIRS} ".")
add_compile_definitions(NOMINMAX
    HAVE_UNORDERED_MAP
    VERSION="MWX-QALC-VER ${PROJECT_VERSION}"
    GETTEXT_PACKAGE="libqalculate"
    PACKAGE_LOCALE_DIR="${LOCALE_DIR}"
    PACKAGE_DATA_DIR="${DATA_DIR}")
add_executable(qalc qalc.cc)
target_link_libraries(qalc PRIVATE libqalculate)
