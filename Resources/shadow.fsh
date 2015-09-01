varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform vec2 position;
uniform float lightSize;
uniform vec4 shadowColor;

void main()
{
    float darkness = 0.55;
    gl_FragColor = shadowColor;
    vec2 centerPos = gl_FragCoord.xy - vec2(position.x, position.y);
    //calculate light density
    float z = sqrt(lightSize*lightSize - centerPos.x*centerPos.x - centerPos.y*centerPos.y);
    z /= lightSize;
    if (length(centerPos) < lightSize) {
        gl_FragColor.a = darkness - z;
    }
//   else if (length(centerPos) < 1.5*lightSize)
//    {
//        gl_FragColor.a = 0.95 - z/2.0;
//    }
    else
    {
        gl_FragColor.a = 0.55;
    }
}