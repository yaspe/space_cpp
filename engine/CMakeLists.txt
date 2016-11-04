set(lib_name engine)

file(GLOB ${lib_name}_HEADERS "*.h")
file(GLOB ${lib_name}_SOURCES "*.cpp")
file(GLOB ${lib_name}_SOURCE_LIST ${${lib_name}_SOURCE_LIST} ${${lib_name}_HEADERS} ${${lib_name}_SOURCES})

add_library(${lib_name} STATIC ${${lib_name}_SOURCE_LIST})