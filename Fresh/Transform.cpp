#include "Transform.h"

glm::vec2 Transform::RotatedP(const glm::vec2& P, const glm::vec2& pivot, float degrees)
{
    float radians = glm::radians(degrees);
    glm::mat2 rotationMatrix = glm::mat2(
        glm::cos(radians), -glm::sin(radians),
        glm::sin(radians), glm::cos(radians)
    );

    glm::vec2 translated = P - pivot;

    glm::vec2 rotated = rotationMatrix * translated;
    rotated += pivot;

    if (glm::abs(rotated.x) < 1e-6) rotated.x = 0.0f;
    if (glm::abs(rotated.y) < 1e-6) rotated.y = 0.0f;

    return rotated;
}
glm::vec2 Transform::RotatedP(float x, float y, const glm::vec2& pivot, float degrees)
{
    float radians = glm::radians(degrees);
    glm::mat2 rotationMatrix = glm::mat2(
        glm::cos(radians), -glm::sin(radians),
        glm::sin(radians), glm::cos(radians)
    );

    glm::vec2 translated(x - pivot.x, y - pivot.y);

    glm::vec2 rotated = rotationMatrix * translated;
    rotated += pivot;

    if (glm::abs(rotated.x) < 1e-6) rotated.x = 0.0f;
    if (glm::abs(rotated.y) < 1e-6) rotated.y = 0.0f;

    return rotated;
}
glm::vec2 Transform::RotatedP(const glm::vec2& p, float pivotX, float pivotY, float degrees)
{
    float radians = glm::radians(degrees);
    glm::mat2 rotationMatrix = glm::mat2(
        glm::cos(radians), -glm::sin(radians),
        glm::sin(radians), glm::cos(radians)
    );

    glm::vec2 translated(p.x - pivotX, p.y - pivotY);

    glm::vec2 rotated = rotationMatrix * translated;
    rotated.x += pivotX;
    rotated.y += pivotY;

    if (glm::abs(rotated.x) < 1e-6) rotated.x = 0.0f;
    if (glm::abs(rotated.y) < 1e-6) rotated.y = 0.0f;

    return rotated;
}
glm::vec2 Transform::RotatedP(float x, float y, float pivotX, float pivotY, float degrees)
{
    float radians = glm::radians(degrees);
    glm::mat2 rotationMatrix = glm::mat2(
        glm::cos(radians), -glm::sin(radians),
        glm::sin(radians), glm::cos(radians)
    );

    glm::vec2 translated(x - pivotX, y - pivotY);

    glm::vec2 rotated = rotationMatrix * translated;
    rotated.x += pivotX;
    rotated.y += pivotY;

    if (glm::abs(rotated.x) < 1e-6) rotated.x = 0.0f;
    if (glm::abs(rotated.y) < 1e-6) rotated.y = 0.0f;

    return rotated;
}

