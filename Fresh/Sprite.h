#pragma once
#include "Transform.h"
#include "GL.h"

//TODO:
//      Specialized Sprite classes - Sprite, Texture, BatchSpr, BatchTex, AnimationSpr, AnimationTex, SprtWithFBO(with reading pixels for outout from shaders)
//      data return for debug from the shaders
// 
// TODO in order: 

class Sprite {
public:
	enum Type {
		None = 0, ColoredLine, ColoredTri, ColoredShape, ColoredCircle, ColoredTfCir, Texture,
        StaticColoredLine, StaticColoredTri, StaticColoredShape, StaticColoredCircle, StaticColoredTfCir, StaticTexture
	};

    enum VertexShader {
        DefaultV = 0, TransformedV = 2, TexturedV = 6
    };

    enum FragmentShader {
        DefaultF = 1, ColoredF = 3, TexturedF = 7, ColoredCirF = 4, ColoredTransformedCirF = 5
    };

    template <class VertexArr, class IndexArr>
    inline Sprite(const VertexArr& vertices, float m_dist_z, const IndexArr& indices, bool isStatic,
        const std::string_view& vertexShader, const std::string_view& fragmentShader, Type type, const std::string_view& filePath = std::string_view(),
        bool flipVerticaly = true, const glm::mat4& m_mat = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT),
        unsigned int pLoc = 0, unsigned int pflPerVertex = 2, unsigned int pstride = 0, unsigned int pbeginOffset = 0,
        unsigned int pLoc2 = 0, unsigned int pflPerVertex2 = 2, unsigned int pstride2 = 0, unsigned int pbeginOffset2 = 0, 
        unsigned int m_indices_size = 6
    )
        : m_array_buffer(), m_vertex_buffer(vertices, isStatic), m_dist_z(m_dist_z),m_index_buffer(indices, isStatic),
            m_shader_program(vertexShader, fragmentShader), m_texture(filePath.data(), flipVerticaly), m_mat(m_mat),
            m_indices_size(indices.size()), m_type(type)
    {
        m_vertex_buffer.AssignPointer(pLoc, pflPerVertex,
            pstride * sizeof(float), (void*)(pbeginOffset * sizeof(float))
        );

        m_vertex_buffer.AssignPointer(pLoc2, pflPerVertex2,
            pstride2 * sizeof(float), (void*)(pbeginOffset2 * sizeof(float))
        );
    }

    template <class VertexArr>
    inline Sprite(const VertexArr& vertices, float m_dist_z, bool isStatic,
        const std::string_view& vertexShader, const std::string_view& fragmentShader, Type type, const std::string_view& filePath = std::string_view(),
        bool flipVerticaly = true, const glm::mat4& m_mat = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT),
        unsigned int pLoc = 0, unsigned int pflPerVertex = 2, unsigned int pstride = 0, unsigned int pbeginOffset = 0
    )
        : m_array_buffer(), m_vertex_buffer(vertices, isStatic), m_dist_z(m_dist_z),
            m_shader_program(vertexShader, fragmentShader), m_texture(filePath.data(), flipVerticaly),
            m_mat(m_mat), m_indices_size(0), m_type(type)
    {
        m_vertex_buffer.AssignPointer(pLoc, pflPerVertex,
            pstride * sizeof(float), (void*)(pbeginOffset * sizeof(float))
        );
    }

    template <typename HitBoxType>
    inline Sprite(Sprite::Type type, const HitBoxType& hitBox, float dist_z, const std::string_view& filePath = std::string_view()
    )
        : m_array_buffer(), m_vertex_buffer(VertexBufferBasedOnType(type, false, hitBox)),
            m_index_buffer(IndexBufferBasedOnType(type, hitBox)), m_indices_size(Transform::IndicesFor(hitBox).size()),
            m_shader_program(ShaderProgramBasedOnType(type)), m_texture(filePath.data(), true), m_dist_z(dist_z),
            m_mat(glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT)), m_type(type) {
    }

    inline ~Sprite() { 
        FreeGPUMemory(); 
    }

