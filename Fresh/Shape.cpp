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

#pragma region Def
void Shape::Def::Move(const glm::vec2& v)
{
    short size = pointsSize();
    for(int i = 0; i < size; i++)
        points[i] += v;
}
void Shape::Def::Move(float x, float y) 
{
    const short size = pointsSize();
    for (int i = 0; i < size; i++)
    {
        points[i].x += x;
        points[i].y += y;
    }
}

glm::vec2 Shape::Def::Center() {
    glm::vec2 sum(0.0f);
    const short size = pointsSize();
    for (int i = 0; i < size; i++)
        sum += points[i];

    return sum / static_cast<float>(pointsSize());
}

void Shape::Def::Rotate(const glm::vec2& pivot, float degrees) {
    const short size = pointsSize(); 
    for(int i = 0; i < size; i++)
        points[i] = Shape::RotatedP(points[i], pivot, degrees);
}
void Shape::Def::Rotate(float pivotX, float pivotY, float degrees) {
    Rotate(glm::vec2(pivotX, pivotY), degrees);
}
void Shape::Def::Rotate(float degrees) {
    Rotate(Center(), degrees);
}

void Shape::Def::Scale(const glm::vec2& scaler)
{
    Scale(scaler, Center());
}
void Shape::Def::Scale(const glm::vec2& scaler, const glm::vec2& pivot)
{
    const short size = pointsSize(); 
    for(int i = 0; i < size; i++)
        points[i] = Shape::ScaledP(points[i], pivot, scaler);
}
void Shape::Def::Scale(const glm::vec2& scaler, float pivotX, float pivotY) 
{
    Scale(scaler, glm::vec2(pivotX, pivotY));
}
void Shape::Def::Scale(float scaleX, float scaleY)
{
    Scale(glm::vec2(scaleX, scaleY), Center());
}
void Shape::Def::Scale(float scaleX, float scaleY, const glm::vec2& pivot) 
{
    Scale(glm::vec2(scaleX, scaleY), pivot);
}
void Shape::Def::Scale(float scaleX, float scaleY, float pivotX, float pivotY) 
{
    Scale(glm::vec2(scaleX, scaleY), glm::vec2(pivotX, pivotY));
}
#pragma endregion

#pragma region Line
Shape::Line::Line() {
    localPoints[0] = glm::vec2(0);
    localPoints[1] = glm::vec2(0);
    points = localPoints;
}
Shape::Line::Line(const glm::vec2& A, const glm::vec2& B) {
    localPoints[0] = A;
    localPoints[1] = B;
    points = localPoints;
}
Shape::Line::Line(float x1, float y1, float x2, float y2) {
    localPoints[0] = glm::vec2(x1, y1);
    localPoints[1] = glm::vec2(x2, y2);
    points = localPoints;  
}

