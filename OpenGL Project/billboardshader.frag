#version 410 core

in vec2 UV;
uniform sampler2D textureSampler;
out vec4 fragColor;

void main() {
    fragColor = texture(textureSampler, UV);
}
