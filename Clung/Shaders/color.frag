#version 150

in vec4 fragmentColor;
in vec2 fragmentPosition;

out vec4 color;

void main() {
    color = fragmentColor * textureColor;
}