glm::vec2 Transform::ScaledP(const glm::vec2& p, const glm::vec2& pivot, const glm::vec2& scaler)
{
    glm::vec2 translated = p - pivot;

    glm::vec2 scaled = translated * scaler;

    return scaled + pivot;
}
glm::vec2 Transform::ScaledP(float x, float y, const glm::vec2& pivot, const glm::vec2& scaler)
{
    glm::vec2 translated(x - pivot.x, y - pivot.y);

    glm::vec2 scaled = translated * scaler;

    return scaled + pivot;
}
glm::vec2 Transform::ScaledP(const glm::vec2& p, const glm::vec2& pivot, float scaleX, float scaleY)
{
    glm::vec2 translated = p - pivot;

    glm::vec2 scaled = translated * glm::vec2(scaleX, scaleY);

    return scaled + pivot;
}
glm::vec2 Transform::ScaledP(float x, float y, const glm::vec2& pivot, float scaleX, float scaleY)
{
    glm::vec2 translated(x - pivot.x, y - pivot.y);

    glm::vec2 scaled = translated * glm::vec2(scaleX, scaleY);

    return scaled + pivot;
}
glm::vec2 Transform::ScaledP(float x, float y, float pivotX, float pivotY, float scaleX, float scaleY)
{
    glm::vec2 translated(x - pivotX, y - pivotY);

    glm::vec2 scaled = translated * glm::vec2(scaleX, scaleY);

    return glm::vec2(scaled.x + pivotX, scaled.y + pivotY);
}
glm::vec2 Transform::ScaledP(const glm::vec2& p, float pivotX, float pivotY, float scaleX, float scaleY)
{
    glm::vec2 translated(p.x - pivotX, p.y - pivotY);

    glm::vec2 scaled = translated * glm::vec2(scaleX, scaleY);

    return glm::vec2(scaled.x + pivotX, scaled.y + pivotY);
}
glm::vec2 Transform::ScaledP(const glm::vec2& p, float pivotX, float pivotY, const glm::vec2& scale)
{
    glm::vec2 translated(p.x - pivotX, p.y - pivotY);

    glm::vec2 scaled = translated * scale;

    return glm::vec2(scaled.x + pivotX, scaled.y + pivotY);
}

Transform::Transform()
    : pos(0.0f, 0.0f), rotation(0.0f), scale(1.0f, 1.0f) {
}
Transform::Transform(const glm::vec2& pos, float rotation, const glm::vec2& scale)
    : pos(pos), rotation(rotation), scale(scale) {
}
Transform::Transform(float posX, float posY, float rotation, float scaleX, float scaleY)
    : pos(posX, posY), rotation(rotation), scale(scaleX, scaleY) {
}
Transform::Transform(const glm::vec2& pos, float rotation, float scaleX, float scaleY)
    : pos(pos), rotation(rotation), scale(scaleX, scaleY) {
}
Transform::Transform(float posX, float posY, float rotation, const glm::vec2& scale)
    : pos(posX, posY), rotation(rotation), scale(scale) {
}

void Transform::Move(const glm::vec2& v) {
    pos += v;
}
void Transform::Move(float x, float y) {
    pos += glm::vec2(x, y);
}

void Transform::Scale(const glm::vec2& scaler) {
    scale *= scaler;
}
void Transform::Scale(float scalerX, float scalerY) {
    scale *= glm::vec2(scalerX, scalerY);
}
void Transform::SetScale(const glm::vec2& scaler) {
    scale = scaler;
}
void Transform::SetScale(float scalerX, float scalerY) {
    scale = glm::vec2(scalerX, scalerY);
}

