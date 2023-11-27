add_library(glad_gl_core_46 STATIC src/gl.c include/glad/gl.h include/KHR/khrplatform.h)
add_library(glad::gl_core_46 ALIAS glad_gl_core_46)

target_include_directories(glad_gl_core_46 PUBLIC include)