public:
    void Select() const;

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

    template<typename VerticesContainer, typename IndicesContainer>
    inline void ReplaceBufferesContents(const VerticesContainer& aVBO, const IndicesContainer& aIBO) const {
        glBindVertexArray(m_array_buffer.id);

        glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer.id);
        glBufferSubData(GL_ARRAY_BUFFER, 0, aVBO.size() * sizeof(float), aVBO.data());

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer.id);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, aIBO.size() * sizeof(float), aIBO.data());
    }

    template<typename VerticesContainer, typename IndicesContainer>
    inline void ReplaceBuffers(const VerticesContainer& aVBO, const IndicesContainer& aIBO) const {
        glBindVertexArray(m_array_buffer.id);

        glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer.id);
        glBufferData(GL_ARRAY_BUFFER, aVBO.size() * sizeof(float), aVBO.data(), GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer.id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, aIBO.size() * sizeof(unsigned int), aIBO.data(), GL_DYNAMIC_DRAW);
    }

    constexpr const Type GetType() const noexcept;

    constexpr const GL::ArrayBuffer& GetArrayBuffer() const noexcept;

    constexpr const GL::VertexBuffer& GetVertexBuffer() const noexcept;

    constexpr const GL::IndexBuffer& GetIndexBuffer() const noexcept;

    constexpr unsigned int GetIndicesSize() const noexcept;

    constexpr const GL::ShaderProgram& GetShaderProgram() const noexcept;

    constexpr const GL::Texture& GetTexture() const noexcept;

    constexpr float GetDistZ() const noexcept;

    constexpr const glm::mat4& GetMat() const noexcept;

    template<typename VerticesContainer>
    void SetVertexBufferData(const VerticesContainer& vertices, unsigned int location = 0, unsigned int flPerVertex = 2, unsigned int stride = 2 * sizeof(float), void* beginOffset = (void*)0) const {
        glBindVertexArray(m_array_buffer.id);

        glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer.id);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

        m_vertex_buffer.AssignPointer(location, flPerVertex, stride, beginOffset);
    }

    void SetVertexBuffer(unsigned int id);

    template<typename IndicesContainer>
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
    Type m_type;

	GL::ArrayBuffer m_array_buffer;
    GL::VertexBuffer m_vertex_buffer;
    GL::IndexBuffer m_index_buffer;
    unsigned int m_indices_size;

	GL::ShaderProgram m_shader_program;
	GL::Texture m_texture;

    float m_dist_z;
    glm::mat4 m_mat;

private:
    template <typename HitBoxType>
    static inline GL::VertexBuffer VertexBufferBasedOnType(Type type, float rot90, const HitBoxType& hitbox) {
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

    template <typename HitBoxType>
    static inline GL::IndexBuffer IndexBufferBasedOnType(Type type, const HitBoxType& hitBox) {
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
            assert(false && "construction of sprite type none or unknown");
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
            return GL::ShaderProgram(s_premade_shaders.at(VertexShader::TransformedV), s_premade_shaders.at(FragmentShader::ColoredF));

        case Type::ColoredCircle:
        case Type::StaticColoredCircle:
            return GL::ShaderProgram(s_premade_shaders.at(VertexShader::TransformedV), s_premade_shaders.at(FragmentShader::ColoredCirF));

        case Type::ColoredTfCir:
        case Type::StaticColoredTfCir:
            return GL::ShaderProgram(s_premade_shaders.at(VertexShader::TransformedV), s_premade_shaders.at(FragmentShader::ColoredTransformedCirF));

        case Type::Texture:
        case Type::StaticTexture:
            return GL::ShaderProgram(s_premade_shaders.at(VertexShader::TexturedV), s_premade_shaders.at(FragmentShader::TexturedF));

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
