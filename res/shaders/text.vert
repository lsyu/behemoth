attribute vec2 position;
attribute vec2 UV;

varying vec2 uv;

void main(void)
{
    uv = UV;
    gl_Position = vec4(vec3(position, 0.0f), 1.0);
}
