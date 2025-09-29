/*
 * This file is part of the OpenTraceView project.
 *
 * Copyright (C) 2020 Soeren Apel <soeren@apelpie.net>
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

#ifndef PULSEVIEW_OTV_VIEWS_TRACE_MATHSIGNAL_HPP
#define PULSEVIEW_OTV_VIEWS_TRACE_MATHSIGNAL_HPP

#include <memory>
#include <vector>

#include <QComboBox>
#include <QDialog>
#include <QPlainTextEdit>
#include <QString>
#include <QTimer>

#include <otv/data/mathsignal.hpp>
#include <otv/views/trace/analogsignal.hpp>

using std::pair;
using std::shared_ptr;
using std::string;
using std::vector;

namespace otv {
namespace views {
namespace trace {

class MathEditDialog : public QDialog
{
	Q_OBJECT

private:
	static const vector< pair<string, string> > Examples;

public:
	MathEditDialog(otv::Session &session, shared_ptr<otv::data::MathSignal> math_signal,
		QWidget *parent = nullptr);

	void set_expr(const QString &expr);

private Q_SLOTS:
	void accept();
	void reject();

private:
	otv::Session &session_;
	shared_ptr<otv::data::MathSignal> math_signal_;
	QString old_expression_;

	QPlainTextEdit *expr_edit_;
};


class MathSignal : public AnalogSignal
{
	Q_OBJECT

public:
	MathSignal(otv::Session &session, shared_ptr<data::SignalBase> base);

protected:
	void populate_popup_form(QWidget *parent, QFormLayout *form);

	shared_ptr<otv::data::MathSignal> math_signal_;

private Q_SLOTS:
	void on_expression_changed(const QString &text);
	void on_sample_count_changed(const QString &text);

	void on_edit_clicked();

private:
	QLineEdit *expression_edit_;
	QComboBox *sample_count_cb_, *sample_rate_cb_;
	QString sample_count_text_, sample_rate_text_;
	QTimer delayed_expr_updater_, delayed_count_updater_, delayed_rate_updater_;
};

} // namespace trace
} // namespace views
} // namespace otv

#endif // PULSEVIEW_OTV_VIEWS_TRACE_MATHSIGNAL_HPP
