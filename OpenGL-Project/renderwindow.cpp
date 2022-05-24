#include "renderwindow.h"
#include <QTimer>
#include <QMatrix4x4>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLDebugLogger>
#include <QKeyEvent>
#include <QStatusBar>
#include <QDebug>

#include <iostream>
#include <cmath>

#include "shader.h"
#include "mainwindow.h"
#include "xyz.h"
#include "grid.h"
#include "cube.h"
#include "quadtree.cpp"
#include "tetrahedron.h"
#include "interactiveobject.h"
#include "linecurve.h"
#include "barycentrictriangle.h"
#include "octahedronball.h"
#include "disc.h"
#include "door.h"
#include "house.h"
#include "texture.h"
#include "light.h"
#include "objmesh.h"
#include "skybox.h"
#include "billboard.h"
#include "heightmap.h"

#define EXISTS(x) mMap.find(x) != mMap.end()

RenderWindow::RenderWindow(const QSurfaceFormat &format, MainWindow *mainWindow)
    : mContext(nullptr), mInitialized(false), mMainWindow(mainWindow), activeNpcPath{1}
{
    //This is sent to QWindow:
    setSurfaceType(QWindow::OpenGLSurface);
    setFormat(format);
    //Make the OpenGL context
    mContext = new QOpenGLContext(this);
    //Give the context the wanted OpenGL format (v4.1 Core)
    mContext->setFormat(requestedFormat());
    if (!mContext->create()) {
        delete mContext;
        mContext = nullptr;
        qDebug() << "Context could not be made - quitting this application";
    }

    //Make the gameloop timer:
    mRenderTimer = new QTimer(this);

    // Camera
    mPlayCamera = new Camera(PLAY_MODE);
    mEditCamera = new Camera(EDIT_MODE);
    mActiveCamera = mPlayCamera;
}

RenderWindow::~RenderWindow()
{
    delete mPlayCamera;
    delete mEditCamera;

    //cleans up the GPU memory
    glDeleteVertexArrays( 1, &mVAO );
    glDeleteBuffers( 1, &mVBO );
}

