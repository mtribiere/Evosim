add_library(ui
    ui.cpp
)
target_include_directories(ui PUBLIC
    includes
    ${SDL2_INCLUDE_DIRS}
)
target_link_libraries(ui PUBLIC
    ${SDL2_LIBRARIES} 
)