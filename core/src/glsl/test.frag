#version 120
uniform float aspect; // width / height (screen)
uniform float x; // geometry of rectangle
uniform float y;
uniform float width;
uniform float height;
uniform float rA; // radiuses of rectangle
uniform float rB;
uniform float rC;
uniform float rD;
uniform float borderWidth;
uniform vec3 borderColor;

varying vec4 fragmentColor;
varying vec2 pos;

vec2 correct(vec2 coord)
{
    return vec2(coord.x * aspect, coord.y);
}

float distFromPointToLine(vec2 point, vec2 lineA, vec2 lineB)
{
    return abs((lineB.x - lineA.x) * (point.y - lineA.y) - (lineB.y - lineA.y) * (point.x - lineA.x))
               / sqrt((lineB.x - lineA.x)*(lineB.x - lineA.x)+(lineB.y - lineA.y)*(lineB.y - lineA.y));
}

// return 0 - outside, 1 - is border, 2 - inside
int genRoundedRectangle(vec2 point, float widthOfBorder, float rA, float rB, float rC, float rD)
{
    // примерно тоже, что и при заливке (isInRoundedRectangle)
    vec2 pos1 = correct(point);

    vec2 c1 = correct(vec2(x, y))+rA;
    vec2 c2 = correct(vec2(x, y + height));
    c2 = vec2(c2.x+rB, c2.y-rB);
    vec2 c3 = correct(vec2(x + width, y + height))-rC;
    vec2 c4 = correct(vec2(x+width, y));
    c4 = vec2(c4.x-rD, c4.y+rD);

    vec2 A1 = vec2(c1.x - rA, c1.y);
    vec2 B1 = vec2(c2.x - rB, c2.y);
    vec2 C1 = vec2(c3.x + rC, c3.y);
    vec2 D1 = vec2(c4.x + rD, c4.y);
    vec2 A2 = vec2(c1.x, c1.y - rA);
    vec2 B2 = vec2(c2.x, c2.y + rB);
    vec2 C2 = vec2(c3.x, c3.y + rC);
    vec2 D2 = vec2(c4.x, c4.y - rD);

    float dist = 0.0f;
    float A1B1 = distFromPointToLine(pos1, A1, B1);
    float B2C2 = distFromPointToLine(pos1, B2, C2);
    float C1D1 = distFromPointToLine(pos1, C1, D1);
    float A2D2 = distFromPointToLine(pos1, A2, D2);

    if (A1B1 <= rA && A2D2 <= rA) {
        // Нижний левый угол
        dist = distance(pos1, c1) - rA;
        if (dist <= 0.0f)
            return dist + widthOfBorder > 0.0f ? 1 : 2;
        else
            return 0;
    }
    if (A1B1 <= rB && B2C2 <= rB) {
        // Верхний правый угол
        dist = distance(pos1, c2) - rB;
        if (dist < 0.0f)
            return dist + widthOfBorder > 0.0f ? 1 : 2;
        else
            return 0;
    }
    if (B2C2 <= rC && C1D1 <= rC) {
        // Верхний левый угол
        dist = distance(pos1, c3) - rC;
        if (dist < 0.0f)
            return dist + widthOfBorder > 0.0f ? 1 : 2;
        else
            return 0;
    }
    if (C1D1 <= rD && A2D2 <= rD) {
        // Нижний левый угол
        dist = distance(pos1, c4) - rD;
        if (dist < 0.0f)
            return dist + widthOfBorder > 0.0f ? 1 : 2;
        else
            return 0;
    }
    //Лево
    dist = A1B1 - widthOfBorder;
    if (dist < 0.0f)
        return 1;
    //Верх
    dist = B2C2 - widthOfBorder;
    if (dist < 0.0f)
        return 1;
    //Право
    dist = C1D1 - widthOfBorder;
    if (dist < 0.0f)
        return 1;
    //Низ
    dist = A2D2 - widthOfBorder;
    if (dist < 0.0f)
        return 1;

    return 2;
}

void main(void)
{
    vec4 outColor = fragmentColor;
    int param = genRoundedRectangle(pos, borderWidth, rA, rB, rC, rD);
    if (param == 0)
        outColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    else if (param == 1)
        outColor = vec4(borderColor, 1.0f);
    gl_FragColor = outColor;
}
