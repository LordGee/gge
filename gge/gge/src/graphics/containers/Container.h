#pragma once

#include "../renderers/Renderer.h"
#include "../renderables/Renderable.h"

namespace gge
{
	namespace graphics
	{
		class Container {
		protected:
			Renderer *					m_Renderer;
			std::vector<Renderable*>	m_Renderables;
			Shader*						m_Shader;
			maths::Matrix				m_ProjectionMatrix;

		public:
			Container(Shader* shader);
			Container(Shader* shader, maths::Matrix projectionMatrix);
			Container(Renderer* renderer, Shader* shader, maths::Matrix projectionMatrix);

			virtual ~Container();
			virtual void AddToContainer(Renderable* renderable);
			virtual void RenderThisContainer();

			inline const std::vector<Renderable*>& GetRenderables() const { return m_Renderables; }

		private:
			void SetupShader();

		};
	}
}