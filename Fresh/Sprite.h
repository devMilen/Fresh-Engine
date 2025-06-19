#pragma once
#include "Transform.h"
#include "GL.h"
#include <algorithm> 
#include <concepts>

//TODO: 
//      finalize Sprite class
//          test
//              compare every function with the expected value and go trouhg edge cases
//          write debugging tools
//              #ifdef _DEBUG with printing, warnings and asserts
// 
//      Specialized Sprite classes - Sprite, 
// BatchSpr, Animation, FBOSpr(with reading pixels for outout from shaders)

class Color {
public:
    inline constexpr Color() noexcept : m_r(0), m_g(0), m_b(0), m_a(1) {}

    inline constexpr Color(float r, float g, float b, float a)
        : m_r(std::clamp(r, 0.0f, 1.0f)), m_g(std::clamp(g, 0.0f, 1.0f)), 
        m_b(std::clamp(b, 0.0f, 1.0f)), m_a(std::clamp(a, 0.0f, 1.0f)) {
    }

    inline constexpr float GetR() const noexcept { return m_r; }

    inline constexpr float GetG() const noexcept { return m_g; }

    inline constexpr float GetB() const noexcept { return m_b; }

    inline constexpr float GetA() const noexcept { return m_a; }

    inline constexpr void SetColor(float r, float g, float b, float a) noexcept {
        m_r = r; m_g = g; m_b = b; m_a = a;

        Normalize();
    }

    inline constexpr void SetColor(const Color& color) noexcept {
        *this = color;

        Normalize();
    }

    inline constexpr void Normalize() noexcept {
        m_r = std::clamp(m_r, 0.0f, 1.0f);
        m_g = std::clamp(m_b, 0.0f, 1.0f);
        m_b = std::clamp(m_b, 0.0f, 1.0f);
        m_a = std::clamp(m_a, 0.0f, 1.0f);
    }

    inline constexpr std::partial_ordering operator<=>(const Color&) const noexcept = default;

private:
    float m_r, m_g, m_b, m_a;
};

namespace SpriteColorConstants {
    
    inline constexpr Color g_RED        = Color(1.0f,  0.0f,  0.0f,  1.0f);                                                       
    
    inline constexpr Color g_WHITE      = Color(1.0f,  1.0f,  1.0f,  1.0f);                                                   
    
    inline constexpr Color g_BLUE       = Color(0.0f,  0.0f,  1.0f,  1.0f);                                                       
    
    inline constexpr Color g_ORANGE     = Color(1.0f,  0.5f,  0.0f,  1.0f);                                                       
    
    inline constexpr Color g_BROWN      = Color(0.6f,  0.3f,  0.0f,  1.0f);
    
    inline constexpr Color g_GREEN      = Color(0.0f,  1.0f,  0.0f,  1.0f);                                                       
    
    inline constexpr Color g_BLACK      = Color(0.0f,  0.0f,  0.0f,  1.0f);                                                      
    
    inline constexpr Color g_YELLOW     = Color(1.0f,  1.0f,  0.0f,  1.0f);                                                   
    
    inline constexpr Color g_PURPLE     = Color(0.5f,  0.0f,  0.5f,  1.0f);                                                  
    
    inline constexpr Color g_CYAN       = Color(0.0f,  1.0f,  1.0f,  1.0f);                                                  
    
    inline constexpr Color g_MAGENTA    = Color(1.0f,  0.0f,  1.0f,  1.0f);                                                   
    
    inline constexpr Color g_GRAY       = Color(0.5f,  0.5f,  0.5f,  1.0f);
    
    inline constexpr Color g_DARK_GRAY  = Color(0.25f, 0.25f, 0.25f, 1.0f);
    
    inline constexpr Color g_LIGHT_GRAY = Color(0.75f, 0.75f, 0.75f, 1.0f);
    
    inline constexpr Color g_PINK       = Color(1.0f,  0.75f, 0.8f,  1.0f);
    
    inline constexpr Color g_TEAL       = Color(0.0f,  0.5f,  0.5f,  1.0f);
    
    inline constexpr Color g_NAVY       = Color(0.0f,  0.0f,  0.5f,  1.0f);
    
    inline constexpr Color g_MAROON     = Color(0.5f,  0.0f,  0.0f,  1.0f);
    
