// This file is generated
#pragma once
#include "../align_push.h"

namespace v3
{

class param_value_queue
	: public funknown
{
public:
	virtual V3_API v3_param_id getParamId() = 0;
	virtual V3_API int32_t getPointCount() = 0;
	virtual V3_API v3_result getPoint(int32_t idx, int32_t *sample_offset, double *value) = 0;
	virtual V3_API v3_result addPoint(int32_t sample_offset, double value, int32_t *idx) = 0;
	static const fuid iid;
};

class param_changes
	: public funknown
{
public:
	virtual V3_API int32_t getParamCount() = 0;
	virtual V3_API struct v3_param_value_queue ** getParamData(int32_t idx) = 0;
	virtual V3_API struct v3_param_value_queue ** addParamData(v3_param_id *id, int32_t *index) = 0;
	static const fuid iid;
};

class process_context_requirements
	: public funknown
{
public:
	virtual V3_API uint32_t getProcessContextRequirements() = 0;
	static const fuid iid;
};

class audio_processor
	: public funknown
{
public:
	virtual V3_API v3_result setBusArrangements(v3_speaker_arrangement *inputs, int32_t num_inputs,
		 v3_speaker_arrangement *outputs, int32_t num_outputs) = 0;
	virtual V3_API v3_result getBusArrangement(int32_t bus_direction, int32_t idx, v3_speaker_arrangement *) = 0;
	virtual V3_API v3_result canProcessSampleSize(int32_t symbolic_sample_size) = 0;
	virtual V3_API uint32_t getLatencySamples() = 0;
	virtual V3_API v3_result setupProcessing(struct v3_process_setup *) = 0;
	virtual V3_API v3_result setProcessing(v3_bool state) = 0;
	virtual V3_API v3_result process(struct v3_process_data *) = 0;
	virtual V3_API uint32_t getTailSamples() = 0;
	static const fuid iid;
};

}
// namespace v3
#include "../align_pop.h"
