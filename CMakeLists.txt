cmake_minimum_required(VERSION 3.15)

project(nodec_scene LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE include
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE nodec
)

option(NODEC_SCENE_ENABLE_SERIALIZATION OFF)

if(NODEC_SCENE_ENABLE_SERIALIZATION)
    target_include_directories(
        ${PROJECT_NAME}
        INTERFACE serialization
    )

    target_link_libraries(${PROJECT_NAME}
        INTERFACE
        nodec_scene_serialization
    )
endif()

# Tests
option(NODEC_SCENE_BUILD_TESTS "Enable buidling tests." OFF)

if(NODEC_SCENE_BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()