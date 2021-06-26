set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false *hpp *cpp)

add_library(${BINARY}_documentRepo STATIC ${SOURCES})

target_link_libraries(${BINARY}_documentRepo -lmysqlclient -lmysqlpp)
target_compile_options(${BINARY}_documentRepo PUBLIC -I/usr/include/mysql)