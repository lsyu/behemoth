#version 120
attribute vec2 position;
attribute vec3 color;

varying vec4 fragmentColor;
varying vec2 pos;

void main(void)
{
    fragmentColor = vec4(color,1.0f);

    pos = position;

    gl_Position = vec4(vec3(position, 0.0f), 1.0);
}
