
# required for igloo:
add_definitions(-Wno-deprecated-declarations)
include_directories(igloo)
include_directories(../src)

set(TEST_SOURCE_FILES
  test_runner.cpp
  test_state.cpp
  test_stack.cpp
  test_function.cpp
  test_export_function.cpp
    )


add_executable(test_runner EXCLUDE_FROM_ALL ${TEST_SOURCE_FILES})
target_link_libraries(test_runner lua ${LIBS})

get_target_property(TEST_RUNNER_BIN test_runner LOCATION) # for running

add_custom_target(test DEPENDS test_runner)
add_custom_command(TARGET test COMMAND valgrind --leak-check=full --show-reachable=yes --log-file="valgrind.log" ${TEST_RUNNER_BIN} --verbose DEPENDS test_runner)
