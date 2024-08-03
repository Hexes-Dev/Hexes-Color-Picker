cmake_minimum_required(VERSION 3.16)
project(ColorPicker VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


add_executable(ColorPicker 
src/main.cpp
src/resources.qrc
src/gui/colorFinderWidget.cpp
src/gui/colorPreviewWidget.cpp
src/gui/mainWidget.cpp
src/gui/widgetFactory.cpp
src/utilities/colorSpace.cpp
)

set_property(TARGET ColorPicker PROPERTY CXX_STANDARD 20)

include(CTest)
enable_testing()

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
    AUTOMOC TRUE
)

set(BUILD_EXAMPLE false)
# set(BUILD_SHARED_LIBS OFF)

# Screen capture lite is no longer being used in this project.

# include(FetchContent)
# set(SCREEN_CAPTURE_LITE_VERSION 17.1.1369)
# FetchContent_Declare(
#     screen_capture_lite
#     URL https://github.com/smasherprog/screen_capture_lite/archive/refs/tags/${SCREEN_CAPTURE_LITE_VERSION}.tar.gz
# )

# FetchContent_MakeAvailable(screen_capture_lite)

# include_directories (${CMAKE_SOURCE_DIR}/src)
# include_directories(${screen_capture_lite_SOURCE_DIR}/include)
# file(COPY ${CMAKE_SOURCE_DIR}/src/assets DESTINATION ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.app/Contents)

find_package(Qt6 COMPONENTS REQUIRED Widgets Gui)
# find_package(OpenCV REQUIRED)

qt_standard_project_setup()

target_link_libraries(${PROJECT_NAME} 
    ${OpenCV_LIBS}
    # screen_capture_lite_shared
    Qt6::Widgets 
    Qt6::Core
    Qt6::Gui
)



