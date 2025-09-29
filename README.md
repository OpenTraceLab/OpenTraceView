# OpenTraceView

OpenTraceView is a Qt-based GUI application for visualizing and analyzing signal traces captured with logic analyzers, oscilloscopes, and other measurement devices.

## Versioning

This project follows semantic versioning starting from version 0.1.0. The ABI (Application Binary Interface) is tied to the minor version number, meaning:

- **Major version** (0.x.x): Breaking API/ABI changes
- **Minor version** (x.1.x): ABI changes, new features  
- **Patch version** (x.x.1): Bug fixes, no ABI changes

Current version: **0.1.0**

## Building

```bash
meson setup build --buildtype=release
meson compile -C build
meson install -C build
```

## Dependencies

- Qt6 (Core, Widgets, Gui, Svg)
- OpenTraceCapture C++ bindings
- GLib/Glibmm
- Meson build system

## Usage

```bash
opentraceview [file.sr]
```
