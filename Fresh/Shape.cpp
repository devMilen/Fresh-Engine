#include "Shape.h"
#include "Transform.h"

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
        points[i] = Transform::RotatedP(points[i], pivot, degrees);
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
        points[i] = Transform::ScaledP(points[i], pivot, scaler);
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

void Shape::Def::InitRegular(const glm::vec2& A, const glm::vec2& pivot) 
{
    points[0] = A;
    const float fpointsSize = pointsSize();
    for (int i = 1; i < fpointsSize; i++)
        points[i] = Transform::RotatedP(A, pivot, i * (360.0f / fpointsSize));
}
void Shape::Def::InitRegular(float Ax, float Ay, float pivotX, float pivotY) 
{
    points[0].x = Ax; points[0].y = Ay;
    const float fpointsSize = pointsSize();
    for (int i = 1; i < fpointsSize; i++)
        points[i] = Transform::RotatedP(Ax, Ay, pivotX, pivotY, i * (360.0f / fpointsSize));
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
Shape::Triangle::Triangle() {
    localPoints[0] = glm::vec2(0);
    localPoints[1] = glm::vec2(0);
    localPoints[2] = glm::vec2(0);
    points = localPoints;
}
Shape::Triangle::Triangle(const glm::vec2& A, const glm::vec2& B, const glm::vec2& C) {
    localPoints[0] = A;
    localPoints[1] = B;
    localPoints[2] = C;
    points = localPoints;
}
Shape::Triangle::Triangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    localPoints[0] = glm::vec2(x1, y1);
    localPoints[1] = glm::vec2(x2, y2);
    localPoints[2] = glm::vec2(x3, y3);
    points = localPoints;
}

const Shape::Types Shape::Triangle::Type() const
{
    return Shape::Types::ShapeTriangle;
}
const unsigned int Shape::Triangle::pointsSize() const
{
    return 3;
}
#pragma endregion

#pragma region Box
Shape::Box::Box() {
    localPoints[0] = glm::vec2(0);
    localPoints[1] = glm::vec2(0);
    localPoints[2] = glm::vec2(0);
    localPoints[3] = glm::vec2(0);
    points = localPoints;
}
Shape::Box::Box(const glm::vec2& A, const glm::vec2& pivot) 
{
    points = localPoints;
    InitRegular(A, pivot);
}
Shape::Box::Box(float Ax, float Ay, float pivotX, float pivotY) 
{
    points = localPoints;
    InitRegular(Ax, Ay, pivotX, pivotY);
}
Shape::Box::Box(const glm::vec2& A, const glm::vec2& B, const glm::vec2& C, 
const glm::vec2& D) {
    localPoints[0] = A;
    localPoints[1] = B;
    localPoints[2] = C;
    localPoints[3] = D;
    points = localPoints;
}
Shape::Box::Box(float x1, float y1, float x2, float y2, float x3, float y3,
float x4, float y4) {
    localPoints[0] = glm::vec2(x1, y1);
    localPoints[1] = glm::vec2(x2, y2);
    localPoints[2] = glm::vec2(x3, y3);
    localPoints[3] = glm::vec2(x4, y4);
    points = localPoints;
}

const Shape::Types Shape::Box::Type() const
{
    return Shape::Types::ShapeBox;
}
const unsigned int Shape::Box::pointsSize() const
{
    return 4;
}
#pragma endregion

#pragma region AABB
Shape::AABB::AABB() {
    localPoints[0] = glm::vec2(0);
    localPoints[1] = glm::vec2(0);
    points = localPoints;
}
Shape::AABB::AABB(const glm::vec2& A, const glm::vec2& B) {
    localPoints[0] = A;
    localPoints[1] = B;
    points = localPoints;
}
Shape::AABB::AABB(float x1, float y1, float x2, float y2) {
    localPoints[0] = glm::vec2(x1, y1);
    localPoints[1] = glm::vec2(x2, y2);
    points = localPoints;
}

float Shape::AABB::Width()
{
    return abs(points[1].x - points[0].x);
}
float Shape::AABB::Height()
{
    return abs(points[1].y - points[0].y);
}

const Shape::Types Shape::AABB::Type() const
{
    return Shape::Types::ShapeAABB;
}
const unsigned int Shape::AABB::pointsSize() const
{
    return 2;
}
#pragma endregion

