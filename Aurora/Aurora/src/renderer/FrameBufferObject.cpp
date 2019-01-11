#include "FrameBufferObject.h"

#include "Texture.h"

namespace aurora
{
	FrameBufferAttachment::FrameBufferAttachment(AttachmentType type)
		: type_(type)
	{
	}

	FrameBufferAttachment::~FrameBufferAttachment()
	{

	}

	TextureBufferAttachment::TextureBufferAttachment(AttachmentType type,const TexturePtr& texture)
		:FrameBufferAttachment(type)
	{

	}

	TextureBufferAttachment::~TextureBufferAttachment()
	{

	}

	void TextureBufferAttachment::AttachToFBO(GLuint fbo,uint32_t index)
	{
		switch (type_)
		{
		case AttachmentType::kColor:
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index,texture_->type(),texture_->id(),0);
			break;
		case AttachmentType::kDepth:
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture_->type(), texture_->id(),0);
			break;
		case AttachmentType::kStencil:
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT,texture_->type(), texture_->id(),0);
			break;
		case AttachmentType::kDepthStencil:
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, texture_->type(), texture_->id(),0);
			break;
		default:
			break;
		}
	}

	RenderBufferAttachment::RenderBufferAttachment(AttachmentType type, uint32_t width, uint32_t height)
		:FrameBufferAttachment(type)
	{
		glGenRenderbuffers(1, &rbo_);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo_);
		
		switch (type)
		{
		case AttachmentType::kColor:
			glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, width_, height_);
			break;
		case AttachmentType::kDepth:
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width_, height_);
			break;
		case AttachmentType::kStencil:
			glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX, width_, height_);
			break;
		case AttachmentType::kDepthStencil:
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL, width_, height_);
			break;
		default:
			break;
		}

		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	RenderBufferAttachment::~RenderBufferAttachment()
	{
		glDeleteRenderbuffers(1, &rbo_);
	}

	void RenderBufferAttachment::AttachToFBO(GLuint fbo,uint32_t index)
	{
		switch (type_)
		{
		case AttachmentType::kColor:
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_RENDERBUFFER, rbo_);
			break;
		case AttachmentType::kDepth:
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo_);
			break;
		case AttachmentType::kStencil:
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo_);
			break;
		case AttachmentType::kDepthStencil:
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo_);
			break;
		default:
			break;
		}
	}


	FrameBufferObject::FrameBufferObject()
	{
		glGenFramebuffers(1, &id_);
	}

	FrameBufferObject::~FrameBufferObject()
	{
		glDeleteFramebuffers(1, &id_);
	}

	bool FrameBufferObject::IsComplete()
	{
		// 检查是否完整
		// 
		//	附加至少一个缓冲（颜色、深度或模板缓冲）。
		//	至少有一个颜色附件(Attachment)。
		//	所有的附件都必须是完整的（保留了内存）。
		//	每个缓冲都应该有相同的样本数。
		return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
	}

	void FrameBufferObject::Bind()
	{
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &old_fbo_);
		glBindFramebuffer(GL_FRAMEBUFFER, id_);
	}

	void FrameBufferObject::UnBind()
	{
		if (old_fbo_ < 0)
		{
			glBindFramebuffer(GL_FRAMEBUFFER,old_fbo_);
		}
		else
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}	
	}

	void FrameBufferObject::AttachAttachment(const FrameBufferAttachment& attachment)
	{
		
	}

	void FrameBufferObject::DeattchAttachment(const FrameBufferAttachment& attachment)
	{
		
	}
}

