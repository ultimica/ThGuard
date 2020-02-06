add_library(thread_guard thread_guard.hpp)
target_include_directories(
        thread_guard 
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )
