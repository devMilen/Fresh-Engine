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
