#pragma once

#include <cstdint>
#include "BufferLayout.h"
#include "VertexBuffer.h"

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void add_buffer(const BufferLayout& layout, const VertexBuffer& vb);

	void Bind() const;
	void Unbind() const;

private:
	uint32_t m_RendererID = 0;
	uint32_t m_VertexBufferIndex = 0;
};