#pragma once
#include <memory>
#include <Engine/Config.h>
#include "CreationSettigns.h"
namespace Engine
{

class SystemImpl;
class ENGINE_API System
{
public:
	System();
	~System();

	void Init(SCreationSettings&& cs);
	void Start();
protected:
	std::unique_ptr<SystemImpl> m_impl;
};

}