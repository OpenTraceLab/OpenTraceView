# OpenTraceView CI Migration Summary

## Changes Made

### 1. CI/CD Improvements

#### `.github/workflows/ci.yml`
- ✅ Added complete multi-platform build support (Linux x86_64, Windows x64, macOS ARM)
- ✅ Added OpenTraceDecode dependency installation (was missing)
- ✅ Added Boost libraries to all platforms
- ✅ Added test execution on all platforms
- ✅ Improved caching for faster builds
- ✅ Proper MSYS2 setup for Windows builds

#### `.github/workflows/build.yml`
- ✅ Added OpenTraceDecode installation
- ✅ Added Boost stacktrace library
- ✅ Added artifact upload for built binary
- ✅ Removed PulseView references

### 2. CMake Cleanup
- ✅ Removed `CMake/` directory
- ✅ Removed `test/CMakeLists.txt`
- ✅ Removed `manual/CMakeLists.txt`
- ✅ Migration to Meson is now complete

### 3. PulseView References Cleanup
- ✅ Renamed `contrib/pulseview_cross.nsi.in` → `contrib/opentraceview_cross.nsi.in`
- ✅ Updated `contrib/org.sigrok.OpenTraceView.appdata.xml`:
  - Changed binary from `pulseview` to `opentraceview`
  - Changed launchable from `org.sigrok.PulseView.desktop` to `org.sigrok.OpenTraceView.desktop`
  - Updated URLs to GitHub OpenTraceLab organization

## Build Status

### Local Build: ✅ SUCCESS
- Platform: Linux x86_64
- Binary size: 9.1 MB
- Location: `testbuild/opentraceview`
- Warnings: Minor (const qualifiers, pedantic)

### CI Platforms Configured

| Platform | Architecture | Status | Notes |
|----------|-------------|--------|-------|
| Linux | x86_64 | ✅ Ready | Ubuntu 22.04 |
| Windows | x64 | ✅ Ready | MSYS2 MINGW64 |
| macOS | ARM64 | ✅ Ready | macOS 14 (Apple Silicon) |

## Boost Dependency Analysis

Boost is **still required** for:

1. **Stacktrace** (`boost::stacktrace`) - Used in `main.cpp` for crash reporting
   - Files: `main.cpp`
   - Libraries: `boost_stacktrace_backtrace` or `boost_stacktrace_basic`

2. **Serialization** (`boost::archive`) - Used in `otv/globalsettings.cpp` for settings persistence
   - Files: `otv/globalsettings.cpp`
   - Libraries: `boost_serialization`

3. **System** - Required by other Boost components
   - Libraries: `boost_system`

### Recommendation
Boost cannot be removed without:
- Replacing stacktrace with platform-specific alternatives (backtrace on Linux, DbgHelp on Windows)
- Replacing serialization with Qt's QDataStream or JSON serialization
- This would be a significant refactoring effort

## Platform-Specific Notes

### Windows x86 (32-bit)
**NOT CURRENTLY SUPPORTED** - The CI uses MINGW64 (x64 only).

To add Windows x86 support:
1. Add matrix entry with `msystem: MINGW32`
2. Change all `mingw-w64-x86_64-*` packages to `mingw-w64-i686-*`
3. Test thoroughly as 32-bit support may have issues

### macOS ARM (Apple Silicon)
- ✅ Configured with `macos-14` runner (native ARM64)
- Homebrew automatically provides ARM64 packages
- Qt6 ARM64 support is included

### Linux x86 (32-bit)
**NOT CURRENTLY SUPPORTED** - Ubuntu 22.04 runners are x64 only.

To add Linux x86 support:
1. Use Docker with 32-bit Ubuntu image
2. Install i386 cross-compilation toolchain
3. Significant CI complexity increase

## Testing

The CI now runs tests on all platforms:
```bash
meson test -C build --print-errorlogs
```

## Next Steps

1. **Push changes and verify CI runs successfully**
2. **Consider adding Windows x86 if needed** (requires separate matrix entry)
3. **Consider replacing Boost** (long-term, significant effort)
4. **Update documentation** to reflect new build requirements

## Files Modified

- `.github/workflows/ci.yml` - Complete rewrite
- `.github/workflows/build.yml` - Updated dependencies
- `contrib/org.sigrok.OpenTraceView.appdata.xml` - Fixed references
- `contrib/opentraceview_cross.nsi.in` - Renamed from pulseview_cross.nsi.in

## Files Removed

- `CMake/` directory
- `test/CMakeLists.txt`
- `manual/CMakeLists.txt`
- `contrib/pulseview_cross.nsi.in`
