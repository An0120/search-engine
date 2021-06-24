set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false *.hpp *.cpp)

add_library(${BINARY}_parser STATIC ${SOURCES})
target_link_libraries(${BINARY}_parser -lgumbo)