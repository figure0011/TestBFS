add_library(lib STATIC
    src/cell.cpp
    src/field.cpp
    src/bfs.cpp
)
target_link_libraries(lib PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_include_directories(lib PUBLIC include)

target_sources(lib PRIVATE
    src/cell.cpp
    src/field.cpp
    src/bfs.cpp
    src/mainwindowstate.cpp
)