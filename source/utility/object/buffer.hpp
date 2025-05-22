#ifndef CUSTOM_BUFFER
#define CUSTOM_BUFFER

#include "precompiled_header.hpp"

namespace Custom {
	namespace Object {
		template <typename Data>
		class Buffer {
		public :
			~Buffer() = default;

			template <typename Self>
			size_t GetSize(this const Self& self) { return self.GetSizeImpl(); }

			template <typename Self>
			Data GetData(this Self& self, size_t index) {
				if (index >= self.GetSizeImpl()) {
					Log::Error("Buffer (", self.GetBufferAddress(), ") : Get index out of range.");
					throw std::out_of_range("Index out of range.");
				}
				return self.GetDatasImpl().at(index);
			}
			template <typename Self>
			std::span<Data> GetDatas(this Self& self) {
				return std::span(self.GetDatasImpl());
			}
			template <typename Self>
			const std::span<const Data> GetDatas(this const Self& self) {
				return std::span(self.GetDatasImpl());
			}
			template <typename Self>
			void SetData(this Self& self, size_t index, const Data& data) {
				if (index >= self.GetSizeImpl()) {
					Log::Error("Buffer (", self.GetBufferAddress(), ") : Get index out of range.");
					throw std::out_of_range("Index out of range.");
				}
				self.GetDatasImpl().at(index) = data;
			}

			template <typename Self, typename F = std::function<std::vector<uint8_t>(const Data&)>>
			std::vector<uint8_t> GetBytes(this const Self& self, F Convert = [](const Data& data) { return Default(data); }) {
				size_t size = self.GetSizeImpl();
				const auto& data = self.GetDatasImpl();
				std::vector<uint8_t> bytes;
				size_t totalBytes = 0;

				for (size_t i = 0; i < size; ++i) {
					std::vector<uint8_t> convertedBytes = Convert(data[i]);
					bytes.insert(bytes.end(), convertedBytes.begin(), convertedBytes.end());
					totalBytes += convertedBytes.size();
				}
				bytes.resize(totalBytes);
				return bytes;
			}

			template <typename Self>
			void SetDataAll(this Self& self, const Data& data) {
				auto& buffer = self.GetDatasImpl();
				std::fill(buffer.begin(), buffer.end(), data);
			}

			template <typename Self>
			std::string GetBufferAddress(this Self& self) {
				std::stringstream ss;
				ss << "0x" << std::hex << std::uppercase << reinterpret_cast<uintptr_t>(self.GetDatasImpl().data());
				return ss.str();
			}
		private :
			template <typename T>
			static std::vector<uint8_t> Default(const T& data) {
				std::vector<uint8_t> bytes(sizeof(Data));
				std::memcpy(bytes.data(), &data, sizeof(Data));
				return bytes;
			}
		};

		template <typename Data, size_t Size>
		class StaticBuffer : public Buffer<Data> {
		public :
			~StaticBuffer() = default;
		private :
			size_t GetSizeImpl() const { return Size; }
			std::array<Data, Size>& GetDatasImpl() { return buffer; }
			const std::array<Data, Size>& GetDatasImpl() const { return buffer; }

			std::array<Data, Size> buffer;
			friend class Buffer<Data>;
		};

		template <typename Data>
		class DynamicBuffer : public Buffer<Data> {
		public:
			DynamicBuffer(size_t size) : size(size), buffer(size) {}
			~DynamicBuffer() = default;

			void Resize(size_t newSize) {
				size = newSize;
				buffer.resize(newSize);
			}
		private :
			size_t GetSizeImpl() const { return size; }
			std::vector<Data>& GetDatasImpl() { return buffer; }
			const std::vector<Data>& GetDatasImpl() const { return buffer; }

			size_t size;
			std::vector<Data> buffer;
			friend class Buffer<Data>;
		};
	}
}

#endif