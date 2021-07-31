#pragma once

#include <math.h>

#include <napi.h>

#include <webp/encode.h>

#include "format.hpp"
#include "image.hpp"

namespace nodeWebp {

	class Encoder : public Napi::AsyncWorker {

		private:

			uint8_t* buffer = nullptr;

			Napi::Promise::Deferred promise;

			float_t quality = 0;

			uint64_t size = 0;

			Image* image = nullptr;

		public:

			Encoder(
				Napi::Env environment,
				Napi::Object source,
				float_t quality
			);

			~Encoder();

			void Execute();

			void OnError(const Napi::Error& error);

			void OnOK();

			Napi::Promise getPromise();

	};

}
