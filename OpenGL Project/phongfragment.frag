#version 410 core
out vec4 fragColor;         //The final color

in vec3 normalTransposed;   //Normal of fragment, already transposed
in vec3 fragmentPosition;
in vec2 UV;

uniform sampler2D textureSampler;

uniform vec3 lightPosition;
uniform vec3 cameraPosition;

uniform float ambientStrengt;
uniform vec3 ambientColor;
uniform float lightStrengt;
uniform vec3 lightColor;
uniform float specularStrength;
uniform int specularExponent;
uniform float constant;
uniform float linear;
uniform float quadratic;

uniform vec3 objectColor = vec3(0.8, 0.8, 0.8); //grey

void main() {    
    // Attenuation
    float distance = length(lightPosition - fragmentPosition);
    float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

    //ambient
    vec3 ambient = ambientStrengt * ambientColor;

    //diffuse
    vec3 normalCorrected = normalize(normalTransposed);
    vec3 lightDirection = normalize(lightPosition - fragmentPosition);
    float angleFactor = max(dot(normalCorrected, lightDirection), 0.0);
    vec3 diffuse = angleFactor * objectColor * lightColor * lightStrengt;

    //specular
    vec3 viewDirection = normalize(cameraPosition - fragmentPosition);
    float spec = 0.0;
    if (angleFactor > 0.0)     //calculations only needed if diffuse is above 0.0
    {
        vec3 reflectDirection = reflect(-lightDirection, normalCorrected);
        spec = pow(max(dot(viewDirection, reflectDirection), 0.0), specularExponent);
    }
    vec3 specular = spec * lightColor * specularStrength;

    vec3 result = (ambient + diffuse + specular) * attenuation;

    fragColor = vec4(result, 1.0) + texture(textureSampler, UV);
}
