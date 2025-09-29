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

#ifndef PULSEVIEW_OTV_PROP_DOUBLE_HPP
#define PULSEVIEW_OTV_PROP_DOUBLE_HPP

#include <utility>

#include <optional>

#include "property.hpp"

using std::pair;

class QDoubleSpinBox;

namespace otv {
namespace prop {

class Double : public Property
{
	Q_OBJECT

public:
	Double(QString name, QString desc, int decimals, QString suffix,
		std::optional< pair<double, double> > range,
		std::optional<double> step,
		Getter getter,
		Setter setter);

	virtual ~Double() = default;

	QWidget* get_widget(QWidget *parent, bool auto_commit);
	void update_widget();

	void commit();

private Q_SLOTS:
	void on_value_changed(double);

private:
	const int decimals_;
	const QString suffix_;
	const std::optional< pair<double, double> > range_;
	const std::optional<double> step_;

	QDoubleSpinBox *spin_box_;
};

}  // namespace prop
}  // namespace otv

#endif // PULSEVIEW_OTV_PROP_DOUBLE_HPP
