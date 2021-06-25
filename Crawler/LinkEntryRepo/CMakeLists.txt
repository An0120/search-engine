set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false *.hpp *.cpp)

add_library(${BINARY}_linkEntryRepo STATIC ${SOURCES})

target_link_libraries(${BINARY}_linkEntryRepo -lmysqlclient -lmysqlpp)
target_compile_options(${BINARY}_linkEntryRepo PUBLIC -I/usr/include/mysql)