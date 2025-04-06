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

#pragma region Box
Shape::Box::Box() : A(0.0f, 0.0f), B(0.0f, 0.0f), C(0.0f, 0.0f), D(0.0f, 0.0f) {}
Shape::Box::Box(const glm::vec2& A, const glm::vec2& B, const glm::vec2& C, const glm::vec2& D) 
    : A(A), B(B), C(C), D(D) {}
Shape::Box::Box(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) 
    : A(x1, y1), B(x2, y2), C(x3, y3), D(x4, y4) {}

void Shape::Box::Move(const glm::vec2& v) {
    A += v;
    B += v;
    C += v;
    D += v;
}
void Shape::Box::Move(float x, float y) {
    A.x += x; A.y += y;
    B.x += x; B.y += y;
    C.x += x; C.y += y;
    D.x += x; D.y += y;
}

glm::vec2 Shape::Box::Center() {
    return (A + B + C + D) / 4.0f;
}

void Shape::Box::Rotate(const glm::vec2& pivot, float degrees) {
    A = RotatedP(A, pivot, degrees);
    B = RotatedP(B, pivot, degrees);
    C = RotatedP(C, pivot, degrees);
    D = RotatedP(D, pivot, degrees);
}
void Shape::Box::Rotate(float pivotX, float pivotY, float degrees) {
    Rotate(glm::vec2(pivotX, pivotY), degrees);
}
void Shape::Box::Rotate(float degrees) {
    glm::vec2 center = Center();
    Rotate(center, degrees);
}

void Shape::Box::Scale(const glm::vec2& scaler) {
    glm::vec2 center = Center();
    A = ScaledP(A, center, scaler);
    B = ScaledP(B, center, scaler);
    C = ScaledP(C, center, scaler);
    D = ScaledP(D, center, scaler);
}
void Shape::Box::Scale(const glm::vec2& scaler, const glm::vec2& pivot) {
    A = ScaledP(A, pivot, scaler);
    B = ScaledP(B, pivot, scaler);
    C = ScaledP(C, pivot, scaler);
    D = ScaledP(D, pivot, scaler);
}
void Shape::Box::Scale(const glm::vec2& scaler, float pivotX, float pivotY) {
    Scale(scaler, glm::vec2(pivotX, pivotY));
}
void Shape::Box::Scale(float scaleX, float scaleY) {
    Scale(glm::vec2(scaleX, scaleY));
}
void Shape::Box::Scale(float scaleX, float scaleY, const glm::vec2& pivot) {
    Scale(glm::vec2(scaleX, scaleY), pivot);
}
void Shape::Box::Scale(float scaleX, float scaleY, float pivotX, float pivotY) {
    Scale(glm::vec2(scaleX, scaleY), glm::vec2(pivotX, pivotY));
}

std::vector<glm::vec2> Shape::Box::PToListVec() {
    return { A, B, C, D };
}
std::vector<Shape::Line> Shape::Box::PToLineVec() {
    return { Shape::Line(A, B), Shape::Line(B, C), Shape::Line(C, D), Shape::Line(D, A) };
}
#pragma endregion

#pragma region AABB
Shape::AABB::AABB() : A(0.0f, 0.0f), B(0.0f, 0.0f) {}
Shape::AABB::AABB(float x1, float y1, float x2, float y2) : A(x1, y1), B(x2, y2) {}
Shape::AABB::AABB(const glm::vec2& A, const glm::vec2& B) : A(A), B(B) {}

float Shape::AABB::Width() 
{
    return abs(B.x - A.x);
}
float Shape::AABB::Height() 
{
    return abs(B.y - A.y);
}

void Shape::AABB::Move(const glm::vec2& v) 
{
    A += v;
    B += v;
}
void Shape::AABB::Move(float x, float y) 
{
    A.x += x; A.y += y;
    B.x += x; B.y += y;
}

glm::vec2 Shape::AABB::Center() 
{
    return (A + B) / 2.0f;
}

