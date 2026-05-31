$input a_position, a_color0
$output v_color0, v_uvw, v_k

#include <bgfx_shader.sh>

static const vec3 default_uvw[3][3] = {
  {
    vec3(0.0, 0.0, 1.0), 
    vec3(1.0, 0.0, 0.0), 
    vec3(0.0, 1.0, 0.0),  
  },

  {
    vec3(0.0, 0.0, -1.0), 
    vec3(0.5, 0.0, -1.0), 
    vec3(1.0, 1.0, -1.0),  
  },

  {
    vec3(0.0, 0.0, 1.0), 
    vec3(0.5, 0.0, 1.0), 
    vec3(1.0, 1.0, 1.0),  
  },
  
};

void main()
{
  int flag_w = int(a_color0.b * 255.0 + 0.5) & 0b00000011;
  int index  = int(a_color0.a * 255.0 + 0.5) & 0b00000011;


  v_uvw = default_uvw[flag_w][index]; 
  v_k = flag_w > 0; 

  v_color0 = a_color0;

  gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));
}