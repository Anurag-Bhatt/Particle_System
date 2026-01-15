#include <glad/glad.h>
#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::add_buffer(const BufferLayout& layout, const VertexBuffer& vb)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.get_elements();
	uint32_t offset = 0;
	for (uint32_t i = 0; i < elements.size(); ++i) {
		const auto& element = elements[i];
		glVertexAttribPointer(m_VertexBufferIndex, element.count, element.type, element.normalized, layout.get_stride(), (const void*)(uintptr_t)offset);
		glEnableVertexAttribArray(m_VertexBufferIndex);

		if (element.instanced) {
			glVertexAttribDivisor(m_VertexBufferIndex, 1);
		}
		else {
			glVertexAttribDivisor(m_VertexBufferIndex, 0);
		}

		offset += element.count * BufferElement::get_size_of_type(element.type);
		m_VertexBufferIndex++;
	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
