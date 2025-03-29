#include "Shape.h"

#pragma region RotatedP and ScaledP
glm::vec2 Shape::RotatedP(const glm::vec2& P, const glm::vec2& pivot, float degrees)
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
glm::vec2 Shape::RotatedP(float x, float y, const glm::vec2& pivot, float degrees)
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
glm::vec2 Shape::RotatedP(const glm::vec2& p, float pivotX, float pivotY, float degrees)
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
glm::vec2 Shape::RotatedP(float x, float y, float pivotX, float pivotY, float degrees)
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

glm::vec2 Shape::ScaledP(const glm::vec2& p, const glm::vec2& pivot, const glm::vec2& scaler)
{
    glm::vec2 translated = p - pivot;

    glm::vec2 scaled = translated * scaler; 

    return scaled + pivot;
}
glm::vec2 Shape::ScaledP(float x, float y, const glm::vec2& pivot, const glm::vec2& scaler)
{
    glm::vec2 translated(x - pivot.x, y - pivot.y);

    glm::vec2 scaled = translated * scaler;

    return scaled + pivot;
}
glm::vec2 Shape::ScaledP(const glm::vec2& p, const glm::vec2& pivot, float scaleX, float scaleY)
{
    glm::vec2 translated = p - pivot;

    glm::vec2 scaled = translated * glm::vec2(scaleX, scaleY);

    return scaled + pivot;
}
glm::vec2 Shape::ScaledP(float x, float y, const glm::vec2& pivot, float scaleX, float scaleY)
{
    glm::vec2 translated(x - pivot.x, y - pivot.y);

    glm::vec2 scaled = translated * glm::vec2(scaleX, scaleY);

    return scaled + pivot;
}
glm::vec2 Shape::ScaledP(float x, float y, float pivotX, float pivotY, float scaleX, float scaleY)
{
    glm::vec2 translated(x - pivotX, y - pivotY);

    glm::vec2 scaled = translated * glm::vec2(scaleX, scaleY);

    return glm::vec2(scaled.x + pivotX, scaled.y + pivotY);
}
glm::vec2 Shape::ScaledP(const glm::vec2& p, float pivotX, float pivotY, float scaleX, float scaleY)
{
    glm::vec2 translated(p.x - pivotX, p.y - pivotY);

    glm::vec2 scaled = translated * glm::vec2(scaleX, scaleY);

    return glm::vec2(scaled.x + pivotX, scaled.y + pivotY);
}
glm::vec2 Shape::ScaledP(const glm::vec2& p, float pivotX, float pivotY, const glm::vec2& scale)
{
    glm::vec2 translated(p.x - pivotX, p.y - pivotY);

    glm::vec2 scaled = translated * scale;

    return glm::vec2(scaled.x + pivotX, scaled.y + pivotY);
}
#pragma endregion

#pragma region Line
Shape::Line::Line() : A(0.0f, 0.0f), B(0.0f, 0.0f) {}

Shape::Line::Line(const glm::vec2& A, const glm::vec2& B) : A(A), B(B) {}

Shape::Line::Line(float x1, float y1, float x2, float y2) : A(x1, y1), B(x2, y2) {}

void Shape::Line::Move(const glm::vec2& v) {
    A += v;
    B += v;
}

void Shape::Line::Move(float x, float y) {
    A.x += x; A.y += y;
    B.x += x; B.y += y;
}

glm::vec2 Shape::Line::Center() {
    return (A + B) * 0.5f;
}

void Shape::Line::Rotate(const glm::vec2& pivot, float degrees) {
    A = RotatedP(A, pivot, degrees);
    B = RotatedP(B, pivot, degrees);
}

void Shape::Line::Rotate(float pivotX, float pivotY, float degrees) {
    Rotate(glm::vec2(pivotX, pivotY), degrees);
}

void Shape::Line::Rotate(float degrees) {
    glm::vec2 center = Center();
    Rotate(center, degrees);
}

