#pragma once

#include "../renderables/Renderable2D.h"

namespace gge
{
	namespace graphics
	{
		class Group : public Renderable2D {
		private:
			std::vector<Renderable2D*>		m_Children;
			maths::Matrix					m_TransformationMatrix;

		public:
			Group(const maths::Matrix& transform);
			~Group();
			void Add(Renderable2D* renderable);
			void Submit(Renderer2D* renderer) const override;
		};
	}
}