# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Desktop/pizh2322_malcev-week07_week16/labwork5/out/build/x64-Debug/_deps/googletest-src"
  "D:/Desktop/pizh2322_malcev-week07_week16/labwork5/out/build/x64-Debug/_deps/googletest-build"
  "D:/Desktop/pizh2322_malcev-week07_week16/labwork5/out/build/x64-Debug/_deps/googletest-subbuild/googletest-populate-prefix"
  "D:/Desktop/pizh2322_malcev-week07_week16/labwork5/out/build/x64-Debug/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "D:/Desktop/pizh2322_malcev-week07_week16/labwork5/out/build/x64-Debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "D:/Desktop/pizh2322_malcev-week07_week16/labwork5/out/build/x64-Debug/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "D:/Desktop/pizh2322_malcev-week07_week16/labwork5/out/build/x64-Debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Desktop/pizh2322_malcev-week07_week16/labwork5/out/build/x64-Debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Desktop/pizh2322_malcev-week07_week16/labwork5/out/build/x64-Debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
