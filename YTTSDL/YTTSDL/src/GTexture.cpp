#include "GTexture.h"

GTexture::GTexture(const SDL_Rect* srcrect, const SDL_Rect* dstrect, SDL_Texture* texture)
	: m_texture{ texture }
{
	if (srcrect == nullptr)
	{
		m_srcrect = nullptr;
	}
	else
	{
		m_srcrect = new SDL_Rect(*srcrect);
	}
	if (dstrect == nullptr)
	{
		m_dstrect = nullptr;
	}
	else
	{
		m_dstrect = new SDL_Rect(*dstrect);
	}
	texture = nullptr;
}

GTexture::GTexture(int src_x, int src_y, int src_w, int src_h, int dst_x, int dst_y, int dst_w, int dst_h, SDL_Texture* texture)
	: m_texture{ texture }
{
	m_srcrect = new SDL_Rect{ src_x, src_y, src_w, src_h };
	m_dstrect = new SDL_Rect{ dst_x, dst_y, dst_w, dst_h };
	texture = nullptr;
}

GTexture::GTexture(GTexture&& texture)
{
	m_srcrect = texture.m_srcrect;
	texture.m_srcrect = nullptr;
	m_dstrect = texture.m_dstrect;
	texture.m_dstrect = nullptr;
	m_texture = texture.m_texture;
	texture.m_texture = nullptr;
}

GTexture::~GTexture()
{
	if (m_srcrect)
	{
		delete m_srcrect;
	}
	if (m_dstrect)
	{
		delete m_dstrect;
	}
	if (m_texture)
	{
		SDL_DestroyTexture(m_texture);
	}
}

void GTexture::changeSrcRect(int src_x, int src_y, int src_w, int src_h)
{
	m_srcrect->x = src_x;
	m_srcrect->y = src_y;
	m_srcrect->w = src_w;
	m_srcrect->h = src_h;
}

void GTexture::changeSrcRect(const SDL_Rect* srcrect)
{
	*m_srcrect = *srcrect;
}

void GTexture::changeDstRect(int dst_x, int dst_y, int dst_w, int dst_h)
{
	m_dstrect->x = dst_x;
	m_dstrect->y = dst_y;
	m_dstrect->w = dst_w;
	m_dstrect->h = dst_h;
}

void GTexture::changeDstRect(const SDL_Rect* dstrect)
{
	*m_dstrect = *dstrect;
}