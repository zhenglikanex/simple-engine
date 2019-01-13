#ifndef FRAME_BUFFER_OBJECT_H_
#define FRAME_BUFFER_OBJECT_H_

#include "OGLSupport.h"
#include "AuroraDef.h"

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

		FrameBufferAttachment(AttachmentType type);
		virtual ~FrameBufferAttachment();

		virtual void AttachToFBO(GLuint fbo,uint32_t index) = 0;

		AttachmentType type() const { return type_; }
	protected:
		AttachmentType type_;
		GLenum attach_type_;
	};


	// 纹理附件 
	class TextureBufferAttachment : public FrameBufferAttachment
	{
	public:
		TextureBufferAttachment(AttachmentType type,const TexturePtr& texture);
		virtual ~TextureBufferAttachment();

		void AttachToFBO(GLuint fbo,uint32_t index) override;
	private:
		TexturePtr texture_;
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
		uint32_t width_;
		uint32_t height_;
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

		void AttachAttachment(const FrameBufferAttachmentPtr& attachment,uint32_t index = 0);
		//void DeattchAttachment(const FrameBufferAttachmentPtr& attachment);

		GLuint id() const { return id_; }
	private:
		GLuint id_;
		GLint old_fbo_;
		bool is_valid_;
	};
}

#endif
