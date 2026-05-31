$input v_uvw, v_color0, v_k

#include <bgfx_shader.sh>

void main() {
  float u = v_uvw.x;
  float v = v_uvw.y;
  float w = v_uvw.z;

  float ft = min(min(u, v), w) + 0.007;
  float fs = w * (u*u - v);

  float f = (1 - v_k) * ft  +  v_k * fs;

  float dfdx = dFdx(f);
  float dfdy = dFdy(f);

  //float dfdx = (2.0 * u * dFdx(u) - dFdx(v));
  //float dfdy = (2.0 * u * dFdy(u) - dFdy(v));

  float inv_grad = inversesqrt(dfdx * dfdx + dfdy * dfdy + 0.000001);
  float pixel_distance = f * inv_grad;
  //float alpha = clamp(pixel_distance, 0.0, 1.0);

  float alpha = smoothstep(-0.5, 0.5, pixel_distance);

  gl_FragColor = vec4(v_color0.rgb, v_color0.a * alpha);
}