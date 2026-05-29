$input a_position, a_color0, a_texcoord0
$output v_color0, v_uvw

#include <bgfx_shader.sh>


void main()
{
  vec2 uvs[3] = {
    vec2(0.0, 0.0), // P0 (Start)
    vec2(0.5, 0.0), // P1 (Control)
    vec2(1.0, 1.0)  // P2 (End)
  };

  int index = int(gl_VertexID) % 3;

  v_uvw = vec3(uvs[index], a_texcoord0);

  v_color0 = a_color0;

  gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));
}
