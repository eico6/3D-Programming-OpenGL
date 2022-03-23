#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include "vertex.h"
#include "visualobject.h"
#include <QWindow>
#include <QOpenGLFunctions_4_1_Core>
#include <QTimer>
#include <QElapsedTimer>
#include <vector>
#include "trianglesurface.h"
#include "cube.h"
#include "matrix4x4.h"
#include "camera.h"
#include <vector>
#include <unordered_map>
#include "quadtree.h"

class Quadtree;
class QOpenGLContext;
class Shader;
class MainWindow;
class Texture;
class Light;
class Material;

enum GameMode{
    PLAY_MODE = 0,
    EDIT_MODE = 1
};

// This inherits from QWindow to get access to the Qt functionality and
// OpenGL surface.
// We also inherit from QOpenGLFunctions, to get access to the OpenGL functions
// This is the same as using "glad" and "glw" from general OpenGL tutorials
class RenderWindow : public QWindow, protected QOpenGLFunctions_4_1_Core
{
    Q_OBJECT
public:
    RenderWindow(const QSurfaceFormat &format, MainWindow *mainWindow);
    ~RenderWindow() override;

    QOpenGLContext *context() { return mContext; }

    void exposeEvent(QExposeEvent *) override;  //gets called when app is shown and resized

    void reset();

    bool mToggleGizmos{false};
    bool mToggleWireframe{false};

    void setIsInHouse(bool isInHouse);

    // Player movement
    inline void setGoingRight(const bool &input) { goingRight = input; }
    inline void setGoingLeft(const bool &input)  { goingLeft = input; }
    inline void setGoingUp(const bool &input)    { goingUp = input; }
    inline void setGoingDown(const bool &input)  { goingDown = input; }

    // Camera movement
    inline void setFlyRight(const bool &input) { flyRight = input; }
    inline void setFlyLeft(const bool &input)  { flyLeft = input; }
    inline void setFlyUp(const bool &input)    { flyUp = input; }
    inline void setFlyDown(const bool &input)  { flyDown = input; }

private slots:
    void render();

private:
    void resetMovements();

    void uncollideTrophies();

    void transformObjects();

    bool mIsColliding{false};

    void checkLooseCondition();

    int mActiveGameMode{PLAY_MODE};        // 0 = PLAY_MODE | 1 = EDIT_MODE

    int trophiesPickedUp{0};

    void wireframeGizmosMode();

    void compileShaders();

    float xMin, zMin, xMax, zMax, hDelta; // For trianglesurface parameters

    float nextYPos{0};                       // Player's next y-position, used in barycentric coordinates

    void barycentricCoordinates();

    void miscRenderStuff();

    void playerMovement();
    void cameraMovement();

    bool activateMovement{false};

    int amountOfTrophies;

    QVector3D thirdPersonPos;
    QVector3D inFrontOfPlayer;

    int activeNpcPath;

    bool trophiesExists;

    bool mIsInHouse{false};

    double timeElapsed;

    std::vector<VisualObject*> mObjects;
    std::unordered_map<std::string, VisualObject*> mMap;  // Hash container
    gsml::Quadtree<std::string, VisualObject*> mQuadtree;

    void init();

    QOpenGLContext *mContext{nullptr};
    bool mInitialized{false};

    void setupPlainShader();
    void setupTextureShader();
    void setupPhongShader();
    void setupBillboardShader();
    GLint mMatrixUniform[4];
    GLint vMatrixUniform[4];
    GLint pMatrixUniform[4];

    Texture *mTexture[5]{nullptr};
    Shader *mShaderProgram[4]{nullptr};      //holds pointer the GLSL shader program

    GLuint mVAO;                             //OpenGL reference to our VAO
    GLuint mVBO;                             //OpenGL reference to our VBO

    QTimer *mRenderTimer{nullptr};           //timer that drives the gameloop
    QElapsedTimer mTimeStart;                //time variable that reads the calculated FPS

    MainWindow *mMainWindow{nullptr};        //points back to MainWindow to be able to put info in StatusBar

    class QOpenGLDebugLogger *mOpenGLDebugLogger{nullptr};  //helper class to get some clean debug info from OpenGL

    void checkForGLerrors();                 //helper function that uses QOpenGLDebugLogger or plain glGetError()

    void calculateFramerate();               //as name says

    void startOpenGLDebugger();              //starts QOpenGLDebugLogger if possible

    float mXMovement, mZMovement;
    float mMovementSpeed{0.035f};
    float mFlyingSpeed{0.08f};

    Camera *mEditCamera;
    Camera *mPlayCamera;
    Camera *mActiveCamera;

protected:
    //    void mousePressEvent(QMouseEvent *event) override{}
    //    void mouseMoveEvent(QMouseEvent *event) override{}
    //    void wheelEvent(QWheelEvent *event) override{}
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    // Player movement
    bool goingRight{false};
    bool goingLeft{false};
    bool goingUp{true};
    bool goingDown{false};

    // Camera movement
    bool flyRight{false};
    bool flyLeft{false};
    bool flyUp{false};
    bool flyDown{false};

};

#endif // RENDERWINDOW_H
