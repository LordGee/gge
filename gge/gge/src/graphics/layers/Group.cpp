#include "Group.h"

namespace gge
{
	namespace graphics
	{
		Group::Group(const maths::Matrix& transform)
			: m_TransformationMatrix(transform) {}

		void Group::Add(Renderable2D* renderable) {
			m_Children.push_back(renderable);
		}

		void Group::Submit(Renderer2D* renderer) const {
			renderer->Push(m_TransformationMatrix);
			for (const Renderable2D* renderable : m_Children) {
				renderable->Submit(renderer);
			}
			renderer->Pop();
		}
	}
}