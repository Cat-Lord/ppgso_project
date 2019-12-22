#pragma once
#include <string>
#include <memory>
#include <list>
#include <map>

#include <glm/glm.hpp>
#include "scene.h"
#include <ppgso/ppgso.h>

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

// Forward declare a scene
class Scene;

class Object {
public:
  std::unique_ptr<ppgso::Mesh> mesh;
  std::unique_ptr<ppgso::Shader> shader;
  std::unique_ptr<ppgso::Texture> texture;
  
  // default values for the object, need to be changed for a specific object
  float reflectivity = 1;
  float shineDamper = 10;

  // Define default constructors as this is an abstract class
  Object() = default;
  Object(const Object&) = default;
  Object(Object&&) = default;
  virtual ~Object() {};

  virtual bool update(Scene &scene, float dt) = 0;
  virtual void render(Scene &scene) = 0;


  virtual void onClick(Scene &scene) {};

  void increasePosition(glm::vec3 increase);
  void increaseRotation(glm::vec3 increase);
  void increaseScale(glm::vec3 increase);

  // Object properties
  glm::vec3 position{0,0,0};
  glm::vec3 rotation{0,0,0};
  glm::vec3 scale{1,1,1};
  glm::mat4 modelMatrix{1};

  protected:
	  void setupUniforms(Scene &scene);
	  void generateModelMatrix();
  public:
	  float toAngle(float rads);
	  float toRads(float angle);
};

