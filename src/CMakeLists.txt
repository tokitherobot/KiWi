set(SDL2_BUILDING_LIBRARY TRUE)
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

include(${CMAKE_SOURCE_DIR}/resources/kiwires.cmake)

set(API_HEADERS
  KW_gui.h
  KW_button.h
  KW_editbox.h
  KW_frame.h
  KW_label.h
  KW_macros.h
  KW_tilerenderer.h
  KW_widget.h
  KW_scrollbox.h
  KW_renderdriver_sdl2.h
  KW_renderdriver.h
  KW_rect.h
  KW_bool.h
  KW_toggle.h
  KW_checkbox.h
)

set(LIB_SOURCES
  KW_scrollbox_internal.c
  KW_scrollbox.c
  KW_editbox_internal.c
  utf8.c
  KW_editbox.c
  KW_eventwatcher.c
  KW_button.c
  KW_label.c
  KW_label_internal.c
  KW_gui.c
  KW_frame.c
  KW_frame_internal.c
  KW_tilerenderer.c
  KW_widget.c
  KW_widget_eventhandlers.c
  KW_renderdriver.c
  KW_renderdriver_sdl2.c
  KW_rect.c
  KW_toggle.c
  KW_checkbox.c
)

kiwires(HEADER resources.h BODY resources.c RESOURCES resources/sourcesans-pro-semibold.ttf)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_library(KiWi SHARED ${LIB_SOURCES} ${API_HEADERS} ${CMAKE_CURRENT_BINARY_DIR}/resources.c)
target_link_libraries(KiWi ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
if(CMAKE_COMPILER_IS_GNUCC)
    target_compile_options(KiWi PRIVATE -fvisibility=hidden -std=c89 -pedantic-errors -Wall -Wextra)
endif(CMAKE_COMPILER_IS_GNUCC)

# Configure install stuff
install(TARGETS KiWi EXPORT KiWiTargets
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

install(FILES ${API_HEADERS} DESTINATION include/KiWi)
