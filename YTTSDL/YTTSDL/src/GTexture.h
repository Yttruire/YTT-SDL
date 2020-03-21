#pragma once
#include <SDL.h>

//Texture wrapper for GraphicsHandler
//Note: Passing all four individual values is faster if no nullptr passed in (No check for nullptr)
class GTexture
{
private:
	SDL_Rect* m_srcrect;
	SDL_Rect* m_dstrect;
	SDL_Texture* m_texture;

public:
	//Available constructors
	GTexture(const SDL_Rect* srcrect, const SDL_Rect* dstrect, SDL_Texture* texture);
	GTexture(int src_x, int src_y, int src_w, int src_h, int dst_x, int dst_y, int dst_w, int dst_h, SDL_Texture* texture);

	GTexture(const GTexture& texture) = delete; //Disable copy constructor
	GTexture(GTexture&& texture); //Move constructor allowed
	void operator= (const GTexture& texture) = delete; //Disable copy assignment
	void operator= (GTexture&& texture) = delete; //Disable move assignment

	~GTexture();

	void changeSrcRect(int src_x, int src_y, int src_w, int src_h);
	void changeSrcRect(const SDL_Rect* srcrect);
	void changeDstRect(int dst_x, int dst_y, int dst_w, int dst_h);
	void changeDstRect(const SDL_Rect* dstrect);

	SDL_Texture* getTexture() { return m_texture; }
	SDL_Rect* getSrcrect() { return m_srcrect; }
	SDL_Rect* getDstrect() { return m_dstrect; }
	int getSrcrectx() { return m_srcrect->x; }
	int getSrcrecty() { return m_srcrect->y; }
	int getSrcrecth() { return m_srcrect->h; }
	int getSrcrectw() { return m_srcrect->w; }
	int getDstrectx() { return m_dstrect->x; }
	int getDstrecty() { return m_dstrect->y; }
	int getDstrecth() { return m_dstrect->h; }
	int getDstrectw() { return m_dstrect->w; }

};

