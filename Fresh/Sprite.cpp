#include "Sprite.h"

#ifdef _DEBUG
void Color::Print() const {
    std::cout << "r: " << m_r << " g: " << m_g << 
        " b: " << m_b << " a: " << m_a << '\n';
}
#endif //_DEBUG

//calculating in coordinate system of (0, 0) top left first then converting
void VertexTexCoords::SetCoorsToGetImageAt(uint32_t index, float texWidth, float texHeight,
    float sprWidth, float sprHeight, EdgePosRelCenter vertex
) {
    int32_t SprsPerRow = static_cast<int32_t>(texWidth / sprWidth);

    m_v = (index / SprsPerRow) * sprHeight;
    m_u = (index % SprsPerRow) * sprWidth;

#ifdef _DEBUG
    std::cout << "sprite box calculated at position: " << m_u << ' ' << m_v << '\n';
#endif //_DEBUG

    if (vertex == EdgePosRelCenter::BottomLeft || vertex == EdgePosRelCenter::BottomRight)
        m_v += sprHeight;
    if (vertex == EdgePosRelCenter::TopRight || vertex == EdgePosRelCenter::BottomRight)
        m_u += sprWidth;

    m_u /= texWidth;
    m_v /= texHeight;
    m_v = 1.0f - m_v;
}

void VertexTexCoords::SetCoorsToGetImageAt(uint32_t index, const glm::vec2& texSpecs,
    const glm::vec2& sprSpecs, EdgePosRelCenter vertex
) {
    int32_t SprsPerRow = static_cast<int32_t>(texSpecs.x / sprSpecs.x);

    m_u = (index % SprsPerRow) * sprSpecs.x;
    m_v = (index / SprsPerRow) * sprSpecs.y;

    if (vertex == EdgePosRelCenter::TopRight || vertex == EdgePosRelCenter::BottomRight)
        m_u += sprSpecs.x;
    if (vertex == EdgePosRelCenter::BottomLeft || vertex == EdgePosRelCenter::BottomRight)
        m_v += sprSpecs.y;

    m_u /= texSpecs.x;
    m_v /= texSpecs.y;
    m_v = 1.0f - m_v;
}

void Sprite::Select() const {
	m_array_buffer.Select();
	m_shader_program.Select();
    glUniformMatrix4fv(m_shader_program.ULocOf("m_mat"), 1, GL_FALSE, &m_mat[0][0]);
    glUniform1f(m_shader_program.ULocOf("m_dist_z"), m_dist_z);
	m_texture.Select();
}

void Sprite::Render() const {
    Select();
    glDrawElements(GL_TRIANGLES, m_index_buffer.size, GL_UNSIGNED_INT, nullptr);
}

void Sprite::Render(float m_r, float m_g, float m_b, float m_a) const {
    Select();
    glUniform4f(m_shader_program.ULocOf("givenColor"), m_r, m_g, m_b, m_a);
    glDrawElements(GL_TRIANGLES, m_index_buffer.size, GL_UNSIGNED_INT, nullptr);
}

void Sprite::Render(float m_r, float m_g, float m_b, float m_a, float width) const {
    glLineWidth(width);
    Select();
    glUniform4f(m_shader_program.ULocOf("givenColor"), m_r, m_g, m_b, m_a);
    glDrawArrays(GL_LINES, 0, 2);
}

void Sprite::Render(float m_r, float m_g, float m_b, float m_a, float radius,
    float donutness, const Transform& transform
) const {
    Select();
    glUniform4f(m_shader_program.ULocOf("givenColor"), m_r, m_g, m_b, m_a);
    glUniform4f(m_shader_program.ULocOf("O_r_donutness"), transform.pos.x, transform.pos.y, radius, donutness);
    glUniform4f(m_shader_program.ULocOf("scale_sin_cos"), transform.scale.x, transform.scale.y,
        sin(glm::radians(transform.rotation)), cos(glm::radians(transform.rotation)));
    glDrawElements(GL_TRIANGLES, m_index_buffer.size, GL_UNSIGNED_INT, nullptr);
}

