set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false *.hpp *.cpp)

add_library(${BINARY}_websiteRepo STATIC ${SOURCES})

target_link_libraries(${BINARY}_websiteRepo -lmysqlclient -lmysqlpp)
target_compile_options(${BINARY}_websiteRepo PUBLIC -I/usr/include/mysql)