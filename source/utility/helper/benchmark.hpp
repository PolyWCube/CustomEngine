#ifndef CUSTOM_BENCHMARK
#define CUSTOM_BENCHMARK

#include "precompiled_header.hpp"

namespace Custom {
	namespace Utility {
		template <typename T>
		using Operation = std::function<T(const T&)>;
		using VoidOperation = std::function<void()>;
		
		using hour = std::chrono::hours;
		using minute = std::chrono::minutes;
		using second = std::chrono::seconds;
		using millisecond = std::chrono::milliseconds;
		using microsecond = std::chrono::microseconds;
		using nanosecond = std::chrono::nanoseconds;
		
		template <typename Unit = std::chrono::microseconds>
		class Benchmark {
		public:
			template <typename T>
			Benchmark(const std::vector<T>& samples, Operation<T> operation)
				: samples_(samples), operation_(operation), isVoid_(false) {}

			Benchmark(VoidOperation voidOperation)
				: voidOperation_(voidOperation), isVoid_(true) {}

			void Run(size_t iterations) {
				auto start = std::chrono::high_resolution_clock::now();
				for (size_t i = 0; i < iterations; ++i) {
					if (!isVoid_) {
						for (const auto& data : samples_) {
							if (operation_)
								results_.push_back(operation_(data));
						}
					} else {
						if (voidOperation_)
							voidOperation_();
					}
				}
				auto end = std::chrono::high_resolution_clock::now();
				duration_ = std::chrono::duration_cast<Unit>(end - start);
			}

			Unit duration() const { return duration_; }
			template <typename T>
			const std::vector<T>& results() const { return results_; }

		private:
			bool isVoid_;
			std::vector<std::any> samples_;
			std::function<std::any(const std::any&)> operation_;
			VoidOperation voidOperation_;
			Unit duration_;
			std::vector<std::any> results_;
		};
	}
}

#endif