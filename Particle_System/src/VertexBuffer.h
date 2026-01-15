#pragma once

#include <cstdint>

class VertexBuffer {
public:

	VertexBuffer(const void* data, const uint32_t size, GLenum usage = GL_STATIC_DRAW);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void update_data(const void* data, const uint32_t size) const;

private:
	uint32_t m_RendererID = 0;
};