#version 120
attribute vec2 position;
attribute vec3 color;
attribute vec2 UV;

varying vec4 fragmentColor;
varying vec2 pos;
varying vec2 uv;

void main(void)
{
    fragmentColor = vec4(color,1.0f);

    pos = position;
    uv = UV;

    gl_Position = vec4(vec3(position, 0.0f), 1.0);
}
