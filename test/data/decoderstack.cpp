#include <opentracecapture/libopentracecapture.h>
#include <opentracedecode/libopentracedecode.h>
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

#if 0

#include <libsigrokdecode/libsigrokdecode.h> /* First, so we avoid a _POSIX_C_SOURCE warning. */
#include <boost/test/unit_test.hpp>

#include <libopentracecapturecxx.hpp>

#include "../../otv/data/decoderstack.hpp"
#include "../../otv/devicemanager.hpp"
#include "../../otv/session.hpp"
#include "../../otv/view/decodetrace.hpp"

using otv::data::DecoderStack;
using otv::data::decode::Decoder;
using otv::view::DecodeTrace;
using std::shared_ptr;
using std::vector;

BOOST_AUTO_TEST_SUITE(DecoderStackTest)

BOOST_AUTO_TEST_CASE(TwoDecoderStack)
{
	otc_context *ctx = nullptr;

	BOOST_REQUIRE(otc_init(&ctx) == OTC_OK);
	BOOST_REQUIRE(ctx);

	BOOST_REQUIRE(otd_init(nullptr) == OTD_OK);

	otd_decoder_load_all();

	{
		otv::DeviceManager dm(ctx);
		otv::Session ss(dm);

		const GSList *l = otd_decoder_list();
		BOOST_REQUIRE(l);
		otd_decoder *const dec = (struct otd_decoder*)l->data;
		BOOST_REQUIRE(dec);

		ss.add_decoder(dec);
		ss.add_decoder(dec);

		// Check the signals were created
		const vector< shared_ptr<DecodeTrace> > sigs =
			ss.get_decode_signals();

		shared_ptr<DecoderStack> dec0 = sigs[0]->decoder();
		BOOST_REQUIRE(dec0);

		shared_ptr<DecoderStack> dec1 = sigs[0]->decoder();
		BOOST_REQUIRE(dec1);

		// Wait for the decode threads to complete
		dec0->decode_thread_.join();
		dec1->decode_thread_.join();

		// Check there were no errors
		BOOST_CHECK_EQUAL(dec0->error_message().isEmpty(), true);
		BOOST_CHECK_EQUAL(dec1->error_message().isEmpty(), true);
	}


	otd_exit();
	otc_exit(ctx);
}

BOOST_AUTO_TEST_SUITE_END()
#endif
