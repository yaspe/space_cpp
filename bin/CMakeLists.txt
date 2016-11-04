set(app_name space)

add_executable(${app_name} main.cpp)
target_link_libraries(${app_name} engine render controller SDL2 SDL2_image)
