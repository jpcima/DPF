// This file is generated
#pragma once
#include "../align_push.h"

namespace v3
{

class bstream
	: public funknown
{
public:
	virtual V3_API v3_result read(void *buffer, int32_t num_bytes, int32_t *bytes_read) = 0;
	virtual V3_API v3_result write(void *buffer, int32_t num_bytes, int32_t *bytes_written) = 0;
	virtual V3_API v3_result seek(int64_t pos, int32_t seek_mode, int64_t *result) = 0;
	virtual V3_API v3_result tell(int64_t *pos) = 0;
	static const fuid iid;
};

}
// namespace v3
#include "../align_pop.h"
