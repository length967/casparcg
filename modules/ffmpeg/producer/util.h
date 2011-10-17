#pragma once

#include <common/memory/safe_ptr.h>

#include <core/video_format.h>
#include <core/producer/frame/pixel_format.h>
#include <core/mixer/audio/audio_mixer.h>


#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable : 4244)
#endif
extern "C" 
{
	#include <libavutil/pixfmt.h>
	#include <libavcodec/avcodec.h>
}
#if defined(_MSC_VER)
#pragma warning (pop)
#endif

struct AVFrame;
struct AVFormatContext;
struct AVPacket;

namespace caspar {

namespace core {

struct pixel_format_desc;
class write_frame;
struct frame_factory;

}

namespace ffmpeg {

static const PixelFormat	CASPAR_PIX_FMT_LUMA = PIX_FMT_MONOBLACK; // Just hijack some unual pixel format.

core::field_mode::type		get_mode(AVFrame& frame);
core::pixel_format::type	get_pixel_format(PixelFormat pix_fmt);
core::pixel_format_desc		get_pixel_format_desc(PixelFormat pix_fmt, size_t width, size_t height);
int							make_alpha_format(int format); // NOTE: Be careful about CASPAR_PIX_FMT_LUMA, change it to PIX_FMT_GRAY8 if you want to use the frame inside some ffmpeg function.
safe_ptr<core::write_frame> make_write_frame(const void* tag, const safe_ptr<AVFrame>& decoded_frame, const safe_ptr<core::frame_factory>& frame_factory, int hints);

void fix_meta_data(AVFormatContext& context);

std::shared_ptr<AVPacket> create_packet();
const std::shared_ptr<AVPacket>& loop_packet();
const std::shared_ptr<AVPacket>& eof_packet();
const std::shared_ptr<AVFrame>& loop_video();
const std::shared_ptr<AVFrame>& empty_video();
const std::shared_ptr<AVFrame>& eof_video();
const std::shared_ptr<core::audio_buffer>& loop_audio();
const std::shared_ptr<core::audio_buffer>& empty_audio();
const std::shared_ptr<core::audio_buffer>& eof_audio();

}}