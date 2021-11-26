uniform sampler2D texture;
uniform float point;
void main()
{
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec4 pixelNorm = pixel - vec4(1);
    if(pixelNorm.length() < 0.5)
        gl_FragColor.a = 0.0;
    else{
        gl_FragColor = pixel;
    }
}