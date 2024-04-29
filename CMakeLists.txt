cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME raytracer)
project(${PROJECT_NAME})
#source_directory(src)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fno-gnu-unique")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -g3 -fno-gnu-unique")
#SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -g -fsanitize=address,leak,undefined")
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address,leak,undefined")

include_directories(src)
include_directories(test)


#add_executable(${PROJECT_NAME} src/main.cpp)

add_executable(rta test/test.cpp)

#TARGET_LINK_LIBRARIES(arcade dl)

add_subdirectory(librairies/template)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "lib")

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
#        $<TARGET_FILE:${PROJECT_NAME}>
#        ${PROJECT_SOURCE_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>)

add_custom_command(TARGET rta POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:rta>
        ${PROJECT_SOURCE_DIR}/$<TARGET_FILE_NAME:rta>)
