/*
 * This file is part of the OpenTraceView project.
 *
 * Copyright (C) 2012 Joel Holdsworth <joel@airwebreathe.org.uk>
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

#ifndef PULSEVIEW_OTV_POPUPS_DEVICEOPTIONS_HPP
#define PULSEVIEW_OTV_POPUPS_DEVICEOPTIONS_HPP

#include <QGroupBox>
#include <QVBoxLayout>

#include <otv/binding/device.hpp>
#include <otv/widgets/popup.hpp>

using std::shared_ptr;

namespace opentrace {
	class Device;
}

namespace otv {
namespace popups {

class DeviceOptions : public otv::widgets::Popup
{
	Q_OBJECT

public:
	DeviceOptions(shared_ptr<opentrace::Device> device, QWidget *parent);

	otv::binding::Device& binding();

	virtual void show();

private:
	shared_ptr<opentrace::Device> device_;

	QVBoxLayout layout_;

	otv::binding::Device binding_;
};

} // namespace popups
} // namespace otv

#endif // PULSEVIEW_OTV_POPUPS_DEVICEOPTIONS_HPP
