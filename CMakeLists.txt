cmake_minimum_required(VERSION 3.24)
project(WorldGeneration)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "build")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

file(GLOB_RECURSE src-1-foundation
        "WorldGeneration/1-foundation/*.h"
        "WorldGeneration/1-foundation/*.cpp"
        )
file(GLOB_RECURSE src-2-services
        "WorldGeneration/2-services/*.h"
        "WorldGeneration/2-services/*.cpp"
        )
file(GLOB_RECURSE src-3-infrastructure
        "WorldGeneration/3-infrastructure/*.h"
        "WorldGeneration/3-infrastructure/*.cpp"
        )
file(GLOB_RECURSE src-4-domain
        "WorldGeneration/4-domain/*.h"
        "WorldGeneration/4-domain/*.cpp"
        )
file(GLOB_RECURSE src-5-controller
        "WorldGeneration/5-controller/*.h"
        "WorldGeneration/5-controller/*.cpp"
        )
file(GLOB_RECURSE src-6-view
        "WorldGeneration/6-view/*.h"
        "WorldGeneration/6-view/*.cpp"
        )

add_executable(WorldGeneration WorldGeneration/main.cpp
        ${src-1-foundation}
        ${src-2-services}
        ${src-3-infrastructure}
        ${src-4-domain}
        ${src-5-controller}
        ${src-6-view}
        )

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set_property(TARGET WorldGeneration PROPERTY WIN32_EXECUTABLE true)
endif()

target_link_libraries(WorldGeneration
        PRIVATE Qt::Core
        PRIVATE  Qt::Gui
        PRIVATE  Qt::Widgets
        )

cmake_path(GET Qt6_DIR PARENT_PATH the_qt_path)
cmake_path(GET the_qt_path PARENT_PATH the_qt_path)
cmake_path(GET the_qt_path PARENT_PATH the_qt_path)

install(DIRECTORY ${the_qt_path}/plugins/platforms/
        DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms
        FILES_MATCHING PATTERN "qwindows*"
        )

install(FILES $<TARGET_RUNTIME_DLLS:WorldGeneration>
        DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )

install(DIRECTORY ${the_qt_path}/bin/
        DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>
        FILES_MATCHING PATTERN "libgcc_s_seh-1.dll"
        )
install(DIRECTORY ${the_qt_path}/bin/
        DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>
        FILES_MATCHING PATTERN "libstdc++-6.dll"
        )
install(DIRECTORY ${the_qt_path}/bin/
        DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>
        FILES_MATCHING PATTERN "libwinpthread-1.dll"
        )

#Output all dll miss by previous install
install(TARGETS WorldGeneration
        COMPONENT WorldGeneration
        RUNTIME_DEPENDENCIES
        PRE_EXCLUDE_REGEXES "api-ms-" "ext-ms-"
        POST_EXCLUDE_REGEXES ".*system32/.*\\.dll"
        DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )