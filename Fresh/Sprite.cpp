#include "Sprite.h"

void Sprite::Select() const  
{
	m_array_buffer.Select();
	m_shader_program.Select();
    glUniformMatrix4fv(m_shader_program.ULocOf("m_mat"), 1, GL_FALSE, &m_mat[0][0]);
    glUniform1f(m_shader_program.ULocOf("m_dist_z"), m_dist_z);
	m_texture.Select();
}

void Sprite::Render() const  
{
    Select();
    glDrawElements(GL_TRIANGLES, m_indices_size, GL_UNSIGNED_INT, nullptr);
}

void Sprite::Render(float r, float g, float b, float a) const 
{
    Select();
    glUniform4f(m_shader_program.ULocOf("givenColor"), r, g, b, a);
    glDrawElements(GL_TRIANGLES, m_indices_size, GL_UNSIGNED_INT, nullptr);
}

void Sprite::Render(float r, float g, float b, float a, float width) const 
{
    glLineWidth(width);
    Select();
    glUniform4f(m_shader_program.ULocOf("givenColor"), r, g, b, a);
    glDrawArrays(GL_LINES, 0, 2);
}

void Sprite::Render(float r, float g, float b, float a, float radius, float donutness, const Transform& transform) const
{
    Select();
    glUniform4f(m_shader_program.ULocOf("givenColor"), r, g, b, a);
    glUniform4f(m_shader_program.ULocOf("O_r_donutness"), transform.pos.x, transform.pos.y, radius, donutness);
    glUniform4f(m_shader_program.ULocOf("scale_sin_cos"), transform.scale.x, transform.scale.y,
        sin(glm::radians(transform.rotation)), cos(glm::radians(transform.rotation)));
    glDrawElements(GL_TRIANGLES, m_indices_size, GL_UNSIGNED_INT, nullptr);
}

void Sprite::Render(float r, float g, float b, float a, float radius, const glm::vec2& O, float donutness, const Transform& transform) const
{
    Select();
    glUniform4f(m_shader_program.ULocOf("givenColor"), r, g, b, a);
    glUniform4f(m_shader_program.ULocOf("O_r_donutness"), O.x, O.y, radius, donutness);
    glUniform4f(m_shader_program.ULocOf("scale_sin_cos"), transform.scale.x, transform.scale.y,
        sin(glm::radians(transform.rotation)), cos(glm::radians(transform.rotation)));
    glDrawElements(GL_TRIANGLES, m_indices_size, GL_UNSIGNED_INT, nullptr);
}

void Sprite::Render(float r, float g, float b, float a, float radius, float Ox, float Oy, float donutness, const Transform& transform) const
{
    Select();
    glUniform4f(m_shader_program.ULocOf("givenColor"), r, g, b, a);
    glUniform4f(m_shader_program.ULocOf("O_r_donutness"), Ox, Oy, radius, donutness);
    glUniform4f(m_shader_program.ULocOf("scale_sin_cos"), transform.scale.x, transform.scale.y,
        sin(glm::radians(transform.rotation)), cos(glm::radians(transform.rotation)));
    glDrawElements(GL_TRIANGLES, m_indices_size, GL_UNSIGNED_INT, nullptr);
}

void Sprite::Render(float r, float g, float b, float a, float radius, const glm::vec2& O, float donutness, const glm::vec2& scale, float rotation) const
{
    Select();
    glUniform4f(m_shader_program.ULocOf("givenColor"), r, g, b, a);
    glUniform4f(m_shader_program.ULocOf("O_r_donutness"), O.x, O.y, radius, donutness);
    glUniform4f(m_shader_program.ULocOf("scale_sin_cos"), scale.x, scale.y, sin(glm::radians(rotation)), cos(glm::radians(rotation)));
    glDrawElements(GL_TRIANGLES, m_indices_size, GL_UNSIGNED_INT, nullptr);
}

