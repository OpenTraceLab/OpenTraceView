/*
 * This file is part of the OpenTraceView project.
 *
 * Copyright (C) 2015 Jens Steinhauser <jens.steinhauser@gmail.com>
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

#ifndef PULSEVIEW_OTV_WIDGETS_TIMESTAMPSPINBOX_HPP
#define PULSEVIEW_OTV_WIDGETS_TIMESTAMPSPINBOX_HPP

#include "otv/util.hpp"

#include <QAbstractSpinBox>

namespace otv {
namespace widgets {

class TimestampSpinBox : public QAbstractSpinBox
{
	Q_OBJECT

	Q_PROPERTY(unsigned precision
		READ precision
		WRITE setPrecision)

	// Needed because of some strange behaviour of the Qt4 MOC that would add
	// a reference to a 'staticMetaObject' member of 'otv::util' (the namespace)
	// if otv::util::Timestamp is used directly in the Q_PROPERTY macros below.
	// Didn't happen with the Qt5 MOC in this case, however others have had
	// similar problems with Qt5: https://bugreports.qt.io/browse/QTBUG-37519
	typedef otv::util::Timestamp Timestamp;

	Q_PROPERTY(Timestamp singleStep
		READ singleStep
		WRITE setSingleStep)

	Q_PROPERTY(Timestamp value
		READ value
		WRITE setValue
		NOTIFY valueChanged
		USER true)

public:
	TimestampSpinBox(QWidget* parent = nullptr);

	void stepBy(int steps) override;

	StepEnabled stepEnabled() const override;

	unsigned precision() const;
	void setPrecision(unsigned precision);

	const otv::util::Timestamp& singleStep() const;
	void setSingleStep(const otv::util::Timestamp& step);

	const otv::util::Timestamp& value() const;

	QSize minimumSizeHint() const override;

public Q_SLOTS:
	void setValue(const otv::util::Timestamp& val);

Q_SIGNALS:
	void valueChanged(const otv::util::Timestamp&);

private Q_SLOTS:
	void on_editingFinished();

private:
	unsigned precision_;
	otv::util::Timestamp stepsize_;
	otv::util::Timestamp value_;

	void updateEdit();
};

}  // namespace widgets
}  // namespace otv

#endif // PULSEVIEW_OTV_WIDGETS_TIMESTAMPSPINBOX_HPP
