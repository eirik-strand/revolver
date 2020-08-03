cmake_minimum_required(VERSION 2.8)
project( Revolver )
set (CMAKE_CXX_STANDARD 11)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( revolver src/revolver.cpp )
target_link_libraries( revolver ${OpenCV_LIBS} )

add_executable( tester src/accuracy_tester.cpp )
target_link_libraries( tester ${OpenCV_LIBS} )