    inline constexpr Color g_OLIVE      = Color(0.5f,  0.5f,  0.0f,  1.0f);
}

class VertexPos {
public:
    inline constexpr VertexPos() : m_x(0), m_y(0){}

    inline constexpr VertexPos(const glm::vec2& pos) : m_pos(pos) {}

    inline constexpr VertexPos(float x, float y) : m_x(x), m_y(y) {}

    inline constexpr void Move(const glm::vec2& v) noexcept { m_pos.x += v.x; m_pos.y += v.y; }

    inline constexpr void Move(float vX, float vY) noexcept { m_x += vX; m_y += vY; }

    inline constexpr const glm::vec2& GetPos() const noexcept { return m_pos; }

    inline constexpr float GetX() const noexcept { return m_x; }

    inline constexpr float GetY() const noexcept { return m_y; }

    inline constexpr void SetPos(const glm::vec2& pos) noexcept { m_pos = pos; }

    inline constexpr void SetPos(float x, float y) noexcept { m_x = x; m_y = y; }

private:
    union {
        glm::vec2 m_pos;
        struct { float m_x, m_y; };
    };
};

class VertexColor {
public:
    inline constexpr VertexColor() : m_color() {}

    inline constexpr VertexColor(float r, float g, float b, float a) : m_color(r, g, b, a) {}

    inline constexpr VertexColor(const Color& color) : m_color(color) {}

    inline constexpr float GetR() const noexcept { return m_r; }

    inline constexpr float GetG() const noexcept { return m_g; }

    inline constexpr float GetB() const noexcept { return m_g; }

    inline constexpr float GetA() const noexcept { return m_a; }

    inline constexpr void SetColor(float r, float g, float b, float a) noexcept {
        m_color.SetColor(r, g, b, a);
    }

    inline constexpr void SetColor(const Color& color) noexcept {
        m_color.SetColor(color);
    }

    inline constexpr void Normalize() {
        m_color.Normalize();
    }

private:
    union {
        Color m_color;
        struct {  float m_r, m_g, m_b, m_a; };
    };
};

class VertexTexCoords {
public:
    enum class EdgePosRelCenter : unsigned int {
        TopLeft = 0, TopRight,
        BottomLeft, BottomRight
    };

    inline constexpr VertexTexCoords() : m_u(0), m_v(0) {}

    inline constexpr VertexTexCoords( float texCoordU, float texCoordV) : m_u(texCoordU), m_v(texCoordV) {}

    inline constexpr VertexTexCoords(const glm::vec2& texCoords) : m_coords(texCoords) {}

    inline constexpr const glm::vec2& GetCoords() const noexcept { return m_coords; }

    inline constexpr const float GetCoordU() const noexcept { return m_u; }

    inline constexpr const float GetCoordV() const noexcept { return m_v; }

    inline constexpr void SetTexCoords(const glm::vec2& coords) noexcept { 
        m_coords = coords;
        
        Normalize();
    }

    inline constexpr void SetTexCoords(float u, float v) noexcept {
        m_u = u; m_v = v;
        
        Normalize();
    }

    inline constexpr void Normalize() noexcept {
        std::min(std::max(m_u, 0.0f), 1.0f);
        std::min(std::max(m_v, 0.0f), 1.0f);
    }

    void SetCoorsToGetImageAt(unsigned int index, float texWidth, float texHeight, 
        float sprWidth, float sprHeight, EdgePosRelCenter vertex
    );

    void SetCoorsToGetImageBoxAt(unsigned int index, const glm::vec2& texSpecs,
        const glm::vec2& sprSpecs, EdgePosRelCenter vertex
    );

private:
    union {
        glm::vec2 m_coords;
        struct { float m_u, m_v; };
    };
};

class VertexPos3D {
public:
    inline constexpr VertexPos3D() : m_x(0), m_y(0), m_z(0) {}

    inline constexpr VertexPos3D(const glm::vec3& pos) : m_x(pos.x), m_y(pos.y), m_z(pos.z) {}

    inline constexpr VertexPos3D(float x, float y, float z) : m_x(x), m_y(y), m_z(z) {}

    inline constexpr void Move(const glm::vec3& v) noexcept {
        m_x += v.x; m_y += v.y; m_z += v.z;
    }

    inline constexpr void Move(float vX, float vY, float vZ) noexcept {
        m_x += vX; m_y += vY; m_z += vZ;
    }

