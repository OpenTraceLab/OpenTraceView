#include <opentracecapture/libopentracecapture.h>
#include <opentracedecode/libopentracedecode.h>
/*
 * This file is part of the OpenTraceView project.
 *
 * Copyright (C) 2014 Marcus Comstedt <marcus@mc.pp.se>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef ENABLE_DECODE
extern "C" {
#include <opentracedecode/opentracedecode.h>
} /* First, so we avoid a _POSIX_C_SOURCE warning. */
#endif

#include <android/log.h>

#include <cstdint>
#include <opentracecapture/opentracecapture.h>

#include "android/loghandler.hpp"

namespace otv {

static otc_log_callback prev_sr_log_cb;
static void *prev_sr_log_cb_data;

#ifdef ENABLE_DECODE
static otd_log_callback prev_otd_log_cb;
static void *prev_otd_log_cb_data;
#endif

int AndroidLogHandler::otc_callback(void *cb_data, int loglevel, const char *format, va_list args)
{
	static const int prio[] = {
		[OTC_LOG_NONE] = ANDROID_LOG_SILENT,
		[OTC_LOG_ERR] = ANDROID_LOG_ERROR,
		[OTC_LOG_WARN] = ANDROID_LOG_WARN,
		[OTC_LOG_INFO] = ANDROID_LOG_INFO,
		[OTC_LOG_DBG] = ANDROID_LOG_DEBUG,
		[OTC_LOG_SPEW] = ANDROID_LOG_VERBOSE,
	};
	va_list args2;
	int ret;

	/* This specific log callback doesn't need the void pointer data. */
	(void)cb_data;

	/* Call the previously registered log callback (library's default). */
	va_copy(args2, args);
	if (prev_sr_log_cb)
		prev_sr_log_cb(prev_sr_log_cb_data, loglevel, format, args2);
	va_end(args2);

	/* Only output messages of at least the selected loglevel(s). */
	if (loglevel > otc_log_loglevel_get())
		return OTC_OK;

	if (loglevel < OTC_LOG_NONE)
		loglevel = OTC_LOG_NONE;
	else if (loglevel > OTC_LOG_SPEW)
		loglevel = OTC_LOG_SPEW;

	ret = __android_log_vprint(prio[loglevel], "sr", format, args);

	return ret;
}

int AndroidLogHandler::otd_callback(void *cb_data, int loglevel, const char *format, va_list args)
{
#ifdef ENABLE_DECODE
	static const int prio[] = {
		[OTD_LOG_NONE] = ANDROID_LOG_SILENT,
		[OTD_LOG_ERR] = ANDROID_LOG_ERROR,
		[OTD_LOG_WARN] = ANDROID_LOG_WARN,
		[OTD_LOG_INFO] = ANDROID_LOG_INFO,
		[OTD_LOG_DBG] = ANDROID_LOG_DEBUG,
		[OTD_LOG_SPEW] = ANDROID_LOG_VERBOSE,
	};
	va_list args2;
	int ret;

	/* This specific log callback doesn't need the void pointer data. */
	(void)cb_data;

	/* Call the previously registered log callback (library's default). */
	va_copy(args2, args);
	if (prev_otd_log_cb)
		prev_otd_log_cb(prev_otd_log_cb_data, loglevel, format, args2);
	va_end(args2);

	/* Only output messages of at least the selected loglevel(s). */
	if (loglevel > otd_log_loglevel_get())
		return OTD_OK;

	if (loglevel < OTD_LOG_NONE)
		loglevel = OTD_LOG_NONE;
	else if (loglevel > OTD_LOG_SPEW)
		loglevel = OTD_LOG_SPEW;

	ret = __android_log_vprint(prio[loglevel], "srd", format, args);

	return ret;
#else
	return 0;
#endif
}

void AndroidLogHandler::install_callbacks()
{
	otc_log_callback_get(&prev_sr_log_cb, &prev_sr_log_cb_data);
	otc_log_callback_set(otc_callback, nullptr);
#ifdef ENABLE_DECODE
	otd_log_callback_get(&prev_otd_log_cb, &prev_otd_log_cb_data);
	otd_log_callback_set(otd_callback, nullptr);
#endif
}

} // namespace otv
