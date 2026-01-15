#include "Shader.h"

Shader::Shader(fs::path vertex_shader_path, fs::path fragment_shader_path)
{

	// Reading files
	if (!fs::exists(vertex_shader_path) or !fs::exists(fragment_shader_path)) {
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n";
		return;
	}

	std::ifstream vertex_shader_file;
	std::ifstream fragment_shader_file;

	// Not sure what this does
	vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragment_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	vertex_shader_file.open(vertex_shader_path);
	fragment_shader_file.open(fragment_shader_path);

	std::stringstream vertex_stream, fragment_stream;

	vertex_stream << vertex_shader_file.rdbuf();
	fragment_stream << fragment_shader_file.rdbuf();

	vertex_shader_file.close();
	fragment_shader_file.close();

	std::string vertex_code = vertex_stream.str();
	std::string fragment_code = fragment_stream.str();

	const char* vertex_source_code = vertex_code.c_str();
	const char* fragment_source_code = fragment_code.c_str();

	// Compiling Shaders
	uint32_t vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader_id, 1, &vertex_source_code, NULL);
	glCompileShader(vertex_shader_id);

	uint32_t fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader_id, 1, &fragment_source_code, NULL);
	glCompileShader(fragment_shader_id);

	// Check shader compilation
	check_compilation(vertex_shader_id	, "SHADER");
	check_compilation(fragment_shader_id, "SHADER");

	// Program
	m_id = glCreateProgram();
	glAttachShader(m_id, vertex_shader_id);
	glAttachShader(m_id, fragment_shader_id);

	glLinkProgram(m_id);

	// Check program compilation
	check_compilation(m_id, "PROGRAM");

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);
}

void Shader::use() const
{
	glUseProgram(m_id);
}

uint32_t Shader::get_id() const
{
	return m_id;
}

void Shader::set_bool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::set_int(const std::string& name, int32_t value) const
{
	glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::set_float(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::set_vec4(const std::string& name, const glm::vec4& values) const
{
	glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, glm::value_ptr(values));
}

void Shader::set_vec4(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(m_id, name.c_str()), x, y, z, w);
}

void Shader::set_mat4(const std::string& name, const glm::mat4& values) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(values));
}

void Shader::check_compilation(uint32_t id, std::string_view type) const
{
	int32_t success;
	char info_log[512];

	if (type == "SHADER") {

		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(id, 512, NULL, info_log);
			std::cerr << "ERROR::SHADER::"<<id<<"::COMPILATION_FAILED\n" <<
				info_log << "\n";
		};
	}
	else if (type == "PROGRAM") {
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(id, 512, NULL, info_log);
			std::cerr << "ERROR::PROGRAM::"<<id<<"::LINKING_FAILED\n" <<
				info_log << std::endl;
		}
	}
	else {
		std::cerr << "ERROR UNIDENTIFIED TYPE\n";
	}
}
