# OpenTraceView Migration Progress

## Completed Tasks (23/35 OpenTraceView-specific)

### Branding & Desktop Integration ✅
- Renamed `contrib/org.sigrok.OpenTraceView.desktop` → `contrib/org.opentrace.OpenTraceView.desktop`
- Updated MIME type: `application/vnd.sigrok.session` → `application/vnd.opentrace.session`
- Renamed `contrib/org.sigrok.OpenTraceView.appdata.xml` → `contrib/org.opentrace.OpenTraceView.appdata.xml`
- Updated appdata.xml: removed sigrok URLs, firmware dependencies, updated screenshots

### Code Namespace ✅
- Replaced `namespace sigrok` with `namespace opentrace` in 17 files:
  - otv/devicemanager.hpp
  - otv/session.hpp
  - All binding files (otv/binding/*.hpp)
  - All data files (otv/data/*.hpp, otv/data/*.cpp)
  - All device files (otv/devices/*.hpp)
  - All dialog files (otv/dialogs/*.hpp)
  - All view files (otv/views/**/*.hpp)
  - All widget files (otv/widgets/*.hpp)

### Documentation ✅
- Updated CI_MIGRATION_SUMMARY.md
- Updated manual/acquisition.txt
- Updated manual/cli.txt
- Updated manual/decoders.txt
- Updated manual/import_export.txt

### Build System ✅
- Updated meson.build to reference renamed desktop/appdata files
- Install paths updated to use opentrace

### Test Suite ✅
- Updated test/data/logicsegment.cpp

## Remaining OpenTraceView Tasks (12)

### Documentation (2)
- manual/installation.txt - Contains many external sigrok.org wiki links
- manual/overview.txt - Contains many external sigrok.org wiki links

### Android Build (6)
- android/AndroidManifest.xml
- android/res/values/strings-pv.xml
- android/res/layout/splash.xml
- android/custom_rules.xml
- android/assetreader.cpp and android/assetreader.hpp
- android/loghandler.hpp (marked complete but needs verification)

### Build System (2)
- meson.build - Still references libsigrokflow and libsigrokandroidutils (external deps)
- meson_options.txt (marked complete but needs verification)

### Test Suite (2)
- test/test.hpp (marked complete but needs verification)

## Tasks for Other Repositories (73)

### OpenTraceDecode (10 tasks)
All tasks pending - requires access to OpenTraceDecode repository

### OpenTraceCapture (38 tasks)
All tasks pending - requires access to OpenTraceCapture repository

### OpenTraceBroadcaster (1 task)
Pending - requires access to OpenTraceBroadcaster repository

### Cross-Project Tasks (14 tasks)
- Session file format definition
- MIME type updates
- Migration tool
- API/ABI versioning policy
- Documentation website
- Migration guides
- Copyright/licensing updates

## Modified Files

1. /home/epkcfsm/src/OpenTraceView/contrib/org.opentrace.OpenTraceView.desktop
2. /home/epkcfsm/src/OpenTraceView/contrib/org.opentrace.OpenTraceView.appdata.xml
3. /home/epkcfsm/src/OpenTraceView/CI_MIGRATION_SUMMARY.md
4. /home/epkcfsm/src/OpenTraceView/manual/cli.txt
5. /home/epkcfsm/src/OpenTraceView/meson.build
6. /home/epkcfsm/src/OpenTraceView/test/data/logicsegment.cpp
7. /home/epkcfsm/src/OpenTraceView/manual/decoders.txt
8. /home/epkcfsm/src/OpenTraceView/manual/import_export.txt
9. 17 C++ source files (namespace changes)

## Next Steps

1. **Verify build** - Ensure OpenTraceView still compiles with changes
2. **Complete remaining manual files** - Update installation.txt and overview.txt
3. **Android build** - Update Android-specific files if Android build is maintained
4. **Other repositories** - Apply similar changes to OpenTraceDecode and OpenTraceCapture
5. **Cross-project** - Define session file format and create migration tools

## Notes

- External dependencies (libsigrokflow, libsigrokandroidutils) remain unchanged
- Manual files contain many references to sigrok.org wiki - these are external resources
- Android build files may not be actively maintained
