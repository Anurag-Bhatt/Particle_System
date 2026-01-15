#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Camera.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

struct ParticleProps {
	glm::vec3 Position;
	glm::vec3 Velocity;
	glm::vec3 VelocityVariation;
	glm::vec4 ColorBegin, ColorEnd;
	float SizeBegin, SizeEnd, SizeVariation;
	float LifeTime = 1.0f;
};

class ParticleSystem {
public:
	ParticleSystem(uint32_t maxParticles);
	~ParticleSystem();

	void OnUpdate(float ts);
	void OnRender(Shader& shader, Camera& camera, float fov=45.0f);
	void Emit(ParticleProps& particleProps);

private:
	struct Particle {
		glm::vec3 Position;
		glm::vec3 Velocity;
		glm::vec4 ColorBegin, ColorEnd;
		float Rotation = 0.0;
		float SizeBegin, SizeEnd;
		float LifeTime = 1.0f, LifeRemaining = 0.0f;
		bool Active = false;
	};

	struct ParticleInstanceData {
		glm::vec3 Position;
		glm::vec4 Color;
		float Size;
		float Rotation;
	};

	std::vector<Particle> m_ParticlePool;
	uint32_t m_PoolIndex = 0;

	uint32_t m_active_Count = 0;

	std::unique_ptr<VertexArray>	m_QuadVA;
	std::unique_ptr<VertexBuffer>	m_QuadVBO;
	std::unique_ptr<IndexBuffer>	m_QuadEBO;

	std::unique_ptr<VertexBuffer>	m_InstanceVBO;

	ParticleInstanceData* m_InstanceBuffer = nullptr;
};