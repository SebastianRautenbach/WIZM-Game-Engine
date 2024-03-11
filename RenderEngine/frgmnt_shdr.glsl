#version 330 core
out vec4 FragColor;

// MATERIAL SETUP ------------------------------------------------------------

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};



uniform Light light;  

uniform Material material;

// UNiforms ------------------------------------------------------------------


in vec3 FragPos;
in vec3 Normal; 
in vec2 oTexture;

uniform sampler2D texture1;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
    

    // BASIC LIGHT ------------------------------------------------------------
    
    float ambientStrength = 0.1;
    
    vec3 ambient = light.ambient * material.ambient;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(vec3(light.position - FragPos));
    
    // DIFFUSE ---------------------------------------------

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    

    // SPECULAR ---------------------------------------------------------------

    float specularStrength = 0.5;
    
    vec3 viewDir = normalize(camPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular); 


    FragColor = texture(texture1, oTexture) * vec4( (ambient + diffuse + specular), 1.0);



}