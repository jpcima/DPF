// This file is generated
#pragma once
#include "../align_push.h"

namespace v3
{

class funknown
{
public:
	virtual V3_API v3_result queryInterface(const v3_tuid iid, void **obj) = 0;
	virtual V3_API uint32_t ref() = 0;
	virtual V3_API uint32_t unref() = 0;
	static const fuid iid;
};

class plugin_base
	: public funknown
{
public:
	virtual V3_API v3_result initialise(struct v3_funknown *context) = 0;
	virtual V3_API v3_result terminate() = 0;
	static const fuid iid;
};

}
// namespace v3
#include "../align_pop.h"
