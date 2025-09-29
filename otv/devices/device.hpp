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

#ifndef PULSEVIEW_OTV_DEVICES_DEVICE_HPP
#define PULSEVIEW_OTV_DEVICES_DEVICE_HPP

#include <memory>
#include <string>

#include <libopentracecapturecxx.hpp>

using std::shared_ptr;
using std::string;

namespace sigrok {
class ConfigKey;
class Device;
class Session;
} // namespace sigrok

namespace otv {

class DeviceManager;

namespace devices {

class Device
{
protected:
	Device() = default;

public:
	virtual ~Device();

	shared_ptr<opentrace::Session> session() const;

	shared_ptr<opentrace::Device> device() const;

	template<typename T>
	T read_config(const opentrace::ConfigKey *key, const T default_value = 0);

	/**
	 * Builds the full name. It only contains all the fields.
	 */
	virtual string full_name() const = 0;

	/**
	 * Builds the display name. It only contains fields as required.
	 * @param device_manager a reference to the device manager is needed
	 * so that other similarly titled devices can be detected.
	 */
	virtual string display_name(
		const DeviceManager &device_manager) const = 0;

	virtual void open() = 0;

	virtual void close() = 0;

	virtual void start();

	virtual void run();

	virtual void stop();

protected:
	shared_ptr<opentrace::Session> session_;
	shared_ptr<opentrace::Device> device_;
};

} // namespace devices
} // namespace otv

#endif // PULSEVIEW_OTV_DEVICES_DEVICE_HPP
