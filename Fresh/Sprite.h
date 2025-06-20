#pragma once
#include "Transform.h"
#include "Shape.h"
#include "GL.h"
#include <algorithm> 
#include <concepts>

#ifdef _DEBUG
    #include <iostream>
#endif //_DEBUG

//TODO: 
//      optional - add support for textures for none 4 sided polygons 
//      check what cannot be inherited from immidiately 
//      SetCoorsToGetImageAt not tested
// 
//      finalize Sprite class
//          write debugging tools
//              #ifdef _DEBUG with printing, warnings and asserts
//          test
//              compare every function with the expected value and go trough edge cases
// 
//      Specialized Sprite classes:
//          DynamicSpr, Animation, FBOSpr(with reading pixels for output from shaders)

class Color {
public:
    inline constexpr Color() noexcept : m_r(0), m_g(0), m_b(0), m_a(1) {}

    inline constexpr Color(float r, float g, float b, float a)
        : m_r(std::clamp(r, 0.0f, 1.0f)), m_g(std::clamp(g, 0.0f, 1.0f)), 
        m_b(std::clamp(b, 0.0f, 1.0f)), m_a(std::clamp(a, 0.0f, 1.0f)) {
    }

    _NODISCARD inline constexpr float GetR() const noexcept { return m_r; }

    _NODISCARD inline constexpr float GetG() const noexcept { return m_g; }

    _NODISCARD inline constexpr float GetB() const noexcept { return m_b; }

    _NODISCARD inline constexpr float GetA() const noexcept { return m_a; }

    inline constexpr void SetColor(float r, float g, float b, float a) noexcept {
        m_r = r; m_g = g; m_b = b; m_a = a;

#ifdef _DEBUG
        if (r > 1 || g > 1 || b > 1 || a > 1 ||
            r < 0 || g < 0 || b < 0 || a < 0
        ) {
            std::cout << "[WARNING]: value passed to SetColor(4f) needs normalization" << '\n';
        }
#endif //_DEBUG

        Normalize();
    }

    inline constexpr void SetColor(const Color& color) noexcept {
        m_r = color.m_r; 
        m_g = color.m_g;
        m_b = color.m_b;
        m_a = color.m_a;

#ifdef _DEBUG
        if (color.m_r > 1 || color.m_g > 1 || color.m_b > 1 || color.m_a > 1 ||
            color.m_r < 0 || color.m_g < 0 || color.m_b < 0 || color.m_a < 0
            ) {
            std::cout << "[WARNING]: value passed to SetColor(const Color&) needs normalization" << '\n';
        }
#endif //_DEBUG

        Normalize();
    }

    inline constexpr void Normalize() noexcept {
        m_r = std::clamp(m_r, 0.0f, 1.0f);
        m_g = std::clamp(m_g, 0.0f, 1.0f);
        m_b = std::clamp(m_b, 0.0f, 1.0f);
        m_a = std::clamp(m_a, 0.0f, 1.0f);
    }

    _NODISCARD inline constexpr bool operator==(const Color& color) const noexcept {
        return (
            m_r == color.m_r && 
            m_g == color.m_g && 
            m_b == color.m_b && 
            m_a == color.m_a 
        );
    };

    _NODISCARD inline constexpr Color operator*(float scaler) const noexcept {
        Color res(m_r * scaler, m_g * scaler, m_b * scaler, m_a);

#ifdef _DEBUG
        if (res.m_r > 1 || res.m_g > 1 || res.m_b > 1 ||
            res.m_r < 0 || res.m_g < 0 || res.m_b < 0
            ) {
            std::cout << "[WARNING]: scaled value needs normalization" << '\n';
        }
#endif //_DEBUG

        res.Normalize();

        return res;
    }

    inline constexpr const Color& operator*=(float scaler) noexcept {
        m_r *= scaler;
        m_g *= scaler;
        m_b *= scaler;

#ifdef _DEBUG
        if (m_r > 1 || m_g > 1 || m_b > 1 ||
            m_r < 0 || m_g < 0 || m_b < 0
            ) {
            std::cout << "[WARNING]: scaled values need normalization" << '\n';
        }
#endif //_DEBUG

        Normalize();

        return *this;
    }

#ifdef _DEBUG
    void Print() const;

