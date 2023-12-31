#include "object2D_t1.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float lengthX,
    float lengthY,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(lengthX, 0, 0), color),
        VertexFormat(corner + glm::vec3(lengthX, lengthY, 0), color),
        VertexFormat(corner + glm::vec3(0, lengthY, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateCircle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float angle,
    glm::vec3 color,
    int fragments,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color)
    };
    for (int i = 1; i < fragments + 2; i++) {
        vertices.push_back(VertexFormat(glm::vec3(corner.x + (angle * cos(i * 2.0f * M_PI / fragments)), corner.y + (angle * sin(i * 2.0f * M_PI / fragments)), 0), color));
    }



    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0 };
    for (int i = 1; i < fragments + 2; i++) {
        indices.push_back(i);
    }

    square->SetDrawMode(GL_TRIANGLE_FAN);

    square->InitFromData(vertices, indices);
    return square;
}