void Shape::AABB::Scale(const glm::vec2& scaler) 
{
    glm::vec2 center = Center();
    A = ScaledP(A, center, scaler);
    B = ScaledP(B, center, scaler);
}
void Shape::AABB::Scale(const glm::vec2& scaler, const glm::vec2& pivot) 
{
    A = ScaledP(A, pivot, scaler);
    B = ScaledP(B, pivot, scaler);
}
void Shape::AABB::Scale(const glm::vec2& scaler, float pivotX, float pivotY) 
{
    Scale(scaler, glm::vec2(pivotX, pivotY));
}
void Shape::AABB::Scale(float scaleX, float scaleY)
{
    Scale(glm::vec2(scaleX, scaleY));
}
void Shape::AABB::Scale(float scaleX, float scaleY, const glm::vec2& pivot)
{
    Scale(glm::vec2(scaleX, scaleY), pivot);
}
void Shape::AABB::Scale(float scaleX, float scaleY, float pivotX, float pivotY) 
{
    Scale(glm::vec2(scaleX, scaleY), glm::vec2(pivotX, pivotY));
}

std::vector<glm::vec2> Shape::AABB::PToListVec() {
    return { A, B };
}
std::vector<Shape::Line> Shape::AABB::PToLineVec() {
    glm::vec2 C(A.x, B.y), D(B.x, A.y);
    return { Shape::Line(A, C), Shape::Line(C, B), Shape::Line(B, D), Shape::Line(D, A) };
}
#pragma endregion

#pragma region Pentagon
Shape::Pentagon::Pentagon() : A(0.0f, 0.0f), B(0.0f, 0.0f), C(0.0f, 0.0f), D(0.0f, 0.0f), E(0.0f, 0.0f) {}
Shape::Pentagon::Pentagon(const glm::vec2& A, const glm::vec2& B, const glm::vec2& C, const glm::vec2& D, const glm::vec2& E)
    : A(A), B(B), C(C), D(D), E(E) {
}
Shape::Pentagon::Pentagon(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5)
    : A(x1, y1), B(x2, y2), C(x3, y3), D(x4, y4), E(x5, y5) {
}

void Shape::Pentagon::Move(const glm::vec2& v) {
    A += v;
    B += v;
    C += v;
    D += v;
    E += v;
}
void Shape::Pentagon::Move(float x, float y) {
    A.x += x; A.y += y;
    B.x += x; B.y += y;
    C.x += x; C.y += y;
    D.x += x; D.y += y;
    E.x += x; E.y += y;
}

glm::vec2 Shape::Pentagon::Center() {
    return (A + B + C + D + E) / 5.0f;
}

void Shape::Pentagon::Rotate(const glm::vec2& pivot, float degrees) {
    A = RotatedP(A, pivot, degrees);
    B = RotatedP(B, pivot, degrees);
    C = RotatedP(C, pivot, degrees);
    D = RotatedP(D, pivot, degrees);
    E = RotatedP(E, pivot, degrees);
}
void Shape::Pentagon::Rotate(float pivotX, float pivotY, float degrees) {
    Rotate(glm::vec2(pivotX, pivotY), degrees);
}
void Shape::Pentagon::Rotate(float degrees) {
    glm::vec2 center = Center();
    Rotate(center, degrees);
}

void Shape::Pentagon::Scale(const glm::vec2& scaler) {
    glm::vec2 center = Center();
    A = ScaledP(A, center, scaler);
    B = ScaledP(B, center, scaler);
    C = ScaledP(C, center, scaler);
    D = ScaledP(D, center, scaler);
    E = ScaledP(E, center, scaler);
}
void Shape::Pentagon::Scale(const glm::vec2& scaler, const glm::vec2& pivot) {
    A = ScaledP(A, pivot, scaler);
    B = ScaledP(B, pivot, scaler);
    C = ScaledP(C, pivot, scaler);
    D = ScaledP(D, pivot, scaler);
    E = ScaledP(E, pivot, scaler);
}
void Shape::Pentagon::Scale(const glm::vec2& scaler, float pivotX, float pivotY) {
    Scale(scaler, glm::vec2(pivotX, pivotY));
}
void Shape::Pentagon::Scale(float scaleX, float scaleY) {
    Scale(glm::vec2(scaleX, scaleY));
}
void Shape::Pentagon::Scale(float scaleX, float scaleY, const glm::vec2& pivot) {
    Scale(glm::vec2(scaleX, scaleY), pivot);
}
void Shape::Pentagon::Scale(float scaleX, float scaleY, float pivotX, float pivotY) {
    Scale(glm::vec2(scaleX, scaleY), glm::vec2(pivotX, pivotY));
}

std::vector<glm::vec2> Shape::Pentagon::PToListVec() {
    return { A, B, C, D, E };
}
std::vector<Shape::Line> Shape::Pentagon::PToLineVec() {
    return { Shape::Line(A, B), Shape::Line(B, C), Shape::Line(C, D), Shape::Line(D, E), Shape::Line(E, A) };
}
#pragma endregion

