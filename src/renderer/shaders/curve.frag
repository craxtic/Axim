$input v_uvw, v_color0, v_k

#include <bgfx_shader.sh>

void main() {
  float u = v_uvw.x;
  float v = v_uvw.y;
  float w = v_uvw.z;

  float f = (u * u - v * w) * v_k;

  float dfdx = (2.0 * u * dFdx(u)) - v * dFdx(w) - w * dFdx(v);
  float dfdy = (2.0 * u * dFdy(u)) - v * dFdy(w) - w * dFdy(v);

  float inv_grad = inversesqrt(dfdx * dfdx + dfdy * dfdy + 0.000001);
  float signed_dist = f * inv_grad;

  float coverage = clamp(0.7 - signed_dist, 0.0, 1.0);

  gl_FragColor = vec4(v_color0.rgb, v_color0.a * coverage);
}