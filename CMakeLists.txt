cmake_minimum_required(VERSION 3.13)

project(IMACRUN)
add_executable(${PROJECT_NAME})
# (optional) put the binary files in this directory
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(third-party/glimac)
target_link_libraries(${PROJECT_NAME} glimac::glimac)
add_subdirectory(third-party/assimp)
target_link_libraries(${PROJECT_NAME} assimp)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR}
                    ${OPENGL_INCLUDE_DIR})

target_link_libraries(  ${PROJECT_NAME} 
                        ${SDL2_LIBRARY}
                        ${SDL2_TTF_LIBRARIES}
                        ${OPENGL_LIBRARIES} 
                        )


file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${SRC_FILES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11) # use at least c++ 11
target_compile_options(${PROJECT_NAME} PRIVATE -W -Wall -Werror -O2)   # specify some compilation flags

# NB: this function requires policy CMP0112 which was set to NEW in CMake 3.19 (https://cmake.org/cmake/help/latest/policy/CMP0112.html#policy:CMP0112)
# If you are using a version of CMake lower than 3.19 then you need to call `cmake_policy(SET CMP0112 NEW)` just after `cmake_minimum_required(...)` in your main CMakeLists.txt file
# Otherwise you will get a "Cyclic dependencies" error

function(copyFolder FOLDER_NAME)
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/assets
                    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)
endfunction()

copyFolder(assets)



