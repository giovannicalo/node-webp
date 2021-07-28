#include "encode.hpp"

namespace nodeWebp {

	Napi::Value encode(const Napi::CallbackInfo& info) {
		if (!info.Length()) {
			Napi::Error::New(
				info.Env(),
				"[nodeWebp::encode] At least one argument is required"
			).ThrowAsJavaScriptException();
			return info.Env().Null();
		}
		if (!info[0].IsObject()) {
			Napi::Error::New(
				info.Env(),
				"[nodeWebp::decode] Argument is not an object"
			).ThrowAsJavaScriptException();
			return info.Env().Null();
		}
		Encoder* encoder = new Encoder(
			info.Env(),
			info[0].As<Napi::Object>(),
			info.Length() >= 2 ? info[1].As<Napi::Number>().FloatValue() : 90
		);
		encoder->Queue();
		return encoder->getPromise();
	}

}