#pragma region Pentagon
Shape::Pentagon::Pentagon() {
    localPoints[0] = glm::vec2(0);
    localPoints[1] = glm::vec2(0);
    localPoints[2] = glm::vec2(0);
    localPoints[3] = glm::vec2(0);
    localPoints[4] = glm::vec2(0);
    points = localPoints;
}
Shape::Pentagon::Pentagon(const glm::vec2& A, const glm::vec2& pivot)
{
    points = localPoints;
    InitRegular(A, pivot);
}
Shape::Pentagon::Pentagon(float Ax, float Ay, float pivotX, float pivotY)
{
    points = localPoints;
    InitRegular(Ax, Ay, pivotX, pivotY);
}
Shape::Pentagon::Pentagon(const glm::vec2& A, const glm::vec2& B, const glm::vec2& C,
    const glm::vec2& D, const glm::vec2& E) {
    localPoints[0] = A;
    localPoints[1] = B;
    localPoints[2] = C;
    localPoints[3] = D;
    localPoints[4] = E;
    points = localPoints;
}
Shape::Pentagon::Pentagon(float x1, float y1, float x2, float y2, float x3, float y3,
    float x4, float y4, float x5, float y5) {
    localPoints[0] = glm::vec2(x1, y1);
    localPoints[1] = glm::vec2(x2, y2);
    localPoints[2] = glm::vec2(x3, y3);
    localPoints[3] = glm::vec2(x4, y4);
    localPoints[4] = glm::vec2(x5, y5);
    points = localPoints;
}

const Shape::Types Shape::Pentagon::Type() const
{
    return Shape::Types::ShapePentagon;
}
const unsigned int Shape::Pentagon::pointsSize() const
{
    return 5;
}
#pragma endregion

#pragma region Hexagon
Shape::Hexagon::Hexagon() {
    localPoints[0] = glm::vec2(0);
    localPoints[1] = glm::vec2(0);
    localPoints[2] = glm::vec2(0);
    localPoints[3] = glm::vec2(0);
    localPoints[4] = glm::vec2(0);
    localPoints[5] = glm::vec2(0);
    points = localPoints;
}
Shape::Hexagon::Hexagon(const glm::vec2& A, const glm::vec2& pivot)
{
    points = localPoints;
    InitRegular(A, pivot);
}
Shape::Hexagon::Hexagon(float Ax, float Ay, float pivotX, float pivotY)
{
    points = localPoints;
    InitRegular(Ax, Ay, pivotX, pivotY);
}
Shape::Hexagon::Hexagon(const glm::vec2& A, const glm::vec2& B, const glm::vec2& C,
const glm::vec2& D, const glm::vec2& E, const glm::vec2& F) {
    localPoints[0] = A;
    localPoints[1] = B;
    localPoints[2] = C;
    localPoints[3] = D;
    localPoints[4] = E;
    localPoints[5] = F;
    points = localPoints;
}
Shape::Hexagon::Hexagon(float x1, float y1, float x2, float y2, float x3, float y3,
    float x4, float y4, float x5, float y5, float x6, float y6) {
    localPoints[0] = glm::vec2(x1, y1);
    localPoints[1] = glm::vec2(x2, y2);
    localPoints[2] = glm::vec2(x3, y3);
    localPoints[3] = glm::vec2(x4, y4);
    localPoints[4] = glm::vec2(x5, y5);
    localPoints[5] = glm::vec2(x6, y6);
    points = localPoints;
}

const Shape::Types Shape::Hexagon::Type() const
{
    return Shape::Types::ShapeHexagon;
}
const unsigned int Shape::Hexagon::pointsSize() const
{
    return 6;
}
#pragma endregion

#pragma region Polygon
Shape::Polygon::Polygon() = default;
Shape::Polygon::Polygon(const glm::vec2& A, const glm::vec2& pivot, unsigned int pointsSize)
{
    localPoints.resize(pointsSize);
    points = localPoints.data();
    InitRegular(A, pivot);
}
Shape::Polygon::Polygon(float Ax, float Ay, float pivotX, float pivotY, unsigned int pointsSize)
{
    localPoints.resize(pointsSize);
    points = localPoints.data();
    InitRegular(Ax, Ay, pivotX, pivotY);
}
Shape::Polygon::Polygon(const std::vector<float>& aPoints) {
    for (int i = 0; i < aPoints.size(); i += 2) 
        localPoints.push_back(glm::vec2(aPoints[i], aPoints[i + 1]));
    points = localPoints.data(); 
}
Shape::Polygon::Polygon(const std::vector<glm::vec2>& aPoints) {
    localPoints = aPoints;  
    points = localPoints.data();  
}

const Shape::Types Shape::Polygon::Type() const {
    return Shape::Types::ShapePolygon;
}
const unsigned int Shape::Polygon::pointsSize() const {
    return localPoints.size(); 
}
#pragma endregion

#pragma region Circle
Shape::Circle::Circle() : r(0.0f) 
{ 
    localPoints[0] = glm::vec2(0);
    points = localPoints;
}
Shape::Circle::Circle(float r) : r(r)
{
    localPoints[0] = glm::vec2(0);
    points = localPoints;
}
Shape::Circle::Circle(float Ox, float Oy, float r) : r(r) 
{
    localPoints[0] = glm::vec2(Ox, Oy);
    points = localPoints;
}
Shape::Circle::Circle(const glm::vec2& O, float r) : r(r) 
{
    localPoints[0] = O;
    points = localPoints;
}

const Shape::Types Shape::Circle::Type() const
{
    return Shape::Types::ShapeCircle;
}
const unsigned int Shape::Circle::pointsSize() const
{
    return 1;
}
#pragma endregion
