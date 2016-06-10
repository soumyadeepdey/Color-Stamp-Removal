cmake_minimum_required(VERSION 2.8)
project( DRD )
find_package( OpenCV REQUIRED )
add_executable( stampr stamp_removal.cpp )
target_link_libraries( stampr ${OpenCV_LIBS} )

