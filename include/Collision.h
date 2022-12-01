#include "Rect.h"
#include "Vec2.h"

#include <algorithm>
#include <cmath>

using namespace std;

class Collision {

	public:
		// ObservaÃ§Ã£o: IsColliding espera Ã¢ngulos em radianos!
		// Para usar graus, forneÃ§a a sua prÃ³pria implementaÃ§Ã£o de Rotate,
		// ou transforme os Ã¢ngulos no corpo de IsColliding.
		static inline bool IsColliding(Rect a, Rect b, float angleOfA, float angleOfB) {

			angleOfA *= PI / 180;
		    angleOfB *= PI / 180;
            Vec2 A[] = { Vec2( a.x, a.y + a.h ),
						  Vec2( a.x + a.w, a.y + a.h ),
						  Vec2( a.x + a.w, a.y ),
						  Vec2( a.x, a.y )
						};
			Vec2 B[] = { Vec2( b.x, b.y + b.h ),
						  Vec2( b.x + b.w, b.y + b.h ),
						  Vec2( b.x + b.w, b.y ),
						  Vec2( b.x, b.y )
						};

			for (auto& v : A) {
				v = Rotate(v - a.GetVecCentralizado(), angleOfA) + a.GetVecCentralizado();
			}

			for (auto& v : B) {
				v = Rotate(v - b.GetVecCentralizado(), angleOfB) + b.GetVecCentralizado();
			}

            Vec2 axes[] = { (A[0] - A[1]).Normalizado(),
			(A[1] - A[2]).Normalizado(),
			(B[0] - B[1]).Normalizado(),
			(B[1] - B[2]).Normalizado() };

			for (auto& axis : axes) {
				float P[4];

				for (int i = 0; i < 4; ++i) P[i] = Dot(A[i], axis);

				float minA = *std::min_element(P, P + 4);
				float maxA = *std::max_element(P, P + 4);

				for (int i = 0; i < 4; ++i) P[i] = Dot(B[i], axis);

				float minB = *std::min_element(P, P + 4);
				float maxB = *std::max_element(P, P + 4);

				if (maxA < minB || minA > maxB)
					return false;
			}

			return true;
		}

	private:

		static inline float Mag(const Vec2& p) {
			return std::sqrt(p.x * p.x + p.y * p.y);
		}

		static inline Vec2 Norm(const Vec2 & p) {
			return p/Mag(p);
            
		}

		static inline float Dot(const Vec2& a, const Vec2& b) {
			return a.x * b.x + a.y * b.y;
		}

		static inline Vec2 Rotate(const Vec2& p, float angle) {
			float cs = std::cos(angle), sn = std::sin(angle);
			return Vec2 ( p.x * cs - p.y * sn, p.x * sn + p.y * cs );
		}
};

// Aqui estÃ£o trÃªs operadores que sua classe Vec2 deve precisar, se jÃ¡ nÃ£o tiver. 
// Se sua classe tiver mÃ©todos para Mag, Norm, Dot e/ou Rotate, vocÃª pode substituir
// os usos desses mÃ©todos por usos dos seus, mas garanta que deem resultados corretos.

// Vec2 operator+(const Vec2& rhs) const {
//    return Vec2(x + rhs.x, y + rhs.y);
// }

// Vec2 operator-(const Vec2& rhs) const {
//    return Vec2(x - rhs.x, y - rhs.y);
// }

// Vec2 operator*(const float rhs) const {
//    return Vec2(x * rhs, y * rhs);
// }