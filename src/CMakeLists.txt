find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

add_executable(mayushiifetch)

target_sources(mayushiifetch 
  PRIVATE
    mayushiifetch.cpp
)

target_link_libraries(mayushiifetch
  PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image)