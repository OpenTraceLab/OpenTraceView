##
## This file is part of the OpenTraceView project.
##
## Copyright (C) 2012 Joel Holdsworth <joel@airwebreathe.org.uk>
## Copyright (C) 2012 Alexandru Gagniuc <mr.nuke.me@gmail.com>
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

set(opentraceview_TEST_SOURCES
	${PROJECT_SOURCE_DIR}/otv/application.cpp
	${PROJECT_SOURCE_DIR}/otv/devicemanager.cpp
	${PROJECT_SOURCE_DIR}/otv/globalsettings.cpp
	${PROJECT_SOURCE_DIR}/otv/logging.cpp
	${PROJECT_SOURCE_DIR}/otv/mainwindow.cpp
	${PROJECT_SOURCE_DIR}/otv/metadata_obj.cpp
	${PROJECT_SOURCE_DIR}/otv/session.cpp
	${PROJECT_SOURCE_DIR}/otv/storesession.cpp
	${PROJECT_SOURCE_DIR}/otv/util.cpp
	${PROJECT_SOURCE_DIR}/otv/binding/binding.cpp
	${PROJECT_SOURCE_DIR}/otv/binding/device.cpp
	${PROJECT_SOURCE_DIR}/otv/binding/inputoutput.cpp
	${PROJECT_SOURCE_DIR}/otv/data/analog.cpp
	${PROJECT_SOURCE_DIR}/otv/data/analogsegment.cpp
	${PROJECT_SOURCE_DIR}/otv/data/logic.cpp
	${PROJECT_SOURCE_DIR}/otv/data/logicsegment.cpp
	${PROJECT_SOURCE_DIR}/otv/data/mathsignal.cpp
	${PROJECT_SOURCE_DIR}/otv/data/segment.cpp
	${PROJECT_SOURCE_DIR}/otv/data/signalbase.cpp
	${PROJECT_SOURCE_DIR}/otv/data/signaldata.cpp
	${PROJECT_SOURCE_DIR}/otv/devices/device.cpp
	${PROJECT_SOURCE_DIR}/otv/devices/file.cpp
	${PROJECT_SOURCE_DIR}/otv/devices/hardwaredevice.cpp
	${PROJECT_SOURCE_DIR}/otv/devices/inputfile.cpp
	${PROJECT_SOURCE_DIR}/otv/devices/sessionfile.cpp
	${PROJECT_SOURCE_DIR}/otv/dialogs/connect.cpp
	${PROJECT_SOURCE_DIR}/otv/dialogs/inputoutputoptions.cpp
	${PROJECT_SOURCE_DIR}/otv/dialogs/settings.cpp
	${PROJECT_SOURCE_DIR}/otv/dialogs/storeprogress.cpp
	${PROJECT_SOURCE_DIR}/otv/prop/bool.cpp
	${PROJECT_SOURCE_DIR}/otv/prop/double.cpp
	${PROJECT_SOURCE_DIR}/otv/prop/enum.cpp
	${PROJECT_SOURCE_DIR}/otv/prop/int.cpp
	${PROJECT_SOURCE_DIR}/otv/prop/property.cpp
	${PROJECT_SOURCE_DIR}/otv/prop/string.cpp
	${PROJECT_SOURCE_DIR}/otv/popups/channels.cpp
	${PROJECT_SOURCE_DIR}/otv/popups/deviceoptions.cpp
	${PROJECT_SOURCE_DIR}/otv/subwindows/subwindowbase.cpp
	${PROJECT_SOURCE_DIR}/otv/toolbars/mainbar.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/analogsignal.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/cursor.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/cursorpair.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/flag.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/header.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/mathsignal.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/marginwidget.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/logicsignal.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/ruler.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/signal.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/timeitem.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/timemarker.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/trace.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/tracegroup.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/tracepalette.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/tracetreeitem.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/tracetreeitemowner.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/triggermarker.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/view.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/viewitem.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/viewitemowner.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/viewitempaintparams.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/viewport.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/viewwidget.cpp
	${PROJECT_SOURCE_DIR}/otv/views/viewbase.cpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/standardbar.cpp
	${PROJECT_SOURCE_DIR}/otv/widgets/colorbutton.cpp
	${PROJECT_SOURCE_DIR}/otv/widgets/colorpopup.cpp
	${PROJECT_SOURCE_DIR}/otv/widgets/devicetoolbutton.cpp
	${PROJECT_SOURCE_DIR}/otv/widgets/exportmenu.cpp
	${PROJECT_SOURCE_DIR}/otv/widgets/flowlayout.cpp
	${PROJECT_SOURCE_DIR}/otv/widgets/importmenu.cpp
	${PROJECT_SOURCE_DIR}/otv/widgets/popup.cpp
	${PROJECT_SOURCE_DIR}/otv/widgets/popuptoolbutton.cpp
	${PROJECT_SOURCE_DIR}/otv/widgets/sweeptimingwidget.cpp
	${PROJECT_SOURCE_DIR}/otv/widgets/timestampspinbox.cpp
	${PROJECT_SOURCE_DIR}/otv/widgets/wellarray.cpp
	data/analogsegment.cpp
	data/logicsegment.cpp
	data/segment.cpp
	view/ruler.cpp
	test.cpp
	util.cpp
)

