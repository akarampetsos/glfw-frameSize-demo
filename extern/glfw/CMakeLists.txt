message(STATUS "Fetching GLFW...")

set(GLFW_USE_WAYLAND ON)

FetchContent_MakeAvailable(glfw)