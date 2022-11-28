phi_include_guard()

include(Functions)

# Detect information about the build environment

# CMake version
phi_trace("CMake version ${CMAKE_VERSION}")

# Detect Platform
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  phi_set_cache_value(NAME PHI_PLATFORM_WINDOWS VALUE 1)
  phi_trace("Platform: Windows")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  phi_set_cache_value(NAME PHI_PLATFORM_UNIX VALUE 1)
  phi_trace("Platform: Unix")

  if(ANDROID)
    phi_set_cache_value(NAME PHI_PLATFORM_ANDROID VALUE 1)
    phi_trace("Platform: Android")
  else()
    phi_set_cache_value(NAME PHI_PLATFORM_LINUX VALUE 1)
    phi_trace("Platform: Linux")
  endif()
elseif(CMAKE_SYSTEM_NAME MATCHES "^k?FreeBSD$")
  phi_set_cache_value(NAME PHI_PLATFORM_FREEBSD VALUE 1)
  phi_trace("Platform: FreeBSD")
elseif(CMAKE_SYSTEM_NAME MATCHES "^OpenBSD$")
  phi_set_cache_value(NAME PHI_PLATFORM_OPENBSD VALUE 1)
  phi_trace("Platform: OpenBSD")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
  if(IOS)
    phi_set_cache_value(NAME PHI_PLATFORM_IOS VALUE 1)
    phi_trace("Platform: IOS")
  else()
    phi_set_cache_value(NAME PHI_PLATFORM_MACOSX VALUE 1)
    phi_trace("Platform: MacOS")
  endif()
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
  phi_set_cache_value(NAME PHI_PLATFORM_ANDROID VALUE 1)
  phi_trace("Platform: Android")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
  phi_set_cache_value(NAME PHI_PLATFORM_EMSCRIPTEN VALUE 1)
  phi_trace("Platform: Emscripten")
else()
  phi_warn("Unsupported operating system or environment: ${CMAKE_SYSTEM_NAME}")
endif()

phi_log("System name: ${CMAKE_SYSTEM_NAME}")

# Detect the architecture (note: this test won't work for cross-compilation)
include(internal/PhiCXXCheckTypeSize)
phi_cxx_check_type_size(void* PHI_SIZEOF_VOID_PTR)
if(${PHI_SIZEOF_VOID_PTR})
  if(${PHI_SIZEOF_VOID_PTR} STREQUAL "4")
    phi_set_cache_value(NAME PHI_ARCH_32BITS VALUE 1)
    phi_set_cache_value(NAME PHI_SIZEOF_VOID_PTR VALUE 4)

    phi_trace("Arch: 32bits")
  elseif(${PHI_SIZEOF_VOID_PTR} STREQUAL "8")
    phi_set_cache_value(NAME PHI_ARCH_64BITS VALUE 1)
    phi_set_cache_value(NAME PHI_SIZEOF_VOID_PTR VALUE 8)

    phi_trace("Arch: 64bits")
  else()
    phi_warn("Unsupported architecture of size ${PHI_SIZEOF_VOID_PTR}")
  endif()
else()
  phi_warn("Failed to get size of void*")
endif()

# Detect compiler
phi_set_cache_value(NAME PHI_FLAG_PREFIX_CHAR VALUE -)