const Shape::Types Shape::Line::Type() const
{
    return Shape::Types::ShapeLine;
}
const unsigned int Shape::Line::pointsSize() const
{
    return 2;
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
#pragma endregion

#pragma region Pentagon
Shape::Pentagon::Pentagon() : A(0.0f, 0.0f), B(0.0f, 0.0f), C(0.0f, 0.0f), D(0.0f, 0.0f), E(0.0f, 0.0f) {}
Shape::Pentagon::Pentagon(float x, float y, float pivotX, float pivotY) : A(x, y)
{
    const float degreesJump = 360.0f / 5.0f;
    B = RotatedP(A, pivotX, pivotY, 1*degreesJump);
    C = RotatedP(A, pivotX, pivotY, 2 * degreesJump);
    D = RotatedP(A, pivotX, pivotY, 3 * degreesJump);
    E = RotatedP(A, pivotX, pivotY, 4 * degreesJump);
}
Shape::Pentagon::Pentagon(const glm::vec2& A, const glm::vec2& pivot) : A(A)
{
    const float degreesJump = 360.0f / 5.0f;
    B = RotatedP(A, pivot, 1 * degreesJump);
    C = RotatedP(A, pivot, 2 * degreesJump);
    D = RotatedP(A, pivot, 3 * degreesJump);
    E = RotatedP(A, pivot, 4 * degreesJump);
}
Shape::Pentagon::Pentagon(float x, float y, const glm::vec2& pivot) : A(x, y)
{
    const float degreesJump = 360.0f / 5.0f;
    B = RotatedP(A, pivot, 1 * degreesJump);
    C = RotatedP(A, pivot, 2 * degreesJump);
    D = RotatedP(A, pivot, 3 * degreesJump);
    E = RotatedP(A, pivot, 4 * degreesJump);
}
Shape::Pentagon::Pentagon(const glm::vec2& A, float pivotX, float pivotY) : A(A)
{
    const float degreesJump = 360.0f / 5.0f;
    B = RotatedP(A, pivotX, pivotY, 1 * degreesJump);
    C = RotatedP(A, pivotX, pivotY, 2 * degreesJump);
    D = RotatedP(A, pivotX, pivotY, 3 * degreesJump);
    E = RotatedP(A, pivotX, pivotY, 4 * degreesJump);
}
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
#pragma endregion

#pragma region Hexagon
Shape::Hexagon::Hexagon() : A(0.0f, 0.0f), B(0.0f, 0.0f), C(0.0f, 0.0f), D(0.0f, 0.0f), E(0.0f, 0.0f), F(0.0f, 0.0f) {}
Shape::Hexagon::Hexagon(float x, float y, float pivotX, float pivotY) : A(x, y)
{
    const float degreesJump = 360.0f / 6.0f;
    B = RotatedP(A, pivotX, pivotY, 1 * degreesJump);
    C = RotatedP(A, pivotX, pivotY, 2 * degreesJump);
    D = RotatedP(A, pivotX, pivotY, 3 * degreesJump);
    E = RotatedP(A, pivotX, pivotY, 4 * degreesJump);
    F = RotatedP(A, pivotX, pivotY, 5 * degreesJump);
}
Shape::Hexagon::Hexagon(const glm::vec2& A, const glm::vec2& pivot) : A(A)
{
    const float degreesJump = 360.0f / 6.0f;
    B = RotatedP(A, pivot, 1 * degreesJump);
    C = RotatedP(A, pivot, 2 * degreesJump);
    D = RotatedP(A, pivot, 3 * degreesJump);
    E = RotatedP(A, pivot, 4 * degreesJump);
    F = RotatedP(A, pivot, 5 * degreesJump);
}
Shape::Hexagon::Hexagon(float x, float y, const glm::vec2& pivot) : A(x, y)
{
    const float degreesJump = 360.0f / 6.0f;
    B = RotatedP(A, pivot, 1 * degreesJump);
    C = RotatedP(A, pivot, 2 * degreesJump);
    D = RotatedP(A, pivot, 3 * degreesJump);
    E = RotatedP(A, pivot, 4 * degreesJump);
    F = RotatedP(A, pivot, 5 * degreesJump);
}
Shape::Hexagon::Hexagon(const glm::vec2& A, float pivotX, float pivotY) : A(A)
{
    const float degreesJump = 360.0f / 6.0f;
    B = RotatedP(A, pivotX, pivotY, 1 * degreesJump);
    C = RotatedP(A, pivotX, pivotY, 2 * degreesJump);
    D = RotatedP(A, pivotX, pivotY, 3 * degreesJump);
    E = RotatedP(A, pivotX, pivotY, 4 * degreesJump);
    F = RotatedP(A, pivotX, pivotY, 5 * degreesJump);
}
Shape::Hexagon::Hexagon(const glm::vec2& A, const glm::vec2& B, const glm::vec2& C, 
    const glm::vec2& D, const glm::vec2& E, const glm::vec2& F)
    : A(A), B(B), C(C), D(D), E(E), F(F) {}
Shape::Hexagon::Hexagon(float x1, float y1, float x2, float y2, float x3, float y3,
    float x4, float y4, float x5, float y5, float x6, float y6)
    : A(x1, y1), B(x2, y2), C(x3, y3), D(x4, y4), E(x5, y5), F(x6, y6) {}

void Shape::Hexagon::Move(const glm::vec2& v) {
    A += v;
    B += v;
    C += v;
    D += v;
    E += v;
    F += v;
}
void Shape::Hexagon::Move(float x, float y) {
    A.x += x; A.y += y;
    B.x += x; B.y += y;
    C.x += x; C.y += y;
    D.x += x; D.y += y;
    E.x += x; E.y += y;
    F.x += x; F.y += y;
}

glm::vec2 Shape::Hexagon::Center() {
    return (A + B + C + D + E + F) / 6.0f;
}

void Shape::Hexagon::Rotate(const glm::vec2& pivot, float degrees) {
    A = RotatedP(A, pivot, degrees);
    B = RotatedP(B, pivot, degrees);
    C = RotatedP(C, pivot, degrees);
    D = RotatedP(D, pivot, degrees);
    E = RotatedP(E, pivot, degrees);
    F = RotatedP(F, pivot, degrees);
}
void Shape::Hexagon::Rotate(float pivotX, float pivotY, float degrees) {
    Rotate(glm::vec2(pivotX, pivotY), degrees);
}
void Shape::Hexagon::Rotate(float degrees) {
    glm::vec2 center = Center();
    Rotate(center, degrees);
}

void Shape::Hexagon::Scale(const glm::vec2& scaler) {
    glm::vec2 center = Center();
    A = ScaledP(A, center, scaler);
    B = ScaledP(B, center, scaler);
    C = ScaledP(C, center, scaler);
    D = ScaledP(D, center, scaler);
    E = ScaledP(E, center, scaler);
    F = ScaledP(F, center, scaler);
}
void Shape::Hexagon::Scale(const glm::vec2& scaler, const glm::vec2& pivot) {
    A = ScaledP(A, pivot, scaler);
    B = ScaledP(B, pivot, scaler);
    C = ScaledP(C, pivot, scaler);
    D = ScaledP(D, pivot, scaler);
    E = ScaledP(E, pivot, scaler);
    F = ScaledP(F, pivot, scaler);
}
void Shape::Hexagon::Scale(const glm::vec2& scaler, float pivotX, float pivotY) {
    Scale(scaler, glm::vec2(pivotX, pivotY));
}
void Shape::Hexagon::Scale(float scaleX, float scaleY) {
    Scale(glm::vec2(scaleX, scaleY));
}
void Shape::Hexagon::Scale(float scaleX, float scaleY, const glm::vec2& pivot) {
    Scale(glm::vec2(scaleX, scaleY), pivot);
}
void Shape::Hexagon::Scale(float scaleX, float scaleY, float pivotX, float pivotY) {
    Scale(glm::vec2(scaleX, scaleY), glm::vec2(pivotX, pivotY));
}

std::vector<glm::vec2> Shape::Hexagon::PToListVec() {
    return { A, B, C, D, E, F };
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
#pragma endregion

#pragma region Circle
Shape::Circle::Circle() : O(0.0f, 0.0f), r(0.0f) {}
Shape::Circle::Circle(float Ox, float Oy, float r) : O(Ox, Oy), r(r) {}
Shape::Circle::Circle(const glm::vec2& O, float r) : O(O), r(r) {}

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
#pragma endregion

#pragma region ScaleCir
Shape::ScaleCir::ScaleCir() : O(0.0f, 0.0f), r(0), scale(0.0f, 0.0f) {}
Shape::ScaleCir::ScaleCir(float Ox, float Oy, float r, float scaleX, float scaleY) 
    : O(Ox, Oy), r(r), scale(scaleX, scaleY) {}
Shape::ScaleCir::ScaleCir(const glm::vec2& O, float r, float scaleX, float scaleY) 
    : O(O), r(r), scale(scaleX, scaleY) {}
Shape::ScaleCir::ScaleCir(float Ox, float Oy, float r, const glm::vec2& scale) 
    : O(Ox, Oy), r(r), scale(scale) {}
Shape::ScaleCir::ScaleCir(const glm::vec2& O, float r, const glm::vec2& scale) 
    : O(O), r(r), scale(scale) {}

void Shape::ScaleCir::Move(const glm::vec2& v)
{
    O += v;
}
void Shape::ScaleCir::Move(float x, float y)
{
    O.x += x; O.y += y;
}

glm::vec2 Shape::ScaleCir::Center()
{
    return O;
}

void Shape::ScaleCir::Rotate(const glm::vec2& pivot, float degrees)
{
    O = RotatedP(O, pivot, degrees);
}
void Shape::ScaleCir::Rotate(float pivotX, float pivotY, float degrees)
{
    O = RotatedP(O, pivotX, pivotY, degrees);
}

void Shape::ScaleCir::Scale(float scaleX, float scaleY) 
{
    scale.x *= scaleX;
    scale.y *= scaleY;
}
void Shape::ScaleCir::Scale(const glm::vec2& aScale)
{
    scale *= aScale;
}
#pragma endregion
