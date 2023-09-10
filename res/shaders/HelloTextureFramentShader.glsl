#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 texColor;

uniform sampler2D ourTexture;
uniform sampler2D texture2;

void main() {
    FragColor = mix(texture(ourTexture, texColor), texture(texture2, vec2(1.0 - texColor.x, texColor.y)), 0.2);
}
