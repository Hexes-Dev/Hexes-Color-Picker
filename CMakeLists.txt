cmake_minimum_required(VERSION 3.16)
project(ColorPicker VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


find_package(Qt6 COMPONENTS REQUIRED Widgets Gui)


qt_standard_project_setup()

qt_add_executable(ColorPicker 
src/main.cpp
src/resources.qrc
src/gui/colorFinderWidget.cpp
src/gui/colorPreviewWidget.cpp
src/gui/mainWidget.cpp
src/gui/widgetFactory.cpp
src/utilities/colorSpace.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
Qt6::Widgets 
Qt6::Core
Qt6::Gui
)

set_target_properties(${PROJECT_NAME} PROPERTIES
WIN32_EXECUTABLE ON
MACOSX_BUNDLE ON
AUTOMOC TRUE
)


set_property(TARGET ColorPicker PROPERTY CXX_STANDARD 20)
