#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define USAGE_STR "usage: demo <x11 | wayland>\r\n"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int parsePlatform(const char* platformStr) {
    int platform;

    if(strcmp(platformStr, "wayland") == 0) {
        platform = GLFW_PLATFORM_WAYLAND;
        printf("Using wayland\r\n");
    } else if(strcmp(platformStr, "x11") == 0) {
        platform = GLFW_PLATFORM_X11;
        printf("Using x11\r\n");
    } else {
        printf("Unknown platform: %s\r\n", platformStr);
        printf(USAGE_STR);
        exit(EXIT_FAILURE);
    }

    if(!glfwPlatformSupported(platform)) {
        printf("Platform %s is not supported\r\n", platformStr);
        exit(EXIT_FAILURE);
    }

    return platform;
}

void initGLFW(int platform) {
    glfwInitHint(GLFW_PLATFORM, platform);

    if(!glfwInit()) {
        const char* description;
        glfwGetError(&description);

        printf("Error initializing GLFW: %s\r\n", description);
        exit(EXIT_FAILURE);
    }
}

GLFWwindow* createWindow(int width, int height, const char* title) {
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);

    if(!window) {
        const char* description;
        glfwGetError(&description);

        printf("Error creating GLFW window: %s\r\n", description);

        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    return window;
}

// Should use glfwGetWindowSize or something similar for window size instead of passing params
void centerWindowInMonitor(GLFWwindow* window, int windowWidth, int windowHeight, GLFWmonitor* monitor) {
    const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
    int freeWidth = videoMode->width - windowWidth;
    int freeHeight = videoMode->height - windowHeight;

    // Supposedly not supported in wayland but it somehow works.
    // Doesn't seem to affect anything, even commenting it out makes no difference other than no centering
    glfwSetWindowPos(window, freeWidth / 2, freeHeight / 2);
}

void printAllWindowSizes(GLFWwindow* window) {
    int width, height, top, right, bottom, left;

    glfwGetWindowSize(window, &width, &height);
    printf("Content area size (WxH): %dx%d\r\n", width, height);

    glfwGetWindowFrameSize(window, &left, &top, &right, &bottom);
    printf("Frame size (TxRxBxL): %dx%dx%dx%d\r\n", top, right, bottom, left);

    glfwGetFramebufferSize(window, &width, &height);
    printf("Framebuffer size (WxH): %dx%d\r\n", width, height);
}

void onGLFWError(int errorCode, const char* errorStr) {
    printf("GLFW Error %d | %s\r\n", errorCode, errorStr);
}

void onWindowSizeChange(GLFWwindow* window, int width, int height) {
    printf("New window size (WxH): %dx%d\r\n", width, height);
    printAllWindowSizes(window);
    printf("---\r\n");
}

void onFramebufferSizeChange(GLFWwindow* window, int width, int height) {
    printf("New framebuffer size (WxH): %dx%d\r\n", width, height);
    printAllWindowSizes(window);
    printf("---\r\n");
}

// Possibly makes glfwGetWindowFrameSize return the correct values on x11, does not on wayland 
// GLFW Error 65548 | Wayland: The platform does not support setting the input focus
// This error may be causing this?
// On x11 loop start -> Focused event, FB size change event, window size change event, ..., focus change events, ...
// On wayland loop start -> FB size change event, focused event, ..., focus change events, ...
void onWindowFocusChange(GLFWwindow* window, int focused) {
    printf("Focus changed: %s\r\n", focused == 1 ? "focused" : "not focused");
    printAllWindowSizes(window);
    printf("---\r\n");
}

int main(int argc, char** argv) {
    if(argc != 2) {
        printf(USAGE_STR);
        return EXIT_FAILURE;
    }

    int platform = parsePlatform(argv[1]);

    initGLFW(platform);
    printf("GLFW version: %s\r\n", glfwGetVersionString());

    glfwSetErrorCallback(onGLFWError);

    GLFWwindow* window = createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "GLFW Window Frame Size Demo");

    glfwSetFramebufferSizeCallback(window, onFramebufferSizeChange);
    glfwSetWindowSizeCallback(window, onWindowSizeChange);
    glfwSetWindowFocusCallback(window, onWindowFocusChange);

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    centerWindowInMonitor(window, WINDOW_WIDTH, WINDOW_HEIGHT, monitor);

    glfwShowWindow(window);
    
    printf("Before loop\r\n");
    printAllWindowSizes(window);
    printf("---\r\n");

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}