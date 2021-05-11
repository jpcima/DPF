// This file is generated
#pragma once
#include "../align_push.h"

namespace v3
{

class component_handler
	: public funknown
{
public:
	virtual V3_API v3_result beginEdit(v3_param_id) = 0;
	virtual V3_API v3_result performEdit(v3_param_id, double value_normalised) = 0;
	virtual V3_API v3_result endEdit(v3_param_id) = 0;
	virtual V3_API v3_result restartComponent(int32_t flags) = 0;
	static const fuid iid;
};

class edit_controller
	: public plugin_base
{
public:
	virtual V3_API v3_result setComponentState(struct v3_bstream *) = 0;
	virtual V3_API v3_result setState(struct v3_bstream *) = 0;
	virtual V3_API v3_result getState(struct v3_bstream *) = 0;
	virtual V3_API int32_t getParameterCount() = 0;
	virtual V3_API v3_result getParamInfo(int32_t param_idx, struct v3_param_info *) = 0;
	virtual V3_API v3_result getParamStringForValue(v3_param_id, double normalised, v3_str_128 output) = 0;
	virtual V3_API v3_result getParamValueForString(v3_param_id, int16_t *input, double *output) = 0;
	virtual V3_API double normalisedParamToPlain(v3_param_id, double normalised) = 0;
	virtual V3_API double plainParamToNormalised(v3_param_id, double normalised) = 0;
	virtual V3_API double getParamNormalised(v3_param_id) = 0;
	virtual V3_API v3_result setParamNormalised(v3_param_id, double normalised) = 0;
	virtual V3_API v3_result setComponentHandler(struct v3_component_handler **) = 0;
	virtual V3_API struct v3_plug_view ** createView(const char *name) = 0;
	static const fuid iid;
};

}
// namespace v3
#include "../align_pop.h"
