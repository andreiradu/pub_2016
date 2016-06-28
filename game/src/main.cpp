
#undef main
#include <Engine/System/System.h>

int main(int argc, char **argv)
{
	auto system = new Engine::System();
	system->Init({ 1024, 768, "Test" });
	system->Start();
	return 0;
}