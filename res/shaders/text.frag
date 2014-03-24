#version 120

uniform sampler2D texture;
varying vec2 v_uv;

void main(void)
{
    gl_FragColor = texture2D(texture, v_uv);
}

