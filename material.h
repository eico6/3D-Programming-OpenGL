#ifndef MATERIAL_H
#define MATERIAL_H

#include <QOpenGLFunctions_4_1_Core>
#include "shader.h"

class Camera;
class Light;

class Material : public QOpenGLFunctions_4_1_Core
{
public:
    Material();
    Material(ShaderType shaderInput);
    void setActiveShader(ShaderType shaderInput);
    void setupModelMatrixUniform(GLint &mMatrixRef, GLint mMatrixArray[4]);
    void retrieveShaders(Shader *plainShader, Shader *textureShader, Shader *phongShader, Shader *billboardShader);
    void setupUniforms();
    void updateUniforms(Camera *mActiveCamera, Light *lightRef);
    inline int getActiveShader() { return mActiveShader; }
    inline void setActiveTextureSlot(const int &inputTextureSlot) { mActiveTextureSlot = inputTextureSlot; }
private:
    Shader *mShaderProgram[4]{nullptr};    //holds pointer the compiled shader
    int mActiveShader;
    int mActiveTextureSlot{0};

    // Texture shader uniforms
    GLint mTextureUniform{-1};

    // Phong shader uniforms
    GLint mLightColorUniform{-1};
    GLint mObjectColorUniform{-1};
    GLint mAmbientLightStrengthUniform{-1};
    GLint mAmbientColor{-1};
    GLint mLightPositionUniform{-1};
    GLint mCameraPositionUniform{-1};
    GLint mSpecularStrengthUniform{-1};
    GLint mSpecularExponentUniform{-1};
    GLint mLightPowerUniform{-1};
    GLint mConstantUniform{-1};
    GLint mLinearUniform{-1};
    GLint mQuadraticUniform{-1};
    GLint mPhongTextureUniform{-1};

    // Billboard shader uniforms
    GLint mBillboardUniform{-1};
};

#endif // MATERIAL_H
