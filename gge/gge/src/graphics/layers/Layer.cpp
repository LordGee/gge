#include "Layer.h"

namespace gge
{
	namespace graphics
	{
		Layer::Layer(Renderer2D* renderer, Shader* shader, maths::Matrix projectionMatrix)
			: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix) {
			m_Shader->Enable();
			m_Shader->SetUniformMatrix("pr_matrix", m_ProjectionMatrix);
			GLint textureIDs[] = {
				0,1,2,3,4,5,6,7,8,9,
				10,11,12,13,14,15,16,17,18,19,
				20,21,22,23,24,25,26,27,28,29,
				30,31
			};
			m_Shader->SetUniform1iv("textures", 32, textureIDs);
			m_Shader->Disable();
		}

		Layer::~Layer() {
			delete m_Shader;
			delete m_Renderer;
			for (int i = 0; i < m_Renderables.size(); i++) {
				delete m_Renderables[i];
			}
		}

		void Layer::Add(Renderable2D* renderable) {
			m_Renderables.push_back(renderable);
		}

		void Layer::Render() {
			m_Shader->Enable();
			m_Renderer->Begin();
			for (const Renderable2D* renderable : m_Renderables) {
				renderable->Submit(m_Renderer);
			}
			m_Renderer->End();
			m_Renderer->Flush();
		}
	}
}