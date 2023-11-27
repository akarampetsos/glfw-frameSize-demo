include(FetchContent)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw
#   GIT_TAG 3.3-stable
  GIT_TAG master
)

add_subdirectory(glad-gl-core-4.6)
add_subdirectory(glfw)