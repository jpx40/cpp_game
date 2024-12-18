cmake_minimum_required(VERSION 3.22)
project(cpp_game CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# # # # # # # # # # # # # # # # # # # # #
# # ############################################################# Add
# dependencies with FetchContent # # # # # # # # # # # # # # # # # # # #
# # ############################################################################

function(add_git_dependency libName gitURL gitTag)
  FetchContent_Declare(
    ${libName}
    GIT_REPOSITORY ${gitURL}
    GIT_TAG ${gitTag}
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE)
  FetchContent_MakeAvailable(${libName})
  target_compile_options(${libName} PRIVATE "-w")
endfunction()

# FetchContent_Declare(
#   LDtkLoader
#   GIT_REPOSITORY https://github.com/Madour/LDtkLoader.git
#   GIT_TAG 1.5.3.1
#   GIT_SHALLOW TRUE
#   GIT_PROGRESS TRUE)
# FetchContent_MakeAvailable(LDtkLoader)
# target_compile_options(LDtkLoader PRIVATE "-w")

# FetchContent_Declare(
#   matchit
#   GIT_REPOSITORY https://github.com/BowenFu/matchit.cpp.git
#   GIT_TAG main)

# FetchContent_GetProperties(matchit)
# if(NOT matchit_POPULATED)
#   FetchContent_Populate(matchit)
#   add_subdirectory(${matchit_SOURCE_DIR} ${matchit_BINARY_DIR} EXCLUDE_FROM_ALL)
# endif()

# Add Raylib
set(BUILD_EXAMPLES
    OFF
    CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES
    OFF
    CACHE BOOL "" FORCE) # don't build the supplied example games
add_git_dependency(raylib https://github.com/raysan5/raylib.git 5.5)

# add_git_dependency(raygui https://github.com/raysan5/raygui 4.0)

# add_git_dependency(raylib-cpp https://github.com/RobLoach/raylib-cpp 5.0.0)
# Add LDtkLoader add_git_dependency(LDtkLoader
# https://github.com/Madour/LDtkLoader.git 1.5.3.1)

# Add Box2d
set(BOX2D_BUILD_UNIT_TESTS
    OFF
    CACHE BOOL "" FORCE)
set(BOX2D_BUILD_TESTBED
    OFF
    CACHE BOOL "" FORCE)
# add_git_dependency(box2d https://github.com/erincatto/box2d.git v2.4.1)

# Add {fmt} library
add_git_dependency(fmt https://github.com/fmtlib/fmt.git 10.2.1)

# # # # # # # # # # # # # # # # # # # # #
# # ############################################################# Project
# executable setup # # # # # # # # # # # # # # # # # # # #
# # ############################################################################

# Adding our source files Define PROJECT_SOURCES as a list of all source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

# Define PROJECT_INCLUDE to be the path to the include directory of the project
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/")

# Declaring our executable
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
# target_link_libraries(${PROJECT_NAME} PRIVATE raylib-cpp)
# target_link_libraries(${PROJECT_NAME} PRIVATE matchit)
# # target_link_libraries(${PROJECT_NAME} PRIVATE raygui)
# target_link_libraries(${PROJECT_NAME} PRIVATE LDtkLoader::LDtkLoader)
# target_link_libraries(${PROJECT_NAME} PRIVATE box2d)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt)

# # # # # # # # # # # # # # # # # # # # #
# # ############################################################# Project build
# settings # # # # # # # # # # # # # # # # # # # #
# # ############################################################################

add_definitions(-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})

# Setting ASSETS_PATH
if(CMAKE_BUILD_TYPE MATCHES "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -DDEBUG")

  # Set the asset path macro to the absolute path on the dev machine
  target_compile_definitions(
    ${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
else()
  # Set the asset path macro in release mode to a relative path that assumes the
  # assets folder is in the same directory as the game executable
  target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets/")
endif()

# Set common compiler flags SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall
# -Wswitch")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if(${PLATFORM} STREQUAL "Web")
  # Tell Emscripten to build an .html file.
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os")
  set(CMAKE_EXE_LINKER_FLAGS
      "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -Os -Wall -s TOTAL_MEMORY=67108864 -s FORCE_FILESYSTEM=1 --preload-file assets/ --shell-file ../src/minshell.html"
  )
  set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your
  # executable to build with the emscripten html template so that you can
  # directly open it.
  set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
  target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="/assets/"
  ) # Set the asset path macro in
  # release mode to a relative path that assumes the assets folder is in the
  # same directory as the game executable
endif()

# Ensure that hot-reload is enabled for VS
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /ZI")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")
endif()
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)
include(FetchContent)
FetchContent_Declare(
  toml11
  GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
  GIT_TAG        v4.1.0
)
FetchContent_MakeAvailable(toml11)

target_link_libraries(${PROJECT_NAME} PRIVATE toml11::toml11)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)