    inline constexpr const glm::vec3& GetPos() const noexcept { return m_pos; }

    inline constexpr float GetX() const noexcept { return m_x; }

    inline constexpr float GetY() const noexcept { return m_y; }

    inline constexpr float GetZ() const noexcept { return m_z; }

    inline constexpr void SetPos(const glm::vec3& pos) noexcept { m_pos = pos; }

    inline constexpr void SetPos(float x, float y, float z) noexcept {
        m_x = x; m_y = y; m_z = z;
    }

private:
    union {
        glm::vec3 m_pos;
        struct { float m_x, m_y, m_z; };
    };
};

template <typename T>
concept DataAndSizeContainer = requires(T t) {
    { t.size() } -> std::convertible_to<std::size_t>;
    { t.data() };
};

template <typename T>
concept Hitbox = requires(T t) {
    { std::derived_from<T, Shape::Def> };
};

class Sprite {
public:
    enum class Type : unsigned int {
        None = 0, ColoredLine, ColoredTri, ColoredShape, ColoredCircle, ColoredTfCir, Texture,
        StaticColoredLine, StaticColoredTri, StaticColoredShape, StaticColoredCircle, StaticColoredTfCir, StaticTexture
    };

    enum class VertexShader : unsigned int {
        Default = 0, Transformed = 2, Textured = 6
    };

    enum class FragmentShader : unsigned int {
        Default = 1, Colored = 3, Textured = 7, ColoredCir = 4, ColoredTransformedCir = 5
    };

    template <DataAndSizeContainer VertexContainer, DataAndSizeContainer IndexContainer>
    inline Sprite(const VertexContainer& vertices, const IndexContainer& indices,
        float m_dist_z, bool isStatic,
        const std::string_view& vertexShader, const std::string_view& fragmentShader,
        Type type,
        const std::filesystem::path& filePath = std::filesystem::path(), bool flipVerticaly = true,
        const glm::mat4& m_mat = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT),
        unsigned int pLoc = 0, unsigned int pflPerVertex = 2, unsigned int pstride = 0, unsigned int pbeginOffset = 0,
        unsigned int pLoc2 = 0, unsigned int pflPerVertex2 = 2, unsigned int pstride2 = 0, unsigned int pbeginOffset2 = 0
    )
        : m_array_buffer(), m_vertex_buffer(vertices, isStatic), m_dist_z(m_dist_z), m_index_buffer(indices, isStatic),
        m_shader_program(vertexShader, fragmentShader), m_texture(filePath, flipVerticaly), m_mat(m_mat)
    {
        m_vertex_buffer.AssignPointer(pLoc, pflPerVertex,
            pstride * sizeof(float), (void*)(pbeginOffset * sizeof(float))
        );

        m_vertex_buffer.AssignPointer(pLoc2, pflPerVertex2,
            pstride2 * sizeof(float), (void*)(pbeginOffset2 * sizeof(float))
        );
    }

    template <DataAndSizeContainer VertexContainer>
    inline Sprite(const VertexContainer& vertices,
        float m_dist_z, bool isStatic,
        const std::string_view& vertexShader, const std::string_view& fragmentShader,
        Type type,
        const std::filesystem::path& filePath = std::filesystem::path(), bool flipVerticaly = true,
        const glm::mat4& m_mat = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT),
        unsigned int pLoc = 0, unsigned int pflPerVertex = 2, unsigned int pstride = 0, unsigned int pbeginOffset = 0
    )
        : m_array_buffer(), m_vertex_buffer(vertices, isStatic), m_dist_z(m_dist_z),
        m_shader_program(vertexShader, fragmentShader), m_texture(filePath, flipVerticaly),
        m_mat(m_mat)
    {
        m_vertex_buffer.AssignPointer(pLoc, pflPerVertex,
            pstride * sizeof(float), (void*)(pbeginOffset * sizeof(float))
        );
    }

    template <Hitbox HitboxType>
    inline Sprite(Sprite::Type type, const HitboxType& hitBox, float dist_z, 
        const std::filesystem::path& filePath = std::filesystem::path()
    )
        : m_array_buffer(), m_vertex_buffer(VertexBufferBasedOnType(type, false, hitBox)),
        m_index_buffer(IndexBufferBasedOnType(type, hitBox)),
        m_shader_program(ShaderProgramBasedOnType(type)), m_texture(filePath, true), m_dist_z(dist_z),
        m_mat(glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT))
    {
        m_vertex_buffer.AssignPointer(0, 2,
            2 * sizeof(float), (void*)(0 * sizeof(float))
        );
    }

    virtual inline ~Sprite() {
        FreeGPUMemory();
    }

