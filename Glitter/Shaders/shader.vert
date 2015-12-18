#version 130

in vec3 position;

out vec4 colorPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj * view * model * vec4(position, 1.0);

    colorPosition = vec4(position, 1.0);
}
