cmake_minimum_required(VERSION 2.8)
project( Clustering_SCCN_SCE )
set(BUILD_SHARED_LIBS OFF)

find_package( OpenCV REQUIRED )

if (OpenCV_FOUND)
   include_directories(${OpenCV_INCLUDE_DIRS})
endif()


SET(stamp_removal_HEADERS 	
				StandardHeaders.h
				folder.h
				binarization.h				
				GeneralFunctions.h
				Image_proc_functions.h
				ScalarColorFeature.h
				color_stamp_removal.h)  


SET(stamp_removal_SOURCES  	
				color_stamp_removal.cpp
				folder.cpp
				binarization.cpp
				GeneralFunctions.cpp				
				Image_proc_functions.cpp
				ScalarColorFeature.cpp
				)


# Or set it globally for all targets:
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

ADD_EXECUTABLE(stampr ${stamp_removal_HEADERS} ${stamp_removal_SOURCES})
TARGET_LINK_LIBRARIES(stampr ${OpenCV_LIBS})
set(CMAKE_BUILD_TYPE Debug)

