add_library(glimac)
add_library(glimac::glimac ALIAS glimac)

target_include_directories(glimac PUBLIC include)
file(GLOB_RECURSE SRC_FILES src/*.cpp)
target_sources(glimac PRIVATE ${SRC_FILES})

add_subdirectory(third-party/glm)
target_link_libraries(glimac PUBLIC glm::glm)

find_package(GLEW REQUIRED)
target_include_directories(glimac PUBLIC ${GLEW_INCLUDE_DIR})
target_link_libraries(glimac PUBLIC ${GLEW_LIBRARIES})

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
# Pour gérer un bug a la fac, a supprimer sur machine perso:
# set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)

target_include_directories(glimac PUBLIC
    ${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})
target_link_libraries(glimac PUBLIC
    ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})