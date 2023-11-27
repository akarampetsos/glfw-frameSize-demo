# Simple demo to examine the behavior of glfwGetWindowFrameSize

## Build

```
git clone https://github.com/akarampetsos/glfw-frameSize-demo.git && \
cd glfw-frameSize-demo && \
cmake -S . -B build && \
cmake --build build
```

## Run for platform

* Wayland: `./build/apps/demo/demo wayland`
* X11: `./build/apps/demo/demo x11`

## Logs

### X11

```
Using x11
GLFW version: 3.4.0 Wayland X11 GLX Null EGL OSMesa monotonic
Before loop
Content area size (WxH): 800x600
Frame size (TxRxBxL): 0x0x0x0
Framebuffer size (WxH): 800x600
---
Focus changed: focused
Content area size (WxH): 800x599
Frame size (TxRxBxL): 31x0x0x0
Framebuffer size (WxH): 800x599
---
New framebuffer size (WxH): 800x599
Content area size (WxH): 800x599
Frame size (TxRxBxL): 31x0x0x0
Framebuffer size (WxH): 800x599
---
New window size (WxH): 800x599
Content area size (WxH): 800x599
Frame size (TxRxBxL): 31x0x0x0
Framebuffer size (WxH): 800x599
---
```

### Wayland

The first error doesn't trigger if position is not set but nothing else changes

```
Using wayland
GLFW version: 3.4.0 Wayland X11 GLX Null EGL OSMesa monotonic
GLFW Error 65548 | Wayland: The platform does not support setting the window position
GLFW Error 65548 | Wayland: The platform does not support setting the input focus
Before loop
Content area size (WxH): 800x600
Frame size (TxRxBxL): 0x0x0x0
Framebuffer size (WxH): 800x600
---
New framebuffer size (WxH): 1600x1200
Content area size (WxH): 800x600
Frame size (TxRxBxL): 0x0x0x0
Framebuffer size (WxH): 1600x1200
---
Focus changed: focused
Content area size (WxH): 800x600
Frame size (TxRxBxL): 0x0x0x0
Framebuffer size (WxH): 1600x1200
---
```