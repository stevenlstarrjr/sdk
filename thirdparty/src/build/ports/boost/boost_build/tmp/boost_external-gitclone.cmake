# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

if(EXISTS "/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/boost_build/src/boost_external-stamp/boost_external-gitclone-lastrun.txt" AND EXISTS "/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/boost_build/src/boost_external-stamp/boost_external-gitinfo.txt" AND
  "/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/boost_build/src/boost_external-stamp/boost_external-gitclone-lastrun.txt" IS_NEWER_THAN "/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/boost_build/src/boost_external-stamp/boost_external-gitinfo.txt")
  message(VERBOSE
    "Avoiding repeated git clone, stamp file is up to date: "
    "'/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/boost_build/src/boost_external-stamp/boost_external-gitclone-lastrun.txt'"
  )
  return()
endif()

# Even at VERBOSE level, we don't want to see the commands executed, but
# enabling them to be shown for DEBUG may be useful to help diagnose problems.
cmake_language(GET_MESSAGE_LOG_LEVEL active_log_level)
if(active_log_level MATCHES "DEBUG|TRACE")
  set(maybe_show_command COMMAND_ECHO STDOUT)
else()
  set(maybe_show_command "")
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/boost_build/src/boost_external"
  RESULT_VARIABLE error_code
  ${maybe_show_command}
)
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/boost_build/src/boost_external'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git"
            clone --no-checkout --depth 1 --no-single-branch --config "advice.detachedHead=false" "https://github.com/boostorg/boost.git" "boost_external"
    WORKING_DIRECTORY "/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/boost_build/src"
    RESULT_VARIABLE error_code
    ${maybe_show_command}
  )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(NOTICE "Had to git clone more than once: ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/boostorg/boost.git'")
endif()

execute_process(
  COMMAND "/usr/bin/git"
          checkout "boost-1.83.0" --
  WORKING_DIRECTORY "/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/boost_build/src/boost_external"
  RESULT_VARIABLE error_code
  ${maybe_show_command}
)
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'boost-1.83.0'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/bin/git" 
            submodule update --recursive --init 
    WORKING_DIRECTORY "/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/boost_build/src/boost_external"
    RESULT_VARIABLE error_code
    ${maybe_show_command}
  )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/boost_build/src/boost_external'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy "/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/boost_build/src/boost_external-stamp/boost_external-gitinfo.txt" "/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/boost_build/src/boost_external-stamp/boost_external-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  ${maybe_show_command}
)
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/home/stevenstarr/Projects/Hultrix/thirdparty/src/build/ports/boost/boost_build/src/boost_external-stamp/boost_external-gitclone-lastrun.txt'")
endif()
