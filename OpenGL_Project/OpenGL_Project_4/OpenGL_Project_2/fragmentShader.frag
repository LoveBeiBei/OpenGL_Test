#version 330 core

in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform vec2 num1;

void main()
{
    //color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);
    //color = mix(texture(ourTexture1, vec2((1-TexCoord.x),TexCoord.y)), texture(ourTexture2, vec2((1-TexCoord.x),TexCoord.y)), 0.2);
    color = mix(texture(ourTexture1, vec2((1-TexCoord.x),TexCoord.y)), texture(ourTexture2, vec2((1-TexCoord.x),TexCoord.y)), num1.x);
}