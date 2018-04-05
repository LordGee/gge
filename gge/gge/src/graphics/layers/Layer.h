#pragma once

#include "../renderers/Renderer2D.h"
#include "../renderers/Renderable2D.h"

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
			
			Layer(Renderer2D* renderer, Shader* shader, maths::Matrix projectionMatrix);

		public:
			virtual ~Layer();
			virtual void Add(Renderable2D* renderable);
			virtual void Render();

		};
	}
}