/*
 * This file is part of the OpenTraceView project.
 *
 * Copyright (C) 2013 Joel Holdsworth <joel@airwebreathe.org.uk>
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

#ifndef PULSEVIEW_OTV_BINDING_DECODER_HPP
#define PULSEVIEW_OTV_BINDING_DECODER_HPP

#include "binding.hpp"

#include <otv/prop/property.hpp>

using std::shared_ptr;

struct otd_decoder_option;

namespace otv {

namespace data {
class DecodeSignal;
namespace decode {
class Decoder;
}
}

namespace binding {

class Decoder : public Binding
{
public:
	Decoder(shared_ptr<otv::data::DecodeSignal> decode_signal,
		shared_ptr<otv::data::decode::Decoder> decoder);

private:
	static shared_ptr<prop::Property> bind_enum(const QString &name,
		const QString &desc, const otd_decoder_option *option,
		prop::Property::Getter getter, prop::Property::Setter setter);

	Glib::VariantBase getter(const char *id);

	void setter(const char *id, Glib::VariantBase value);

private:
	shared_ptr<otv::data::DecodeSignal> decode_signal_;
	shared_ptr<otv::data::decode::Decoder> decoder_;
};

}  // namespace binding
}  // namespace otv

#endif // PULSEVIEW_OTV_BINDING_DECODER_HPP
