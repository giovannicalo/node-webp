#include "decoder.hpp"

namespace nodeWebp {

	Decoder::Decoder(
		Napi::Env environment,
		Napi::Uint8Array source,
		Format format
	) :
		Napi::AsyncWorker(environment),
		format(format),
		promise(Napi::Promise::Deferred::New(environment)),
		source(source)
	{}

	Decoder::~Decoder() {}

	void Decoder::Execute() {
		int32_t height = 0;
		int32_t width = 0;
		if(!WebPGetInfo(
			source.Data(),
			source.ByteLength(),
			&width,
			&height
		)) {
			SetError("[nodeWebp::Decoder::Execute] Failed to read header");
			return;
		}
		if (format == Format::yuv) {
			// TODO: Support odd dimensions
			height = (height + 1) & ~1;
			width = (width + 1) & ~1;
			uint64_t ySize = width * height;
			uint32_t uvStride = std::floor((width + 1) / 2);
			uint64_t uvSize = uvStride * std::floor((height + 1) / 2);
			uint64_t size = ySize + uvSize * 2;
			image = new Image(Format::yuv, width, height, size);
			std::memset(image->data, 0, size);
			if (!WebPDecodeYUVInto(
				source.Data(),
				source.ByteLength(),
				image->data,
				ySize,
				width,
				image->data + ySize,
				uvSize,
				uvStride,
				image->data + ySize + uvSize,
				uvSize,
				uvStride
			)) {
				SetError("[nodeWebp::Decoder::Execute] Failed to decode");
				delete image;
			}
		} else if (format == Format::rgba) {
			uint32_t stride = width * 4;
			uint64_t size = stride * height;
			image = new Image(Format::rgba, width, height, size);
			if (!WebPDecodeRGBAInto(
				source.Data(),
				source.ByteLength(),
				image->data,
				image->size,
				stride
			)) {
				SetError("[nodeWebp::Decoder::Execute] Failed to decode");
				delete image;
			}
		} else {
			SetError("[nodeWebp::Decoder::Execute] Format is invalid");
		}
	}

	void Decoder::OnError(const Napi::Error& error) {
		promise.Reject(error.Value());
	}

	void Decoder::OnOK() {
		Napi::Object output = Napi::Object::New(Env());
		output.Set("data", Napi::Uint8Array::New(
			Env(),
			image->size,
			Napi::ArrayBuffer::New(
				Env(),
				image->data,
				image->size,
				[](Napi::Env environment, void* data, void* image) {
					delete static_cast<Image*>(image);
				},
				image
			),
			0,
			napi_uint8_clamped_array
		));
		output.Set(
			"format",
			Napi::Number::New(Env(), image->format)
		);
		output.Set(
			"height",
			Napi::Number::New(Env(), image->height)
		);
		output.Set(
			"width",
			Napi::Number::New(Env(), image->width)
		);
		promise.Resolve(output);
	}

	Napi::Promise Decoder::getPromise() {
		return promise.Promise();
	}

}
