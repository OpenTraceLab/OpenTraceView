/*
 * This file is part of the OpenTraceView project.
 *
 * Copyright (C) 2015 Daniel Elstner <daniel.kitta@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PULSEVIEW_ANDROID_ASSETREADER_HPP
#define PULSEVIEW_ANDROID_ASSETREADER_HPP

#include <libopentracecapturecxx.hpp>

using std::string;

namespace otv {

class AndroidAssetReader : public opentracecapture::ResourceReader
{
public:
	AndroidAssetReader() = default;
	virtual ~AndroidAssetReader() = default;

private:
	void open(struct otc_resource *res, string name) override;
	void close(struct otc_resource *res) override;
	size_t read(const struct otc_resource *res, void *buf, size_t count) override;
};

} // namespace otv

#endif // !PULSEVIEW_ANDROID_ASSETREADER_HPP
