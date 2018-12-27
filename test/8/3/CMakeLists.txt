cmake_minimum_required(VERSION 2.8)

project(IMAGEOPENCV)

set(CMAKE_CXX_FLAGS "-std=c++11")

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} include)

AUX_SOURCE_DIRECTORY(src DIR_SRC)

add_executable(imageBasics ${DIR_SRC})

target_link_libraries(imageBasics ${OpenCV_LIBS})