public:
    virtual void Select() const;

    void Render() const;

    void Render(float r, float g, float b, float a) const;

    void Render(float r, float g, float b, float a, float width) const;

    void Render(float r, float g, float b, float a, float radius, float donutness, const Transform& transform) const;

    void Render(float r, float g, float b, float a, float radius,
        const glm::vec2& O, float donutness, const Transform& transform) const;

    void Render(float r, float g, float b, float a, float radius,
        float Ox, float Oy, float donutness, const Transform& transform) const;

    void Render(float r, float g, float b, float a, float radius,
        const glm::vec2& O, float donutness = 0, const glm::vec2& scale = glm::vec2(0), float rotation = 0.0f) const;

    void Render(float r, float g, float b, float a, float radius,
        float Ox, float Oy, float donutness = 0, float scaleX = 1.0f, float scaleY = 1.0f, float rotation = 0.0f) const;

    void Render(float r, float g, float b, float a, float radius,
        const glm::vec2& O, float donutness = 0, float scaleX = 1.0f, float scaleY = 1.0f, float rotation = 0.0f) const;

    void Render(float r, float g, float b, float a, float radius,
        float Ox, float Oy, float donutness = 0, const glm::vec2& scale = glm::vec2(0), float rotation = 0.0f) const;

    void Render(const Color& color) const;

    void Render(const Color& color, float width) const;

    void Render(const Color& color, float radius, float donutness, const Transform& transform) const;

    void Render(const Color& color, float radius,
        const glm::vec2& O, float donutness, const Transform& transform) const;

    void Render(const Color& color, float radius,
        float Ox, float Oy, float donutness, const Transform& transform) const;

    void Render(const Color& color, float radius,
        const glm::vec2& O, float donutness = 0, const glm::vec2& scale = glm::vec2(0), float rotation = 0.0f) const;

    void Render(const Color& color, float radius,
        float Ox, float Oy, float donutness = 0, float scaleX = 1.0f, float scaleY = 1.0f, float rotation = 0.0f) const;

    void Render(const Color& color, float radius,
        const glm::vec2& O, float donutness = 0, float scaleX = 1.0f, float scaleY = 1.0f, float rotation = 0.0f) const;

    void Render(const Color& color, float radius,
        float Ox, float Oy, float donutness = 0, const glm::vec2& scale = glm::vec2(0), float rotation = 0.0f) const;

    template<DataAndSizeContainer VerticesContainer, DataAndSizeContainer IndicesContainer>
    inline void ReplaceBufferesContents(const VerticesContainer& aVBO, const IndicesContainer& aIBO) const {
        glBindVertexArray(m_array_buffer.id);

        glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer.id);
        glBufferSubData(GL_ARRAY_BUFFER, 0, aVBO.size() * sizeof(float), aVBO.data());

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer.id);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, aIBO.size() * sizeof(float), aIBO.data());
    }

    template<DataAndSizeContainer VerticesContainer, DataAndSizeContainer IndicesContainer>
    inline void ReplaceBuffers(const VerticesContainer& aVBO, const IndicesContainer& aIBO) const {
        glBindVertexArray(m_array_buffer.id);

        glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer.id);
        glBufferData(GL_ARRAY_BUFFER, aVBO.size() * sizeof(float), aVBO.data(), GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer.id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, aIBO.size() * sizeof(unsigned int), aIBO.data(), GL_DYNAMIC_DRAW);
    }

    constexpr const GL::ArrayBuffer& GetArrayBuffer() const noexcept { return m_array_buffer; }

    constexpr const GL::VertexBuffer& GetVertexBuffer() const noexcept { return m_vertex_buffer; }

    constexpr const GL::IndexBuffer& GetIndexBuffer() const noexcept { return m_index_buffer; }

    constexpr unsigned int GetIndicesSize() const noexcept { return m_index_buffer.size; }

    constexpr const GL::ShaderProgram& GetShaderProgram() const noexcept { return m_shader_program; }

    constexpr const GL::Texture& GetTexture() const noexcept { return m_texture; }

    constexpr float GetDistZ() const noexcept { return m_dist_z; }

    constexpr const glm::mat4& GetMat() const noexcept { return m_mat; }

    template<DataAndSizeContainer VerticesContainer>
    void SetVertexBufferData(const VerticesContainer& vertices, 
        unsigned int location = 0, unsigned int flPerVertex = 2, 
        unsigned int stride = 2 * sizeof(float), void* beginOffset = (void*)0
    ) const {
        glBindVertexArray(m_array_buffer.id);

        glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer.id);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

        m_vertex_buffer.AssignPointer(location, flPerVertex, stride, beginOffset);
    }

    void SetVertexBuffer(unsigned int id);

    template<DataAndSizeContainer IndicesContainer>
    void SetIndexBufferData(const IndicesContainer& indices) const {
        glBindVertexArray(m_array_buffer.id);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer.id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);
    }

    void SetIndexBuffer(unsigned int id);

    void SetNewShaders(const std::string_view& vertexShader, const std::string_view& frammentShader);

    void SetShaderProgram(unsigned int id);

    void SetNewTexture(const std::string_view& filePath, bool flip180);

    void SetTexture(unsigned int id);

    void SetDistZ(float distZ);

    void SetMat(const Transform& tf);

    void SetMat(const glm::mat4& mat);

    void TransformMat(const Transform& transformation);

    void Validate() const;

    void FreeGPUMemory() const;

