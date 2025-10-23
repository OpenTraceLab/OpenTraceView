##
## This file is part of the OpenTraceView project.
##
## Copyright (C) 2012 Joel Holdsworth <joel@airwebreathe.org.uk>
## Copyright (C) 2012-2013 Alexandru Gagniuc <mr.nuke.me@gmail.com>
## Copyright (C) 2020 Soeren Apel <soeren@apelpie.net>
##
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 2 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.
##

project('opentraceview', 'cpp', 
  version: '0.1.0',
  default_options: ['cpp_std=c++20', 'warning_level=3'],
  meson_version: '>=0.57.0'
)

# Get compiler for library checks
compiler = meson.get_compiler('cpp')

# User Options
disable_werror = get_option('disable_werror')
enable_signals = get_option('enable_signals')
enable_stacktrace = get_option('enable_stacktrace')
enable_decode = get_option('enable_decode')
enable_flow = get_option('enable_flow')
enable_tests = get_option('enable_tests')
static_pkgdeps_libs = get_option('static_pkgdeps_libs')
enable_ts_update = get_option('enable_ts_update')

# Platform-specific defaults
if host_machine.system() == 'windows'
  static_pkgdeps_libs = true
  enable_signals = false
endif

# Dependencies
qt6 = import('qt6')
pkgconfig = import('pkgconfig')

# Core dependencies
glib_dep = dependency('glib-2.0', version: '>=2.28.0')

# Try glibmm-2.4 first, fallback to glibmm-2.68
glibmm_dep = dependency('glibmm-2.4', version: '>=2.28.0', required: false)
if not glibmm_dep.found()
  glibmm_dep = dependency('glibmm-2.68', version: '>=2.68.0')
endif

# Qt6 dependencies - use super-package with modules for better compatibility
qt6_dep = dependency('qt6', modules: ['Core', 'Gui', 'Widgets', 'Svg'])
qt_deps = [qt6_dep]

# LinguistTools is optional for translations
linguist_dep = dependency('qt6', modules: 'LinguistTools', required: false)

# libopentracecapture C API
libopentracecapture_dep = dependency('opentracecapture')

# libopentracecapture C++ bindings
libopentracecapturecxx_dep = dependency('libopentracecapturecxx')

# Optional dependencies
deps = [glib_dep, glibmm_dep] + qt_deps + [libopentracecapture_dep, libopentracecapturecxx_dep]

if enable_flow
  deps += dependency('gstreamermm-1.0', version: '>=1.8.0')
  deps += dependency('libsigrokflow', version: '>=0.1.0')
endif

if enable_decode
  deps += dependency('opentracedecode', version: '>=0.1.0')
endif

if host_machine.system() == 'android'
  deps += dependency('libsigrokandroidutils', version: '>=0.1.0')
endif

# Boost dependencies - use compiler.find_library as fallback
boost_modules = ['serialization', 'system']
if enable_tests
  boost_modules += 'unit_test_framework'
endif

if enable_stacktrace
  backtrace_dep = dependency('backtrace', required: false)
  if backtrace_dep.found()
    boost_modules += 'stacktrace_backtrace'
    deps += backtrace_dep
  else
    boost_modules += 'stacktrace_basic'
  endif
endif

# Try to find boost libraries using compiler
boost_deps = []
foreach module : boost_modules
  boost_lib = compiler.find_library('boost_' + module, required: false)
  if boost_lib.found()
    boost_deps += boost_lib
  else
    # Try without boost_ prefix
    boost_lib = compiler.find_library(module, required: true)
    boost_deps += boost_lib
  endif
endforeach
deps += boost_deps

# Thread support
thread_dep = dependency('threads')
deps += thread_dep

# Atomic library check
atomic_dep = dependency('', required: false)
if not compiler.links('''
#include <atomic>
std::atomic<int> x;
int main() {
  return std::atomic_fetch_add_explicit(&x, 1, std::memory_order_seq_cst);
}
''', name: 'std::atomic')
  atomic_dep = compiler.find_library('atomic', required: true)
  deps += atomic_dep
