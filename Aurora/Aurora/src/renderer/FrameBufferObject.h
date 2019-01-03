#ifndef FRAME_BUFFER_OBJECT_H_
#define FRAME_BUFFER_OBJECT_H_

#include "OGLSupport.h"

namespace aurora
{
	class FrameBufferAttachment
	{
	public:
		enum class AttachmentType
		{
			kColor,
			kDepth,
			kStencil,
			kDepthStencil
		};

		FrameBufferAttachment(AttachmentType type, uint32_t width, uint32_t height);
		virtual ~FrameBufferAttachment();

		virtual void AttachToFBO(GLuint fbo,uint32_t index) = 0;

		AttachmentType type() const { return type_; }
		uint32_t width() const { return width_; }
		uint32_t height() const{ return height_; }
	protected:
		AttachmentType type_;
		uint32_t width_;
		uint32_t height_;
		GLenum attach_type_;
	};


	// 纹理附件 
	class TextureBufferAttachment : public FrameBufferAttachment
	{
	public:
		TextureBufferAttachment(AttachmentType type, uint32_t width, uint32_t height);
		virtual ~TextureBufferAttachment();

		void AttachToFBO(GLuint fbo,uint32_t index) override;
	private:
		GLuint tex_;
	};

	// 渲染附件
	class RenderBufferAttachment : public FrameBufferAttachment
	{
	public:
		RenderBufferAttachment(AttachmentType type, uint32_t width, uint32_t height);
		virtual ~RenderBufferAttachment();

		void AttachToFBO(GLuint fbo,uint32_t index) override;
	private:
		GLuint rbo_;
	};

	class FrameBufferObject
	{
	public:
		FrameBufferObject();
		~FrameBufferObject();

		// 检查FBO是否可用
		bool IsComplete();

		void Bind();
		void UnBind();

		void AttachAttachment(const FrameBufferAttachment& attachment);
		void DeattchAttachment(const FrameBufferAttachment& attachment);

		GLuint fbo() const { return fbo_; }
	private:
		GLuint fbo_;
		GLint old_fbo_;
		bool is_valid_;
	};
}

#endif
