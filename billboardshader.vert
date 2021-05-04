#version 410 core
layout(location = 0) in vec4 posAttr;
layout(location = 1) in vec4 colAttr;
layout(location = 2) in vec2 vertexUV;

out vec4 col;
out vec2 UV;
uniform mat4 mMatrix;
uniform mat4 vMatrix;
uniform mat4 pMatrix;

void main() {
//   vec4 cameraRight = vec4(vMatrix[0][0], vMatrix[1][0], vMatrix[2][0], 0.0f);
//   vec4 cameraUp = vec4(vMatrix[0][1], vMatrix[1][1], vMatrix[2][1], 0.0f);
   col = colAttr;
   UV = vertexUV;
   mat4 mvMatrix = vMatrix * mMatrix;
   mvMatrix[0] = vec4(1.0f, 0.0f, 0.0f, 0.0f);
   mvMatrix[1] = vec4(0.0f, 1.0f, 0.0f, 0.0f);
   mvMatrix[2] = vec4(0.0f, 0.0f, 1.0f, 0.0f);
   gl_Position = pMatrix * mvMatrix * posAttr;
}
