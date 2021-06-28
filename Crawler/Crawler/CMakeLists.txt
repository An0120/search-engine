set(BINARY ${CMAKE_PROJECT_NAME})
set(INCLUDE_DIR
    ../PageLoader/ ../Parser/
    ../WebsiteRepo/ ../LinkEntryRepo

include_directories(${INCLUDE_DIR})

add_executable(${BINARY}_run main.cpp)

target_link_libraries(${BINARY}_run PUBLIC
                      gumbo curl curlpp
                      ${BINARY}_loader ${BINARY}_parser
                      ${BINARY}_linkEntryRepo ${BINARY}_websiteRepo
