#version 120

uniform sampler2D texture;
uniform vec3 color;
varying vec2 v_uv;

void main(void)
{
    gl_FragColor = vec4(color, texture2D(texture, v_uv).r);
}