private:
    GL::ArrayBuffer m_array_buffer;
    GL::VertexBuffer m_vertex_buffer;
    GL::IndexBuffer m_index_buffer;

    GL::ShaderProgram m_shader_program;
    GL::Texture m_texture;

    float m_dist_z;
    glm::mat4 m_mat;

private:
    template <Hitbox HitboxType>
    static inline GL::VertexBuffer VertexBufferBasedOnType(
        Type type, float rot90, const HitboxType& hitbox
    ) {
        switch (type) {
        case Type::ColoredLine:
        case Type::ColoredTri:
        case Type::ColoredShape:
        case Type::ColoredCircle:
        case Type::ColoredTfCir:
            return GL::VertexBuffer(Transform::VerticesFor(hitbox), false);

        case Type::StaticColoredLine:
        case Type::StaticColoredTri:
        case Type::StaticColoredShape:
        case Type::StaticColoredCircle:
        case Type::StaticColoredTfCir:
            return GL::VertexBuffer(Transform::VerticesFor(hitbox), true);

        case Type::Texture:
            return GL::VertexBuffer(Transform::VerticesFor(hitbox, rot90), false);

        case Type::StaticTexture:
            return GL::VertexBuffer(Transform::VerticesFor(hitbox, rot90), true);

        default:
            assert(false && "construction of sprite type none or unknown");
        }
    }

    template <Hitbox HitboxType>
    static inline GL::IndexBuffer IndexBufferBasedOnType(Type type, const HitboxType& hitBox) {
        switch (type) {
        case Type::ColoredLine:
        case Type::ColoredTri:
        case Type::ColoredShape:
        case Type::ColoredCircle:
        case Type::ColoredTfCir:
        case Type::Texture:
            return GL::IndexBuffer(Transform::IndicesFor(hitBox), false);

        case Type::StaticColoredLine:
        case Type::StaticColoredTri:
        case Type::StaticColoredShape:
        case Type::StaticColoredCircle:
        case Type::StaticColoredTfCir:
        case Type::StaticTexture:
            return GL::IndexBuffer(Transform::IndicesFor(hitBox), true);

        default:
            assert(!"construction of sprite type none or unknown");
        }
    }

    static inline GL::ShaderProgram ShaderProgramBasedOnType(Type type) {
        switch (type) {
        case Type::ColoredLine:
        case Type::ColoredTri:
        case Type::ColoredShape:
        case Type::StaticColoredLine:
        case Type::StaticColoredTri:
        case Type::StaticColoredShape:
            return GL::ShaderProgram(
                s_premade_shaders.at(static_cast<int>(VertexShader::Transformed)),
                s_premade_shaders.at(static_cast<int>(FragmentShader::Colored))
            );

        case Type::ColoredCircle:
        case Type::StaticColoredCircle:
            return GL::ShaderProgram(
                s_premade_shaders.at(static_cast<int>(VertexShader::Transformed)),
                s_premade_shaders.at(static_cast<int>(FragmentShader::ColoredCir))
            );

        case Type::ColoredTfCir:
        case Type::StaticColoredTfCir:
            return GL::ShaderProgram(
                s_premade_shaders.at(static_cast<int>(VertexShader::Transformed)),
                s_premade_shaders.at(static_cast<int>(FragmentShader::ColoredTransformedCir))
            );

        case Type::Texture:
        case Type::StaticTexture:
            return GL::ShaderProgram(
                s_premade_shaders.at(static_cast<int>(VertexShader::Textured)),
                s_premade_shaders.at(static_cast<int>(FragmentShader::Textured))
            );

        default:
            assert(false && "construction of sprite type none or unknown");
        }
    }

