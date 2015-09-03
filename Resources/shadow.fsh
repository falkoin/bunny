varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform vec2 position;
uniform float lightSize;
uniform vec4 shadowColor;

void main()
{
    float darkness = 0.20;
//    gl_FragColor = shadowColor;
    gl_FragColor = vec4(0.0,0.0,0.0,0.0);
    vec2 centerPos = gl_FragCoord.xy - vec2(position.x, position.y);
    //calculate light density
    float z = sqrt(lightSize*lightSize - centerPos.x*centerPos.x - centerPos.y*centerPos.y);
    z /= lightSize*2.0;
    if (length(centerPos) < lightSize) {
        gl_FragColor.a = darkness - z*z;
    }
    else
    {
        gl_FragColor.a = 0.20;
    }
}