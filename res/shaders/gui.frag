#version 120
uniform float aspect; // width / height (screen)
uniform float alpha;
uniform vec4 size; // x - x, y - y, z - width, w - height
uniform vec4 radius; // x - bl, y - tl, z - tr, w - br
uniform vec4 border; // w(alpha) - width of border, rgb - color
uniform sampler2D texture;

varying vec2 v_position;
varying vec4 v_color;
varying vec2 v_uv;

vec2 correct(vec2 coord)
{
    return vec2(coord.x * aspect, coord.y);
}

float distFromPointToLine(vec2 point, vec2 lineA, vec2 lineB)
{
    return abs((lineB.x - lineA.x) * (point.y - lineA.y) - (lineB.y - lineA.y) * (point.x - lineA.x))
               / sqrt((lineB.x - lineA.x)*(lineB.x - lineA.x)+(lineB.y - lineA.y)*(lineB.y - lineA.y));
}

vec2 c1 = correct(vec2(size.x, size.y))+radius.x;
vec2 c2 = correct(vec2(size.x, size.y + size.w)) + vec2(radius.y,-radius.y);
vec2 c3 = correct(vec2(size.x + size.z, size.y + size.w))-radius.z;
vec2 c4 = correct(vec2(size.x+size.z, size.y)) + vec2(-radius.w, radius.w);

vec2 A1 = vec2(c1.x - radius.x, c1.y);
vec2 B1 = vec2(c2.x - radius.y, c2.y);
vec2 C1 = vec2(c3.x + radius.z, c3.y);
vec2 D1 = vec2(c4.x + radius.w, c4.y);
vec2 A2 = vec2(c1.x, c1.y - radius.x);
vec2 B2 = vec2(c2.x, c2.y + radius.y);
vec2 C2 = vec2(c3.x, c3.y + radius.z);
vec2 D2 = vec2(c4.x, c4.y - radius.w);

// return 0 - outside, 1 - is border, 2 - inside
int genRoundedRectangle(vec2 point, float widthOfBorder, float rA, float rB, float rC, float rD)
{
    if (point.x < size.x || point.x > point.x+size.z || point.y < size.y || point.y > size.y+size.w)
        return 0;
    vec2 pos1 = correct(point);

    float dist = 0.0f;
    float A1B1 = distFromPointToLine(pos1, A1, B1);
    float A2D2 = distFromPointToLine(pos1, A2, D2);

    if (A1B1 <= rA && A2D2 <= rA) {
        // bottom left
        dist = distance(pos1, c1) - rA;
        if (dist <= 0.0f)
            return dist + widthOfBorder > 0.0f ? 1 : 2;
        else
            return 0;
    }
    float B2C2 = distFromPointToLine(pos1, B2, C2);
    if (A1B1 <= rB && B2C2 <= rB) {
        // top right
        dist = distance(pos1, c2) - rB;
        if (dist < 0.0f)
            return dist + widthOfBorder > 0.0f ? 1 : 2;
        else
            return 0;
    }
    float C1D1 = distFromPointToLine(pos1, C1, D1);
    if (B2C2 <= rC && C1D1 <= rC) {
        // top left
        dist = distance(pos1, c3) - rC;
        if (dist < 0.0f)
            return dist + widthOfBorder > 0.0f ? 1 : 2;
        else
            return 0;
    }
    if (C1D1 <= rD && A2D2 <= rD) {
        // bottom left
        dist = distance(pos1, c4) - rD;
        if (dist < 0.0f)
            return dist + widthOfBorder > 0.0f ? 1 : 2;
        else
            return 0;
    }
    // left
    dist = A1B1 - widthOfBorder;
    if (dist < 0.0f)
        return 1;
    // top
    dist = B2C2 - widthOfBorder;
    if (dist < 0.0f)
        return 1;
    // right
    dist = C1D1 - widthOfBorder;
    if (dist < 0.0f)
        return 1;
    // bottom
    dist = A2D2 - widthOfBorder;
    if (dist < 0.0f)
        return 1;

    return 2;
}

void main(void)
{
    vec4 outColor;
    int param = genRoundedRectangle(v_position, border.w, radius.x, radius.y, radius.z, radius.w);
    if (param == 0)
        outColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    else if (param == 1)
        outColor = vec4(border.rgb, 1.0f);
    else if (v_uv.x >= 0.0 && v_uv.y >= 0.0)
        outColor = texture2D(texture, v_uv);
    else
        outColor = vec4(v_color.rgb, alpha);

    gl_FragColor = outColor;
}

