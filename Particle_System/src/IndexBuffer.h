#pragma once
#pragma once

#include <cstdint>

class IndexBuffer {
public:

	IndexBuffer(const void* data, const uint32_t size, GLenum usage = GL_STATIC_DRAW);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	uint32_t get_count() const;

private:
	uint32_t m_RendererID = 0;
	uint32_t m_Count;
};