std::array<float, 4> Transform::VerticesFor(const Shape::Line& line) 
{
    return std::array<float, 4> {
        line.points[0].x, line.points[0].y,
        line.points[1].x, line.points[1].y
    };
}
std::array<float, 6> Transform::VerticesFor(const Shape::Triangle& triangle) 
{
    return std::array<float, 6> {
        triangle.points[0].x, triangle.points[0].y,
        triangle.points[1].x, triangle.points[1].y,
        triangle.points[2].x, triangle.points[2].y
    };
}
std::array<float, 8> Transform::VerticesFor(const Shape::Box& box) 
{
    return std::array<float, 8> {
        box.points[0].x, box.points[0].y,
        box.points[1].x, box.points[1].y,
        box.points[2].x, box.points[2].y,
        box.points[3].x, box.points[3].y
    };
}
std::array<float, 8> Transform::VerticesFor(const Shape::AABB& aabb) 
{
    return std::array<float, 8> {
        aabb.points[0].x, aabb.points[0].y,
        aabb.points[0].x, aabb.points[1].y,
        aabb.points[1].x, aabb.points[1].y,
        aabb.points[1].x, aabb.points[0].y,
    };
}
std::array<float, 10> Transform::VerticesFor(const Shape::Pentagon& pentagon) 
{
    return std::array<float, 10> {
        pentagon.points[0].x, pentagon.points[0].y,
        pentagon.points[1].x, pentagon.points[1].y,
        pentagon.points[2].x, pentagon.points[2].y,
        pentagon.points[3].x, pentagon.points[3].y,
        pentagon.points[4].x, pentagon.points[4].y
    };
}
std::array<float, 12> Transform::VerticesFor(const Shape::Hexagon& hexagon) 
{
    return std::array<float, 12> {
        hexagon.points[0].x, hexagon.points[0].y,
        hexagon.points[1].x, hexagon.points[1].y,
        hexagon.points[2].x, hexagon.points[2].y,
        hexagon.points[3].x, hexagon.points[3].y,
        hexagon.points[4].x, hexagon.points[4].y,
        hexagon.points[5].x, hexagon.points[5].y
    };
}
std::vector<float> Transform::VerticesFor(const Shape::Polygon& poly)
{
    std::vector<float> res = {};
    res.reserve(poly.pointsSize() * 2);

    for (int i = 0; i < poly.pointsSize(); i++)
    {
        res.emplace_back(poly.points[i].x);
        res.emplace_back(poly.points[i].y);
    }

    return res;
}
std::array<float, 8> Transform::VerticesFor(const Shape::Circle& cir)
{
    return std::array<float, 8> {
       0, 0,
       0, WINDOW_HEIGHT,
       WINDOW_WIDTH, WINDOW_HEIGHT,
       WINDOW_WIDTH, 0
    };
}

std::array<float, 12> VerticesFor(const Shape::Triangle& triangle, bool rot90)
{
    if (!rot90) return std::array<float, 12> {
            triangle.points[0].x, triangle.points[0].y, 0.0f, 0.0f,
            triangle.points[1].x, triangle.points[1].y, 1.0f, 0.0f,
            triangle.points[2].x, triangle.points[2].y, 0.5f, 1.0f
        };
    else return std::array<float, 12> {
            triangle.points[0].x, triangle.points[0].y, 0.0f, 0.0f,
            triangle.points[1].x, triangle.points[1].y, 1.0f, 0.0f,
            triangle.points[2].x, triangle.points[2].y, 0.5f, 1.0f
        };

}
std::array<float, 16> VerticesFor(const Shape::Box& box, bool rot90) 
{
    if (!rot90) return std::array<float, 16> {
            box.points[0].x, box.points[0].y, POSITIONS_1
            box.points[1].x, box.points[1].y, POSITIONS_2
            box.points[2].x, box.points[2].y, POSITIONS_3
            box.points[3].x, box.points[3].y, POSITIONS_5
        };
    else return std::array<float, 16> {
            box.points[0].x, box.points[0].y, POSITIONS_1
            box.points[1].x, box.points[1].y, POSITIONS_2_90
            box.points[2].x, box.points[2].y, POSITIONS_3
            box.points[3].x, box.points[3].y, POSITIONS_5_90
        };
}
std::array<float, 16> VerticesFor(const Shape::AABB& aabb, bool rot90) 
{
    if (!rot90) return std::array<float, 16> {
            aabb.points[0].x, aabb.points[0].y, POSITIONS_1
            aabb.points[0].x, aabb.points[1].y, POSITIONS_2
            aabb.points[1].x, aabb.points[1].y, POSITIONS_3
            aabb.points[1].x, aabb.points[0].y, POSITIONS_5
        };
    else return std::array<float, 16> {
            aabb.points[0].x, aabb.points[0].y, POSITIONS_1
            aabb.points[0].x, aabb.points[1].y, POSITIONS_2_90
            aabb.points[1].x, aabb.points[1].y, POSITIONS_3
            aabb.points[1].x, aabb.points[0].y, POSITIONS_5_90
        };
}

