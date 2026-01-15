#include "ParticleSystem.h"
#include "Utility.h"

#include <glm/glm.hpp>
#include <iostream>

static const float s_QuadVertices[] = {
	-0.5f, -0.5f, 0.3f, 0.0f, 0.0f,	// Bottom Left
	 0.5f, -0.5f, 0.6f, 1.0f, 0.0f,	// Bottom Right
	 0.5f,  0.5f, 0.2f, 1.0f, 1.0f,	// Top Right
	-0.5f,  0.5f, 0.8f, 0.0f, 1.0f	// Bottom Right
};

static const uint32_t s_QuadIndices[] = {
	0, 1, 2,
	2, 3, 0
};

ParticleSystem::ParticleSystem(uint32_t maxParticles)
	:m_PoolIndex(maxParticles - 1)
{
	m_ParticlePool.resize(maxParticles);

	m_InstanceBuffer = new ParticleInstanceData[maxParticles];

	m_QuadVA = std::make_unique<VertexArray>();

	m_QuadVBO = std::make_unique<VertexBuffer>(s_QuadVertices, sizeof(s_QuadVertices));

	BufferLayout quadLayout;
	quadLayout.push_floats(3);
	quadLayout.push_floats(2);

	m_QuadVA->add_buffer(quadLayout, *m_QuadVBO);

	m_InstanceVBO = std::make_unique<VertexBuffer>(nullptr, 
		maxParticles * sizeof(ParticleInstanceData), GL_DYNAMIC_DRAW);

	BufferLayout instanceLayout;

	instanceLayout.push_floats_instanced(3);
	instanceLayout.push_floats_instanced(4);
	instanceLayout.push_floats_instanced(1);
	instanceLayout.push_floats_instanced(1);

	m_QuadVA->add_buffer(instanceLayout, *m_InstanceVBO);

	m_QuadEBO = std::make_unique<IndexBuffer>(s_QuadIndices, 6);
}

ParticleSystem::~ParticleSystem()
{
	delete[] m_InstanceBuffer;
}

void ParticleSystem::OnUpdate(float ts)
{
	
	uint32_t active_count = 0;

	ParticleInstanceData* buffer_ptr = m_InstanceBuffer;

	for (auto& particle : m_ParticlePool) {

		if (!particle.Active) {
			continue;
		}

		if (particle.LifeRemaining <= 0.0f) {
			particle.Active = false;
			continue;
		}


		particle.Position += particle.Velocity * ts;
		particle.Rotation += 0.01 * ts * Random::Float(-5.0f, 5.0f);

		particle.Velocity.y -= 9.8 * ts;
		particle.Velocity *= 0.98;

		particle.LifeRemaining -= ts;

		float life = static_cast<float>(1.0) - (particle.LifeRemaining / particle.LifeTime);

		glm::vec4 color = glm::mix(particle.ColorBegin, particle.ColorEnd, life);

		float size = glm::mix(particle.SizeBegin, particle.SizeEnd, life);

		buffer_ptr->Position = particle.Position;
		buffer_ptr->Color = color;
		buffer_ptr->Size = size;
		buffer_ptr->Rotation = particle.Rotation;

		buffer_ptr++;
		active_count++;
	}

	m_active_Count = active_count;

	uint32_t data_size = m_active_Count * sizeof(ParticleInstanceData);
	m_InstanceVBO->update_data(m_InstanceBuffer, data_size);
}

void ParticleSystem::OnRender(Shader& shader, Camera& camera, float fov)
{
	if (m_active_Count == 0) {
		return;
	}

	shader.use();
	shader.set_mat4("u_View", camera.look_at());
	shader.set_mat4("u_Projection", glm::perspective(glm::radians(fov), camera.m_aspect_ratio, 0.1f, 100.0f));

	m_QuadVA->Bind();

	glDrawElementsInstanced(GL_TRIANGLES, m_QuadEBO->get_count(), GL_UNSIGNED_INT, nullptr, m_active_Count);

	m_QuadVA->Unbind();
}

void ParticleSystem::Emit(ParticleProps& particleProps)
{
	m_active_Count = 0;
	Particle& particle =		m_ParticlePool[m_PoolIndex];

	particle.Active =			true;
	particle.Position =			particleProps.Position;

	particle.ColorBegin =		particleProps.ColorBegin;
	particle.ColorEnd =			particleProps.ColorEnd;
	
	particle.SizeBegin =		particleProps.SizeBegin + particleProps.SizeVariation * (Random::Float() -  0.5f);
	particle.SizeEnd =			particleProps.SizeEnd;

	particle.LifeTime =			particleProps.LifeTime;
	particle.LifeRemaining =	particleProps.LifeTime;

	particle.Velocity =			particleProps.Velocity;

	particle.Velocity.x +=		particleProps.VelocityVariation.x * (Random::Float() - 0.5f);
	particle.Velocity.y +=		particleProps.VelocityVariation.y * (Random::Float() - 0.5f);
	particle.Velocity.z +=		particleProps.VelocityVariation.z * (Random::Float() - 0.5f);
	
	particle.Rotation =			Random::Float() * 2.0f * 3.14159f;

	m_PoolIndex--;

	if (m_PoolIndex >= m_ParticlePool.size()) {
		m_PoolIndex = m_ParticlePool.size() - 1;
	}
}