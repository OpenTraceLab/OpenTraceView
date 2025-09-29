#include <opentracecapture/libopentracecapture.h>
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

#include <cstdint>

#include <QDebug>

#include "device.hpp"

#include <otv/prop/bool.hpp>
#include <otv/prop/enum.hpp>
#include <otv/prop/int.hpp>

#include <libopentracecapturecxx.hpp>

using std::optional;

using std::function;
using std::pair;
using std::set;
using std::shared_ptr;
using std::string;
using std::vector;

using opentrace::Capability;
using opentrace::Configurable;
using opentrace::ConfigKey;
using opentrace::Error;

using otv::prop::Bool;
using otv::prop::Enum;
using otv::prop::Int;
using otv::prop::Property;

namespace otv {
namespace binding {

Device::Device(shared_ptr<opentrace::Configurable> configurable) :
	configurable_(configurable)
{

	auto keys = configurable->config_keys();

	for (auto key : keys) {

		string descr_str;
		try {
			descr_str = key->description();
		} catch (Error& e) {
			descr_str = key->name();
		}
		const QString descr = QString::fromStdString(descr_str);

		auto capabilities = configurable->config_capabilities(key);

		if (!capabilities.count(Capability::GET) ||
			!capabilities.count(Capability::SET)) {

			// Ignore common read-only keys
			if ((key->id() == OTC_CONF_CONTINUOUS) || (key->id() == OTC_CONF_TRIGGER_MATCH) ||
			    (key->id() == OTC_CONF_CONN) || (key->id() == OTC_CONF_SERIALCOMM) || (key->id() == OTC_CONF_NUM_LOGIC_CHANNELS) ||
			    (key->id() == OTC_CONF_NUM_ANALOG_CHANNELS) || (key->id() == OTC_CONF_SESSIONFILE) || (key->id() == OTC_CONF_CAPTUREFILE) ||
			    (key->id() == OTC_CONF_CAPTURE_UNITSIZE))
				continue;

			qDebug() << QString(tr("Note for device developers: Ignoring device configuration capability '%1' " \
				"as it is missing GET and/or SET")).arg(descr);
			continue;
		}

		const Property::Getter get = [&, key]() {
			return configurable_->config_get(key); };
		const Property::Setter set = [&, key](Glib::VariantBase value) {
			configurable_->config_set(key, value);
			config_changed();
		};

		switch (key->id()) {
		case OTC_CONF_SAMPLERATE:
			// Sample rate values are not bound because they are shown
			// in the MainBar
			break;

		case OTC_CONF_CAPTURE_RATIO:
			bind_int(descr, "", "%", pair<int64_t, int64_t>(0, 100), get, set);
			break;

		case OTC_CONF_LIMIT_FRAMES:
			// Value 0 means that there is no limit
			bind_int(descr, "", "", pair<int64_t, int64_t>(0, 1000000), get, set,
				tr("No Limit"));
			break;

		case OTC_CONF_PATTERN_MODE:
		case OTC_CONF_BUFFERSIZE:
		case OTC_CONF_TRIGGER_SOURCE:
		case OTC_CONF_TRIGGER_SLOPE:
		case OTC_CONF_COUPLING:
		case OTC_CONF_CLOCK_EDGE:
		case OTC_CONF_DATA_SOURCE:
		case OTC_CONF_EXTERNAL_CLOCK_SOURCE:
			bind_enum(descr, "", key, capabilities, get, set);
			break;

		case OTC_CONF_FILTER:
		case OTC_CONF_EXTERNAL_CLOCK:
		case OTC_CONF_RLE:
		case OTC_CONF_POWER_OFF:
		case OTC_CONF_AVERAGING:
		case OTC_CONF_CONTINUOUS:
			bind_bool(descr, "", get, set);
			break;

		case OTC_CONF_TIMEBASE:
			bind_enum(descr, "", key, capabilities, get, set, print_timebase);
			break;

		case OTC_CONF_VDIV:
			bind_enum(descr, "", key, capabilities, get, set, print_vdiv);
			break;

		case OTC_CONF_VOLTAGE_THRESHOLD:
			bind_enum(descr, "", key, capabilities, get, set, print_voltage_threshold);
			break;

		case OTC_CONF_PROBE_FACTOR:
			if (capabilities.count(Capability::LIST))
				bind_enum(descr, "", key, capabilities, get, set, print_probe_factor);
			else
				bind_int(descr, "", "", pair<int64_t, int64_t>(1, 500), get, set);
			break;

		case OTC_CONF_AVG_SAMPLES:
			if (capabilities.count(Capability::LIST))
				bind_enum(descr, "", key, capabilities, get, set, print_averages);
			else
				bind_int(descr, "", "", pair<int64_t, int64_t>(0, INT32_MAX), get, set);
			break;

		default:
			break;
		}
	}
}

void Device::bind_bool(const QString &name, const QString &desc,
	Property::Getter getter, Property::Setter setter)
{
	assert(configurable_);
	properties_.push_back(shared_ptr<Property>(new Bool(
		name, desc, getter, setter)));
}

void Device::bind_enum(const QString &name, const QString &desc,
	const ConfigKey *key, set<const Capability *> capabilities,
	Property::Getter getter,
	Property::Setter setter, function<QString (Glib::VariantBase)> printer)
{
	assert(configurable_);

	if (!capabilities.count(Capability::LIST))
		return;

	try {
		Glib::VariantContainerBase gvar = configurable_->config_list(key);
		Glib::VariantIter iter(gvar);

		vector< pair<Glib::VariantBase, QString> > values;
		while ((iter.next_value(gvar)))
			values.emplace_back(gvar, printer(gvar));

		properties_.push_back(shared_ptr<Property>(new Enum(name, desc, values,
			getter, setter)));

	} catch (opentrace::Error& e) {
		qDebug() << "Error: Listing device key" << name << "failed!";
		return;
	}
}

void Device::bind_int(const QString &name, const QString &desc, QString suffix,
	optional< pair<int64_t, int64_t> > range, Property::Getter getter,
	Property::Setter setter, QString special_value_text)
{
	assert(configurable_);

	properties_.push_back(shared_ptr<Property>(new Int(name, desc, suffix,
		range, getter, setter, special_value_text)));
}

QString Device::print_timebase(Glib::VariantBase gvar)
{
	uint64_t p, q;
	g_variant_get(gvar.gobj(), "(tt)", &p, &q);
	return QString::fromUtf8(otc_period_string(p, q));
}

QString Device::print_vdiv(Glib::VariantBase gvar)
{
	uint64_t p, q;
	g_variant_get(gvar.gobj(), "(tt)", &p, &q);
	return QString::fromUtf8(otc_voltage_string(p, q));
}

QString Device::print_voltage_threshold(Glib::VariantBase gvar)
{
	gdouble lo, hi;
	g_variant_get(gvar.gobj(), "(dd)", &lo, &hi);
	return QString("L<%1V H>%2V").arg(lo, 0, 'f', 1).arg(hi, 0, 'f', 1);
}

QString Device::print_probe_factor(Glib::VariantBase gvar)
{
	uint64_t factor;
	factor = g_variant_get_uint64(gvar.gobj());
	return QString("%1x").arg(factor);
}

QString Device::print_averages(Glib::VariantBase gvar)
{
	uint64_t avg;
	avg = g_variant_get_uint64(gvar.gobj());
	return QString("%1").arg(avg);
}

}  // namespace binding
}  // namespace otv
