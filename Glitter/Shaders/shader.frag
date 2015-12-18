#version 130

in vec4 colorPosition;

out vec4 outColor;

void main()
{
    outColor = colorPosition;    
    //vec4(1.0, 1.0, 1.0, 1.0);
}