void Sprite::Render(float r, float g, float b, float a, float radius, float Ox, float Oy, float donutness, float scaleX, float scaleY, float rotation) const
{
    Select();
    glUniform4f(m_shader_program.ULocOf("givenColor"), r, g, b, a);
    glUniform4f(m_shader_program.ULocOf("O_r_donutness"), Ox, Oy, radius, donutness);
    glUniform4f(m_shader_program.ULocOf("scale_sin_cos"), scaleX, scaleY, sin(glm::radians(rotation)), cos(glm::radians(rotation)));
    glDrawElements(GL_TRIANGLES, m_indices_size, GL_UNSIGNED_INT, nullptr);
}

void Sprite::Render(float r, float g, float b, float a, float radius, const glm::vec2& O, float donutness, float scaleX, float scaleY, float rotation) const
{
    Select();
    glUniform4f(m_shader_program.ULocOf("givenColor"), r, g, b, a);
    glUniform4f(m_shader_program.ULocOf("O_r_donutness"), O.x, O.y, radius, donutness);
    glUniform4f(m_shader_program.ULocOf("scale_sin_cos"), scaleX, scaleY, sin(glm::radians(rotation)), cos(glm::radians(rotation)));
    glDrawElements(GL_TRIANGLES, m_indices_size, GL_UNSIGNED_INT, nullptr);
}

void Sprite::Render(float r, float g, float b, float a, float radius, float Ox, float Oy, float donutness, const glm::vec2& scale, float rotation) const
{
    Select();
    glUniform4f(m_shader_program.ULocOf("givenColor"), r, g, b, a);
    glUniform4f(m_shader_program.ULocOf("O_r_donutness"), Ox, Oy, radius, donutness);
    glUniform4f(m_shader_program.ULocOf("scale_sin_cos"), scale.x, scale.y, sin(glm::radians(rotation)), cos(glm::radians(rotation)));
    glDrawElements(GL_TRIANGLES, m_indices_size, GL_UNSIGNED_INT, nullptr);
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

constexpr const Sprite::Type Sprite::GetType() const noexcept {
    return m_type;
}

constexpr const GL::ArrayBuffer& Sprite::GetArrayBuffer() const noexcept {
    return m_array_buffer;
}

constexpr const GL::VertexBuffer& Sprite::GetVertexBuffer() const noexcept {
    return m_vertex_buffer;
}

constexpr const GL::IndexBuffer& Sprite::GetIndexBuffer() const noexcept {
    return m_index_buffer;
}

constexpr unsigned int Sprite::GetIndicesSize() const noexcept {
    return m_indices_size;
}

constexpr const GL::ShaderProgram& Sprite::GetShaderProgram() const noexcept {
    return m_shader_program;
}

constexpr const GL::Texture& Sprite::GetTexture() const noexcept {
    return m_texture;
}

constexpr float Sprite::GetDistZ() const noexcept {
    return m_dist_z;
}

constexpr const glm::mat4& Sprite::GetMat() const noexcept {
    return m_mat;
}

void Sprite::SetVertexBuffer(unsigned int id) {
    assert(glIsBuffer(id) && "invalid vertex buffer id");

    glDeleteBuffers(1, &m_vertex_buffer.id);
    m_vertex_buffer.id = id;
}

void Sprite::SetIndexBuffer(unsigned int id) {
    assert(glIsBuffer(id) && "invalid index buffer id");

    glDeleteBuffers(1, &m_index_buffer.id);
    m_index_buffer.id = id;
}
 
void Sprite::SetNewShaders(const std::string_view& vertexShader, const std::string_view& fragmentShader) {
    glDeleteProgram(m_shader_program.id);
    m_shader_program = GL::ShaderProgram(vertexShader, fragmentShader);
}

void Sprite::SetShaderProgram(unsigned int id) {
    assert(glIsProgram(id) && "invalid shader program id");

    glDeleteProgram(m_shader_program.id);
    m_shader_program.id = id;
}

void Sprite::SetNewTexture(const std::string_view& filePath, bool flip180) {
    glDeleteTextures(1, &m_texture.id);

    m_texture = GL::Texture(filePath.data(), flip180);
}

void Sprite::SetTexture(unsigned int id) {
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