# This list includes only QObject derived class headers.
set(opentraceview_TEST_HEADERS
	${PROJECT_SOURCE_DIR}/otv/application.hpp
	${PROJECT_SOURCE_DIR}/otv/devicemanager.hpp
	${PROJECT_SOURCE_DIR}/otv/exprtk.hpp
	${PROJECT_SOURCE_DIR}/otv/globalsettings.hpp
	${PROJECT_SOURCE_DIR}/otv/logging.hpp
	${PROJECT_SOURCE_DIR}/otv/mainwindow.hpp
	${PROJECT_SOURCE_DIR}/otv/metadata_obj.hpp
	${PROJECT_SOURCE_DIR}/otv/session.hpp
	${PROJECT_SOURCE_DIR}/otv/storesession.hpp
	${PROJECT_SOURCE_DIR}/otv/binding/device.hpp
	${PROJECT_SOURCE_DIR}/otv/data/analog.hpp
	${PROJECT_SOURCE_DIR}/otv/data/analogsegment.hpp
	${PROJECT_SOURCE_DIR}/otv/data/logic.hpp
	${PROJECT_SOURCE_DIR}/otv/data/logicsegment.hpp
	${PROJECT_SOURCE_DIR}/otv/data/mathsignal.hpp
	${PROJECT_SOURCE_DIR}/otv/data/signalbase.hpp
	${PROJECT_SOURCE_DIR}/otv/devices/device.hpp
	${PROJECT_SOURCE_DIR}/otv/dialogs/connect.hpp
	${PROJECT_SOURCE_DIR}/otv/dialogs/inputoutputoptions.hpp
	${PROJECT_SOURCE_DIR}/otv/dialogs/settings.hpp
	${PROJECT_SOURCE_DIR}/otv/dialogs/storeprogress.hpp
	${PROJECT_SOURCE_DIR}/otv/popups/channels.hpp
	${PROJECT_SOURCE_DIR}/otv/popups/deviceoptions.hpp
	${PROJECT_SOURCE_DIR}/otv/prop/bool.hpp
	${PROJECT_SOURCE_DIR}/otv/prop/double.hpp
	${PROJECT_SOURCE_DIR}/otv/prop/enum.hpp
	${PROJECT_SOURCE_DIR}/otv/prop/int.hpp
	${PROJECT_SOURCE_DIR}/otv/prop/property.hpp
	${PROJECT_SOURCE_DIR}/otv/prop/string.hpp
	${PROJECT_SOURCE_DIR}/otv/subwindows/subwindowbase.hpp
	${PROJECT_SOURCE_DIR}/otv/toolbars/mainbar.hpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/analogsignal.hpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/cursor.hpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/flag.hpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/header.hpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/logicsignal.hpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/mathsignal.hpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/marginwidget.hpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/ruler.hpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/signal.hpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/timeitem.hpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/timemarker.hpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/trace.hpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/tracegroup.hpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/tracetreeitem.hpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/triggermarker.hpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/view.hpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/viewitem.hpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/viewport.hpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/viewwidget.hpp
	${PROJECT_SOURCE_DIR}/otv/views/viewbase.hpp
	${PROJECT_SOURCE_DIR}/otv/views/trace/standardbar.hpp
	${PROJECT_SOURCE_DIR}/otv/widgets/colorbutton.hpp
	${PROJECT_SOURCE_DIR}/otv/widgets/colorpopup.hpp
	${PROJECT_SOURCE_DIR}/otv/widgets/devicetoolbutton.hpp
	${PROJECT_SOURCE_DIR}/otv/widgets/exportmenu.hpp
	${PROJECT_SOURCE_DIR}/otv/widgets/flowlayout.hpp
	${PROJECT_SOURCE_DIR}/otv/widgets/importmenu.hpp
	${PROJECT_SOURCE_DIR}/otv/widgets/popup.hpp
	${PROJECT_SOURCE_DIR}/otv/widgets/popuptoolbutton.hpp
	${PROJECT_SOURCE_DIR}/otv/widgets/sweeptimingwidget.hpp
	${PROJECT_SOURCE_DIR}/otv/widgets/timestampspinbox.hpp
	${PROJECT_SOURCE_DIR}/otv/widgets/wellarray.hpp
)