endif

# Configuration
conf_data = configuration_data()
conf_data.set('OTV_TITLE', '"OpenTraceView"')
conf_data.set('OTV_VERSION_STRING', '"' + meson.project_version() + '"')
conf_data.set('OTV_GLIBMM_VERSION', '"' + glibmm_dep.version() + '"')
conf_data.set('ENABLE_SIGNALS', enable_signals)
conf_data.set('ENABLE_DECODE', enable_decode)
conf_data.set('ENABLE_FLOW', enable_flow)
conf_data.set('ENABLE_STACKTRACE', enable_stacktrace)

if enable_stacktrace and backtrace_dep.found()
  conf_data.set('BOOST_STACKTRACE_USE_BACKTRACE', true)
endif

# Check for SRD session send EOF
if enable_decode
  has_otd_session_send_eof = compiler.links('''
#include <opentracedecode/libopentracedecode.h>
int main(int argc, char *argv[]) {
  (void)argc; (void)argv;
  return otd_session_send_eof(NULL);
}
''', dependencies: dependency('opentracedecode'), name: 'otd_session_send_eof')
  conf_data.set('HAVE_OTD_SESSION_SEND_EOF', has_otd_session_send_eof)
endif

# Memory access check (simplified)
conf_data.set('HAVE_UNALIGNED_LITTLE_ENDIAN_ACCESS', host_machine.endian() == 'little')

configure_file(
  input: 'config.h.in',
  output: 'config.h',
  configuration: conf_data
)

# Add config.h as global include
add_project_arguments('-include', 'config.h', language: 'cpp')

# Source files
opentraceview_sources = files(
  'main.cpp',
  'otv/application.cpp',
  'otv/devicemanager.cpp',
  'otv/globalsettings.cpp',
  'otv/logging.cpp',
  'otv/mainwindow.cpp',
  'otv/metadata_obj.cpp',
  'otv/session.cpp',
  'otv/storesession.cpp',
  'otv/util.cpp',
  'otv/binding/binding.cpp',
  'otv/binding/inputoutput.cpp',
  'otv/binding/device.cpp',
  'otv/data/analog.cpp',
  'otv/data/analogsegment.cpp',
  'otv/data/logic.cpp',
  'otv/data/logicsegment.cpp',
  'otv/data/mathsignal.cpp',
  'otv/data/signalbase.cpp',
  'otv/data/signaldata.cpp',
  'otv/data/segment.cpp',
  'otv/devices/device.cpp',
  'otv/devices/file.cpp',
  'otv/devices/hardwaredevice.cpp',
  'otv/devices/inputfile.cpp',
  'otv/devices/sessionfile.cpp',
  'otv/dialogs/connect.cpp',
  'otv/dialogs/inputoutputoptions.cpp',
  'otv/dialogs/settings.cpp',
  'otv/dialogs/storeprogress.cpp',
  'otv/popups/deviceoptions.cpp',
  'otv/popups/channels.cpp',
  'otv/prop/bool.cpp',
  'otv/prop/double.cpp',
  'otv/prop/enum.cpp',
  'otv/prop/int.cpp',
  'otv/prop/property.cpp',
  'otv/prop/string.cpp',
  'otv/subwindows/subwindowbase.cpp',
  'otv/toolbars/mainbar.cpp',
  'otv/views/trace/analogsignal.cpp',
  'otv/views/trace/cursor.cpp',
  'otv/views/trace/cursorpair.cpp',
  'otv/views/trace/flag.cpp',
  'otv/views/trace/header.cpp',
  'otv/views/trace/mathsignal.cpp',
  'otv/views/trace/marginwidget.cpp',
  'otv/views/trace/logicsignal.cpp',
  'otv/views/trace/ruler.cpp',
  'otv/views/trace/signal.cpp',
  'otv/views/trace/timeitem.cpp',
  'otv/views/trace/timemarker.cpp',
  'otv/views/trace/trace.cpp',
  'otv/views/trace/tracegroup.cpp',
  'otv/views/trace/tracepalette.cpp',
  'otv/views/trace/tracetreeitem.cpp',
  'otv/views/trace/tracetreeitemowner.cpp',
  'otv/views/trace/triggermarker.cpp',
  'otv/views/trace/view.cpp',
  'otv/views/trace/viewitem.cpp',
  'otv/views/trace/viewitemowner.cpp',
  'otv/views/trace/viewitempaintparams.cpp',
  'otv/views/trace/viewport.cpp',
  'otv/views/trace/viewwidget.cpp',
  'otv/views/viewbase.cpp',
  'otv/views/trace/standardbar.cpp',
  'otv/widgets/colorbutton.cpp',
  'otv/widgets/colorpopup.cpp',
  'otv/widgets/devicetoolbutton.cpp',
  'otv/widgets/exportmenu.cpp',
  'otv/widgets/flowlayout.cpp',
  'otv/widgets/importmenu.cpp',
  'otv/widgets/popup.cpp',
  'otv/widgets/popuptoolbutton.cpp',
  'otv/widgets/sweeptimingwidget.cpp',
  'otv/widgets/timestampspinbox.cpp',
  'otv/widgets/wellarray.cpp'
)

