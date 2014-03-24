attribute vec2 a_position;
attribute vec2 a_uv;

varying vec2 v_uv;

void main(void)
{
    v_uv = a_uv;
    gl_Position = vec4(a_position, 0.0f, 1.0f);
}
