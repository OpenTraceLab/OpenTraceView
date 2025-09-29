/*
 * This file is part of the OpenTraceView project.
 *
 * Copyright (C) 2015 Joel Holdsworth <joel@airwebreathe.org.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PULSEVIEW_OTV_DEVICES_INPUTFILE_HPP
#define PULSEVIEW_OTV_DEVICES_INPUTFILE_HPP

#include <atomic>

#include <libopentracecapturecxx.hpp>

#include "file.hpp"

#include <QSettings>

using std::atomic;
using std::ifstream;
using std::map;
using std::shared_ptr;
using std::streamsize;
using std::string;

namespace otv {
namespace devices {

class InputFile final : public File
{
private:
	static const streamsize BufferSize;

public:
	InputFile(const shared_ptr<opentrace::Context> &context,
		const string &file_name,
		shared_ptr<opentrace::InputFormat> format,
		const map<string, Glib::VariantBase> &options);

	/**
	 * Constructor that loads a file using the metadata saved by
	 * save_meta_to_settings() before.
	 */
	InputFile(const shared_ptr<opentrace::Context> &context,
		QSettings &settings);

	void save_meta_to_settings(QSettings &settings);

	void open();

	void close();

	void start();

	void run();

	void stop();

private:
	const shared_ptr<opentrace::Context> context_;
	shared_ptr<opentrace::InputFormat> format_;
	map<string, Glib::VariantBase> options_;
	shared_ptr<opentrace::Input> input_;

	ifstream *f;
	atomic<bool> interrupt_;
};

} // namespace devices
} // namespace otv

#endif // PULSEVIEW_OTV_DEVICES_INPUTFILE_HPP