# Conditional sources and headers
if enable_signals
  opentraceview_sources += files('signalhandler.cpp')
endif

if enable_decode
  opentraceview_sources += files(
    'otv/binding/decoder.cpp',
    'otv/data/decodesignal.cpp',
    'otv/data/decode/annotation.cpp',
    'otv/data/decode/decoder.cpp',
    'otv/data/decode/row.cpp',
    'otv/data/decode/rowdata.cpp',
    'otv/subwindows/decoder_selector/item.cpp',
    'otv/subwindows/decoder_selector/model.cpp',
    'otv/subwindows/decoder_selector/subwindow.cpp',
    'otv/views/decoder_binary/view.cpp',
    'otv/views/decoder_binary/QHexView.cpp',
    'otv/views/tabular_decoder/model.cpp',
    'otv/views/tabular_decoder/view.cpp',
    'otv/views/trace/decodetrace.cpp',
    'otv/widgets/decodergroupbox.cpp',
    'otv/widgets/decodermenu.cpp'
  )
endif

if host_machine.system() == 'android'
  opentraceview_sources += files(
    'android/assetreader.cpp',
    'android/loghandler.cpp'
  )
endif

# Resources and translations
opentraceview_qrc = files('opentraceview.qrc')

# Only include translations if LinguistTools is available
qrc_files = [opentraceview_qrc]
if linguist_dep.found()
  translations_qrc = files('translations.qrc')
  qrc_files += translations_qrc
endif

