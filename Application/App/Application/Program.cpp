#include "PreCompile.h"
#include "App.h"

int main(int argc, char *argv[])
{
	// Start the application
	App::GetInstance()->Start(argc, argv);

	// Stop the application
	App::GetInstance()->Stop();

	return 0;
}
