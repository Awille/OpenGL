#version 330 core
in vec4 ourColor;

out vec4 FragColor;

uniform vec4 linearColor;


void main() {
    FragColor = ourColor;
}
