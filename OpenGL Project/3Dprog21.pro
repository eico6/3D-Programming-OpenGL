QT          += core gui widgets opengl

TEMPLATE    = app
CONFIG      += c++17

TARGET      = 3D-programmering

SOURCES += main.cpp \
    barycentrictriangle.cpp \
    billboard.cpp \
    camera.cpp \
    collisionbox.cpp \
    cube.cpp \
    disc.cpp \
    door.cpp \
    grid.cpp \
    heightmap.cpp \
    house.cpp \
    interactiveobject.cpp \
    light.cpp \
    linecurve.cpp \
    material.cpp \
    matrix4x4.cpp \
    objmesh.cpp \
    octahedronball.cpp \
    quadtree.cpp \
    renderwindow.cpp \
    shader.cpp \
    mainwindow.cpp \
    skybox.cpp \
    tetrahedron.cpp \
    texture.cpp \
    trianglesurface.cpp \
    vertex.cpp \
    visualobject.cpp \
    xyz.cpp

HEADERS += \
    barycentrictriangle.h \
    billboard.h \
    camera.h \
    collisionbox.h \
    cube.h \
    disc.h \
    door.h \
    grid.h \
    heightmap.h \
    house.h \
    interactiveobject.h \
    light.h \
    linecurve.h \
    material.h \
    matrix4x4.h \
    objmesh.h \
    octahedronball.h \
    quadtree.h \
    renderwindow.h \
    shader.h \
    mainwindow.h \
    skybox.h \
    tetrahedron.h \
    texture.h \
    trianglesurface.h \
    vertex.h \
    visualobject.h \
    xyz.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    billboardshader.frag \
    billboardshader.vert \
    phongfragment.frag \
    phongvertex.vert \
    plainshader.frag \
    plainshader.vert \
    texturefragment.frag \
    texturevertex.vert
