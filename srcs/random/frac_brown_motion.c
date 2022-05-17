#include "random.h"
#include <math.h>
#include "mmath.h"

#define NUM_OCTAVES 5

float fbm(t_vector2_f _st)
{
    float v = 0.0;
    float a = 0.5;
    t_vector2_f shift = v2_f(100.0, 100.0);
    // Rotate to reduce axial bias
    t_vector4_f rot = v4_f(cos(0.5), sin(0.5),
                    -sin(0.5), cos(0.50));
    for (int i = 0; i < NUM_OCTAVES; ++i) {
        v += a * pnoise(_st.x, _st.y);
        _st.x = (rot.x * _st.x + rot.y * _st.x) * 2.0 + shift.x;
        _st.y = (rot.z * _st.y + rot.w * _st.y) * 2.0 + shift.y;
        a *= 0.5;
    }
    return v;
}