# Process Qt files - handle all potential MOC naming conflicts
# Define all MOC headers without conflicts
main_moc_headers = files(
  'otv/logging.hpp',
  'otv/globalsettings.hpp',
  'otv/mainwindow.hpp',
  'otv/metadata_obj.hpp',
  'otv/session.hpp',
  'otv/storesession.hpp',
  'otv/binding/binding.hpp',
  'otv/binding/device.hpp',
  'otv/data/analog.hpp',
  'otv/data/analogsegment.hpp',
  'otv/data/logic.hpp',
  'otv/data/logicsegment.hpp',
  'otv/data/segment.hpp',
  'otv/data/signalbase.hpp',
  'otv/data/signaldata.hpp',
  'otv/dialogs/connect.hpp',
  'otv/dialogs/inputoutputoptions.hpp',
  'otv/dialogs/settings.hpp',
  'otv/dialogs/storeprogress.hpp',
  'otv/popups/channels.hpp',
  'otv/popups/deviceoptions.hpp',
  'otv/prop/bool.hpp',
  'otv/prop/double.hpp',
  'otv/prop/enum.hpp',
  'otv/prop/int.hpp',
  'otv/prop/property.hpp',
  'otv/prop/string.hpp',
  'otv/subwindows/subwindowbase.hpp',
  'otv/toolbars/mainbar.hpp',
  'otv/views/trace/analogsignal.hpp',
  'otv/views/trace/cursor.hpp',
  'otv/views/trace/cursorpair.hpp',
  'otv/views/trace/flag.hpp',
  'otv/views/trace/header.hpp',
  'otv/views/trace/logicsignal.hpp',
  'otv/views/trace/marginwidget.hpp',
  'otv/views/trace/ruler.hpp',
  'otv/views/trace/signal.hpp',
  'otv/views/trace/timeitem.hpp',
  'otv/views/trace/timemarker.hpp',
  'otv/views/trace/trace.hpp',
  'otv/views/trace/tracegroup.hpp',
  'otv/views/trace/tracetreeitem.hpp',
  'otv/views/trace/triggermarker.hpp',
  'otv/views/trace/viewitem.hpp',
  'otv/views/trace/viewport.hpp',
  'otv/views/trace/viewwidget.hpp',
  'otv/views/viewbase.hpp',
  'otv/views/trace/standardbar.hpp',
  'otv/widgets/colorbutton.hpp',
  'otv/widgets/colorpopup.hpp',
  'otv/widgets/devicetoolbutton.hpp',
  'otv/widgets/exportmenu.hpp',
  'otv/widgets/flowlayout.hpp',
  'otv/widgets/importmenu.hpp',
  'otv/widgets/popup.hpp',
  'otv/widgets/popuptoolbutton.hpp',
  'otv/widgets/sweeptimingwidget.hpp',
  'otv/widgets/timestampspinbox.hpp',
  'otv/widgets/wellarray.hpp'
)

# Add conditional headers
if enable_signals
  main_moc_headers += files('signalhandler.hpp')
endif

# Add Application header
main_moc_headers += files('otv/application.hpp')

# Process main Qt MOC headers and resources
processed_files = qt6.preprocess(
  moc_headers: main_moc_headers,
  qresources: qrc_files
)

# Handle conflicting MOC files with custom targets
qt6_moc_tool = find_program('/usr/lib/qt6/libexec/moc', required: true)

# Data mathsignal
data_mathsignal_moc = custom_target('data_mathsignal_moc',
  input: files('otv/data/mathsignal.hpp'),
  output: 'moc_data_mathsignal.cpp',
  command: [qt6_moc_tool, '@INPUT@', '-o', '@OUTPUT@']
)

# Views mathsignal  
views_mathsignal_moc = custom_target('views_mathsignal_moc',
  input: files('otv/views/trace/mathsignal.hpp'),
  output: 'moc_views_mathsignal.cpp',
  command: [qt6_moc_tool, '@INPUT@', '-o', '@OUTPUT@']
)

# Views trace view
views_trace_view_moc = custom_target('views_trace_view_moc',
  input: files('otv/views/trace/view.hpp'),
  output: 'moc_views_trace_view.cpp',
  command: [qt6_moc_tool, '@INPUT@', '-o', '@OUTPUT@']
)

processed_files += [data_mathsignal_moc, views_mathsignal_moc, views_trace_view_moc]

