// Copyright 2015, Christopher J. Foster and the other displaz contributors.
// Use of this code is governed by the BSD-style license found in LICENSE.txt

#include "NGShaderProgram.h"

#include <memory>
#include <iostream>

#include <QAction>
#include <QMenu>

using namespace nanogui;

NGShaderProgram::NGShaderProgram()
{
}

NGShaderProgram::~NGShaderProgram()
{
    mShader.free();
}

void NGShaderProgram::init()
{
    mShader.init(
        /* An identifying name */
        "a_simple_shader",

        /* Vertex shader */
        "#version 330\n"
        "uniform mat4 modelViewProj;\n"
        "in vec3 position;\n"
        "void main() {\n"
        "    gl_Position = modelViewProj * vec4(position, 1.0);\n"
        "}",

        /* Fragment shader */
        "#version 330\n"
        "out vec4 color;\n"
        "uniform float intensity;\n"
        "void main() {\n"
        "    color = vec4(vec3(intensity), 1.0);\n"
        "}"
    );
}

void NGShaderProgram::bind()
{
    mShader.bind();
}

void NGShaderProgram::setup()
{
    MatrixXu indices(3, 2); /* Draw 2 triangles */
    indices.col(0) << 0, 1, 2;
    indices.col(1) << 2, 3, 0;

    MatrixXf positions(3, 4);
    positions.col(0) << -1, -1, 0;
    positions.col(1) <<  1, -1, 0;
    positions.col(2) <<  1,  1, 0;
    positions.col(3) << -1,  1, 0;

    mShader.uploadIndices(indices);
    mShader.uploadAttrib("position", positions);
    mShader.setUniform("intensity", 0.5f);
}

void NGShaderProgram::draw(int size_x, int size_y)
{
    Matrix4f mvp;
    mvp.setIdentity();
    mvp.topLeftCorner<3,3>() = Matrix3f(Eigen::AngleAxisf((float) glfwGetTime(),  Vector3f::UnitZ())) * 0.25f;

    mvp.row(0) *= (float) size_y / (float) size_x;

    mShader.setUniform("modelViewProj", mvp);

    /* Draw 2 triangles starting at index 0 */
    mShader.drawIndexed(GL_TRIANGLES, 0, 2);
}
