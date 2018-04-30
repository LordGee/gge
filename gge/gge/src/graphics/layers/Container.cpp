#include "Container.h"
#include "../renderers/BatchRenderer.h"

namespace gge
{
	namespace graphics
	{
		Container::Container(Shader* shader) 
			: m_Shader(shader) 
		{
			m_Renderer = new BatchRenderer();
			m_ProjectionMatrix = maths::Matrix::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f);
			SetupShader();
		}

		Container::Container(Shader* shader, maths::Matrix projectionMatrix)
			: m_Shader(shader), m_ProjectionMatrix(projectionMatrix)
		{
			m_Renderer = new BatchRenderer();
			SetupShader();
		}

		Container::Container(Renderer* renderer, Shader* shader, maths::Matrix projectionMatrix)
			: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix) 
		{
			SetupShader();
		}

		Container::~Container() {
			delete m_Shader;
			delete m_Renderer;
			for (int i = 0; i < m_Renderables.size(); i++) {
				delete m_Renderables[i];
			}
		}

		void Container::AddToContainer(Renderable* renderable) {
			m_Renderables.push_back(renderable);
		}

		void Container::RenderThisContainer() {
			m_Shader->Enable();
			m_Renderer->Begin();
			for (const Renderable* renderable : m_Renderables) {
				renderable->Submit(m_Renderer);
			}
			m_Renderer->End();
			m_Renderer->Flush();
		}

		void Container::SetupShader() {
			m_Shader->Enable();
			m_Shader->SetUniformMatrix("pr_matrix", m_ProjectionMatrix);
			GLint textureID[] = {
				0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
				10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
				20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
				30, 31
			};
			m_Shader->SetUniform1iv("textures", 32, textureID);
			m_Shader->Disable();
		}
	}
}
