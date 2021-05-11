// This file is generated
#pragma once
#include "../align_push.h"

namespace v3
{

class plugin_factory
	: public funknown
{
public:
	virtual V3_API v3_result getFactoryInfo(struct v3_factory_info *) = 0;
	virtual V3_API int32_t numClasses() = 0;
	virtual V3_API v3_result getClassInfo(int32_t idx, struct v3_class_info *) = 0;
	virtual V3_API v3_result createInstance(const char *class_id, const char *_iid, void **instance) = 0;
	static const fuid iid;
};

class plugin_factory_2
	: public plugin_factory
{
public:
	virtual V3_API v3_result getClassInfo_2(int32_t idx, struct v3_class_info_2 *) = 0;
	static const fuid iid;
};

class plugin_factory_3
	: public plugin_factory_2
{
public:
	virtual V3_API v3_result getClassInfoUtf16(int32_t idx, struct v3_class_info_3 *) = 0;
	virtual V3_API v3_result setHostContext(struct v3_funknown *host) = 0;
	static const fuid iid;
};

}
// namespace v3
#include "../align_pop.h"
