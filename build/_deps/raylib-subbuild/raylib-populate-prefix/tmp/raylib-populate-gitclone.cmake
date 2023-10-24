# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

<<<<<<< Updated upstream
cmake_minimum_required(VERSION 3.5)

if(EXISTS "D:/ComOrg/MeowXMonster/build/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp/raylib-populate-gitclone-lastrun.txt" AND EXISTS "D:/ComOrg/MeowXMonster/build/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp/raylib-populate-gitinfo.txt" AND
  "D:/ComOrg/MeowXMonster/build/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp/raylib-populate-gitclone-lastrun.txt" IS_NEWER_THAN "D:/ComOrg/MeowXMonster/build/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp/raylib-populate-gitinfo.txt")
  message(STATUS
    "Avoiding repeated git clone, stamp file is up to date: "
    "'D:/ComOrg/MeowXMonster/build/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp/raylib-populate-gitclone-lastrun.txt'"
  )
=======
if(NOT "/home/pi/Desktop/MeowXMonster/build/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp/raylib-populate-gitinfo.txt" IS_NEWER_THAN "/home/pi/Desktop/MeowXMonster/build/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp/raylib-populate-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/home/pi/Desktop/MeowXMonster/build/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp/raylib-populate-gitclone-lastrun.txt'")
>>>>>>> Stashed changes
  return()
endif()

execute_process(
<<<<<<< Updated upstream
  COMMAND ${CMAKE_COMMAND} -E rm -rf "D:/ComOrg/MeowXMonster/build/_deps/raylib-src"
=======
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/home/pi/Desktop/MeowXMonster/build/_deps/raylib-src"
>>>>>>> Stashed changes
  RESULT_VARIABLE error_code
)
if(error_code)
<<<<<<< Updated upstream
  message(FATAL_ERROR "Failed to remove directory: 'D:/ComOrg/MeowXMonster/build/_deps/raylib-src'")
=======
  message(FATAL_ERROR "Failed to remove directory: '/home/pi/Desktop/MeowXMonster/build/_deps/raylib-src'")
>>>>>>> Stashed changes
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
<<<<<<< Updated upstream
    COMMAND "C:/Program Files/Git/cmd/git.exe" 
            clone --no-checkout --progress --config "advice.detachedHead=false" "https://github.com/raysan5/raylib.git" "raylib-src"
    WORKING_DIRECTORY "D:/ComOrg/MeowXMonster/build/_deps"
=======
    COMMAND "/usr/bin/git"  clone --no-checkout --progress "https://github.com/raysan5/raylib.git" "raylib-src"
    WORKING_DIRECTORY "/home/pi/Desktop/MeowXMonster/build/_deps"
>>>>>>> Stashed changes
    RESULT_VARIABLE error_code
  )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once: ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/raysan5/raylib.git'")
endif()

execute_process(
<<<<<<< Updated upstream
  COMMAND "C:/Program Files/Git/cmd/git.exe" 
          checkout "master" --
  WORKING_DIRECTORY "D:/ComOrg/MeowXMonster/build/_deps/raylib-src"
=======
  COMMAND "/usr/bin/git"  checkout master --
  WORKING_DIRECTORY "/home/pi/Desktop/MeowXMonster/build/_deps/raylib-src"
>>>>>>> Stashed changes
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'master'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
<<<<<<< Updated upstream
    COMMAND "C:/Program Files/Git/cmd/git.exe" 
            submodule update --recursive --init 
    WORKING_DIRECTORY "D:/ComOrg/MeowXMonster/build/_deps/raylib-src"
=======
    COMMAND "/usr/bin/git"  submodule update --recursive --init 
    WORKING_DIRECTORY "/home/pi/Desktop/MeowXMonster/build/_deps/raylib-src"
>>>>>>> Stashed changes
    RESULT_VARIABLE error_code
  )
endif()
if(error_code)
<<<<<<< Updated upstream
  message(FATAL_ERROR "Failed to update submodules in: 'D:/ComOrg/MeowXMonster/build/_deps/raylib-src'")
=======
  message(FATAL_ERROR "Failed to update submodules in: '/home/pi/Desktop/MeowXMonster/build/_deps/raylib-src'")
>>>>>>> Stashed changes
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
<<<<<<< Updated upstream
  COMMAND ${CMAKE_COMMAND} -E copy "D:/ComOrg/MeowXMonster/build/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp/raylib-populate-gitinfo.txt" "D:/ComOrg/MeowXMonster/build/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp/raylib-populate-gitclone-lastrun.txt"
=======
  COMMAND ${CMAKE_COMMAND} -E copy
    "/home/pi/Desktop/MeowXMonster/build/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp/raylib-populate-gitinfo.txt"
    "/home/pi/Desktop/MeowXMonster/build/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp/raylib-populate-gitclone-lastrun.txt"
>>>>>>> Stashed changes
  RESULT_VARIABLE error_code
)
if(error_code)
<<<<<<< Updated upstream
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: 'D:/ComOrg/MeowXMonster/build/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp/raylib-populate-gitclone-lastrun.txt'")
=======
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/home/pi/Desktop/MeowXMonster/build/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp/raylib-populate-gitclone-lastrun.txt'")
>>>>>>> Stashed changes
endif()
