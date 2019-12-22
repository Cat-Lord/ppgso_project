#version 330
// A texture is expected as program attribute
uniform sampler2D Texture;

// Direction of light
uniform vec3 LightDirection;
uniform vec3 lightColor[4];
uniform float shineDamper;
uniform float reflectivity;

// (optional) Transparency
uniform float Transparency;

// (optional) Texture offset
uniform vec2 TextureOffset;

// The vertex shader will feed this input
in vec2 texCoord;

// Wordspace normal passed from vertex shader
in vec4 normal;
in vec3 surfaceNormal;
in vec3 toLightVector[4];
in vec3 toCameraVector;

// The final color
out vec4 FragmentColor;

void main() {
  // Compute diffuse lighting
  
  vec3 unitNormal = normalize(surfaceNormal);
  vec3 unitVectorCamera = normalize(toCameraVector);

  vec3 totalDiffuse = vec3(0.0);
  vec3 totalSpecular = vec3(0.0);

 for(int i = 0; i < 4; i++){
  vec3 unitLightVector = normalize(toLightVector[i]);
  float nDot1 = dot(unitNormal, unitLightVector);
  float brightness = max(nDot1, 0.0);
  vec3 lightDirection = -unitLightVector;
  vec3 reflectedLight = reflect(lightDirection, unitNormal);	// reflected vector
  float specularFactor = dot(reflectedLight, unitVectorCamera);
  specularFactor = max(specularFactor, 0.0);
  float damperFactor = pow(specularFactor, shineDamper);
  totalDiffuse = totalDiffuse + brightness * lightColor[i];
  totalSpecular = totalSpecular + damperFactor * reflectivity * lightColor[i];
 }

  totalDiffuse = max(totalDiffuse, 0.2);

  FragmentColor = vec4(totalDiffuse, 1.0) * texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset) + vec4(totalSpecular, 1.0);
  FragmentColor.a = Transparency;
}
