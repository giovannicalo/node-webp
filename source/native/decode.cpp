#include "decode.hpp"

Napi::Value nodeWebp::decode(const Napi::CallbackInfo& info) {
	if (!info.Length()) {
		Napi::Error::New(
			info.Env(),
			"[nodeWebp::decode] At least one argument is required"
		).ThrowAsJavaScriptException();
		return info.Env().Null();
	}
	if (!info[0].IsBuffer()) {
		Napi::Error::New(
			info.Env(),
			"[nodeWebp::decode] Argument is not a buffer"
		).ThrowAsJavaScriptException();
		return info.Env().Null();
	}
	auto decoder = new Decoder(
		info.Env(),
		info[0].As<Napi::Uint8Array>(),
		info.Length() >= 2 ? static_cast<Format>(
			info[1].As<Napi::Number>().Int32Value()
		) : Format::rgba
	);
	decoder->Queue();
	return decoder->getPromise();
}