    static inline constexpr void Test() {
#pragma warning(push)
#pragma warning(disable: 4305) //double to float shrunkation for testing

        constexpr Color col1;
        constexpr Color col2(1.0, 1.0f, 1, 1);
        constexpr Color col3(-1.0, 10, 0.0003, 1.0f);

        static_assert(col1 == Color(0, 0, 0, 1), "default constructor");
        static_assert(col2 == Color(1, 1, 1, 1), "basic constructor");
        static_assert(col3 == Color(0.0f, 1.0f, 0.0003f, 1.0f), "edge constructor");

        static_assert(col3.GetR() == col3.m_r, "getter m_r");
        static_assert(col3.GetG() == col3.m_g, "getter m_g");
        static_assert(col3.GetB() == col3.m_b, "getter m_b");
        static_assert(col3.GetA() == col3.m_a, "getter m_a");

        Color col3Copy1 = col3, col3Copy2 = col3;

        col3Copy1.SetColor(col3Copy1);
        assert(col3Copy1 == col3Copy2);

        col3Copy1.SetColor(Color(1, 0, 1, 1));
        assert(col3Copy1 == Color(1, 0, 1, 1) && "color setter");

        col3Copy1.SetColor(1, 0, 0, 1);
        assert(col3Copy1 == Color(1, 0, 0, 1) && "4f setter");

        col3Copy1.SetColor(Color(-10.0f, 1000000000, 0, 0.00003));
        assert(col3Copy1 == Color(0, 1, 0, 0.00003f) && "color setter edge");

        col3Copy1.SetColor(0, 0, 0, 0);

        col3Copy1.SetColor(-10.0f, 1000000000, 0, 0.00003);
        assert(col3Copy1 == Color(0, 1, 0, 0.00003f) && "4f setter edge");

        assert(col3Copy1.GetR() == col3Copy1.m_r && "getter m_r");
        assert(col3Copy1.GetG() == col3Copy1.m_g && "getter m_g");
        assert(col3Copy1.GetB() == col3Copy1.m_b && "getter m_b");
        assert(col3Copy1.GetA() == col3Copy1.m_a && "getter m_a");
#pragma warning(pop)
    }
#endif //_DEBUG

private:
    float m_r = 0.0f, m_g = 0.0f, m_b = 0.0f, m_a = 0.0f;
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

    _NODISCARD inline constexpr const glm::vec2& GetPos() const noexcept { return m_pos; }

    _NODISCARD inline constexpr float GetX() const noexcept { return m_x; }

    _NODISCARD inline constexpr float GetY() const noexcept { return m_y; }

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

    _NODISCARD inline constexpr float GetR() const noexcept { return m_r; }

    _NODISCARD inline constexpr float GetG() const noexcept { return m_g; }

    _NODISCARD inline constexpr float GetB() const noexcept { return m_b; }

    _NODISCARD inline constexpr float GetA() const noexcept { return m_a; }

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
    enum class EdgePosRelCenter : uint32_t {
        TopLeft = 0, TopRight,
        BottomLeft, BottomRight
    };

    inline constexpr VertexTexCoords() : m_u(0), m_v(0) {}

    inline constexpr VertexTexCoords( float texCoordU, float texCoordV) : m_u(texCoordU), m_v(texCoordV) {}

    inline constexpr VertexTexCoords(const glm::vec2& texCoords) : m_coords(texCoords) {}

    _NODISCARD inline constexpr const glm::vec2& GetCoords() const noexcept { return m_coords; }

    _NODISCARD inline constexpr const float GetCoordU() const noexcept { return m_u; }

    _NODISCARD inline constexpr const float GetCoordV() const noexcept { return m_v; }

