// This file is generated
#pragma once
#include "../align_push.h"

namespace v3
{

class plug_view
	: public funknown
{
public:
	virtual V3_API v3_result isPlatformTypeSupported(const char *platform_type) = 0;
	virtual V3_API v3_result attached(void *parent, const char *platform_type) = 0;
	virtual V3_API v3_result removed() = 0;
	virtual V3_API v3_result onWheel(float distance) = 0;
	virtual V3_API v3_result onKeyDown(int16_t key_char, int16_t key_code, int16_t modifiers) = 0;
	virtual V3_API v3_result onKeyUp(int16_t key_char, int16_t key_code, int16_t modifiers) = 0;
	virtual V3_API v3_result getSize(struct v3_view_rect *) = 0;
	virtual V3_API v3_result setSize(struct v3_view_rect *) = 0;
	virtual V3_API v3_result onFocus(v3_bool state) = 0;
	virtual V3_API v3_result setFrame(struct v3_plug_frame *) = 0;
	virtual V3_API v3_result canResize() = 0;
	virtual V3_API v3_result checkSizeConstraint(struct v3_view_rect *) = 0;
	static const fuid iid;
};

class plug_frame
	: public funknown
{
public:
	virtual V3_API v3_result resizeView(struct v3_plug_view *, struct v3_view_rect *) = 0;
	static const fuid iid;
};

class plug_view_content_scale_steinberg
	: public funknown
{
public:
	virtual V3_API v3_result setContentScaleFactor(float factor) = 0;
	static const fuid iid;
};

class plug_view_param_finder
	: public funknown
{
public:
	virtual V3_API v3_result findParameter(int32_t x, int32_t y, v3_param_id *) = 0;
	static const fuid iid;
};

}
// namespace v3
#include "../align_pop.h"
