cmake_minimum_required(VERSION 3.13)

project(IMACRUN)
add_executable(${PROJECT_NAME})
# (optional) put the binary files in this directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)

# Pour gérer un bug a la fac, a supprimer sur machine perso:
# set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

add_subdirectory(third-party/glimac)
target_link_libraries(${PROJECT_NAME} glimac::glimac)

set(ALL_LIBRARIES ${SDL_LIBRARY} ${OPENGL_LIBRARIES})

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} ${ALL_LIBRARIES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11) # use at least c++ 11
target_compile_options(${PROJECT_NAME} PRIVATE -W -Wall -Werror -O2)   # specify some compilation flags

file(COPY assets DESTINATION ${PROJECT_BINARY_DIR}/bin)