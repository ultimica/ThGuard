add_library(data dummy_dcc.cpp)
target_include_directories(
        data 
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )
