find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

add_executable(mayurifetch)

target_sources(mayurifetch 
  PRIVATE
    main.cpp
    Window.h
)

target_link_libraries(mayurifetch
  PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
)