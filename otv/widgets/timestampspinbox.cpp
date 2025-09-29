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

#include "timestampspinbox.hpp"

#include <QLineEdit>
#include <QRegularExpression>

namespace otv {
namespace widgets {

TimestampSpinBox::TimestampSpinBox(QWidget* parent)
	: QAbstractSpinBox(parent)
	, precision_(9)
	, stepsize_(1e-6)
{
	connect(this, SIGNAL(editingFinished()), this, SLOT(on_editingFinished()));
	connect(lineEdit(), SIGNAL(editingFinished()), this, SLOT(on_editingFinished()));

	updateEdit();
}

void TimestampSpinBox::stepBy(int steps)
{
	setValue(value_ + steps * stepsize_);
}

QAbstractSpinBox::StepEnabled TimestampSpinBox::stepEnabled() const
{
	return QAbstractSpinBox::StepUpEnabled | QAbstractSpinBox::StepDownEnabled;
}

unsigned TimestampSpinBox::precision() const
{
	return precision_;
}

void TimestampSpinBox::setPrecision(unsigned precision)
{
	precision_ = precision;
	updateEdit();
}

const otv::util::Timestamp& TimestampSpinBox::singleStep() const
{
	return stepsize_;
}

void TimestampSpinBox::setSingleStep(const otv::util::Timestamp& step)
{
	stepsize_ = step;
}

const otv::util::Timestamp& TimestampSpinBox::value() const
{
	return value_;
}

QSize TimestampSpinBox::minimumSizeHint() const
{
	const QFontMetrics fm(fontMetrics());
	const int l = QString::number(round(value_)).size() + precision_ + 10;
	const int w = util::text_width(fm, QString(l, '0'));
	const int h = lineEdit()->minimumSizeHint().height();
	return QSize(w, h);
}

void TimestampSpinBox::setValue(const otv::util::Timestamp& val)
{
	if (val == value_)
		return;

	value_ = val;
	updateEdit();
	valueChanged(value_);
}

void TimestampSpinBox::on_editingFinished()
{
	static const auto re_pattern = R"(\s*([-+]?)\s*([0-9]+\.?[0-9]*).*)";

	QRegularExpression re(re_pattern);
	auto match = re.match(text());
	bool has_match = match.hasMatch();
	QStringList captures;
	if (has_match) {
		captures = match.capturedTexts();
	}

	if (has_match) {
		captures.removeFirst(); // remove entire match
		QString str = captures.join("");
		setValue(str.toDouble());

	} else {
		// replace the malformed entered string with the old value
		updateEdit();
	}
}

void TimestampSpinBox::updateEdit()
{
	QString newtext = otv::util::format_time_si(
		value_, otv::util::SIPrefix::none, precision_);
	const QSignalBlocker blocker(lineEdit());
	// Keep cursor position
	int cursor = lineEdit()->cursorPosition();
	lineEdit()->setText(newtext);
	lineEdit()->setCursorPosition(cursor);
}

}  // namespace widgets
}  // namespace otv