void Sprite::Render(float m_r, float m_g, float m_b, float m_a, float radius,
    const glm::vec2& O, float donutness, const Transform& transform
) const {
    Select();
    glUniform4f(m_shader_program.ULocOf("givenColor"), m_r, m_g, m_b, m_a);
    glUniform4f(m_shader_program.ULocOf("O_r_donutness"), O.x, O.y, radius, donutness);
    glUniform4f(m_shader_program.ULocOf("scale_sin_cos"), transform.scale.x, transform.scale.y,
        sin(glm::radians(transform.rotation)), cos(glm::radians(transform.rotation)));
    glDrawElements(GL_TRIANGLES, m_index_buffer.size, GL_UNSIGNED_INT, nullptr);
}

void Sprite::Render(float m_r, float m_g, float m_b, float m_a, float radius, 
    float Ox, float Oy, float donutness, const Transform& transform
) const {
    Select();
    glUniform4f(m_shader_program.ULocOf("givenColor"), m_r, m_g, m_b, m_a);
    glUniform4f(m_shader_program.ULocOf("O_r_donutness"), Ox, Oy, radius, donutness);
    glUniform4f(m_shader_program.ULocOf("scale_sin_cos"), transform.scale.x, transform.scale.y,
        sin(glm::radians(transform.rotation)), cos(glm::radians(transform.rotation)));
    glDrawElements(GL_TRIANGLES, m_index_buffer.size, GL_UNSIGNED_INT, nullptr);
}

void Sprite::Render(float m_r, float m_g, float m_b, float m_a, float radius, const glm::vec2& O, 
    float donutness, const glm::vec2& scale, float rotation
) const {
    Select();
    glUniform4f(m_shader_program.ULocOf("givenColor"), m_r, m_g, m_b, m_a);
    glUniform4f(m_shader_program.ULocOf("O_r_donutness"), O.x, O.y, radius, donutness);
    glUniform4f(m_shader_program.ULocOf("scale_sin_cos"), scale.x, scale.y, sin(glm::radians(rotation)), cos(glm::radians(rotation)));
    glDrawElements(GL_TRIANGLES, m_index_buffer.size, GL_UNSIGNED_INT, nullptr);
}

void Sprite::Render(float m_r, float m_g, float m_b, float m_a, float radius, float Ox, float Oy, 
    float donutness, float scaleX, float scaleY, float rotation
) const {
    Select();
    glUniform4f(m_shader_program.ULocOf("givenColor"), m_r, m_g, m_b, m_a);
    glUniform4f(m_shader_program.ULocOf("O_r_donutness"), Ox, Oy, radius, donutness);
    glUniform4f(m_shader_program.ULocOf("scale_sin_cos"), scaleX, scaleY, sin(glm::radians(rotation)), cos(glm::radians(rotation)));
    glDrawElements(GL_TRIANGLES, m_index_buffer.size, GL_UNSIGNED_INT, nullptr);
}

void Sprite::Render(float m_r, float m_g, float m_b, float m_a, float radius, const glm::vec2& O, 
    float donutness, float scaleX, float scaleY, float rotation
) const {
    Select();
    glUniform4f(m_shader_program.ULocOf("givenColor"), m_r, m_g, m_b, m_a);
    glUniform4f(m_shader_program.ULocOf("O_r_donutness"), O.x, O.y, radius, donutness);
    glUniform4f(m_shader_program.ULocOf("scale_sin_cos"), scaleX, scaleY, sin(glm::radians(rotation)), cos(glm::radians(rotation)));
    glDrawElements(GL_TRIANGLES, m_index_buffer.size, GL_UNSIGNED_INT, nullptr);
}

void Sprite::Render(float m_r, float m_g, float m_b, float m_a, float radius, float Ox, float Oy, 
    float donutness, const glm::vec2& scale, float rotation
) const {
    Select();
    glUniform4f(m_shader_program.ULocOf("givenColor"), m_r, m_g, m_b, m_a);
    glUniform4f(m_shader_program.ULocOf("O_r_donutness"), Ox, Oy, radius, donutness);
    glUniform4f(m_shader_program.ULocOf("scale_sin_cos"), scale.x, scale.y, sin(glm::radians(rotation)), cos(glm::radians(rotation)));
    glDrawElements(GL_TRIANGLES, m_index_buffer.size, GL_UNSIGNED_INT, nullptr);
}

