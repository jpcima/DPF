/*
 * travesty, pure C interface to steinberg VST3 SDK
 * Copyright (C) 2021 Filipe Coelho <falktx@falktx.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any purpose with
 * or without fee is hereby granted, provided that the above copyright notice and this
 * permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
 * TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#pragma once
#include "base.h"

#ifdef __cplusplus
#include <atomic>

namespace v3 {

class fobject : public funknown {
public:
	virtual ~fobject() {}

	virtual V3_API v3_result queryInterface(const v3_tuid iid, void **obj)
	{
		if (funknown::iid == iid)
		{
			*obj = static_cast<funknown*>(this);
			return V3_OK;
		}
		else
		{
			return V3_NO_INTERFACE;
		}
	}

	virtual V3_API uint32_t ref()
	{
		return fCounter.fetch_add(1, std::memory_order_relaxed) + 1;
	}

	virtual V3_API uint32_t unref()
	{
		uint32_t value = fCounter.fetch_sub(1, std::memory_order_acq_rel) - 1;
		if (value == 0)
			delete this;
		return value;
	}

private:
	std::atomic<uint32_t> fCounter {1};
};

#define V3_REFCOUNT_METHODS(Base)               \
	virtual V3_API uint32_t ref() override      \
	{                                           \
		return Base::ref();                     \
	}                                           \
	virtual V3_API uint32_t unref() override    \
	{                                           \
		return Base::unref();                   \
	}                                           \

} // namespace v3

#endif
