cmake_minimum_required(VERSION 3.16)

project(2B3ChromieApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Gui)
qt_standard_project_setup()

add_subdirectory(2B3Chromie/lib2B3Chromie)



set(SRCS
    main.cpp
    colorspacegenerator.cpp
)

set(HEADERS
    colorspacegenerator.h
)


qt_add_executable(app2B3ChromieApp
    ${SRCS} ${HEADERS}
)

qt_add_resources(app2B3ChromieApp "images"
    PREFIX "/"
    FILES
        images/test.jpg
)

qt_add_qml_module(app2B3ChromieApp
    URI 2B3ChromieApp
    VERSION 1.0
    QML_FILES Main.qml
)

set_target_properties(app2B3ChromieApp PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(app2B3ChromieApp
    PRIVATE Qt6::Quick Qt6::Gui
    2B3ChromieCore
)

install(TARGETS app2B3ChromieApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
