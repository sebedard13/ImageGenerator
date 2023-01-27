cmake_minimum_required(VERSION 3.24)
project(WorldGeneration)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

file(GLOB_RECURSE src1
        "WorldGeneration/1-foundation/*.h"
        "WorldGeneration/1-foundation/*.cpp"
        )
file(GLOB_RECURSE src2
        "WorldGeneration/2-services/*.h"
        "WorldGeneration/2-services/*.cpp"
        )
file(GLOB_RECURSE src3
        "WorldGeneration/3-infrastructure/*.h"
        "WorldGeneration/3-infrastructure/*.cpp"
        )
file(GLOB_RECURSE src4
        "WorldGeneration/4-domain/*.h"
        "WorldGeneration/4-domain/*.cpp"
        )
file(GLOB_RECURSE src5
        "WorldGeneration/5-controller/*.h"
        "WorldGeneration/5-controller/*.cpp"
        )
file(GLOB_RECURSE src6
        "WorldGeneration/6-view/*.h"
        "WorldGeneration/6-view/*.cpp"
        )

add_executable(WorldGeneration WorldGeneration/main.cpp
        ${src1}
        ${src2}
        ${src3}
        ${src4}
        ${src5}
        ${src6}
        )

target_link_libraries(WorldGeneration
        Qt::Core -static
        Qt::Gui -static
        Qt::Widgets -static
        )

if (WIN32)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()

#    TODO
    set(QT_INSTALL_PATH "C:/Qt/6.4.2/mingw_64")


    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()


