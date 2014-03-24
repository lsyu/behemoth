#version 120
attribute vec2 a_position;
attribute vec3 a_color;
attribute vec2 a_uv; // (-1,-1) if no texture

varying vec2 v_position;
varying vec4 v_color;
varying vec2 v_uv;

void main(void)
{
    v_position = a_position;
    v_color = vec4(a_color,1.0f);
    v_uv = a_uv;
    gl_Position = vec4(a_position, 0.0f, 1.0);
}

