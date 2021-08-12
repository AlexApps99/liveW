example:
	clang -o liveW -O2 src/*.c -Wall -Iinclude -lm -lpthread -lGL -lGLU -lX11 -lXrender -DGL_GLEXT_PROTOTYPES -DGLX_GLXEXT_PROTOTYPES
