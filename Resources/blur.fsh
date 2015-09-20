varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform float lightSize;

void main()
{
    float darkness = 0.70;
    gl_FragColor = vec4(0.0,0.0,0.0,0.0);
    vec2 centerPos = gl_FragCoord.xy;

    gl_FragColor.r = 0.70;

}