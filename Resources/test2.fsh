varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform vec2 position;
uniform float lightSize;

void main()
{
    float darkness = 0.9;
    gl_FragColor = vec4(0.4,0.4,0.4, darkness);
    gl_FragColor = vec4(0.0,0.0,0.0, darkness);
    vec2 centerPos = gl_FragCoord.xy - vec2(position.x, position.y);
    //calculate light density
    float z = sqrt(lightSize*lightSize - centerPos.x*centerPos.x - centerPos.y*centerPos.y);
    z /= lightSize;
    if (length(centerPos) < lightSize)
    {
        gl_FragColor.a = darkness - z*z;
    }
//    if (length(centerPos) < 200.0)
//    {
//        gl_FragColor.a = darkness*0.5 - z;
//    }
}