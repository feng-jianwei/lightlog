include(gtest)
include_directories(
	${PROJECT_SOURCE_DIR}/src/logger
	${PROJECT_SOURCE_DIR}/src/logmgr
	${PROJECT_SOURCE_DIR}/src	
	${PROJECT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include
	${CMAKE_CURRENT_SOURCE_DIR}/googletest/googlemock/include
	)

add_executable(test_lightlog 	
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/test_lightlog.cpp
	)

target_link_directories(test_lightlog PRIVATE
	${CMAKE_BINARY_DIR}/lib
	)

target_link_libraries(test_lightlog PRIVATE
	gtest
	gmock
	lightlog
	)

add_test(NAME test_lightlog COMMAND test_lightlog)
