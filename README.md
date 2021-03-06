# ZombieSurvival
A sandbox survival game where the player needs to fight off waves of zombies, made for the Artificial Intelligence Assessment and with AIE's OpenGL bootstrap.
![Zombie Survival](https://lachlanwernert.com/images/Zombie%20Survival.PNG)


## AI Behavior Tree Diagram 
![AI Behavior Diagram](https://user-images.githubusercontent.com/43165818/144357054-b49051f7-3beb-4e96-a86d-261496b401f1.png)

# aieBootstrap
The base project code used for the Advanced Diploma of Professional Game Development to aid in graphical real-time applications.

Bootstrap is a static library that can be linked against to implement real-time graphical applications with OpenGL as the base API.

To build and run projects ensure that Bootstrap is the first project built, and ensure you have set the Working Directory to the bin folder, i.e. <b>"$(SolutionDir)bin\"</b>.

Provided is VS2015 project templates that can create a basic 2D project, and another for a 3D project. These are within the Tools sub-folder as .zip files. Add these to your Visual Studio Project Template directory, i.e <b>"C:/Users/<i>username</i>/Documents/Visual Studio 2015/Templates/ProjectTemplates/Visual C++ Project/"</b>.

Alternatively, to create an application simply derive from the ```aie::Application``` class like so:
```c++
class MyApplication : public aie::Application {
public:

	MyApplication();
	virtual ~MyApplication();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

};
```
Then implement a ```main()``` function to create an instance of your application:
```c++
int main() {
	
	auto app = new MyApplication();
	// window title, dimensions and if it is fullscreen
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}
```
The ```run()``` method implements a game loop that executes in the following manner:
```
  if startup() is true then
    while quit is false
      update()
      draw()
  shutdown()
```

# Tutorial Videos

<b>Creating your Git Repo using aieBootstrap</b>

[![Video: Creating your Git Repo using aieBootstrap](https://i.vimeocdn.com/video/629137423.webp?mw=600&amp;mh=450)](https://vimeo.com/213005085/3609374652)



<b>Getting Started with aieBootstrap</b>

[![Video: Getting Started with aieBootstrap](https://i.vimeocdn.com/video/629873947.webp?mw=600&amp;mh=450)](https://vimeo.com/213607377/77c8867175)

