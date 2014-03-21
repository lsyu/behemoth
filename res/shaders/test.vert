#version 120
attribute vec3 vertex;

uniform mat4 modelview_matrix;
uniform mat4 projection_matrix;

void main(void)
{
    gl_Position = projection_matrix * modelview_matrix * vec4(vertex, 1.0f);
}