    inline constexpr void SetTexCoords(const glm::vec2& coords) noexcept { 
        m_coords = coords;
        
#ifdef _DEBUG
        if (m_u > 1 || m_u < 0 || m_v > 1 || m_v < 0)
            std::cout << "[WARNING]: values passed to SetTexCoords need normalization" << '\n';
#endif //_DEBUG

        Normalize();
    }

    inline constexpr void SetTexCoords(float u, float v) noexcept {
        m_u = u; m_v = v;
        
#ifdef _DEBUG
        if (m_u > 1 || m_u < 0 || m_v > 1 || m_v < 0)
            std::cout << "[WARNING]: values passed to SetTexCoords need normalization" << '\n';
#endif //_DEBUG

        Normalize();
    }

    inline constexpr void Normalize() noexcept {
        m_u = std::min(std::max(m_u, 0.0f), 1.0f);
        m_v = std::min(std::max(m_v, 0.0f), 1.0f);
    }

    void SetCoorsToGetImageAt(uint32_t index, float texWidth, float texHeight, 
        float sprWidth, float sprHeight, EdgePosRelCenter vertex
    );

    void SetCoorsToGetImageAt(uint32_t index, const glm::vec2& texSpecs,
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

    _NODISCARD inline constexpr const glm::vec3& GetPos() const noexcept { return m_pos; }

    _NODISCARD inline constexpr float GetX() const noexcept { return m_x; }

    _NODISCARD inline constexpr float GetY() const noexcept { return m_y; }

    _NODISCARD inline constexpr float GetZ() const noexcept { return m_z; }

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
    enum class Type : uint32_t {
        None = 0, ColoredLine, ColoredTri, ColoredShape, ColoredCircle, ColoredTfCir, Texture,
        StaticColoredLine, StaticColoredTri, StaticColoredShape, StaticColoredCircle, StaticColoredTfCir, StaticTexture
    };

    enum class VertexShader : uint32_t {
        Default = 0, Transformed = 2, Textured = 6
    };

    enum class FragmentShader : uint32_t {
        Default = 1, Colored = 3, Textured = 7, ColoredCir = 4, ColoredTransformedCir = 5
    };

    template <DataAndSizeContainer VertexContainer, DataAndSizeContainer IndexContainer>
    inline Sprite(const VertexContainer& vertices, const IndexContainer& indices,
        float m_dist_z, bool isStatic,
        const std::string_view& vertexShader, const std::string_view& fragmentShader,
        Type type,
        const std::filesystem::path& filePath = std::filesystem::path(), bool flipVerticaly = true,
        const glm::mat4& m_mat = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT),
        uint32_t pLoc = 0, uint32_t pflPerVertex = 2, uint32_t pstride = 0, uint32_t pbeginOffset = 0,
        uint32_t pLoc2 = 0, uint32_t pflPerVertex2 = 2, uint32_t pstride2 = 0, uint32_t pbeginOffset2 = 0
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
        uint32_t pLoc = 0, uint32_t pflPerVertex = 2, uint32_t pstride = 0, uint32_t pbeginOffset = 0
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
        glBufferSubData(GL_ARRAY_BUFFER, 0, aVBO.size() * sizeof(aVBO.at(0)), aVBO.data());

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer.id);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, aIBO.size() * sizeof(aIBO.at(0)), aIBO.data());
    }

    template<DataAndSizeContainer VerticesContainer, DataAndSizeContainer IndicesContainer>
    inline void ReplaceBuffers(const VerticesContainer& aVBO, const IndicesContainer& aIBO) const {
        glBindVertexArray(m_array_buffer.id);

        glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer.id);
        glBufferData(GL_ARRAY_BUFFER, aVBO.size() * sizeof(aVBO.at(0)), aVBO.data(), GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer.id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, aIBO.size() * sizeof(aIBO.at(0)), aIBO.data(), GL_DYNAMIC_DRAW);
    }

    _NODISCARD constexpr const GL::ArrayBuffer& GetArrayBuffer() const noexcept { return m_array_buffer; }

    _NODISCARD constexpr const GL::VertexBuffer& GetVertexBuffer() const noexcept { return m_vertex_buffer; }

    _NODISCARD constexpr const GL::IndexBuffer& GetIndexBuffer() const noexcept { return m_index_buffer; }

    _NODISCARD constexpr uint32_t GetIndicesSize() const noexcept { return m_index_buffer.size; }

    _NODISCARD constexpr const GL::ShaderProgram& GetShaderProgram() const noexcept { return m_shader_program; }

    _NODISCARD constexpr const GL::Texture& GetTexture() const noexcept { return m_texture; }

    _NODISCARD constexpr float GetDistZ() const noexcept { return m_dist_z; }

    _NODISCARD constexpr const glm::mat4& GetMat() const noexcept { return m_mat; }

    template<DataAndSizeContainer VerticesContainer>
    void SetVertexBufferData(const VerticesContainer& vertices, 
        uint32_t location = 0, uint32_t flPerVertex = 2, 
        uint32_t stride = 2 * sizeof(float), void* beginOffset = (void*)0
    ) const {
        glBindVertexArray(m_array_buffer.id);

        glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer.id);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices.at(0)), 
            vertices.data(), GL_DYNAMIC_DRAW
        );

        m_vertex_buffer.AssignPointer(location, flPerVertex, stride, beginOffset);
    }

    void SetVertexBuffer(uint32_t id);

    template<DataAndSizeContainer IndicesContainer>
    void SetIndexBufferData(const IndicesContainer& indices) const {
        glBindVertexArray(m_array_buffer.id);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer.id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices.at(0)), 
            indices.data(), GL_DYNAMIC_DRAW
        );
    }

    void SetIndexBuffer(uint32_t id);

    void SetNewShaders(const std::string_view& vertexShader, const std::string_view& frammentShader);

    void SetShaderProgram(uint32_t id);

    void SetNewTexture(const std::string_view& filePath, bool flip180);

    void SetTexture(uint32_t id);

    void SetDistZ(float distZ);

    void SetMat(const Transform& tf);

    void SetMat(const glm::mat4& mat);

    void TransformMat(const Transform& transformation);

    void Validate() const;

    void FreeGPUMemory() const;

    _NODISCARD static std::array<float, 4> VerticesFor(const Shape::Line& line) noexcept;

    _NODISCARD static std::array<float, 6> VerticesFor(const Shape::Triangle& triangle) noexcept;

    _NODISCARD static std::array<float, 8> VerticesFor(const Shape::Box& box) noexcept;

    _NODISCARD static std::array<float, 8> VerticesFor(const Shape::AABB& aabb) noexcept;

    _NODISCARD static std::array<float, 10> VerticesFor(const Shape::Pentagon& pentagon) noexcept;

    _NODISCARD static std::array<float, 12> VerticesFor(const Shape::Hexagon& hexagon) noexcept;

    _NODISCARD static std::vector<float> VerticesFor(const Shape::Polygon& poly) noexcept;

    _NODISCARD static std::array<float, 8> VerticesFor(const Shape::Circle& cir) noexcept;

    _NODISCARD static std::array<float, 4> VerticesFor(const Shape::Line& line, bool rot90) noexcept;
    
    _NODISCARD static std::array<float, 6> VerticesFor(const Shape::Triangle& triangle, bool rot90) noexcept;
    
    _NODISCARD static std::array<float, 16> VerticesFor(const Shape::Box& box, bool rot90) noexcept;
    
    _NODISCARD static std::array<float, 16> VerticesFor(const Shape::AABB& aabb, bool rot90) noexcept;
    
    _NODISCARD static std::array<float, 10> VerticesFor(const Shape::Pentagon& pentagon, bool rot90) noexcept;
    
    _NODISCARD static std::array<float, 12> VerticesFor(const Shape::Hexagon& hexagon, bool rot90) noexcept;
    
    _NODISCARD static std::vector<float> VerticesFor(const Shape::Polygon& poly, bool rot90) noexcept;
    
    _NODISCARD static std::array<float, 8> VerticesFor(const Shape::Circle& cir, bool rot90) noexcept;

    _NODISCARD static std::array<uint32_t, 6> IndicesFor(const Shape::Box& box) noexcept;

    _NODISCARD static std::array<uint32_t, 6> IndicesFor(const Shape::AABB& aabb) noexcept;

    _NODISCARD static std::array<uint32_t, 9> IndicesFor(const Shape::Pentagon& pentagon) noexcept;

    _NODISCARD static std::array<uint32_t, 12> IndicesFor(const Shape::Hexagon& hexagon) noexcept;

    _NODISCARD static std::array<uint32_t, 6> IndicesFor(const Shape::Circle& cir) noexcept;

