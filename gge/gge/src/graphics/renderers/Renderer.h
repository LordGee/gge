#pragma once

#include "../../maths/Maths.h"
#include <vector>
#include "../fonts/Font.h"

namespace gge
{
	namespace graphics
	{
		class Renderable;

		class Renderer {
		protected:
			std::vector<maths::Matrix>		m_TransformationStack;
			const maths::Matrix*			m_TransformationBack;

		protected:
			Renderer() {
				/* Add an identity matrix to the transformation stack */
				m_TransformationStack.push_back(maths::Matrix::identity());
				/* Transformation back holds a reference of the last element added to the stack */
				m_TransformationBack = &m_TransformationStack.back();
			}

		public:
			void Push(const maths::Matrix& matrix, bool override = false) {
				if (override) {
					/* Adds a new matrix to the back of the stack array */
					m_TransformationStack.push_back(matrix);
				} else {
					/* Adds a new matrix timed by the last element addedto the back of the stack array */
					/* This was going to be for the Group class, just not been added successfully yet :( */
					m_TransformationStack.push_back(m_TransformationStack.back() * matrix);
				}
				/* Updat the transform back value */
				m_TransformationBack = &m_TransformationStack.back();
			}

			void Pop() {
				/* remove the last element added to the transoformation stack */
				if (m_TransformationStack.size() > 1) {
					m_TransformationStack.pop_back();
				}
				/* Update the transformation back with the previous last element */
				m_TransformationBack = &m_TransformationStack.back();
			}

			virtual void Begin() {}
			virtual void Submit(const Renderable* renderable) = 0;
			virtual void SubmitText(const std::string& text, const maths::Vector3& position, const Font& font, unsigned int colour) {}
			virtual void End() {}
			virtual void Flush() = 0;
		};
	}
}
