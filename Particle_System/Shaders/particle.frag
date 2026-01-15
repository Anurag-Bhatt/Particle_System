#version 330 core

in vec2 v_TexCoord;
in vec4 v_Color;

out vec4 FragColor;

void main()
{
    // Basic Colored Square
    //vec2 circCoord = 2.0 * v_TexCoord - 1.0;
    //if (dot(circCoord, circCoord) > 1.0) {
    //    discard;
    //}

    FragColor = v_Color;
    
    //vec2 coord = v_TexCoord * 2.0 - 1.0;
    //float r = length(coord);
    //float alpha  = 1 - smoothstep(0.0, 1.0, r);

    //FragColor = vec4(v_Color.rgb, v_Color.a * 1.0);
    //if(FragColor.a < 0.01){
    //discard;
    //}
}