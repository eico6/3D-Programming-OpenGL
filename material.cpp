#include <QDebug>

#include "material.h"
#include "shader.h"
#include "light.h"
#include "camera.h"

Material::Material()
    : mActiveShader{ShaderType::PLAIN_SHADER}
{ }

Material::Material(ShaderType shaderInput)
    : mActiveShader{shaderInput}
{ }

void Material::setActiveShader(ShaderType shaderInput)
{
    mActiveShader = shaderInput;
}

void Material::setupModelMatrixUniform(GLint &mMatrixRef, GLint mMatrixArray[4])
{
    switch (mActiveShader) {
    case ShaderType::PLAIN_SHADER:
        mMatrixRef = mMatrixArray[ShaderType::PLAIN_SHADER];
        break;
    case ShaderType::TEXTURE_SHADER:
        mMatrixRef = mMatrixArray[ShaderType::TEXTURE_SHADER];
        break;
    case ShaderType::PHONG_SHADER:
        mMatrixRef = mMatrixArray[ShaderType::PHONG_SHADER];
        break;
    case ShaderType::BILLBOARD_SHADER:
        mMatrixRef = mMatrixArray[ShaderType::BILLBOARD_SHADER];
    default:
        break;
    }
}

void Material::retrieveShaders(Shader *plainShader, Shader *textureShader, Shader *phongShader, Shader *billboardShader)
{
    mShaderProgram[PLAIN_SHADER]     = plainShader;
    mShaderProgram[TEXTURE_SHADER]   = textureShader;
    mShaderProgram[PHONG_SHADER]     = phongShader;
    mShaderProgram[BILLBOARD_SHADER] = billboardShader;

    setupUniforms();
}

void Material::setupUniforms()
{
    initializeOpenGLFunctions();

    switch (mActiveShader) {
    case ShaderType::PLAIN_SHADER:
        // The plain shdaer currently has no uniforms
        break;
    case ShaderType::TEXTURE_SHADER:
        mTextureUniform              = glGetUniformLocation( mShaderProgram[TEXTURE_SHADER]->getProgram(), "textureSampler" );
        break;
    case ShaderType::PHONG_SHADER:
        mLightColorUniform           = glGetUniformLocation( mShaderProgram[PHONG_SHADER]->getProgram(), "lightColor" );
        mObjectColorUniform          = glGetUniformLocation( mShaderProgram[PHONG_SHADER]->getProgram(), "objectColor" );
        mAmbientLightStrengthUniform = glGetUniformLocation( mShaderProgram[PHONG_SHADER]->getProgram(), "ambientStrengt" );
        mAmbientColor                = glGetUniformLocation( mShaderProgram[PHONG_SHADER]->getProgram(), "ambientColor" );
        mLightPositionUniform        = glGetUniformLocation( mShaderProgram[PHONG_SHADER]->getProgram(), "lightPosition" );
        mSpecularStrengthUniform     = glGetUniformLocation( mShaderProgram[PHONG_SHADER]->getProgram(), "specularStrength" );
        mSpecularExponentUniform     = glGetUniformLocation( mShaderProgram[PHONG_SHADER]->getProgram(), "specularExponent" );
        mLightPowerUniform           = glGetUniformLocation( mShaderProgram[PHONG_SHADER]->getProgram(), "lightStrengt" );
        mCameraPositionUniform       = glGetUniformLocation( mShaderProgram[PHONG_SHADER]->getProgram(), "cameraPosition" );
        mConstantUniform             = glGetUniformLocation( mShaderProgram[PHONG_SHADER]->getProgram(), "constant" );
        mLinearUniform               = glGetUniformLocation( mShaderProgram[PHONG_SHADER]->getProgram(), "linear" );
        mQuadraticUniform            = glGetUniformLocation( mShaderProgram[PHONG_SHADER]->getProgram(), "quadratic" );
        mPhongTextureUniform         = glGetUniformLocation( mShaderProgram[PHONG_SHADER]->getProgram(), "textureSampler");
        break;
    case ShaderType::BILLBOARD_SHADER:
        mBillboardUniform            = glGetUniformLocation( mShaderProgram[BILLBOARD_SHADER]->getProgram(), "textureSampler" );
    default:
        break;
    }
}

void Material::updateUniforms(Camera *mActiveCamera, Light *lightRef)
{
    initializeOpenGLFunctions();

    switch (mActiveShader) {
    case ShaderType::PLAIN_SHADER:
        // The plain shdaer currently has no uniforms
        break;
    case ShaderType::TEXTURE_SHADER:
        glUniform1i(mTextureUniform, mActiveTextureSlot);
        break;
    case ShaderType::PHONG_SHADER:
        glUniform3f(mLightPositionUniform, lightRef->mMatrix.column(3).x(), lightRef->mMatrix.column(3).y(), lightRef->mMatrix.column(3).z());
        glUniform3f(mCameraPositionUniform, mActiveCamera->getEyePos().x(), mActiveCamera->getEyePos().y(), mActiveCamera->getEyePos().z());
        glUniform3f(mLightColorUniform, lightRef->mLightColor.x(), lightRef->mLightColor.y(), lightRef->mLightColor.z());
        glUniform1f(mSpecularStrengthUniform, lightRef->mSpecularStrenght);
        glUniform1i(mSpecularExponentUniform, lightRef->mSpecularExponent);
        glUniform1f(mAmbientLightStrengthUniform, lightRef->mAmbientStrenght);
        glUniform3f(mAmbientColor, lightRef->mAmbientColor.x(), lightRef->mAmbientColor.y(), lightRef->mAmbientColor.z());
        glUniform1f(mLightPowerUniform, lightRef->mLightStrenght);
        glUniform1f(mConstantUniform, lightRef->constant);
        glUniform1f(mLinearUniform, lightRef->linear);
        glUniform1f(mQuadraticUniform, lightRef->quadratic);
        glUniform1i(mPhongTextureUniform, mActiveTextureSlot);
        break;
    case ShaderType::BILLBOARD_SHADER:
        glUniform1i(mBillboardUniform, mActiveTextureSlot);
    default:
        break;
    }
}