void Sprite::Render(const Color& color) const {
    Render(color.GetR(), color.GetG(), color.GetB(), color.GetA());
}

void Sprite::Render(const Color& color, float width) const {
    Render(color.GetR(), color.GetG(), color.GetB(), color.GetA(), width);
}

void Sprite::Render(const Color& color, float radius, 
    float donutness, const Transform& transform
) const {
    Render(color.GetR(), color.GetG(), color.GetB(), color.GetA(), radius, donutness, transform);
}

void Sprite::Render(const Color& color, float radius,
    const glm::vec2& O, float donutness, const Transform& transform
) const {
    Render(color.GetR(), color.GetG(), color.GetB(), color.GetA(), radius, O, donutness, transform);
}

void Sprite::Render(const Color& color, float radius,
    float Ox, float Oy, float donutness, const Transform& transform
) const {
    Render(color.GetR(), color.GetG(), color.GetB(), color.GetA(), radius, Ox, Oy, donutness, transform);
}

void Sprite::Render(const Color& color, float radius,
    const glm::vec2& O, float donutness, const glm::vec2& scale, float rotation
) const {
    Render(color.GetR(), color.GetG(), color.GetB(), color.GetA(), radius, O, donutness, scale, rotation);
}

void Sprite::Render(const Color& color, float radius,
    float Ox, float Oy, float donutness, float scaleX, float scaleY, float rotation
) const {
    Render(color.GetR(), color.GetG(), color.GetB(), color.GetA(), radius, Ox, Oy, donutness, scaleX, scaleY, rotation);
}

void Sprite::Render(const Color& color, float radius,
    const glm::vec2& O, float donutness, float scaleX, float scaleY, float rotation
) const {
    Render(color.GetR(), color.GetG(), color.GetB(), color.GetA(), radius, O, donutness, scaleX, scaleY, rotation);
}

void Sprite::Render(const Color& color, float radius,
    float Ox, float Oy, float donutness, const glm::vec2& scale, float rotation
) const {
    Render(color.GetR(), color.GetG(), color.GetB(), color.GetA(), radius, Ox, Oy, donutness, scale, rotation);
}

