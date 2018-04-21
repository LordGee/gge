#pragma once

#include "../../maths/Maths.h"
#include <vector>
#include "../fonts/Font.h"

namespace gge
{
	namespace graphics
	{
		class Renderable2D;

		class Renderer2D {
		protected:
			std::vector<maths::Matrix>		m_TransformationStack;
			const maths::Matrix*			m_TransformationBack;
		protected:
			Renderer2D() {
				m_TransformationStack.push_back(maths::Matrix::identity());
				m_TransformationBack = &m_TransformationStack.back();
			}

		public:
			void Push(const maths::Matrix& matrix, bool override = false) {
				if (override) {
					m_TransformationStack.push_back(matrix);
				}
				else {
					m_TransformationStack.push_back(m_TransformationStack.back() * matrix);
				}
				m_TransformationBack = &m_TransformationStack.back();
			}

			void Pop() {
				if (m_TransformationStack.size() > 1) {
					m_TransformationStack.pop_back();
				}
				m_TransformationBack = &m_TransformationStack.back();
			}

			virtual void Begin() {}
			virtual void Submit(const Renderable2D* renderable) = 0;
			virtual void SubmitText(const std::string& text, const maths::Vector3& position, const Font& font, unsigned int colour) {}
			virtual void End() {}
			virtual void Flush() = 0;
		};
	}
}
