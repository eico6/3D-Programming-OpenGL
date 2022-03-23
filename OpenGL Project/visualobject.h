#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>

#include "vertex.h"
#include "material.h"
#include "collisionbox.h"

class VisualObject : public QOpenGLFunctions_4_1_Core {
public:
   VisualObject();
   virtual ~VisualObject();
   virtual void init(GLint matrixUniform[4])=0;
   virtual void draw()=0;
   virtual void move(float dx, float dy, float dz);
   virtual void move(float dt);
   std::pair<double, double> getPosition2D();
   std::string getName() const;
   void setName(std::string newName);
   void sendShaders(Shader *plainShader, Shader *textureShader, Shader *phongShader, Shader *billboardShader);
   void updateUniforms(Camera *mActiveCamera, Light *lightRef);

   // Returns true if the player is within the objet's collision box, else false
   bool isColliding(const CollisionBox &playerCollision);

   inline Material* getMaterial() { return mMaterial; }
   inline void setRenderObject(const bool &shouldRender){ renderObject = shouldRender; }
   inline CollisionBox getWorldCollisionBox() const { return mWorldCollisionBox; }

   QMatrix4x4 mMatrix;
   QMatrix4x4 mPosition;
   std::vector<Vertex> mVertices;

   void scaleObject(const QVector3D &scalar);
   void rotateObject(const float &angle, const QVector3D &aroundAxis);

protected:
   CollisionBox mLocalCollisionBox;
   CollisionBox mWorldCollisionBox;

   void convertCollision();

   bool renderObject{true};

   std::vector<GLuint> mIndices;

   Material* mMaterial{nullptr};

   GLuint mEAB{0};
   GLuint mVAO{0};
   GLuint mVBO{0};
   GLint mMatrixUniform{0};

   QMatrix4x4 mRotation;
   QMatrix4x4 mScale;

   QVector3D mVelocity;

   std::string mName;
};
#endif // VISUALOBJECT_H
