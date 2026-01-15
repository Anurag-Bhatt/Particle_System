#pragma once

#include <glad/glad.h>
#include <cstdint>
#include <vector>

struct BufferElement {

	uint32_t type;
	uint32_t count;
	bool normalized;
	bool instanced;

	BufferElement(uint32_t _type, uint32_t _count, bool _normalized = false, bool _instanced = false)
		:type(_type), count(_count), normalized(_normalized), instanced(_instanced) {}

	static uint32_t get_size_of_type(uint32_t type) {
		
		switch (type)
		{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
		}
		return 0;
	}
};

class BufferLayout {
public:
	
	inline void push_floats(uint32_t count) 
	{
		m_Elements.push_back({ GL_FLOAT, count, false, false});
		m_Stride += count * BufferElement::get_size_of_type(GL_FLOAT);
	}

	inline void push_floats_instanced(uint32_t count) {

		m_Elements.push_back({ GL_FLOAT, count, false, true});
		m_Stride += count * BufferElement::get_size_of_type(GL_FLOAT);
	}

	inline const std::vector<BufferElement>& get_elements() const {
		return m_Elements;
	}

	inline uint32_t get_stride() const {
		return m_Stride;
	}

private:
	std::vector<BufferElement> m_Elements;
	uint32_t m_Stride = 0;
};