// Sets up the general OpenGL stuff and the buffers needed to render a triangle
void RenderWindow::init()
{
    //Connect the gameloop timer to the render function:
    //This makes our render loop
    connect(mRenderTimer, SIGNAL(timeout()), this, SLOT(render()));

    //The OpenGL context has to be set.
    //The context belongs to the instanse of this class!
    if (!mContext->makeCurrent(this)) {
        qDebug() << "makeCurrent() failed";
        return;
    }

    // Trianglesurface parameters
//    xMin = -7.0f;
//    xMax = 7.0f;
//    zMin = -7.0f;
//    zMax = 7.0f;
//    hDelta = 0.35f; // 0.35f is nice
//    mMap.insert(std::pair<std::string, VisualObject*>{"trianglesurface", new TriangleSurface("trianglesurface.txt", xMin, xMax, zMin, zMax, hDelta, 1)});

    // insert all objects into a std::unordered_map
    mMap.insert(std::pair<std::string, VisualObject*>{"heightmap", new Heightmap("../3D-Programming-OpenGL/OpenGL-Project/Assets/heightmap.bmp")});
    mMap.insert(std::pair<std::string, VisualObject*>{"linecurve", new LineCurve("linecurve.txt", 1)});
    mMap.insert(std::pair<std::string, VisualObject*>{"beziercurve", new LineCurve("beziercurve.txt", 2)});
    mMap.insert(std::pair<std::string, VisualObject*>{"leastsquaresmethod", new LineCurve("leastsquaresmethod.txt", 3)});
    mMap.insert(std::pair<std::string, VisualObject*>{"interpolation", new LineCurve("interpolation.txt", 4)});
    mMap.insert(std::pair<std::string, VisualObject*>{"disc", new Disc("disc.txt")});
    mMap.insert(std::pair<std::string, VisualObject*>{"cube", new Cube()});
    mMap.insert(std::pair<std::string, VisualObject*>{"xyz", new XYZ()});
    mMap.insert(std::pair<std::string, VisualObject*>{"grid", new Grid()});
    mMap.insert(std::pair<std::string, VisualObject*>{"Trophy1", new Tetrahedron()});
    mMap.insert(std::pair<std::string, VisualObject*>{"Trophy2", new Tetrahedron()});
    mMap.insert(std::pair<std::string, VisualObject*>{"Trophy3", new Tetrahedron()});
    mMap.insert(std::pair<std::string, VisualObject*>{"Trophy4", new Tetrahedron()});
    mMap.insert(std::pair<std::string, VisualObject*>{"Trophy5", new Tetrahedron()});
    mMap.insert(std::pair<std::string, VisualObject*>{"Trophy6", new Tetrahedron()});
    mMap.insert(std::pair<std::string, VisualObject*>{"door", new Door()});
    mMap.insert(std::pair<std::string, VisualObject*>{"house", new House()});
    mMap.insert(std::pair<std::string, VisualObject*>{"octahedronball1", new OctahedronBall(3)});
    mMap.insert(std::pair<std::string, VisualObject*>{"octahedronball2", new OctahedronBall(2)});
    mMap.insert(std::pair<std::string, VisualObject*>{"octahedronball3", new OctahedronBall(1)});
    mMap.insert(std::pair<std::string, VisualObject*>{"light", new Light()});
    mMap.insert(std::pair<std::string, VisualObject*>{"suzanne", new ObjMesh("../3D-Programming-OpenGL/OpenGL-Project/Assets/suzanne.obj")});
    mMap.insert(std::pair<std::string, VisualObject*>{"cactus1", new ObjMesh("../3D-Programming-OpenGL/OpenGL-Project/Assets/cactus.obj")});
    mMap.insert(std::pair<std::string, VisualObject*>{"cactus2", new ObjMesh("../3D-Programming-OpenGL/OpenGL-Project/Assets/cactus.obj")});
    mMap.insert(std::pair<std::string, VisualObject*>{"cactus3", new ObjMesh("../3D-Programming-OpenGL/OpenGL-Project/Assets/cactus.obj")});
    mMap.insert(std::pair<std::string, VisualObject*>{"cactus4", new ObjMesh("../3D-Programming-OpenGL/OpenGL-Project/Assets/cactus.obj")});
    mMap.insert(std::pair<std::string, VisualObject*>{"winner", new ObjMesh("../3D-Programming-OpenGL/OpenGL-Project/Assets/winner.obj")});
    mMap.insert(std::pair<std::string, VisualObject*>{"camera", new ObjMesh("../3D-Programming-OpenGL/OpenGL-Project/Assets/camera.obj")});
    mMap.insert(std::pair<std::string, VisualObject*>{"skybox", new Skybox()});
    mMap.insert(std::pair<std::string, VisualObject*>{"pyramid", new Billboard()});

    // Name each object in the container
    for(auto it = mMap.begin(); it != mMap.end(); it++)
    {
        it->second->setName(it->first);
    }

    gsml::Point2D nw{-7,-7}, ne{7,-7}, sw{-7, 7}, se{7, 7};
    mQuadtree.init(nw, ne, sw, se);

    mXMovement = 0.0f;
    mZMovement = 0.0f;
    timeElapsed = 0.0f;

    thirdPersonPos = QVector3D(0.0f, 0.0f, 0.0f);
    inFrontOfPlayer = QVector3D(0.0f, 0.0f, 0.0f);

    amountOfTrophies = 6;
    int trophyCounter{0};
    for(int i{1}; i <= amountOfTrophies; i++)
    {
        if (EXISTS("Trophy" + std::to_string(i)))
            trophyCounter++;
    }
    trophiesExists = (trophyCounter == amountOfTrophies) ? true : false;

    // The "YOU WIN!" display should start off as hidden
    if (EXISTS("winner"))
    mMap["winner"]->setRenderObject(false);

    //just to make sure we don't init several times
    //used in exposeEvent()
    if (!mInitialized)
        mInitialized = true;

    //must call this to use OpenGL functions
    initializeOpenGLFunctions();

    //Print render version info (what GPU is used):
    //(Have to use cout to see text- qDebug just writes numbers...)
    //Nice to see if you use the Intel GPU or the dedicated GPU on your laptop
    // - can be deleted
    std::cout << "The active GPU and API: \n";
    std::cout << "  Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "  Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "  Version: " << glGetString(GL_VERSION) << std::endl;

    startOpenGLDebugger();

    glEnable(GL_DEPTH_TEST);                 //enables depth sorting - must then use GL_DEPTH_BUFFER_BIT in glClear
    //    glEnable(GL_CULL_FACE);            //draws only front side of models - usually what you want - test it out!
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);    //gray color used in glClear GL_COLOR_BUFFER_BIT

    //Compile shaders:
    compileShaders();
    setupPlainShader();
    setupTextureShader();
    setupPhongShader();
    setupBillboardShader();

    //**********************  Load texture ready for use  **********************
    //Returns a pointer to the Texture class. This reads and sets up the texture for OpenGL
    //and returns the Texture ID that OpenGL uses from Texture::id()
    mTexture[0] = new Texture();
    mTexture[1] = new Texture("../3D-Programming-OpenGL/OpenGL-Project/Assets/dirt.bmp");
    mTexture[2] = new Texture("../3D-Programming-OpenGL/OpenGL-Project/Assets/stone.bmp");
    mTexture[3] = new Texture("../3D-Programming-OpenGL/OpenGL-Project/Assets/skybox.bmp");
    mTexture[4] = new Texture("../3D-Programming-OpenGL/OpenGL-Project/Assets/pyramid.bmp");

    //Set the textures loaded to a texture unit (also called a texture slot)
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTexture[0]->id());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mTexture[1]->id());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, mTexture[2]->id());
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, mTexture[3]->id());
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, mTexture[4]->id());

    // Call init() for all objects and send shaders
    for (auto it = mMap.begin(); it != mMap.end(); it++){
        (*it).second->init(mMatrixUniform);
        (*it).second->sendShaders(mShaderProgram[PLAIN_SHADER], mShaderProgram[TEXTURE_SHADER], mShaderProgram[PHONG_SHADER], mShaderProgram[BILLBOARD_SHADER]);
    }

    // 'PLAY_MODE' camera
    mPlayCamera->init();
    mPlayCamera->perspective(100, 4.0/3.0, 0.1, 60.0);

    // 'EDIT_MODE' camera
    mEditCamera->init();
    mEditCamera->perspective(110, 4/3, 0.1, 120.0);
    mEditCamera->setEyePos(3.0f, 3.0f, 3.0f);

    transformObjects();
    mQuadtree.subDivide(5);

    for(auto it = mMap.begin(); it!= mMap.end(); it++)
    {
        mQuadtree.insert(gsml::Point2D(it->second->getPosition2D()), it->first, it->second);
    }

    glBindVertexArray(0);       //unbinds any VertexArray - good practice

}

// Called each frame - doing the rendering!!!
void RenderWindow::render()
{
    initializeOpenGLFunctions(); //must call this every frame it seems...
    mContext->makeCurrent(this); //must be called every frame (every time mContext->swapBuffers is called)
    mTimeStart.restart(); //restart FPS clock

    // 'PLAY_MODE' camera variables
    thirdPersonPos = static_cast<Cube*>(mMap["cube"])->getPos() + QVector3D(0.0f, 0.6f, 0.7f);
    inFrontOfPlayer = static_cast<Cube*>(mMap["cube"])->getCameraTarget();

    // 'PLAY_MODE' camera rendering
    if (mActiveCamera == mPlayCamera) {
        if (mIsInHouse) {
            QVector3D housePos{mMap["house"]->mMatrix.column(3)};
            QVector3D houseCameraPos{housePos};
            houseCameraPos[0] -= 0.8f;
            houseCameraPos[1] += 1.0f;
            houseCameraPos[2] += 0.8f;
            mPlayCamera->lookAt(houseCameraPos, housePos, QVector3D{0,1,0});
        } else {
            mPlayCamera->lookAt(thirdPersonPos, inFrontOfPlayer, QVector3D{0,1,0});
        }
    }

    miscRenderStuff();     // void function for more compact code
    wireframeGizmosMode(); // Disable object that should not render
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Light* lightRef = static_cast<Light*>(mMap["light"]);

    //**********************  Draw() all objects  **********************
    for (auto it = mMap.begin(); it != mMap.end(); it++)
    {
        // Update camera
        const int activeShader{ (*it).second->getMaterial()->getActiveShader() };
        glUseProgram(mShaderProgram[activeShader]->getProgram());
        mActiveCamera->update(pMatrixUniform[activeShader], vMatrixUniform[activeShader]);

        // Update uniforms and draw()
        (*it).second->updateUniforms(mActiveCamera, lightRef);
        (*it).second->draw();
        checkForGLerrors();
    }

    if (mActiveGameMode == PLAY_MODE) playerMovement();
    if (mActiveGameMode == EDIT_MODE) cameraMovement();
    calculateFramerate();
    mContext->swapBuffers(this);

    checkForGLerrors();
}

