$input  v_texcoord0

#include "../../deps/bgfx.cmake/bgfx/src/bgfx_shader.sh"

SAMPLER2D(s_color, 0);

void main()
{
	//gl_FragColor = v_color0;
	//gl_FragColor.rgb = vec3(1.0f, 0.7f, 0.7f);

	 vec4 color = texture2D(s_color, v_texcoord0);

	 gl_FragColor.rgb = color.rgb;
	 gl_FragColor.a = 1.0f;

}