# CMAKE_CXX_COMPILER_ID is an internal CMake variable subject to change, but there is no other way
# to detect CLang at the moment
if(CMAKE_CXX_COMPILER MATCHES "clang[+][+]" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # Treat emcc separate from regular clang
  if(PHI_PLATFORM_EMSCRIPTEN)
    phi_set_cache_value(NAME PHI_COMPILER_EMCC VALUE 1)

    execute_process(COMMAND "${CMAKE_CXX_COMPILER}" "-dumpversion"
                    OUTPUT_VARIABLE EMCC_VERSION_OUTPUT)
    string(REGEX REPLACE "([.0-9]+).*" "\\1" PHI_EMCC_VERSION "${EMCC_VERSION_OUTPUT}")

    execute_process(COMMAND "${CMAKE_CXX_COMPILER}" "-dumpmachine" OUTPUT_VARIABLE PHI_EMCC_MACHINE)
    string(STRIP "${PHI_EMCC_MACHINE}" PHI_EMCC_MACHINE)

    phi_trace("Compiler: emcc-${PHI_EMCC_VERSION}")
    phi_trace("Machine: ${PHI_EMCC_MACHINE}")
  else()
    phi_set_cache_value(NAME PHI_COMPILER_CLANG VALUE 1)
    execute_process(COMMAND "${CMAKE_CXX_COMPILER}" "--version"
                    OUTPUT_VARIABLE CLANG_VERSION_OUTPUT)
    string(REGEX REPLACE ".*clang version ([.0-9]+).*" "\\1" PHI_CLANG_VERSION
                         "${CLANG_VERSION_OUTPUT}")

    execute_process(COMMAND "${CMAKE_CXX_COMPILER}" "-dumpmachine"
                    OUTPUT_VARIABLE PHI_CLANG_MACHINE)
    string(STRIP "${PHI_CLANG_MACHINE}" PHI_CLANG_MACHINE)

    phi_trace("Compiler: Clang-${PHI_CLANG_VERSION}")

    # Test for AppleClang
    if(CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
      phi_set_cache_value(NAME PHI_COMPILER_APPLECLANG VALUE 1)
      phi_trace("Compiler: AppleClang")
    endif()

    phi_trace("Machine: ${PHI_CLANG_MACHINE}")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCXX)
  phi_set_cache_value(NAME PHI_COMPILER_GCC VALUE 1)

  execute_process(COMMAND "${CMAKE_CXX_COMPILER}" "-dumpversion" OUTPUT_VARIABLE GCC_VERSION_OUTPUT)
  string(REGEX REPLACE "([.0-9]+).*" "\\1" PHI_GCC_VERSION "${GCC_VERSION_OUTPUT}")

  execute_process(COMMAND "${CMAKE_CXX_COMPILER}" "--version" OUTPUT_VARIABLE GCC_COMPILER_VERSION)
  string(REGEX MATCHALL ".*(tdm[64]*-[1-9]).*" PHI_COMPILER_GCC_TDM "${GCC_COMPILER_VERSION}")

  execute_process(COMMAND "${CMAKE_CXX_COMPILER}" "-dumpmachine" OUTPUT_VARIABLE PHI_GCC_MACHINE)
  string(STRIP "${PHI_GCC_MACHINE}" PHI_GCC_MACHINE)

  phi_trace("Compiler: GCC-${PHI_GCC_VERSION}")
  phi_trace("Machine: ${PHI_GCC_MACHINE}")

  if(GCC_MACHINE MATCHES ".*w64.*")
    phi_set_cache_value(NAME PHI_COMPILER_GCC_W64 VALUE 1)
  endif()
elseif(MSVC)
  phi_set_cache_value(NAME PHI_COMPILER_MSVC VALUE 1)
  phi_set_cache_value(NAME PHI_FLAG_PREFIX_CHAR VALUE /)

  if(MSVC_VERSION EQUAL 800)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 1.0)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "")
  elseif(MSVC_VERSION EQUAL 900)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 2.0)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "")
  elseif(MSVC_VERSION EQUAL 1000)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 4.0)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Developer Studio 4.0")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "")
  elseif(MSVC_VERSION EQUAL 1020)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 4.2)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Developer Studio 4.2")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "")
  elseif(MSVC_VERSION EQUAL 1100)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 5.0)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 5.0")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "")
  elseif(MSVC_VERSION EQUAL 1200)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 6.0)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 6.0")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "")
  elseif(MSVC_VERSION EQUAL 1300)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 7.0)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2003 7.0")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2003")
  elseif(MSVC_VERSION EQUAL 1310)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 7.1)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2003 7.1")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2003")
  elseif(MSVC_VERSION EQUAL 1400)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 8)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2005 8.0")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2005")
  elseif(MSVC_VERSION EQUAL 1500)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 9)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2008 9.0")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2008")
  elseif(MSVC_VERSION EQUAL 1600)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 10)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2010 10.0")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2010")
  elseif(MSVC_VERSION EQUAL 1700)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 11)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2012 11.0")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2012")
  elseif(MSVC_VERSION EQUAL 1800)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 12)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2013 12.0")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2013")
  elseif(MSVC_VERSION EQUAL 1900)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 14)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2015 14.0")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2015")
  elseif(MSVC_VERSION EQUAL 1910)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 14.1)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2017 15.0")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2017")
  elseif(MSVC_VERSION EQUAL 1911)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 14.11)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2017 15.3)")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2017")
  elseif(MSVC_VERSION EQUAL 1912)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 14.12)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2017 15.5)")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2017")
  elseif(MSVC_VERSION EQUAL 1913)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 14.13)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2017 version 15.6")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2017")
  elseif(MSVC_VERSION EQUAL 1914)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 14.14)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2017 version 15.7")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2017")
  elseif(MSVC_VERSION EQUAL 1915)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 14.15)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2017 version 15.8")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2017")
  elseif(MSVC_VERSION EQUAL 1916)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 14.16)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2017 version 15.9")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2017")
  elseif(MSVC_VERSION EQUAL 1920)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 14.2)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2019 Version 16.0")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2019")
  elseif(MSVC_VERSION EQUAL 1921)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 14.21)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2019 Version 16.1")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2019")
  elseif(MSVC_VERSION EQUAL 1922)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 14.22)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2019 Version 16.2")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2019")
  elseif(MSVC_VERSION EQUAL 1923)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 14.23)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2019 Version 16.3")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2019")
  elseif(MSVC_VERSION EQUAL 1924)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 14.24)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2019 Version 16.4")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2019")
  elseif(MSVC_VERSION EQUAL 1925)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 14.25)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2019 Version 16.5")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2019")
  elseif(MSVC_VERSION EQUAL 1926)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 14.26)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2019 Version 16.6")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2019")
  elseif(MSVC_VERSION EQUAL 1927)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 14.27)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2019 Version 16.7")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2019")
  elseif(MSVC_VERSION EQUAL 1928)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 14.28)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2019 Version 16.8/16.9")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2019")
  elseif(MSVC_VERSION EQUAL 1929)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 14.29)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2019 Version 16.10/16.11")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2019")
  elseif(MSVC_VERSION EQUAL 1930)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 14.30)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2022 Version 17.0")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2022")
  elseif(MSVC_VERSION EQUAL 1931)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 14.31)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2022 Version 17.1")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2022")
  elseif(MSVC_VERSION EQUAL 1932)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 14.32)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2022 Version 17.2")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2022")
  elseif(MSVC_VERSION EQUAL 1933)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 14.33)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2022 Version 17.3")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2022")
  elseif(MSVC_VERSION EQUAL 1934)
    phi_set_cache_value(NAME PHI_MSVC_VERSION VALUE 14.34)
    phi_set_cache_value(NAME PHI_MSVC_NAME VALUE "Visual Studio 2022 Version 17.4")
    phi_set_cache_value(NAME PHI_MSVC_YEAR VALUE "2022")
  else()
    phi_warn("Unknown version of MSVC used. MSVC_VERSION=${MSVC_VERSION}")
  endif()

  if(PHI_MSVC_VERSION)
    phi_log("Compiler: MSVC ${MSVC_VERSION}")
    phi_log("Compiler: MSVC ${PHI_MSVC_VERSION}")
    phi_log("Compiler: ${PHI_MSVC_NAME}")
  endif()
