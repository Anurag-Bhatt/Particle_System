#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdint>
#include <filesystem>

namespace fs = std::filesystem;

class Shader {

public:

	Shader(fs::path vertex_shader_path, fs::path fragment_shader_path);

	// To use the shader
	void use() const;

	uint32_t get_id() const;

	// utility uniform functions
	void set_bool(const std::string& name, bool value) const;
	void set_int(const std::string& name, int32_t value) const;
	void set_float(const std::string& name, float value) const;

	// TODO: More utility functions for setting uniforms and matrices
	
	void set_vec4(const std::string& name, const glm::vec4 & values) const;
	void set_vec4(const std::string& name, float x, float y, float z, float w) const;

	void set_mat4(const std::string& name, const glm::mat4& values) const;

private:

	void check_compilation(uint32_t id, std::string_view type) const;

	uint32_t m_id = 0;
};