void RenderWindow::wireframeGizmosMode()
{
    // Gizmos
    switch (mActiveGameMode) {
    case PLAY_MODE:
        mMap["xyz"]->setRenderObject(mToggleGizmos);
        mMap["grid"]->setRenderObject(mToggleGizmos);
        mMap["camera"]->setRenderObject(false);
        mMap["linecurve"]->setRenderObject(mToggleGizmos);
        mMap["leastsquaresmethod"]->setRenderObject(mToggleGizmos);
        mMap["beziercurve"]->setRenderObject(mToggleGizmos);
        mMap["interpolation"]->setRenderObject(mToggleGizmos);
        break;
    case EDIT_MODE:
        mMap["xyz"]->setRenderObject(mToggleGizmos);
        mMap["grid"]->setRenderObject(mToggleGizmos);
        mMap["camera"]->setRenderObject(mToggleGizmos);
        mMap["linecurve"]->setRenderObject(mToggleGizmos);
        mMap["leastsquaresmethod"]->setRenderObject(mToggleGizmos);
        mMap["beziercurve"]->setRenderObject(mToggleGizmos);
        mMap["interpolation"]->setRenderObject(mToggleGizmos);
        break;
    default:
        break;
    }

    // Wireframe
    if (mToggleWireframe){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else{
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void RenderWindow::miscRenderStuff()
{
    // NPC movement
    if (EXISTS("disc"))
    static_cast<Disc*>(mMap["disc"])->NpcMovement(activeNpcPath);

    // Rotate trophies
    if (trophiesExists) {
        for(int i{1}; i <= amountOfTrophies; i++) {
            mMap["Trophy" + std::to_string(i)]->rotateObject((180.0f * 0.05f +
            (30.0f * static_cast<Tetrahedron*>(mMap["Trophy" + std::to_string(i)])->colliding)) / (float)M_PI, QVector3D(0.0f, 1.0f, 0.0f));
        }
    }

    // "Rocking" animation for "YOU WIN!"
    if (EXISTS("winner")){
        mMap["winner"]->rotateObject((cos(timeElapsed / 1000.0f)) / (float)M_PI * 0.5f, QVector3D(0.0f, 0.0f, 1.0f));
    }

    // Open/Close door
    if (EXISTS("door")) {
        static_cast<Door*>(mMap["door"])->openDoor(0.025);
        static_cast<Door*>(mMap["door"])->closeDoor(-0.025);
    }

    // Light orbit animation
    if(EXISTS("light"))
    static_cast<Light*>(mMap["light"])->orbitAnimation();

    // Spin OctahedronBall around its y-axis
    if (EXISTS("octahedronball1") && EXISTS("octahedronball2") && EXISTS("octahedronball3")){
        static_cast<OctahedronBall*>(mMap["octahedronball1"])->rotateAroundYAxis(0.1f);
        static_cast<OctahedronBall*>(mMap["octahedronball2"])->rotateAroundYAxis(-0.13f);
        static_cast<OctahedronBall*>(mMap["octahedronball3"])->rotateAroundYAxis(0.30f);
    }
}

void RenderWindow::barycentricCoordinates()
{
    // barycentricCoordinates() will calculate the next y-coordinate out from current playerPos.
    // So the player will always be one step ahead in the y-direction.
    QVector2D a, b, c;
    QVector3D barycCoords;
    float area{};
    QVector3D collidingQuad[6] {};
    const Heightmap* surfaceRef = static_cast<Heightmap*>(mMap["heightmap"]);
    const QVector2D playerPos = QVector2D(static_cast<Cube*>(mMap["cube"])->getPos().x(), static_cast<Cube*>(mMap["cube"])->getPos().z());
    int indexOffset{};

    // 0.35f is 'h' | '20' is the amount of quads in negative x- and y-direction respectively (abs(-7.0 / 0.35)) |
    // '240' is the amount of vertices per change in x-direction (6 * (abs(-7.0) + 7.0) / 0.35f) | '6' is the amount of vertices per change in z-direction
    indexOffset = ((floorf(playerPos.x() / 0.35f) + 20) * 240) + ((floorf(playerPos.y() / 0.35f) + 20) * 6);

    // Fill up 'collidingQuad[]'
    int j{0};
    for (int i{indexOffset}; i < indexOffset + 6; i++){
        collidingQuad[j] = QVector3D(surfaceRef->mVertices[i].m_xyz[0], surfaceRef->mVertices[i].m_xyz[1], surfaceRef->mVertices[i].m_xyz[2]);
        j += 1;
    }

    // ------------------------------------- BARYCENTRIC COORDINATES FOR TRIANGLE (1/2) -------------------------------------
    a = QVector2D(collidingQuad[0].x(), collidingQuad[0].z());
    b = QVector2D(collidingQuad[1].x(), collidingQuad[1].z());
    c = QVector2D(collidingQuad[2].x(), collidingQuad[2].z());

    QVector2D ab = b - a;
    QVector2D ac = c - a;
    QVector3D n = QVector3D::crossProduct(ab, ac);
    area = n.length();

    QVector2D p = b - playerPos;
    QVector2D q = c - playerPos;
    n = QVector3D::crossProduct(p, q);
    barycCoords.setX(n.z() / area);

    p = c - playerPos;
    q = a - playerPos;
    n = QVector3D::crossProduct(p, q);
    barycCoords.setY(n.z() / area);

    p = a - playerPos;
    q = b - playerPos;
    n = QVector3D::crossProduct(p, q);
    barycCoords.setZ(n.z() / area);
    // ---------------------------------------------------------------------------------------------------------------------

    // If player is within the bounds of triangle (1/2), else the player is within the bounds of triangle (2/2)
    if (barycCoords.x() > 0 && barycCoords.y() > 0 && barycCoords.z() > 0){
        // Calculate player's height at current position
        // Then turn it into an additive value.
        // The movement function adds previous position to new one, but I want the height to stay exact (so I "reverse" it here).
        nextYPos = collidingQuad[2].y() * barycCoords.z() + collidingQuad[1].y() * barycCoords.y() + collidingQuad[0].y() * barycCoords.x();
        nextYPos -= static_cast<Cube*>(mMap["cube"])->mPosition.column(3).y();
    } else {

        // ------------------------------------- BARYCENTRIC COORDINATES FOR TRIANGLE (2/2) -------------------------------------
        a = QVector2D(collidingQuad[3].x(), collidingQuad[3].z());
        b = QVector2D(collidingQuad[4].x(), collidingQuad[4].z());
        c = QVector2D(collidingQuad[5].x(), collidingQuad[5].z());

        QVector2D ab = b - a;
        QVector2D ac = c - a;
        QVector3D n = QVector3D::crossProduct(ab, ac);
        area = n.length();

        QVector2D p = b - playerPos;
        QVector2D q = c - playerPos;
        n = QVector3D::crossProduct(p, q);
        barycCoords.setX(n.z() / area);

        p = c - playerPos;
        q = a - playerPos;
        n = QVector3D::crossProduct(p, q);
        barycCoords.setY(n.z() / area);

        p = a - playerPos;
        q = b - playerPos;
        n = QVector3D::crossProduct(p, q);
        barycCoords.setZ(n.z() / area);
        // ---------------------------------------------------------------------------------------------------------------------

        // Calculate player's height at current position
        // Then turn it into an additive value.
        // The movement function adds previous position to new one, but I want the height to stay exact (so I "reverse" it here).
        nextYPos = collidingQuad[5].y() * barycCoords.z() + collidingQuad[4].y() * barycCoords.y() + collidingQuad[3].y() * barycCoords.x();
        nextYPos -= static_cast<Cube*>(mMap["cube"])->mPosition.column(3).y();
    }

}

void RenderWindow::compileShaders()
{
    mShaderProgram[PLAIN_SHADER] = new Shader("../3D-Programming-OpenGL/OpenGL-Project/plainshader.vert", "../3D-Programming-OpenGL/OpenGL-Project/plainshader.frag");
    qDebug() << "Plain shader program id: " << mShaderProgram[PLAIN_SHADER]->getProgram();
    mShaderProgram[TEXTURE_SHADER] = new Shader("../3D-Programming-OpenGL/OpenGL-Project/texturevertex.vert", "../3D-Programming-OpenGL/OpenGL-Project/texturefragment.frag");
    qDebug() << "Texture shader program id: " << mShaderProgram[TEXTURE_SHADER]->getProgram();
    mShaderProgram[PHONG_SHADER] = new Shader("../3D-Programming-OpenGL/OpenGL-Project/phongvertex.vert", "../3D-Programming-OpenGL/OpenGL-Project/phongfragment.frag");
    qDebug() << "Texture shader program id: " << mShaderProgram[PHONG_SHADER]->getProgram();
    mShaderProgram[BILLBOARD_SHADER] = new Shader("../3D-Programming-OpenGL/OpenGL-Project/billboardshader.vert", "../3D-Programming-OpenGL/OpenGL-Project/billboardshader.frag");
    qDebug() << "Texture shader program id: " << mShaderProgram[BILLBOARD_SHADER]->getProgram();
}

void RenderWindow::setupPlainShader()
{
    mMatrixUniform[PLAIN_SHADER] = glGetUniformLocation( mShaderProgram[PLAIN_SHADER]->getProgram(), "matrix"  );
    vMatrixUniform[PLAIN_SHADER] = glGetUniformLocation( mShaderProgram[PLAIN_SHADER]->getProgram(), "vmatrix" );
    pMatrixUniform[PLAIN_SHADER] = glGetUniformLocation( mShaderProgram[PLAIN_SHADER]->getProgram(), "pmatrix" );
}

void RenderWindow::setupTextureShader()
{
    mMatrixUniform[TEXTURE_SHADER] = glGetUniformLocation( mShaderProgram[TEXTURE_SHADER]->getProgram(), "mMatrix" );
    vMatrixUniform[TEXTURE_SHADER] = glGetUniformLocation( mShaderProgram[TEXTURE_SHADER]->getProgram(), "vMatrix" );
    pMatrixUniform[TEXTURE_SHADER] = glGetUniformLocation( mShaderProgram[TEXTURE_SHADER]->getProgram(), "pMatrix" );
}

void RenderWindow::setupPhongShader()
{
    mMatrixUniform[PHONG_SHADER] = glGetUniformLocation( mShaderProgram[PHONG_SHADER]->getProgram(), "mMatrix" );
    vMatrixUniform[PHONG_SHADER] = glGetUniformLocation( mShaderProgram[PHONG_SHADER]->getProgram(), "vMatrix" );
    pMatrixUniform[PHONG_SHADER] = glGetUniformLocation( mShaderProgram[PHONG_SHADER]->getProgram(), "pMatrix" );
}

void RenderWindow::setupBillboardShader()
{
    mMatrixUniform[BILLBOARD_SHADER] = glGetUniformLocation( mShaderProgram[BILLBOARD_SHADER]->getProgram(), "mMatrix" );
    vMatrixUniform[BILLBOARD_SHADER] = glGetUniformLocation( mShaderProgram[BILLBOARD_SHADER]->getProgram(), "vMatrix" );
    pMatrixUniform[BILLBOARD_SHADER] = glGetUniformLocation( mShaderProgram[BILLBOARD_SHADER]->getProgram(), "pMatrix" );
}

void RenderWindow::transformObjects()
{
    if(trophiesExists)
    {
        mMap["Trophy1"]->move( 0.40f,  0.64f,  4.92f);
        mMap["Trophy2"]->move(-4.81f,  0.69f,  3.06f);
        mMap["Trophy3"]->move( 3.95f,  1.31f, -0.64f);
        mMap["Trophy4"]->move(-5.98f,  1.37f, -5.61f);
        mMap["Trophy5"]->move( 5.80f,  1.44f,  2.00f);
        mMap["Trophy6"]->move( 2.12f, -0.51f, -5.23f);
    }

    if(EXISTS("door"))
    {
        mMap["door"]->move(-0.25f, 0.0f, 1.0f);             //Move door to house's door opening
        mMap["door"]->move(5.85f, 1.38f, 2.00f);            //Move door to mountain
    }

    if(EXISTS("house")){
        mMap["house"]->move(5.85f, 1.38f, 2.00f);               //Move house to mountain
        mMap["house"]->scaleObject(QVector3D(2.0f, 2.0f, 2.0f));
    }

    if (EXISTS("linecurve")){
        mMap["linecurve"]->move(5.1f, 3.0f, -9.0f);
        mMap["linecurve"]->scaleObject(QVector3D(1.8f, 1.8f, 1.8f));
    }

    if(EXISTS("disc")){
        mMap["disc"]->move(-5.5f, 1.5f, -0.4f);
        mMap["disc"]->scaleObject(QVector3D(0.2f, 0.2f, 0.2f));
    }

    if(EXISTS("interpolation")){
        mMap["interpolation"]->move(-5.5f, 1.5f, -0.4f);        //Move interpolation to the disc
        mMap["interpolation"]->scaleObject(QVector3D(0.1f, 0.1f, 0.1f));
    }

    if(EXISTS("leastsquaresmethod")){
        mMap["leastsquaresmethod"]->move(-5.5f, 1.5f, -0.4f);   //Move leastsquaresmethod to disc
        mMap["leastsquaresmethod"]->scaleObject(QVector3D(0.13f, 0.13f, 0.13f));
    }

    if(EXISTS("beziercurve")){
        mMap["beziercurve"]->move(-4.0f, 0.1f, 4.9f);
        mMap["beziercurve"]->scaleObject(QVector3D(0.35f, 0.35f, 0.35f));
    }

    if(EXISTS("cube")){
        mMap["cube"]->VisualObject::move(-0.24f, 0.39f, 6.20f); //Player's spawn position
        mMap["cube"]->scaleObject(QVector3D(0.2f, 0.2f, 0.2f));
    }

    if(EXISTS("octahedronball1") && EXISTS("octahedronball2") && EXISTS("octahedronball3")){
        mMap["octahedronball1"]->move( 2.0f, 3.8f, -1.0f);
        mMap["octahedronball2"]->move(-0.4f, 2.9f,  0.8f);
        mMap["octahedronball3"]->move(-1.3f, 5.0f, -1.3f);
        mMap["octahedronball1"]->scaleObject(QVector3D(0.8f, 0.8f, 0.8f));
        mMap["octahedronball2"]->scaleObject(QVector3D(0.6f, 0.6f, 0.6f));
        mMap["octahedronball3"]->scaleObject(QVector3D(0.3f, 0.3f, 0.3f));
    }

    if(EXISTS("light")){
        mMap["light"]->move(-2.2f, 4.0f, 0.8f);                 // Difference from "octahedronball2" is (-1.8, 1.0, 0.0)
    }

    if(EXISTS("suzanne")){
        mMap["suzanne"]->move(-8.5f, 3.5f, -9.0f);
        mMap["suzanne"]->rotateObject(42.0f, QVector3D(0.0f, 1.0f, 0.0f));
        mMap["suzanne"]->scaleObject(QVector3D(2.0f, 2.0f, 2.0f));
    }

    if(EXISTS("cactus1") && EXISTS("cactus2") && EXISTS("cactus3") && EXISTS("cactus4")){
        mMap["cactus1"]->move( 6.18f, -0.50f, -6.01f);
        mMap["cactus2"]->move( 4.59f,  1.00f,  5.58f);
        mMap["cactus3"]->move(-2.71f, -0.70f,  1.87f);
        mMap["cactus4"]->move(-2.19f, -0.70f,  1.57f);
        mMap["cactus1"]->scaleObject(QVector3D(0.23f, 0.23f, 0.23f));
        mMap["cactus2"]->scaleObject(QVector3D(0.10f, 0.10f, 0.10f));
        mMap["cactus3"]->scaleObject(QVector3D(0.16f, 0.16f, 0.16f));
        mMap["cactus4"]->scaleObject(QVector3D(0.10f, 0.10f, 0.10f));
    }

    if(EXISTS("skybox")){
        mMap["skybox"]->rotateObject(90.01f, QVector3D(0.0f, 1.0f, 0.0f));
        mMap["skybox"]->scaleObject(QVector3D(60.0f, 60.0f, 60.0f));
    }

    if(EXISTS("winner")){
        mMap["winner"]->move(0.0f, 6.0f, -20.0f);
        mMap["winner"]->scaleObject(QVector3D(2.5f, 2.5f, 2.5f));
    }

    if(EXISTS("camera")){
        mMap["camera"]->rotateObject(-25.0f, QVector3D(1.0f, 0.0f, 0.0f));
        mMap["camera"]->rotateObject( 90.0f, QVector3D(0.0f, 1.0f, 0.0f));
        mMap["camera"]->scaleObject(QVector3D(0.15f, 0.20f, 0.20f));
    }

    if(EXISTS("pyramid")){
        mMap["pyramid"]->move(-3.05f, -0.03f, -1.57f);
    }

    if(EXISTS("xyz"))
    mMap["xyz"]->scaleObject(QVector3D(15.0f, 15.0f, 15.0f));

    if (trophiesExists){
        for(int i{1}; i <= amountOfTrophies; i++){
            mMap["Trophy" + std::to_string(i)]->scaleObject(QVector3D(0.15f,0.15f,0.15f));
        }
    }
}

void RenderWindow::setIsInHouse(bool isInHouse)
{
    if(isInHouse){
        mIsInHouse = isInHouse;
    }
}

//This function is called from Qt when window is exposed (shown)
// and when it is resized
//exposeEvent is a overridden function from QWindow that we inherit from
void RenderWindow::exposeEvent(QExposeEvent *)
{
    //if not already initialized - run init() function - happens on program start up
    if (!mInitialized)
        init();

    //This is just to support modern screens with "double" pixels (Macs and some 4k Windows laptops)
    const qreal retinaScale = devicePixelRatio();

    //Set viewport width and height to the size of the QWindow we have set up for OpenGL
    glViewport(0, 0, static_cast<GLint>(width() * retinaScale), static_cast<GLint>(height() * retinaScale));

    //If the window actually is exposed to the screen we start the main loop
    //isExposed() is a function in QWindow
    if (isExposed())
    {
        //This timer runs the actual MainLoop
        //16 means 16ms = 60 Frames pr second (should be 16.6666666 to be exact...)
        mRenderTimer->start(16);
        mTimeStart.start();
    }
}

//The way this function is set up is that we start the clock before doing the draw call,
// and check the time right after it is finished (done in the render function)
//This will approximate what framerate we COULD have.
//The actual frame rate on your monitor is limited by the vsync and is probably 60Hz
void RenderWindow::calculateFramerate()
{
    long nsecElapsed = mTimeStart.nsecsElapsed();
    timeElapsed += nsecElapsed/33000;
    static int frameCount{0};                       //counting actual frames for a quick "timer" for the statusbar

    if (mMainWindow)            //if no mainWindow, something is really wrong...
    {
        ++frameCount;
        if (frameCount > 30)    //once pr 30 frames = update the message == twice pr second (on a 60Hz monitor)
        {
            //showing some statistics in status bar
            mMainWindow->statusBar()->showMessage(" Time pr FrameDraw: " +
                                                  QString::number(nsecElapsed/1000000.f, 'g', 4) + " ms  |  " +
                                                  "FPS (approximated): " + QString::number(1E9 / nsecElapsed, 'g', 7));
            frameCount = 0;     //reset to show a new message in 30 frames
        }
    }
}

//Uses QOpenGLDebugLogger if this is present
//Reverts to glGetError() if not
void RenderWindow::checkForGLerrors()
{
    if(mOpenGLDebugLogger)  //if our machine got this class to work
    {
        const QList<QOpenGLDebugMessage> messages = mOpenGLDebugLogger->loggedMessages();
        for (const QOpenGLDebugMessage &message : messages)
            qDebug() << message;
    }
    else
    {
        GLenum err = GL_NO_ERROR;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            qDebug() << "glGetError returns " << err;
            switch (err) {
            case 1280:
                qDebug() << "GL_INVALID_ENUM - Given when an enumeration parameter is not a "
                                "legal enumeration for that function.";
                break;
            case 1281:
                qDebug() << "GL_INVALID_VALUE - Given when a value parameter is not a legal "
                                "value for that function.";
                break;
            case 1282:
                qDebug() << "GL_INVALID_OPERATION - Given when the set of state for a command "
                                "is not legal for the parameters given to that command. "
                                "It is also given for commands where combinations of parameters "
                                "define what the legal parameters are.";
                break;
            }
        }
    }
}

//Tries to start the extended OpenGL debugger that comes with Qt
//Usually works on Windows machines, but not on Mac...
void RenderWindow::startOpenGLDebugger()
{
    QOpenGLContext * temp = this->context();
    if (temp)
    {
        QSurfaceFormat format = temp->format();
        if (! format.testOption(QSurfaceFormat::DebugContext))
            qDebug() << "This system can not use QOpenGLDebugLogger, so we revert to glGetError()";

        if(temp->hasExtension(QByteArrayLiteral("GL_KHR_debug")))
        {
            qDebug() << "System can log OpenGL errors!";
            mOpenGLDebugLogger = new QOpenGLDebugLogger(this);
            if (mOpenGLDebugLogger->initialize()) // initializes in the current context
                qDebug() << "Started OpenGL debug logger!";
        }
    }
}

void RenderWindow::uncollideTrophies()
{
    if (trophiesExists){
        for(int i{1}; i <= amountOfTrophies; i++){
            static_cast<Tetrahedron*>(mMap["Trophy" + std::to_string(i)])->colliding = false;
        }
    }
}

void RenderWindow::playerMovement()
{
    if(EXISTS("cube"))
    {
        if (goingLeft || goingDown || goingUp || goingRight)
        {
            // Reset these values each frame to avoid an "additive behaviour"
            mXMovement = 0.0f;
            mZMovement = 0.0f;

            // Simple movement conditions
            if (goingRight)
                mXMovement += mMovementSpeed;
            if (goingLeft)
                mXMovement -= mMovementSpeed;
            if (goingUp)
                mZMovement -= mMovementSpeed;
            if (goingDown)
                mZMovement += mMovementSpeed;

            // Diagonal movement
            if (abs(mZMovement) > 0.0f && abs(mXMovement) > 0.0f){
                mZMovement /= sqrt(2);
                mXMovement /= sqrt(2);
            }

            // Different movement behaviours for inside/outside the house
            if (!mIsInHouse){
                uncollideTrophies();
                barycentricCoordinates();
                static_cast<Cube*>(mMap["cube"])->move(mXMovement, nextYPos, mZMovement);

                // Checks if the player is colliding with any objects
                for (auto it = mMap.begin(); it != mMap.end(); it++)
                {
                    // "If it's not the cube" (makes sure that the cube does not collide with itself)
                    if (it->first != "cube"){
                        mIsColliding = (*it).second->isColliding(mMap["cube"]->getWorldCollisionBox());

                        // If there is a collision
                        if (mIsColliding){
                            bool collidingWithTrophy{false};

                            // Check if the player collided with a trophy
                            if (trophiesExists){
                                for(int i{1}; i <= amountOfTrophies; i++){
                                    if (it->first == "Trophy" + std::to_string(i)){
                                        collidingWithTrophy = true;
                                        static_cast<Tetrahedron*>(mMap["Trophy" + std::to_string(i)])->colliding = true;
                                        break;
                                    }
                                }
                            }

                            // If object is colliding and is not a trophy, revert the movement
                            if (!collidingWithTrophy)
                                static_cast<Cube*>(mMap["cube"])->move(-mXMovement, -0.08f, -mZMovement);

                            break;
                        }
                    }
                }
            } else if (mIsInHouse){
                static_cast<Cube*>(mMap["cube"])->moveInHouse(mXMovement, mZMovement);
                static_cast<Tetrahedron*>(mMap["Trophy5"])->colliding = false;

                // Check if player is colliding with the trophy inside the house
                if (mMap["Trophy5"]->isColliding(mMap["cube"]->getWorldCollisionBox())){
                    static_cast<Tetrahedron*>(mMap["Trophy5"])->colliding = true;
                }

                // If player is colliding with any of the walls, revert the movement
                CollisionBox playerBox = mMap["cube"]->getWorldCollisionBox();
                if (playerBox.p1.x() <= 4.85f || playerBox.p2.x() >= 6.85f || playerBox.p2.y() <= 1.00f ||
                   (playerBox.p1.x() <= 5.60f && playerBox.p1.y() >= 3.00f)||
                   (playerBox.p2.x() >= 6.10f && playerBox.p1.y() >= 3.00f)){
                    static_cast<Cube*>(mMap["cube"])->moveInHouse(-mXMovement, -mZMovement);
                }
            }


            // Move 'skybox' to player's position each frame to avoid "depth-perception" of the sky.
            if (!mIsInHouse){
                QVector4D playerNewPos = QVector4D(static_cast<Cube*>(mMap["cube"])->getPos(), 1.0f);
                static_cast<Skybox*>(mMap["skybox"])->mMatrix.setColumn(3, playerNewPos);
            }

            // Move the gizmo camera to 'PLAY_MODE' camera position
            if (EXISTS("camera")){
                if (!mIsInHouse){
                    QVector4D cameraPos = QVector4D(mPlayCamera->getEyePos(), 1.0f);
                    static_cast<ObjMesh*>(mMap["camera"])->mMatrix.setColumn(3, cameraPos);
                } else {
                    QVector4D cameraPos = QVector4D(mPlayCamera->getEyePos(), 1.0f);
                    cameraPos.setY(cameraPos.y() + 0.7f);
                    static_cast<ObjMesh*>(mMap["camera"])->mMatrix.setColumn(3, cameraPos);
                }
            }

            // If player moves outside of the house while inside the house, set player to be outside of the house
            if (mIsInHouse && static_cast<Cube*>(mMap["cube"])->getPos().z() >= 3.25f){
                static_cast<Door*>(mMap["door"])->openingDoor = false;
                static_cast<Door*>(mMap["door"])->closingDoor = true;
                mIsInHouse = false;
            }

            // Player will loose if he/she walks outside of the map's boundaries
            checkLooseCondition();

            // Not necessary
            if (!activateMovement){
                activateMovement = true;
                setGoingUp(false);
            }
        }
    }
}

void RenderWindow::cameraMovement()
{
    if (flyLeft || flyDown || flyUp || flyRight)
    {
        // Simple movement conditions
        if (flyRight)
            mActiveCamera->moveRight(mFlyingSpeed);
        if (flyLeft)
            mActiveCamera->moveRight(-mFlyingSpeed);
        if (flyUp)
            mActiveCamera->setSpeed(-mFlyingSpeed);
        if (flyDown)
            mActiveCamera->setSpeed(mFlyingSpeed);
    }
}

void RenderWindow::checkLooseCondition()
{
    // Gives the player a little "warning" by reducing the movement speed
    if (static_cast<Cube*>(mMap["cube"])->getPos().z() >=  6.8f ||
        static_cast<Cube*>(mMap["cube"])->getPos().z() <= -6.8f ||
        static_cast<Cube*>(mMap["cube"])->getPos().x() >=  6.8f ||
        static_cast<Cube*>(mMap["cube"])->getPos().x() <= -6.8f){
        mMovementSpeed = 0.0045f;
    } else{
        mMovementSpeed = 0.035f;
    }

    // Actual loose condition
    if (static_cast<Cube*>(mMap["cube"])->getPos().z() >=  7.0f ||
        static_cast<Cube*>(mMap["cube"])->getPos().z() <= -7.0f ||
        static_cast<Cube*>(mMap["cube"])->getPos().x() >=  7.0f ||
        static_cast<Cube*>(mMap["cube"])->getPos().x() <= -7.0f){
        reset();
    }
}

//Event sent from Qt when program receives a keyPress
void RenderWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (mActiveGameMode == PLAY_MODE && EXISTS("cube")){
        if(event->key() == Qt::Key_W)
            setGoingUp(false);

        if(event->key() == Qt::Key_A)
            setGoingLeft(false);

        if(event->key() == Qt::Key_S)
            setGoingDown(false);

        if(event->key() == Qt::Key_D)
            setGoingRight(false);
    }

    if (mActiveGameMode == EDIT_MODE){
        if(event->key() == Qt::Key_W)
            setFlyUp(false);

        if(event->key() == Qt::Key_A)
            setFlyLeft(false);

        if(event->key() == Qt::Key_S)
            setFlyDown(false);

        if(event->key() == Qt::Key_D)
            setFlyRight(false);
    }
}

void RenderWindow::keyPressEvent(QKeyEvent *event)
{    
    if (event->key() == Qt::Key_R)
        reset();

    if (event->key() == Qt::Key_Q){
        if (mActiveGameMode == PLAY_MODE){
            mActiveGameMode = EDIT_MODE;
            mActiveCamera = mEditCamera;
            mEditCamera->lookAt(mEditCamera->getEyePos(), QVector3D{0.0f, 0.0f ,0.0f}, QVector3D{0.0f, 1.0f, 0.0f});
            resetMovements();
            mToggleGizmos = true;
        } else {
            mActiveGameMode = PLAY_MODE;
            mActiveCamera = mPlayCamera;
            resetMovements();
            mToggleGizmos = false;
            mToggleWireframe = false;
        }
    }

    if (event->key() == Qt::Key_Escape)
        mMainWindow->close();

    // Player movement
    if (mActiveGameMode == PLAY_MODE && EXISTS("cube"))
    {
        if(event->key() == Qt::Key_W)
            setGoingUp(true);

        if(event->key() == Qt::Key_A)
            setGoingLeft(true);

        if(event->key() == Qt::Key_S)
            setGoingDown(true);

        if(event->key() == Qt::Key_D)
            setGoingRight(true);
    }

    // 'EDIT_MODE' camera movement
    if (mActiveGameMode == EDIT_MODE)
    {
        if(event->key() == Qt::Key_W)
            setFlyUp(true);

        if(event->key() == Qt::Key_A)
            setFlyLeft(true);

        if(event->key() == Qt::Key_S)
            setFlyDown(true);

        if(event->key() == Qt::Key_D)
            setFlyRight(true);
    }

    // Switch NPC path
    if (EXISTS("disc")){
        if (event->key() == Qt::Key_F){
            activeNpcPath = (activeNpcPath == 2) ? 1 : 2;
        }
    }

    // Pick up
    if(EXISTS("cube"))
    {
        if(event->key() == Qt::Key_E)
        {
            const QVector2D pos{ QVector2D( static_cast<Cube*>(mMap["cube"])->getPos().x(),  static_cast<Cube*>(mMap["cube"])->getPos().z()) };

            if ((pos.x() >= 5.70f && pos.x() <= 5.95f) &&
                (pos.y() >= 3.10f && pos.y() <= 3.20f) &&
                (!mIsInHouse))
            {
                static_cast<Door*>(mMap["door"])->closingDoor = false;
                static_cast<Door*>(mMap["door"])->openingDoor = true;
                mIsInHouse = true;
            }

            // Pick up a trophy if it's colliding
            if (trophiesExists){
                for(int i{1}; i <= amountOfTrophies; i++){
                    Tetrahedron* trophyRef{ static_cast<Tetrahedron*>(mMap["Trophy" + std::to_string(i)]) };

                    // If the trophy is colliding and is not already picked up
                    if (trophyRef->colliding == true && trophyRef->getPickedUp() == false){
                        trophyRef->Overlap();
                        trophiesPickedUp++;

                        // Checck for win condition
                        if (trophiesPickedUp >= amountOfTrophies)
                        {
                            if (EXISTS("winner"))
                            mMap["winner"]->setRenderObject(true);
                        }
                    }
                }
            }
        }
    }
}

void RenderWindow::resetMovements()
{
    setGoingLeft(false);
    setGoingDown(false);
    setGoingRight(false);
    setGoingUp(false);
    setFlyLeft(false);
    setFlyDown(false);
    setFlyRight(false);
    setFlyUp(false);
}

void RenderWindow::reset()
{
    // Should always start in 'PLAY_MODE'
    mActiveGameMode = PLAY_MODE;
    mActiveCamera = mPlayCamera;
    mEditCamera->setEyePos(3.0f, 3.0f, 3.0f);

    // Hide the "YOU WIN!" display
    if (EXISTS("winner"))
    mMap["winner"]->setRenderObject(false);

    // Hide gizmos and disable wireframes
    mToggleGizmos = false;
    mToggleWireframe = false;

    // Set player to be outside of the house
    if (mIsInHouse){
        static_cast<Door*>(mMap["door"])->openingDoor = false;
        static_cast<Door*>(mMap["door"])->closingDoor = true;
        mIsInHouse = false;
    }

    // Reset player's and skybox's position to inital spawn location
    if(EXISTS("cube") && EXISTS("skybox")){
        Cube* cubeRef{static_cast<Cube*>(mMap["cube"])};
        cubeRef->move(-cubeRef->mMatrix.column(3).x(), -cubeRef->mMatrix.column(3).y(), -cubeRef->mMatrix.column(3).z());
        mMap["cube"]->move(-0.24f, 0.39f, 6.20f);
        QVector4D playerNewPos = QVector4D(static_cast<Cube*>(mMap["cube"])->getPos(), 1.0f);
        static_cast<Skybox*>(mMap["skybox"])->mMatrix.setColumn(3, playerNewPos);
        mMovementSpeed = 0.035f;
    }

    // "Respawn" picked-up trophies
    trophiesPickedUp = 0;
    if (trophiesExists){
        for(int i = 1; i <= amountOfTrophies; i++)
        {
            static_cast<Tetrahedron*>(mMap["Trophy" + std::to_string(i)])->undoOverlap();
        }
    }

    // Restart animations
    if(EXISTS("light")){
        Light* lightRef{static_cast<Light*>(mMap["light"])};
        lightRef->move(-lightRef->mMatrix.column(3).x(), -lightRef->mMatrix.column(3).y(), -lightRef->mMatrix.column(3).z());
        mMap["light"]->move(-2.2f, 4.0f, 0.8f);
        lightRef->resetAnimProgress();
    }
    if (EXISTS("disc")){
        Disc* discRef{static_cast<Disc*>(mMap["disc"])};
        discRef->restartAnimation();
        activeNpcPath = 1;
    }

    // Reset position of gizmo camera
    if (EXISTS("camera")){
        QVector4D cameraPos = QVector4D(static_cast<Cube*>(mMap["cube"])->getPos(), 1.0f);
        cameraPos.setY(cameraPos.y() + 0.7f);
        cameraPos.setZ(cameraPos.z() + 0.7f);
        static_cast<ObjMesh*>(mMap["camera"])->mMatrix.setColumn(3, cameraPos);
    }
}
