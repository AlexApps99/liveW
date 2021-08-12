example:
	clang -o liveW -O2 -flto src/*.c -Wall -lm -lGL -lX11 -lXrender -DGL_GLEXT_PROTOTYPES -DGLX_GLXEXT_PROTOTYPES
