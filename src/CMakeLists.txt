set(src_list 
	${CMAKE_CURRENT_SOURCE_DIR}/logger/logger.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/lightlog.cpp
	)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
add_library(lightlog ${src_list})