void Shape::Line::Scale(const glm::vec2& scaler) {
    glm::vec2 center = Center();
    A = ScaledP(A, center, scaler);
    B = ScaledP(B, center, scaler);
}

void Shape::Line::Scale(const glm::vec2& scaler, const glm::vec2& pivot) {
    A = ScaledP(A, pivot, scaler);
    B = ScaledP(B, pivot, scaler);
}

void Shape::Line::Scale(const glm::vec2& scaler, float pivotX, float pivotY) {
    Scale(scaler, glm::vec2(pivotX, pivotY));
}

void Shape::Line::Scale(float scaleX, float scaleY) {
    Scale(glm::vec2(scaleX, scaleY));
}

void Shape::Line::Scale(float scaleX, float scaleY, const glm::vec2& pivot) {
    Scale(glm::vec2(scaleX, scaleY), pivot);
}

void Shape::Line::Scale(float scaleX, float scaleY, float pivotX, float pivotY) {
    Scale(glm::vec2(scaleX, scaleY), glm::vec2(pivotX, pivotY));
}

std::vector<glm::vec2> Shape::Line::PToListVec() {
    return { A, B };
}

#pragma endregion

#pragma region Triangle
Shape::Triangle::Triangle() : A(0.0f, 0.0f), B(0.0f, 0.0f), C(0.0f, 0.0f) {}

Shape::Triangle::Triangle(const glm::vec2& A, const glm::vec2& B, const glm::vec2& C) : A(A), B(B), C(C) {}

Shape::Triangle::Triangle(float x1, float y1, float x2, float y2, float x3, float y3) : A(x1, y1), B(x2, y2), C(x3, y3) {}

void Shape::Triangle::Move(const glm::vec2& v) {
    A += v;
    B += v;
    C += v;
}

void Shape::Triangle::Move(float x, float y) {
    A.x += x; A.y += y;
    B.x += x; B.y += y;
    C.x += x; C.y += y;
}

glm::vec2 Shape::Triangle::Center() {
    return (A + B + C) / 3.0f;
}

void Shape::Triangle::Rotate(const glm::vec2& pivot, float degrees) {
    A = RotatedP(A, pivot, degrees);
    B = RotatedP(B, pivot, degrees);
    C = RotatedP(C, pivot, degrees);
}

void Shape::Triangle::Rotate(float pivotX, float pivotY, float degrees) {
    Rotate(glm::vec2(pivotX, pivotY), degrees);
}

void Shape::Triangle::Rotate(float degrees) {
    glm::vec2 center = Center();
    Rotate(center, degrees);
}

void Shape::Triangle::Scale(const glm::vec2& scaler) {
    glm::vec2 center = Center();
    A = ScaledP(A, center, scaler);
    B = ScaledP(B, center, scaler);
    C = ScaledP(C, center, scaler);
}

void Shape::Triangle::Scale(const glm::vec2& scaler, const glm::vec2& pivot) {
    A = ScaledP(A, pivot, scaler);
    B = ScaledP(B, pivot, scaler);
    C = ScaledP(C, pivot, scaler);
}

void Shape::Triangle::Scale(const glm::vec2& scaler, float pivotX, float pivotY) {
    Scale(scaler, glm::vec2(pivotX, pivotY));
}

void Shape::Triangle::Scale(float scaleX, float scaleY) {
    Scale(glm::vec2(scaleX, scaleY));
}

void Shape::Triangle::Scale(float scaleX, float scaleY, const glm::vec2& pivot) {
    Scale(glm::vec2(scaleX, scaleY), pivot);
}

void Shape::Triangle::Scale(float scaleX, float scaleY, float pivotX, float pivotY) {
    Scale(glm::vec2(scaleX, scaleY), glm::vec2(pivotX, pivotY));
}

std::vector<glm::vec2> Shape::Triangle::PToListVec() {
    return { A, B, C };
}

std::vector<Shape::Line> Shape::Triangle::PToLineVec() {
    return { Shape::Line(A, B), Shape::Line(B, C), Shape::Line(C, A) };
}
#pragma endregion