if(ENABLE_DECODE)
	list(APPEND opentraceview_TEST_SOURCES
		${PROJECT_SOURCE_DIR}/otv/binding/decoder.cpp
		${PROJECT_SOURCE_DIR}/otv/data/decodesignal.cpp
		${PROJECT_SOURCE_DIR}/otv/data/decode/annotation.cpp
		${PROJECT_SOURCE_DIR}/otv/data/decode/decoder.cpp
		${PROJECT_SOURCE_DIR}/otv/data/decode/row.cpp
		${PROJECT_SOURCE_DIR}/otv/data/decode/rowdata.cpp
		${PROJECT_SOURCE_DIR}/otv/subwindows/decoder_selector/item.cpp
		${PROJECT_SOURCE_DIR}/otv/subwindows/decoder_selector/model.cpp
		${PROJECT_SOURCE_DIR}/otv/subwindows/decoder_selector/subwindow.cpp
		${PROJECT_SOURCE_DIR}/otv/views/decoder_binary/view.cpp
		${PROJECT_SOURCE_DIR}/otv/views/decoder_binary/QHexView.cpp
		${PROJECT_SOURCE_DIR}/otv/views/tabular_decoder/model.cpp
		${PROJECT_SOURCE_DIR}/otv/views/tabular_decoder/view.cpp
		${PROJECT_SOURCE_DIR}/otv/views/trace/decodetrace.cpp
		${PROJECT_SOURCE_DIR}/otv/widgets/decodergroupbox.cpp
		${PROJECT_SOURCE_DIR}/otv/widgets/decodermenu.cpp
	)

	list(APPEND opentraceview_TEST_HEADERS
		${PROJECT_SOURCE_DIR}/otv/data/decodesignal.hpp
		${PROJECT_SOURCE_DIR}/otv/subwindows/decoder_selector/subwindow.hpp
		${PROJECT_SOURCE_DIR}/otv/views/decoder_binary/view.hpp
		${PROJECT_SOURCE_DIR}/otv/views/decoder_binary/QHexView.hpp
		${PROJECT_SOURCE_DIR}/otv/views/tabular_decoder/view.hpp
		${PROJECT_SOURCE_DIR}/otv/views/trace/decodetrace.hpp
		${PROJECT_SOURCE_DIR}/otv/widgets/decodergroupbox.hpp
		${PROJECT_SOURCE_DIR}/otv/widgets/decodermenu.hpp
	)
endif()

# On MinGW we need to use static linking.
if(NOT WIN32)
	add_definitions(-DBOOST_TEST_DYN_LINK)
endif()

add_executable(opentraceview-test
	${opentraceview_TEST_SOURCES}
	${opentraceview_TEST_HEADERS_MOC}
)

target_link_libraries(opentraceview-test ${PULSEVIEW_LINK_LIBS})

