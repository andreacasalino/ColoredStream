macro(MAKE_SAMPLE NAME)
    add_executable(${NAME} ${NAME}.cpp)
    target_link_libraries(${NAME} PUBLIC
        ColoredStream
    )    
endmacro()

MAKE_SAMPLE(Sample-README)

MAKE_SAMPLE(Sample-classical)

MAKE_SAMPLE(Sample-custom)

MAKE_SAMPLE(Sample-rgb)

MAKE_SAMPLE(Sample-stream)