void Sprite::SetMat(const Transform& tf) {
    m_mat = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT);
    m_mat = glm::translate(m_mat, glm::vec3(tf.pos.x, tf.pos.y, 0.0f));
    m_mat = glm::rotate(m_mat, glm::radians(tf.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    m_mat = glm::scale(m_mat, glm::vec3(tf.scale.x, tf.scale.y, 1.0f));
}

void Sprite::SetMat(const glm::mat4& mat) {
    m_mat = mat;
}

void Sprite::TransformMat(const Transform& transformation) {
    m_mat = glm::translate(m_mat, glm::vec3(transformation.pos.x, transformation.pos.y, 0.0f));
    m_mat = glm::rotate(m_mat, glm::radians(transformation.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    m_mat = glm::scale(m_mat, glm::vec3(transformation.scale.x, transformation.scale.y, 1.0f));
}

void Sprite::SetVertexBuffer(uint32_t id) {
    assert(glIsBuffer(id) && "invalid vertex buffer id");

    glDeleteBuffers(1, &m_vertex_buffer.id);
    m_vertex_buffer.id = id;
}

void Sprite::SetIndexBuffer(uint32_t id) {
    assert(glIsBuffer(id) && "invalid index buffer id");

    glDeleteBuffers(1, &m_index_buffer.id);
    m_index_buffer.id = id;
}
 
void Sprite::SetNewShaders(const std::string_view& vertexShader, const std::string_view& fragmentShader) {
    glDeleteProgram(m_shader_program.id);
    m_shader_program = GL::ShaderProgram(vertexShader, fragmentShader);
}

void Sprite::SetShaderProgram(uint32_t id) {
    assert(glIsProgram(id) && "invalid shader program id");

    glDeleteProgram(m_shader_program.id);
    m_shader_program.id = id;
}

void Sprite::SetNewTexture(const std::string_view& filePath, bool flip180) {
    glDeleteTextures(1, &m_texture.id);

    m_texture = GL::Texture(filePath.data(), flip180);
}

void Sprite::SetTexture(uint32_t id) {
    assert(glIsTexture(id) && "invalid texture id");

    glDeleteTextures(1, &m_texture.id);
    m_texture.id = id;
}

void Sprite::SetDistZ(float distZ) {
    assert(distZ < 1.0f && distZ > -1.0f && "distance needs to be normalized");

    m_dist_z = distZ;
}

void Sprite::Validate() const { 
    assert(glIsBuffer(m_vertex_buffer.id)     && "invalid vertex buffer id");
    assert(glIsBuffer(m_index_buffer.id)      && "invalid index buffer id");
    assert(glIsVertexArray(m_array_buffer.id) && "invalid array buffer id");
    assert(glIsTexture(m_texture.id)          && "invalid texture id");
    assert(glIsProgram(m_shader_program.id)   && "invalid shader program id");
}

void Sprite::FreeGPUMemory() const {
    glDeleteBuffers(1, &m_vertex_buffer.id);
    glDeleteBuffers(1, &m_index_buffer.id);
    glDeleteVertexArrays(1, &m_array_buffer.id);
    glDeleteTextures(1, &m_texture.id);
    glDeleteProgram(m_shader_program.id);
}


std::array<float, 4> Sprite::VerticesFor(const Shape::Line& line) noexcept
{
    return std::array<float, 4> {
        line.points[0].x, line.points[0].y,
            line.points[1].x, line.points[1].y
    };
}

std::array<float, 6> Sprite::VerticesFor(const Shape::Triangle& triangle) noexcept
{
    return std::array<float, 6> {
        triangle.points[0].x, triangle.points[0].y,
            triangle.points[1].x, triangle.points[1].y,
            triangle.points[2].x, triangle.points[2].y
    };
}

std::array<float, 8> Sprite::VerticesFor(const Shape::Box& box) noexcept
{
    return std::array<float, 8> {
        box.points[0].x, box.points[0].y,
            box.points[1].x, box.points[1].y,
            box.points[2].x, box.points[2].y,
            box.points[3].x, box.points[3].y
    };
}

std::array<float, 8> Sprite::VerticesFor(const Shape::AABB& aabb) noexcept
{
    return std::array<float, 8> {
        aabb.points[0].x, aabb.points[0].y,
            aabb.points[0].x, aabb.points[1].y,
            aabb.points[1].x, aabb.points[1].y,
            aabb.points[1].x, aabb.points[0].y,
    };
}

std::array<float, 10> Sprite::VerticesFor(const Shape::Pentagon& pentagon) noexcept
{
    return std::array<float, 10> {
        pentagon.points[0].x, pentagon.points[0].y,
            pentagon.points[1].x, pentagon.points[1].y,
            pentagon.points[2].x, pentagon.points[2].y,
            pentagon.points[3].x, pentagon.points[3].y,
            pentagon.points[4].x, pentagon.points[4].y
    };
}

std::array<float, 12> Sprite::VerticesFor(const Shape::Hexagon& hexagon) noexcept
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

std::vector<float> Sprite::VerticesFor(const Shape::Polygon& poly) noexcept
{
    std::vector<float> res = {};
    res.reserve(poly.pointsSize() * 2);

    for (uint32_t i = 0; i < poly.pointsSize(); i++)
    {
        res.emplace_back(poly.points[i].x);
        res.emplace_back(poly.points[i].y);
    }

    return res;
}

std::array<float, 8> Sprite::VerticesFor(const Shape::Circle& cir) noexcept
{
    return std::array<float, 8> {
        cir.points[0].x - cir.m_r, cir.points[0].y + cir.m_r,
            cir.points[0].x - cir.m_r, cir.points[0].y - cir.m_r,
            cir.points[0].x + cir.m_r, cir.points[0].y - cir.m_r,
            cir.points[0].x + cir.m_r, cir.points[0].y + cir.m_r
    };
}

std::array<float, 4> Sprite::VerticesFor(const Shape::Line& line, bool rot90)  noexcept {
    return VerticesFor(line);
}

std::array<float, 6> Sprite::VerticesFor(const Shape::Triangle& triangle, bool rot90)  noexcept {
    return VerticesFor(triangle);
}

std::array<float, 16> Sprite::VerticesFor(const Shape::Box& box, bool rot90) noexcept
{
    if (!rot90) {
        return std::array<float, 16> {
            box.points[0].x, box.points[0].y, POSITIONS_1
                box.points[1].x, box.points[1].y, POSITIONS_2
                box.points[2].x, box.points[2].y, POSITIONS_3
                box.points[3].x, box.points[3].y, POSITIONS_5
        };
    }
    else {
        return std::array<float, 16> {
            box.points[0].x, box.points[0].y, POSITIONS_1
                box.points[1].x, box.points[1].y, POSITIONS_2_90
                box.points[2].x, box.points[2].y, POSITIONS_3
                box.points[3].x, box.points[3].y, POSITIONS_5_90
        };
    }
}

std::array<float, 16> Sprite::VerticesFor(const Shape::AABB& aabb, bool rot90) noexcept
{
    if (!rot90) {
        return std::array<float, 16> {
            aabb.points[0].x, aabb.points[0].y, POSITIONS_1
                aabb.points[0].x, aabb.points[1].y, POSITIONS_2
                aabb.points[1].x, aabb.points[1].y, POSITIONS_3
                aabb.points[1].x, aabb.points[0].y, POSITIONS_5
        };
    }
    else {
        return std::array<float, 16> {
            aabb.points[0].x, aabb.points[0].y, POSITIONS_1
                aabb.points[0].x, aabb.points[1].y, POSITIONS_2_90
                aabb.points[1].x, aabb.points[1].y, POSITIONS_3
                aabb.points[1].x, aabb.points[0].y, POSITIONS_5_90
        };
    }
}

std::array<float, 10> Sprite::VerticesFor(const Shape::Pentagon& pentagon, bool rot90)  noexcept {
    return VerticesFor(pentagon);
}

std::array<float, 12> Sprite::VerticesFor(const Shape::Hexagon& hexagon, bool rot90)  noexcept {
    return VerticesFor(hexagon);
}

std::vector<float> Sprite::VerticesFor(const Shape::Polygon& poly, bool rot90)  noexcept {
    return VerticesFor(poly);
}

std::array<float, 8> Sprite::VerticesFor(const Shape::Circle& cir, bool rot90)  noexcept {
    return VerticesFor(cir);
}

std::array<uint32_t, 6> Sprite::IndicesFor(const Shape::Box& box) noexcept
{
    return std::array<uint32_t, 6> {
        0, 1, 2, 2, 3, 0
    };
}

std::array<uint32_t, 6> Sprite::IndicesFor(const Shape::AABB& aabb) noexcept
{
    return std::array<uint32_t, 6> {
        0, 1, 2, 2, 3, 0
    };
}

std::array<uint32_t, 9> Sprite::IndicesFor(const Shape::Pentagon& pentagon) noexcept
{
    return std::array<uint32_t, 9> {
        0, 1, 2, 3, 4, 0, 0, 2, 3
    };
}

std::array<uint32_t, 12> Sprite::IndicesFor(const Shape::Hexagon& hexagon) noexcept
{
    return std::array<uint32_t, 12> {
        0, 1, 2, 2, 3, 4, 2, 0, 5, 2, 4, 5
    };
}

std::array<uint32_t, 6> Sprite::IndicesFor(const Shape::Circle& cir) noexcept
{
    return std::array<uint32_t, 6> {
        0, 1, 2, 2, 3, 0
    };
}
