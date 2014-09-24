
set(SOURCE_FILES
    )

add_library(thelua STATIC ${SOURCE_FILES})
target_link_libraries(thelua ${LIBS})
install(TARGETS thelua DESTINATION lib)

