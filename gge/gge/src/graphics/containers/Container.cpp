#include "Container.h"
#include "../renderers/BatchRenderer.h"

namespace gge
{
	namespace graphics
	{
		Container::Container(Shader* shader) 
			: m_Shader(shader) 
		{
			/* Create a default batch renderer */
			m_Renderer = new BatchRenderer();
			/* Create a default projection matrix */
			// TODO: Add a portrait projection matrix to the constructor
			m_ProjectionMatrix = maths::Matrix::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f);
			/* Setup the the shader with the projection matrix & texture ids */
			SetupShader();
		}

		Container::Container(Shader* shader, maths::Matrix projectionMatrix)
			: m_Shader(shader), m_ProjectionMatrix(projectionMatrix)
		{
			/* Create a default batch renderer */
			m_Renderer = new BatchRenderer();
			/* Setup the the shader with the projection matrix & texture ids */
			SetupShader();
		}

		Container::Container(Renderer* renderer, Shader* shader, maths::Matrix projectionMatrix)
			: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix) 
		{
			/* Setup the the shader with the projection matrix & texture ids */
			SetupShader();
		}

		Container::~Container() {
			/* Remove shader from memory */
			delete m_Shader;
			/* Remove rendere from the memory */
			delete m_Renderer;
			/* Iterate through each renderable and remove */
			for (int i = 0; i < m_Renderables.size(); i++) {
				delete m_Renderables[i];
			}
		}

		void Container::AddToContainer(Renderable* renderable) {
			/* Add a renderable to the Container array */
			m_Renderables.push_back(renderable);
		}

		void Container::RenderThisContainer() {
			/* Enable the shader */
			m_Shader->Enable();
			/* Start up the renderer */
			m_Renderer->Begin();
			/* Iterate through each renderable item and submit it to the renderer */
			for (const Renderable* renderable : m_Renderables) {
				renderable->Submit(m_Renderer);
			}
			/* End the render process */
			m_Renderer->End();
			/* Finalise the render */
			m_Renderer->Flush();
		}

		void Container::SetupShader() {
			/* Enable the shader reasdy for use*/
			m_Shader->Enable();
			/* Set the shader to include the projection matrix */
			m_Shader->SetUniformMatrix("pr_matrix", m_ProjectionMatrix);
			/* Define a selection of texture ID's that can be used (MAX = 32) */
			GLint textureID[] = {
				0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
				10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
				20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
				30, 31
			};
			/* Assign the texture IDs to the shader */
			m_Shader->SetUniform1iv("textures", 32, textureID);
			/* Disable the shader ready for next use */
			m_Shader->Disable();
		}
	}
}
