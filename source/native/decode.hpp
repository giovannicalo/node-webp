#pragma once

#include <napi.h>

#include "decoder.hpp"
#include "format.hpp"

namespace nodeWebp {

	Napi::Value decode(const Napi::CallbackInfo& info);

}