private:
    static inline constexpr const std::array<std::string_view, 8> s_premade_shaders = {
        std::string_view(R"(
            #version 330 core
            layout(location = 0) in vec2 pos;       
            uniform float m_dist_z;
            
            void main() {
                gl_Position = vec4(pos, m_dist_z, 1.0f);
            })"
        ),
        std::string_view(R"(
            #version 330 core
            out vec4 pixelColor;

            void main() {
                pixelColor = vec4(1.0, 1.0, 1.0, 1.0);
            })"
        ),
        std::string_view(R"(
            #version 330 core

            layout (location = 0) in vec2 pos;

            uniform float m_dist_z;
            uniform vec2 offset = vec2(0.0);
            uniform mat4 m_mat;

            void main() {
                gl_Position = m_mat * vec4( pos + offset, m_dist_z, 1.0f );
            })"
        ),
        std::string_view(R"(
            #version 330 core
            out vec4 pixelColor;  
            uniform vec4 givenColor;
            
            void main() {
                pixelColor = givenColor;
            })"
        ),
        std::string_view(R"(
            #version 330 core
            out vec4 finalColor;
        
            uniform vec4 givenColor;
            uniform vec4 O_r_donutness;
        
            void main() {
                finalColor = vec4(0.0);
        
                vec2 PxPosRel00 = gl_FragCoord.xy - O_r_donutness.xy;
                float squaredAdded = PxPosRel00.x*PxPosRel00.x + PxPosRel00.y*PxPosRel00.y;
        
                if(squaredAdded <= O_r_donutness.z*O_r_donutness.z && squaredAdded >= O_r_donutness.w*O_r_donutness.w)
                    finalColor = givenColor;
            })"
        ),
        std::string_view(R"(
            #version 330 core
            out vec4 finalColor;

            uniform vec4 givenColor;
            uniform vec4 O_r_donutness;
            uniform vec4 scale_sin_cos;

            void main() {
                vec2 PxPosRel00 = gl_FragCoord.xy - O_r_donutness.xy;
                PxPosRel00 = vec2(
                    PxPosRel00.x * scale_sin_cos.w - PxPosRel00.y * scale_sin_cos.z,
                    PxPosRel00.x * scale_sin_cos.z + PxPosRel00.y * scale_sin_cos.w
                );

                vec2 safeScale = max(scale_sin_cos.xy, vec2(1e-6));
                PxPosRel00 /= safeScale;

                float sqSum = dot(PxPosRel00, PxPosRel00);

                float outerR2 = O_r_donutness.z * O_r_donutness.z;
                float innerR2 = O_r_donutness.w * O_r_donutness.w;

                if (sqSum <= outerR2 && sqSum >= innerR2)
                    finalColor = givenColor;
                else
                    discard;
            })"
        ),
        std::string_view(R"(
            #version 330 core
        
            layout (location = 0) in vec2 pos;
            layout (location = 1) in vec2 givenTexCoord;
        
            out vec2 texCoord;
            uniform vec2 offset = vec2(0.0);
            uniform float m_dist_z;
            uniform mat4 m_mat = mat4(
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0
            );
        
            void main() {
                gl_Position = m_mat * vec4(pos + offset, m_dist_z, 1.0);
                texCoord = givenTexCoord;
            })"
        ),
        std::string_view(R"(
            #version 330 core
            out vec4 finalColor;
            in vec2 texCoord;
            uniform sampler2D ourTexture;
        
            void main() {
                finalColor = m_texture(ourTexture, texCoord);
            })"
        ),
    };
};