else()
  phi_warn("Unsupported compiler ${CMAKE_CXX_COMPILER_ID}")
endif()

phi_log("Compiler ID: \"${CMAKE_CXX_COMPILER_ID}\"")

# Check if using a problematic compiler
phi_set_cache_value(NAME PHI_IS_PROBLEMATIC_COMPILER VALUE FALSE)
if(PHI_COMPILER_APPLECLANG
   OR PHI_COMPILER_EMCC
   OR (PHI_COMPILER_GCC AND PHI_PLATFORM_WINDOWS))
  # TODO: Warning suppression for AppleClang, Emscripten and Mingw seems to not work correctly so we
  # disable warnings as errors and warnings to be able to build at all
  phi_set_cache_value(NAME PHI_IS_PROBLEMATIC_COMPILER VALUE TRUE)

  phi_warn(
    "Your using a known problematic compiler. Warnings and warnings as errors have been automatically disabled"
  )
endif()

phi_log("Generator: \"${CMAKE_GENERATOR}\"")

# Crosscompiling emulator
if(CMAKE_CROSSCOMPILING_EMULATOR)
  phi_log("Crosscompiling emulator: \"${CMAKE_CROSSCOMPILING_EMULATOR}\"")
endif()

# Check if CI Build
if(DEFINED ENV{CI})
  phi_set_cache_value(NAME PHI_CI_BUILD VALUE TRUE)
else()
  phi_set_cache_value(NAME PHI_CI_BUILD VALUE FALSE)
endif()

include(ProcessorCount)
ProcessorCount(ProcCount)
if(NOT ProcCount EQUAL 0)
  phi_set_cache_value(NAME PHI_PROCESSOR_COUNT VALUE ${ProcCount})
else()
  phi_warn("Failed to get processor count")

  # We always assume to have atleast one processor
  phi_set_cache_value(NAME PHI_PROCESSOR_COUNT VALUE 1)
endif()

phi_trace("Processor Count: ${PHI_PROCESSOR_COUNT}")
