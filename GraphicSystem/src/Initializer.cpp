#include "../include/Initializer.h"

#include <stdlib.h>
#include <stdio.h>

namespace graphic_system_lib
{
	int Initializer::init(bool close_instantly)
	{
		int res = glfwInit();
		if (close_instantly)
		{
			if (res)
				return res;
			else
			{
				printf("GLFW initializion was failed");
				exit(1);
			}
		}
		else
			return res;
	}

	Initializer Initializer::m_Instance;
}