# Decode-specific MOC files with custom targets to avoid conflicts
if enable_decode
  decode_moc_files = []
  
  # Decoder binary view
  decoder_binary_view_moc = custom_target('decoder_binary_view_moc',
    input: files('otv/views/decoder_binary/view.hpp'),
    output: 'moc_decoder_binary_view.cpp',
    command: [qt6_moc_tool, '@INPUT@', '-o', '@OUTPUT@']
  )
  decode_moc_files += decoder_binary_view_moc
  
  # Tabular decoder view
  tabular_decoder_view_moc = custom_target('tabular_decoder_view_moc',
    input: files('otv/views/tabular_decoder/view.hpp'),
    output: 'moc_tabular_decoder_view.cpp',
    command: [qt6_moc_tool, '@INPUT@', '-o', '@OUTPUT@']
  )
  decode_moc_files += tabular_decoder_view_moc
  
  # Other decode headers without conflicts
  decode_headers_no_conflict = files(
    'otv/data/decodesignal.hpp',
    'otv/data/decode/row.hpp',
    'otv/subwindows/decoder_selector/subwindow.hpp',
    'otv/views/decoder_binary/QHexView.hpp',
    'otv/views/trace/decodetrace.hpp',
    'otv/widgets/decodergroupbox.hpp',
    'otv/widgets/decodermenu.hpp'
  )
  
  decode_processed = qt6.preprocess(moc_headers: decode_headers_no_conflict)
  
  # Handle decoder headers with custom targets to avoid conflicts
  binding_decoder_moc = custom_target('binding_decoder_moc',
    input: files('otv/binding/decoder.hpp'),
    output: 'moc_binding_decoder.cpp',
    command: [qt6_moc_tool, '@INPUT@', '-o', '@OUTPUT@']
  )
  
  data_decode_decoder_moc = custom_target('data_decode_decoder_moc',
    input: files('otv/data/decode/decoder.hpp'),
    output: 'moc_data_decode_decoder.cpp',
    command: [qt6_moc_tool, '@INPUT@', '-o', '@OUTPUT@']
  )
  
  processed_files += decode_processed + decode_moc_files + [binding_decoder_moc, data_decode_decoder_moc]
endif

# Translations
ts_files = run_command('find', meson.current_source_dir() / 'l10n', '-name', '*.ts', check: false).stdout().strip().split('\n')
if ts_files != [''] and linguist_dep.found()
  qm_files = qt6.compile_translations(ts_files: ts_files)
  processed_files += qm_files
endif

# Compile flags
compile_args = [
  '-DQT_NO_KEYWORDS',
  '-D__STDC_LIMIT_MACROS',
  '-DBOOST_MATH_DISABLE_FLOAT128=1'
]

if enable_flow
  compile_args += '-DENABLE_FLOW'
endif

if enable_stacktrace
  compile_args += ['-DENABLE_STACKTRACE', '-no-pie', '-fno-pie']
  if backtrace_dep.found()
    compile_args += '-DBOOST_STACKTRACE_USE_BACKTRACE'
  endif
endif

if not disable_werror
  compile_args += '-Werror'
endif

if host_machine.system() == 'windows'
  compile_args += ['-Wa,-mbig-obj', '-O3', '-DQT_STATICPLUGIN']
  opentraceview_sources += files('opentraceviewico.rc')
endif

# Link flags
link_args = []
if host_machine.system() == 'windows' and get_option('buildtype') != 'debug'
  link_args += '-mwindows'
endif

if enable_stacktrace
  link_args += ['-no-pie', '-fno-pie']
endif

# Additional libraries for specific platforms
extra_deps = []
if host_machine.system() == 'android'
  extra_deps += compiler.find_library('log')
endif

# Build executable
exe = executable('opentraceview',
  sources: opentraceview_sources + processed_files,
  dependencies: deps + extra_deps,
  cpp_args: compile_args,
  link_args: link_args,
  include_directories: include_directories('.'),
  install: true
)

# Installation
install_man('doc/opentraceview.1')
install_data('contrib/org.sigrok.OpenTraceView.desktop',
  install_dir: get_option('datadir') / 'applications')
install_data('contrib/org.sigrok.OpenTraceView.appdata.xml',
  install_dir: get_option('datadir') / 'metainfo')
install_data('icons/opentraceview.png',
  install_dir: get_option('datadir') / 'icons/hicolor/48x48/apps')
install_data('icons/opentraceview.svg',
  install_dir: get_option('datadir') / 'icons/hicolor/scalable/apps')

# Tests
if enable_tests
  subdir('test')
endif

# Manual
subdir('manual')
