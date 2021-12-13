include_directories(${PROJECT_SOURCE_DIR}/include)
set(src_list ${CMAKE_CURRENT_SOURCE_DIR}/logmgr.cpp)

add_library(logmgr ${src_list})
