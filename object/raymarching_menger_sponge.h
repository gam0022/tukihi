#ifndef	_RAYMARCHINNG_MENGER_SPONGE_H_
#define	_RAYMARCHINNG_MENGER_SPONGE_H_

#include <cmath>
#include <algorithm>

#include "math/vec3.h"
#include "math/vec2.h"
#include "material.h"
#include "constant.h"
#include "intersection.h"
#include "object/raymarching_object.h"

namespace tsukihi {

	struct RaymarchingMengerSponge : public RaymarchingObject {
	public:
		RaymarchingMengerSponge(const Vec3 &position, const double scale, const Color &emission, const Color &color, const ReflectionType reflection_type) :
			RaymarchingObject(position, scale, emission, color, reflection_type) {
		}

		inline double box(const Vec3 p, double x) const {
			//Vec d = abs(p) - x;
			//return std::min(std::max(d.x, std::max(d.y, d.z)), 0.0) + max(d, 0.0).length();
			return max(abs(p) - x, 0.0).length();
		}

		inline double bar(const Vec2 p, double x) const {
			Vec2 d = abs(p) - x;
			return std::min(std::max(d.x, d.y), 0.0) + max(d, 0.0).length() + 0.01 * x;
			//return max(abs(p) - x, 0.0).length();
		}

		inline double crossBar(const Vec3 p, double x) const {
			double bar_x = bar(p.yz(), x);
			double bar_y = bar(p.zx(), x);
			double bar_z = bar(p.xy(), x);
			return std::min(bar_z, std::min(bar_x, bar_y));
		}

		inline Vec3 opRep(const Vec3 p, double interval) const {
			return mod(p, interval) - interval * 0.5;
		}

		const double mengerSponge(const Vec3& p) const {
			double d = box(p, 1.0);
			const double one_third = 1.0 / 3.0;
			for (int i = 0; i < 4; i++) {
				double k = pow(one_third, i);
				double kh = k * 0.5;
				d = std::max(d, -crossBar(mod(p + kh, k * 2.0) - kh, k * one_third));
			}
			return d;
		}

		double distanceFunction(const Vec3 &p) const {
			return mengerSponge((p - position) / scale) * scale;
		}
	};
}

#endif