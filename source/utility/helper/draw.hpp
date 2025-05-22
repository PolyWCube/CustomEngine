#ifndef CUSTOM_DRAW
#define CUSTOM_DRAW

#include "precompiled_header.hpp"

namespace Custom {
	namespace Graphic {
		namespace Draw {
			template <typename BufferType>
			void Line(BufferType& buffer, Math::Vector2<uint16_t> size, Math::Vector2<int> A, Math::Vector2<int> B, RGBAColor<uint8_t, float> rgbaColor) {
				int x0 = A.x, y0 = A.y, x1 = B.x, y1 = B.y;

				int dx = std::abs(x1 - x0);
				int dy = std::abs(y1 - y0);
				int sx = (x0 < x1) ? 1 : -1;
				int sy = (y0 < y1) ? 1 : -1;
				int err = dx - dy;
			
				while (true) {
					size_t index = y0 * size.x + x0;
					buffer.SetData(index, rgbaColor);
					if (x0 == x1 && y0 == y1) break;
					int e2 = 2 * err;
					if (e2 > -dy) {
						err -= dy;
						x0 += sx;
					}
					if (e2 < dx) {
						err += dx;
						y0 += sy;
					}
				}
			}

			template <typename BufferType>
			void Rectangle(BufferType& buffer, Math::Vector2<uint16_t> size, Math::Vector2<int16_t> A, Math::Vector2<int16_t> B, RGBAColor<uint8_t> rgbaColor) {
				Math::Vector2<int16_t> LT(A.x, A.y), RT(B.x, A.y), LB(A.x, B.y), RB(B.x, B.y);
				Line(buffer, size, LT, RT, rgbaColor);
				Line(buffer, size, LT, LB, rgbaColor);
				Line(buffer, size, RT, RB, rgbaColor);
				Line(buffer, size, LB, RB, rgbaColor);
			}

			template <typename BufferType>
			void FillRectangle(BufferType& buffer, Math::Vector2<uint16_t> size, Math::Vector2<int16_t> A, Math::Vector2<int16_t> B, RGBAColor<uint8_t> rgbaColor) {
				int16_t minX = A.x, maxX = B.x, minY = A.y, maxY = B.y;

				for (int16_t y = minY; y <= maxY; ++y) {
					for (int16_t x = minX; x <= maxX; ++x) {
						size_t index = static_cast<size_t>(y) * size.x + static_cast<size_t>(x);
						buffer.SetData(index, rgbaColor);
					}
				}
			}

			template <typename BufferType>
			void Triangle(BufferType& buffer, Math::Vector2<uint16_t> size, Math::Vector2<int16_t> A, Math::Vector2<int16_t> B, Math::Vector2<int16_t> C, RGBAColor<uint8_t, float> rgbaColor) {
				Line(buffer, size, A, B, rgbaColor);
				Line(buffer, size, B, C, rgbaColor);
				Line(buffer, size, C, A, rgbaColor);
			}

			template <typename BufferType>
			void TriangleBuffer(BufferType& buffer, Math::Vector2<uint16_t> size, const std::vector<Math::Vector2<int16_t>>& points, const std::vector<uint16_t>& indices, RGBAColor<uint8_t, float> rgbaColor) {
				if (indices.size() % 3 != 0) {
					return;
				}

				std::set<std::pair<int16_t, int16_t>> drawnEdges;

				for (size_t i = 0; i < indices.size(); i += 3) {
					uint16_t indexA = indices[i];
					uint16_t indexB = indices[i + 1];
					uint16_t indexC = indices[i + 2];

					if (indexA >= points.size() || indexB >= points.size() || indexC >= points.size())
						continue;

					std::pair<int16_t, int16_t> edgeAB = std::make_pair(std::min(indexA, indexB), std::max(indexA, indexB));
					std::pair<int16_t, int16_t> edgeBC = std::make_pair(std::min(indexB, indexC), std::max(indexB, indexC));
					std::pair<int16_t, int16_t> edgeCA = std::make_pair(std::min(indexC, indexA), std::max(indexC, indexA));

					if (drawnEdges.find(edgeAB) == drawnEdges.end()) {
						Line(buffer, size, points[indexA], points[indexB], rgbaColor);
						drawnEdges.insert(edgeAB);
					}

					if (drawnEdges.find(edgeBC) == drawnEdges.end()) {
						Line(buffer, size, points[indexB], points[indexC], rgbaColor);
						drawnEdges.insert(edgeBC);
					}

					if (drawnEdges.find(edgeCA) == drawnEdges.end()) {
						Line(buffer, size, points[indexC], points[indexA], rgbaColor);
						drawnEdges.insert(edgeCA);
					}
				}
			}

			template <typename BufferType>
			void FillTriangleBuffer(BufferType& buffer, Math::Vector2<uint16_t> size, Math::Vector2<int16_t> v1, Math::Vector2<int16_t> v2, Math::Vector2<int16_t> v3, RGBAColor<uint8_t, float> rgbaColor) {
				int minX = std::min({ v1.x, v2.x, v3.x });
				int minY = std::min({ v1.y, v2.y, v3.y });
				int maxX = std::max({ v1.x, v2.x, v3.x });
				int maxY = std::max({ v1.y, v2.y, v3.y });

				minX = std::max(minX, 0);
				minY = std::max(minY, 0);
				maxX = std::min(maxX, static_cast<int>(size.x) - 1);
				maxY = std::min(maxY, static_cast<int>(size.y) - 1);

				for (int y = minY; y <= maxY; ++y) {
					std::vector<float> intersections;

					auto findIntersection = [&](const Math::Vector2<int>& a, const Math::Vector2<int>& b, int scanlineY) -> std::optional<float> {
						if ((a.y <= scanlineY && b.y > scanlineY) || (b.y <= scanlineY && a.y > scanlineY)) {
							float t = static_cast<float>(scanlineY - a.y) / (b.y - a.y);
							return a.x + t * (b.x - a.x);
						}
						return std::nullopt;
					};

					if (auto x = findIntersection(v1, v2, y); x.has_value()) intersections.push_back(x.value());
					if (auto x = findIntersection(v2, v3, y); x.has_value()) intersections.push_back(x.value());
					if (auto x = findIntersection(v3, v1, y); x.has_value()) intersections.push_back(x.value());

					std::sort(intersections.begin(), intersections.end());

					for (size_t i = 0; i < intersections.size() - 1; i += 2) {
						int startX = static_cast<int>(std::round(intersections[i]));
						int endX = static_cast<int>(std::round(intersections[i + 1]));

						startX = std::max(startX, 0);
						endX = std::min(endX, static_cast<int>(size.x) - 1);

						for (int x = startX; x <= endX; ++x) {
							size_t index = y * size.x + x;
							buffer.SetData(index, rgbaColor);
						}
					}
				}
			}
		}
	}
}

#endif