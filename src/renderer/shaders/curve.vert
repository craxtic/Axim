$input a_position, a_color0, a_texcoord0
$output v_color0, v_uvw, v_k

#include <bgfx_shader.sh>

static const vec3 t_uvw[3] = {
  vec3(0.0, 0.0, 1.0), 
  vec3(0.5, 0.0, 1.0), 
  vec3(1.0, 1.0, 1.0),
};

void main()
{

  int index  = int(a_color0.a * 255.0 + 0.5) & 0b00000011;
  float w = abs(a_texcoord0);
  

  v_uvw = vec3(
    t_uvw[index].x / w,
    t_uvw[index].y,
    t_uvw[index].z / w
  );

  v_k = w/a_texcoord0;
  v_color0 = a_color0;

  gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));
}