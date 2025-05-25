#pragma once
#include "elements.h"
#include "renderer.h"

class Window {
	protected:
		
        Window();

		static Smart::Window window;
		static Renderer renderer;

    private:

        static bool isSDLInitialized;    

		void initializeLibraries();
        void allocateUIResources();
};
