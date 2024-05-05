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
include_directories(src/maths)
include_directories(src/material)
include_directories(src/camera)
include_directories(src/primitive)
include_directories(src/list_object)
include_directories(src/DlLoader)


add_executable(${PROJECT_NAME} src/main.cpp
        src/builder/builder.cpp
        src/maths/Interval.cpp
        src/maths/Utils.cpp
        src/maths/Ray.cpp
        src/maths/Vec3.cpp
        src/material/Color.cpp
        src/DlLoader/CLibEncapsulation.cpp
        src/camera/Camera.cpp
        src/list_object/HitRecord.cpp
        src/primitive/PrimList.cpp
        src/material/ColorMat.cpp
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} config++)

#add_subdirectory(librairies/template)
add_subdirectory(librairies/lambertian)
add_subdirectory(librairies/sphere)
add_subdirectory(librairies/metals)
add_subdirectory(librairies/dialectric)
add_subdirectory(librairies/plan)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "lib")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:${PROJECT_NAME}>
        ${PROJECT_SOURCE_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>)