#pragma region Polygon
Shape::Polygon::Polygon() {}
Shape::Polygon::Polygon(const std::vector<float>& aPoints) 
{
    assert(aPoints.size() % 2 == 0);
    for (int i = 0; i < aPoints.size() - 1; i+=2)
        points.emplace_back(aPoints[i], aPoints[i + 1]);
}
Shape::Polygon::Polygon(const std::vector<glm::vec2>& aPoints) : points(aPoints) {}

void Shape::Polygon::Move(const glm::vec2& v) {
    for (glm::vec2& p : points)
        p += v;
}
void Shape::Polygon::Move(float x, float y) {
    for (glm::vec2& p : points) 
    {
        p.x += x; 
        p.y += y;
    }
}

glm::vec2 Shape::Polygon::Center() {
    if (points.empty()) return glm::vec2(0.0f, 0.0f);

    glm::vec2 sum(0.0f, 0.0f);
    for (glm::vec2& p : points)
        sum += p;

    return sum / (float)points.size();
}

void Shape::Polygon::Rotate(const glm::vec2& pivot, float degrees) {
    for (glm::vec2& p : points)
        p = RotatedP(p, pivot, degrees);
}
void Shape::Polygon::Rotate(float pivotX, float pivotY, float degrees) {
    Rotate(glm::vec2(pivotX, pivotY), degrees);
}
void Shape::Polygon::Rotate(float degrees) {
    glm::vec2 center = Center();
    Rotate(center, degrees);
}

void Shape::Polygon::Scale(const glm::vec2& scaler) {
    glm::vec2 center = Center();
    for (glm::vec2& p : points)
        p = ScaledP(p, center, scaler);
}
void Shape::Polygon::Scale(const glm::vec2& scaler, const glm::vec2& pivot) {
    for (glm::vec2& p : points)
        p = ScaledP(p, pivot, scaler);
}
void Shape::Polygon::Scale(const glm::vec2& scaler, float pivotX, float pivotY) {
    Scale(scaler, glm::vec2(pivotX, pivotY));
}
void Shape::Polygon::Scale(float scaleX, float scaleY) {
    Scale(glm::vec2(scaleX, scaleY));
}
void Shape::Polygon::Scale(float scaleX, float scaleY, const glm::vec2& pivot) {
    Scale(glm::vec2(scaleX, scaleY), pivot);
}
void Shape::Polygon::Scale(float scaleX, float scaleY, float pivotX, float pivotY) {
    Scale(glm::vec2(scaleX, scaleY), glm::vec2(pivotX, pivotY));
}

std::vector<glm::vec2> Shape::Polygon::PToListVec() {
    return points;
}
std::vector<Shape::Line> Shape::Polygon::PToLineVec() {
    std::vector<Shape::Line> res = {};
    for (int i = 0; i < points.size() - 1; i++)
        res.emplace_back(points[i], points[i + 1]);

    res.emplace_back(points[points.size() - 1], points[0]);
    return res;
}
#pragma endregion

#pragma region Circle
Shape::Circle::Circle() : O(0.0f, 0.0f), r(0.0f) {}
Shape::Circle::Circle(float Ox, float Oy, float r) : O(Ox, Oy), r(r){}
Shape::Circle::Circle(const glm::vec2& O, float r) :O(O), r(r) {}

void Shape::Circle::Move(const glm::vec2& v) 
{
    O += v;
}
void Shape::Circle::Move(float x, float y) 
{
    O.x += x; O.y += y;
}

glm::vec2 Shape::Circle::Center() 
{
    return O;
}

void Shape::Circle::Rotate(const glm::vec2& pivot, float degrees) 
{
    O = RotatedP(O, pivot, degrees);
}
void Shape::Circle::Rotate(float pivotX, float pivotY, float degrees) 
{
    O = RotatedP(O, pivotX, pivotY, degrees);
}

void Scale(const glm::vec2& scaler) {}
void Scale(const glm::vec2& scaler, const glm::vec2& pivot) {}
void Scale(const glm::vec2& scaler, float pivotX, float pivotY) {}
void Scale(float scaleX, float scaleY) {}
void Scale(float scaleX, float scaleY, const glm::vec2& pivot) {}
void Scale(float scaleX, float scaleY, float pivotX, float pivotY) {}
#pragma endregion

