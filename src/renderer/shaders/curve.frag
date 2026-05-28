$input v_uv, v_color0

#include <bgfx_shader.sh>

void main() {
  float u = v_uv.x;
  float v = v_uv.y;

  float f = (u * u) - v;

  float dudx = dFdx(u);
  float dvdx = dFdx(v);
  float dudy = dFdy(u);
  float dvdy = dFdy(v);
  float dfdx = 2.0 * u * dudx - dvdx;
  float dfdy = 2.0 * u * dudy - dvdy;


  float inv_grad = inversesqrt(dfdx * dfdx + dfdy * dfdy + 0.000001);
  float pixel_distance = f * inv_grad;

  float alpha = clamp(0.5 - pixel_distance , 0.0, 1.0);
  
  gl_FragColor = vec4(v_color0.rgb, v_color0.a * alpha);
}
