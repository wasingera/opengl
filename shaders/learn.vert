#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord0;
out vec2 TexCoord1;

out vec3 fPos;

void main() {
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord0 = aTexCoord;
    TexCoord1 = vec2(1 - aTexCoord.x, aTexCoord.y);
}