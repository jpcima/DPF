// This file is generated
#pragma once
#include "../align_push.h"

namespace v3
{

class component
	: public plugin_base
{
public:
	virtual V3_API v3_result getControllerClassId(v3_tuid class_id) = 0;
	virtual V3_API v3_result setIoMode(int32_t io_mode) = 0;
	virtual V3_API int32_t getBusCount(int32_t media_type, int32_t bus_direction) = 0;
	virtual V3_API v3_result getBusInfo(int32_t media_type, int32_t bus_direction,
		 int32_t bus_idx, struct v3_bus_info *bus_info) = 0;
	virtual V3_API v3_result getRoutingInfo(struct v3_routing_info *input,
		 struct v3_routing_info *output) = 0;
	virtual V3_API v3_result activateBus(int32_t media_type, int32_t bus_direction,
		 int32_t bus_idx, v3_bool state) = 0;
	virtual V3_API v3_result setActive(v3_bool state) = 0;
	virtual V3_API v3_result setState(struct v3_bstream **) = 0;
	virtual V3_API v3_result getState(struct v3_bstream **) = 0;
	static const fuid iid;
};

}
// namespace v3
#include "../align_pop.h"
