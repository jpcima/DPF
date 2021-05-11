// This file is generated
#pragma once
#include "../align_push.h"

namespace v3
{

class event_list
	: public funknown
{
public:
	virtual V3_API uint32_t getEventCount() = 0;
	virtual V3_API v3_result getEvent(int32_t idx, struct v3_event *) = 0;
	virtual V3_API v3_result addEvent(struct v3_event *) = 0;
	static const fuid iid;
};

}
// namespace v3
#include "../align_pop.h"