private:
    GL::ArrayBuffer m_array_buffer;
    GL::VertexBuffer m_vertex_buffer;
    GL::IndexBuffer m_index_buffer;

    GL::ShaderProgram m_shader_program;
    GL::Texture m_texture;

    float m_dist_z = 0.0f;
    glm::mat4 m_mat = glm::mat4(1.0f);;

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
            return GL::VertexBuffer(VerticesFor(hitbox), false);

        case Type::StaticColoredLine:
        case Type::StaticColoredTri:
        case Type::StaticColoredShape:
        case Type::StaticColoredCircle:
        case Type::StaticColoredTfCir:
            return GL::VertexBuffer(VerticesFor(hitbox), true);

        case Type::Texture:

            assert(hitbox.Type() == Shape::Types::ShapeAABB || hitbox.Type() == Shape::Types::ShapeBox &&
                "currently supprorted texture vertices for Shape::Box and Shape::AABB");

            return GL::VertexBuffer(VerticesFor(hitbox, rot90), false);

        case Type::StaticTexture:

            assert(hitbox.Type() == Shape::Types::ShapeAABB || hitbox.Type() == Shape::Types::ShapeBox &&
                "currently supprorted texture vertices for Shape::Box and Shape::AABB");

            return GL::VertexBuffer(VerticesFor(hitbox, rot90), true);

        default:
            assert(!"construction of sprite type none or unknown");
            GL::VertexBuffer nullBuffer;
            nullBuffer.id = -1;
            return nullBuffer;
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
            return GL::IndexBuffer(IndicesFor(hitBox), false);

        case Type::StaticColoredLine:
        case Type::StaticColoredTri:
        case Type::StaticColoredShape:
        case Type::StaticColoredCircle:
        case Type::StaticColoredTfCir:
        case Type::StaticTexture:
            return GL::IndexBuffer(IndicesFor(hitBox), true);

        default:
            assert(!"construction of sprite type none or unknown");
            GL::IndexBuffer nullBuffer;
            nullBuffer.id = -1;
            return nullBuffer;
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
                s_premade_shaders.at(static_cast<int32_t>(VertexShader::Transformed)),
                s_premade_shaders.at(static_cast<int32_t>(FragmentShader::Colored))
            );

        case Type::ColoredCircle:
        case Type::StaticColoredCircle:
            return GL::ShaderProgram(
                s_premade_shaders.at(static_cast<int32_t>(VertexShader::Transformed)),
                s_premade_shaders.at(static_cast<int32_t>(FragmentShader::ColoredCir))
            );

        case Type::ColoredTfCir:
        case Type::StaticColoredTfCir:
            return GL::ShaderProgram(
                s_premade_shaders.at(static_cast<int32_t>(VertexShader::Transformed)),
                s_premade_shaders.at(static_cast<int32_t>(FragmentShader::ColoredTransformedCir))
            );

        case Type::Texture:
        case Type::StaticTexture:
            return GL::ShaderProgram(
                s_premade_shaders.at(static_cast<int32_t>(VertexShader::Textured)),
                s_premade_shaders.at(static_cast<int32_t>(FragmentShader::Textured))
            );

        default:
            assert(!"construction of sprite type none or unknown");
            return GL::ShaderProgram("", "");
        }
    }
};

class DynamicSprite  : public Sprite {

};