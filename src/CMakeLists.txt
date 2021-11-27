cmake_minimum_required(VERSION 3.13)


file(GLOB HEADER_FILES *.hpp)
file(GLOB SRC_FILES *.cpp)
file(GLOB_RECURSE SHADER_FILES *.glsl)

foreach(SRC_FILE ${SRC_FILES})
    get_filename_component(FILE ${SRC_FILE} NAME_WE)
    get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    set(OUTPUT IMACRUN)
    add_executable(${OUTPUT} ${SRC_FILE} ${HEADER_FILES} ${SHADER_FILES})
    target_link_libraries(${OUTPUT} ${ALL_LIBRARIES})
	target_compile_features(${OUTPUT} PRIVATE cxx_std_11) # use at least c++ 11
	target_compile_options(${OUTPUT} PRIVATE -W -Wall -Werror -O2)   # specify some compilation flags
endforeach()

file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

