# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/boost_build/src/boost_external")
  file(MAKE_DIRECTORY "/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/boost_build/src/boost_external")
endif()
file(MAKE_DIRECTORY
  "/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/boost_build/src/boost_external-build"
  "/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/installed"
  "/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/boost_build/tmp"
  "/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/boost_build/src/boost_external-stamp"
  "/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/boost_build/src"
  "/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/boost_build/src/boost_external-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/boost_build/src/boost_external-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/boost_build/src/boost_external-stamp${cfgdir}") # cfgdir has leading slash
endif()
