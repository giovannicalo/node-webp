#include <napi.h>

#include "./decode.hpp"
#include "./encode.hpp"

Napi::Object initialize(Napi::Env environment, Napi::Object exports) {
	exports.Set(
		"decode",
		Napi::Function::New(environment, nodeWebp::decode)
	);
	exports.Set(
		"encode",
		Napi::Function::New(environment, nodeWebp::encode)
	);
	Napi::Object format = Napi::Object::New(environment);
	format.Set(
		"rgba",
		Napi::Number::New(environment, nodeWebp::Format::rgba)
	);
	format.Set(
		"yuv",
		Napi::Number::New(environment, nodeWebp::Format::yuv)
	);
	exports.Set("Format", format);
	return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, initialize)
