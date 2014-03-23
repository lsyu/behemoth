#version 120
//phong vertex shader

attribute vec3 vertex;
attribute vec3 normal;

uniform mat4 modelview_matrix;
uniform mat4 projection_matrix;
uniform mat3 normal_matrix;

uniform vec3 light_position;
uniform vec3 eye_position;

varying vec3 direction_to_light;
varying vec3 direction_to_eye;
varying vec3 normal_in_point;

void main(void)
{
	vec3 point_position = vec3(modelview_matrix * vec4(vertex, 1.0)); // point in world-space
	direction_to_light = light_position - point_position; // normalize in fragment shader
	direction_to_eye = eye_position - point_position; // normalize in fragment shader
	normal_in_point = normal_matrix * normal; // normal in world-space
	gl_Position = projection_matrix * modelview_matrix * vec4(vertex, 1.0);
}