# OpenGL
A repository to show my experience learning OpenGL (and how to use Visual Studio too) on Windows.
Principal sourse: learnopengl.com.

So, for me to not forget, first of all I'll write how to set up a new project.
When you create new projects, you need to link the libraries we are using with the projects. This libraries are stored in \Resourses. To do that, go to Project -> Properties -> Configuration Properties -> VC++ Directories, and add the directories routes.

Then, go to Linker -> Input, and add 'glfw3.lib' and 'opengl32.lib'.
