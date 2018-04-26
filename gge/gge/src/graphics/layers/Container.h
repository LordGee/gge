#pragma once

#include "../renderers/Renderer2D.h"
#include "../renderables/Renderable2D.h"

namespace gge
{
	namespace graphics
	{
		class Container {
		protected:
			Renderer2D *				m_Renderer;
			std::vector<Renderable2D*>	m_Renderables;
			Shader*						m_Shader;
			maths::Matrix				m_ProjectionMatrix;

		public:
			Container(Shader* shader);
			Container(Shader* shader, maths::Matrix projectionMatrix);
			Container(Renderer2D* renderer, Shader* shader, maths::Matrix projectionMatrix);

			virtual ~Container();
			virtual void AddToContainer(Renderable2D* renderable);
			virtual void RenderThisContainer();

			inline const std::vector<Renderable2D*>& GetRenderables() const { return m_Renderables; }

		private:
			void SetupShader();

		};
	}
}