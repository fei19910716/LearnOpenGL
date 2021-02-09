#include "SkyBox.h"

void SkyBox::load(const std::string imagePath)
{
	std::string front = imagePath + "front.bmp";
	front_ = Texture::createTexture(front,true);

	std::string back = imagePath + "back.bmp";
	back_ = Texture::createTexture(back, true);

	std::string left = imagePath + "left.bmp";
	left_ = Texture::createTexture(left, true);

	std::string right = imagePath + "right.bmp";
	right_ = Texture::createTexture(right, true);

	std::string top = imagePath + "top.bmp";
	top_ = Texture::createTexture(top, true);

	std::string bottom = imagePath + "bottom.bmp";
	bottom_ = Texture::createTexture(bottom, true);
}

void SkyBox::draw(float x, float y, float z)
{
	glEnable(GL_CULL_FACE);
	//绘制天空盒需要关闭深度测试，让天空盒纹理总是绘制在最远处
	glDisable(GL_DEPTH_TEST); 
	//关闭灯光，因为没有指定normal
	glDisable(GL_LIGHTING);

	glPushMatrix();
	glTranslatef(x, y, z);

	// front
	glBindTexture(GL_TEXTURE_2D, front_->textureID_);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();

	// left
	glBindTexture(GL_TEXTURE_2D, left_->textureID_);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

	glEnd();

	// right
	glBindTexture(GL_TEXTURE_2D, right_->textureID_);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);

	glEnd();

	// top
	glBindTexture(GL_TEXTURE_2D, top_->textureID_);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

	glEnd();

	// bottom
	glBindTexture(GL_TEXTURE_2D, bottom_->textureID_);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);

	glEnd();

	// back
	glBindTexture(GL_TEXTURE_2D, back_->textureID_);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);

	glEnd();

	glPopMatrix();
}
