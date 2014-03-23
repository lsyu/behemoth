#version 120
// phong fragment shader

varying vec3 direction_to_light;
varying vec3 direction_to_eye;
varying vec3 normal_in_point;

void main(void)
{
	const vec4 ambient_color = vec4(0.5, 0.0, 0.0, 1.0);
	const vec4 diffuse_color = vec4(0.5, 0.0, 0.0, 1.0);
	const vec4 specular_color = vec4(0.7, 0.7, 0.0, 1.0);
	const float specular_power = 10.0;

	vec3 n = normalize(normal_in_point);
	vec3 l = normalize(direction_to_light);
	vec3 e = normalize(direction_to_eye);
	vec3 r = reflect(-e, n);

	vec4 final_diffuse = diffuse_color * max( dot(n, l), 0.0 );
	vec4 final_specular = specular_color * pow( max(dot(l, r), 0.0), specular_power );

	gl_FragColor = ambient_color + final_diffuse + final_specular;
}