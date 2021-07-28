#pragma once

#include <napi.h>

#include "encoder.hpp"
#include "format.hpp"

namespace nodeWebp {

	Napi::Value encode(const Napi::CallbackInfo& info);

}
