#pragma once

#include "../renderers/Renderer2D.h"
#include "../renderables/Renderable2D.h"

namespace gge
{
	namespace graphics
	{
		class Layer {
		protected:
			Renderer2D *				m_Renderer;
			std::vector<Renderable2D*>	m_Renderables;
			Shader*						m_Shader;
			maths::Matrix				m_ProjectionMatrix;

		public:
			Layer(Renderer2D* renderer, Shader* shader, maths::Matrix projectionMatrix);

			virtual ~Layer();
			virtual void Add(Renderable2D* renderable);
			virtual void Render();

			inline const std::vector<Renderable2D*>& GetRenderables() const { return m_Renderables; }
		};
	}
}