// VisualObject.cpp
#include "visualobject.h"

VisualObject::VisualObject()
{
    mMatrix.setToIdentity();
    mPosition.setToIdentity();
    mRotation.setToIdentity();
    mScale.setToIdentity();

    mMaterial = new Material();
}

VisualObject::~VisualObject() {
   glDeleteVertexArrays( 1, &mVAO );
   glDeleteBuffers( 1, &mVBO );
}

void VisualObject::move(float dx, float dy, float dz)
{
    mPosition.setColumn(3, mPosition.column(3) + QVector4D(dx,dy,dz,0));
    mMatrix.translate(dx,dy,dz);

    // Converts objetc's collision box from local- to world space
    if (mLocalCollisionBox.collisionBoxIsActive())
        convertCollision();
}

void VisualObject::move(float dt) {}

std::pair<double, double> VisualObject::getPosition2D()
{
    auto col = mPosition.column(3);
    return std::pair<double, double>(col.x(), col.z());
}

std::string VisualObject::getName() const
{
    return mName;
}

void VisualObject::setName(std::string newName)
{
    mName = newName;
}

void VisualObject::sendShaders(Shader *plainShader, Shader *textureShader, Shader *phongShader, Shader *billboardShader)
{
    mMaterial->retrieveShaders(plainShader, textureShader, phongShader, billboardShader);
}

void VisualObject::updateUniforms(Camera *mActiveCamera, Light *lightRef)
{
    mMaterial->updateUniforms(mActiveCamera, lightRef);
}

void VisualObject::scaleObject(const QVector3D &scalar)
{
    mMatrix.scale(scalar);

    // Converts objetc's collision box from local- to world space
    if (mLocalCollisionBox.collisionBoxIsActive())
        convertCollision();
}

void VisualObject::rotateObject(const float &angle, const QVector3D &aroundAxis)
{
    mMatrix.rotate(angle, aroundAxis);
}

bool VisualObject::isColliding(const CollisionBox &playerCollision)
{
    // If object's collision box is active.
    if (mLocalCollisionBox.collisionBoxIsActive()){

        // Checks if player is within the boundaries along the x-direction.
        if (playerCollision.p2[X] >= mWorldCollisionBox.p1[X] &&
            playerCollision.p1[X] <= mWorldCollisionBox.p2[X]){

            // Checks if player is within the boundaries along the z-direction.
            if (playerCollision.p2[Z] <= mWorldCollisionBox.p1[Z] &&
                playerCollision.p1[Z] >= mWorldCollisionBox.p2[Z]){

                // Both checked true. Player is therefore colliding with this object.
                return true;
            }
        }
    }

    // Collision box is either inactive, or one of the collision-checks failed.
    return false;
}

void VisualObject::convertCollision()
{
    QMatrix4x4 collisionAsMatrix;
    QVector4D answer;

    // p1 = Lower-left corner
    collisionAsMatrix.setToIdentity();
    collisionAsMatrix.setColumn(3, QVector4D(mLocalCollisionBox.p1[X], 0.0f, mLocalCollisionBox.p1[Z], 1.0f));
    answer = (mMatrix * collisionAsMatrix).column(3);
    mWorldCollisionBox.p1 = QVector2D(answer.x(), answer.z());

    // p2 = Upper-right corner
    collisionAsMatrix.setToIdentity();
    collisionAsMatrix.setColumn(3, QVector4D(mLocalCollisionBox.p2[X], 0.0f, mLocalCollisionBox.p2[Z], 1.0f));
    answer = (mMatrix * collisionAsMatrix).column(3);
    mWorldCollisionBox.p2 = QVector2D(answer.x(), answer.z());
}
