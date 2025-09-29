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

#ifndef PULSEVIEW_OTV_PROP_INT_HPP
#define PULSEVIEW_OTV_PROP_INT_HPP

#include <utility>

#include <optional>

#include "property.hpp"

using std::pair;

class QSpinBox;

namespace otv {
namespace prop {

class Int : public Property
{
	Q_OBJECT

public:
	Int(QString name, QString desc, QString suffix,
		std::optional< pair<int64_t, int64_t> > range,
		Getter getter, Setter setter, QString special_value_text = "");

	virtual ~Int() = default;

	QWidget* get_widget(QWidget *parent, bool auto_commit);
	void update_widget();

	void commit();

private Q_SLOTS:
	void on_value_changed(int);

private:
	const QString suffix_, special_value_text_;
	const std::optional< pair<int64_t, int64_t> > range_;

	Glib::VariantBase value_;
	QSpinBox *spin_box_;
};

}  // namespace prop
}  // namespace otv

#endif // PULSEVIEW_OTV_PROP_INT_HPP
