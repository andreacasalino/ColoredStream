set(LIB_NAME ColoredStream)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/ColoredStream/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(${LIB_NAME} ${SOURCES})

target_include_directories(${LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