std::array<unsigned int, 6> Transform::IndicesFor(const Shape::Box& box)
{
    return std::array<unsigned int, 6> {
        0, 1, 2, 2, 3, 0
    };
}
std::array<unsigned int, 6> Transform::IndicesFor(const Shape::AABB& aabb)
{
    return std::array<unsigned int, 6> {
        0, 1, 2, 2, 3, 0
    };
}
std::array<unsigned int, 9> Transform::IndicesFor(const Shape::Pentagon& pentagon)
{
    return std::array<unsigned int, 9> {
        0, 1, 2, 3, 4, 0, 0, 2, 3
    };
}
std::array<unsigned int, 12> Transform::IndicesFor(const Shape::Hexagon& hexagon)
{
    return std::array<unsigned int, 12> {
        0, 1, 2, 2, 3, 4, 2, 0, 5, 2, 4, 5
    };
}
std::array<unsigned int, 6> Transform::IndicesFor(const Shape::Circle& cir)
{
    return std::array<unsigned int, 6> {
        0, 1, 2, 2, 3, 0
    };
}

void Transform::SetMat(glm::mat4& mat)
{
    mat = glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f);
    mat = glm::translate(mat, glm::vec3(pos.x, pos.y, 0.0f));
    mat = glm::rotate(mat, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    mat = glm::scale(mat, glm::vec3(scale.x, scale.y, 1.0f));
}
void Transform::SetMat(glm::mat4& mat, const Transform& initTransform)
{
    mat = glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f);
    mat = glm::translate(mat, glm::vec3(pos.x - initTransform.pos.x, pos.y - initTransform.pos.y, 0.0f));
    mat = glm::rotate(mat, glm::radians(rotation - initTransform.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    mat = glm::scale(mat, glm::vec3(scale.x / initTransform.scale.x, scale.y / initTransform.scale.y, 1.0f));
}
void Transform::SetMat(glm::mat4& mat, const glm::vec2& initpos, float initrotation, const glm::vec2& initscale)
{
    mat = glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f);
    mat = glm::translate(mat, glm::vec3(pos.x - initpos.x, pos.y - initpos.y, 0.0f));
    mat = glm::rotate(mat, glm::radians(rotation - initrotation), glm::vec3(0.0f, 0.0f, 1.0f));
    mat = glm::scale(mat, glm::vec3(scale.x / initscale.x, scale.y / initscale.y, 1.0f));
}
void Transform::SetMat(glm::mat4& mat, const glm::vec2& initpos, float initrotation, float initscaleX, float initscaleY)
{
    mat = glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f);
    mat = glm::translate(mat, glm::vec3(pos.x - initpos.x, pos.y - initpos.y, 0.0f));
    mat = glm::rotate(mat, glm::radians(rotation - initrotation), glm::vec3(0.0f, 0.0f, 1.0f));
    mat = glm::scale(mat, glm::vec3(scale.x / initscaleX, scale.y / initscaleY, 1.0f));
}
void Transform::SetMat(glm::mat4& mat, float initposX, float initposY, float initrotation, const glm::vec2& initscale)
{
    mat = glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f);
    mat = glm::translate(mat, glm::vec3(pos.x - initposX, pos.y - initposY, 0.0f));
    mat = glm::rotate(mat, glm::radians(rotation - initrotation), glm::vec3(0.0f, 0.0f, 1.0f));
    mat = glm::scale(mat, glm::vec3(scale.x / initscale.x, scale.y / initscale.y, 1.0f));
}
void Transform::SetMat(glm::mat4& mat, float initposX, float initposY, float initrotation, float initscaleX, float initscaleY)
{
    mat = glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f);
    mat = glm::translate(mat, glm::vec3(pos.x - initposX, pos.y - initposY, 0.0f));
    mat = glm::rotate(mat, glm::radians(rotation - initrotation), glm::vec3(0.0f, 0.0f, 1.0f));
    mat = glm::scale(mat, glm::vec3(scale.x / initscaleX, scale.y / initscaleY, 1.0f));
}
