#pragma once

#include "Geomatries/TextureRect.h"

class TestDemo : public IObject
{
public:
	// IObject��(��) ���� ��ӵ�
	void Init() override;
	void Destroy() override;
	void Update() override;
	void Render() override;
	void PostRender() override;
	void GUI() override;

private:
	AnimationRect* ar = nullptr;
};