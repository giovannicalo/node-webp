#include "encoder.hpp"

namespace nodeWebp {

	Encoder::Encoder(
		Napi::Env environment,
		Napi::Object source,
		float_t quality
	) :
		Napi::AsyncWorker(environment),
		promise(Napi::Promise::Deferred::New(environment)),
		quality(quality)
	{
		Napi::Uint8Array data = source.Get("data").As<Napi::Uint8Array>();
		image = new Image(
			static_cast<Format>(source.Get("format").As<Napi::Number>().Int32Value()),
			source.Get("width").As<Napi::Number>().Uint32Value(),
			source.Get("height").As<Napi::Number>().Uint32Value(),
			data.ByteLength()
		);
		std::memcpy(image->data, data.Data(), data.ByteLength());
	}

	Encoder::~Encoder() {
		delete image;
	}

	void Encoder::Execute() {
		if (image->format == Format::rgba) {
			size = WebPEncodeRGBA(
				image->data,
				image->width,
				image->height,
				image->width * 4,
				quality,
				&buffer
			);
			if (!size) {
				SetError("[nodeWebp::Encoder::Execute] Failed to encode");
			}
		} else if (image->format == Format::yuv) {
			// TODO: Support YUV
			SetError("[nodeWebp::Encoder::Execute] Encoding YUV images is not yet supported");
		} else {
			SetError("[nodeWebp::Encoder::Execute] Format is invalid");
		}
	}

	void Encoder::OnError(const Napi::Error& error) {
		promise.Reject(error.Value());
	}

	void Encoder::OnOK() {
		promise.Resolve(Napi::Buffer<uint8_t>::New(
			Env(),
			buffer,
			size,
			[](Napi::Env environment, void* data) {
				WebPFree(data);
			}
		));
	}

	Napi::Promise Encoder::getPromise() {
		return promise.Promise();
	}

}
