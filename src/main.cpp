#include "context.h"
#include "shader.h"

#include "texture.h"

#include "clock.h"


#include "camera.h"
#include "player.h"
//#include "inputs.h"


//
#include <bx/timer.h>
#include <bx/math.h>
#include "entry/entry.h"
#include "entry/cmd.h"
#include "entry/input.h"
#include <bx/allocator.h>
//



int _main_(int _argc, char** _argv)
{
	Context& context = Context::Instance();
	context.init(_argc, _argv, 1280, 720);
	Model m;
	m.addFace(LEFT_FACE, { 0,0,0 }, { 0,0,0 });
	m.addFace(RIGHT_FACE, { 0,0,0 }, { 0,0,0 });
	m.addFace(TOP_FACE, { 0,0,0 }, { 0,0,0 });
	m.addFace(BOTTOM_FACE, { 0,0,0 }, { 0,0,0 });
	m.addFace(FRONT_FACE, { 0,0,0 }, { 0,0,0 });
	m.addFace(BACK_FACE, { 0,0,0 }, { 0,0,0 });

	m.buffer(&m);

	// model if ^^ before shader, works. hm, well bolls.

	Shader shader("a", "b");

	//Inputs& input = Inputs::Instance();

	Texture tex("res/textures/grass.png");

	Player p;


	while (context.isRunning)
	{
		static Clock clock;
		float dt = clock.restart();

		//inputSetMouseLock(true); // ?que te gusta?

		context.update();
		
		p.update(dt, context.m_mouseState, context.m_state);

		const Camera& cam = p.getCamera();

		shader.loadMatrix(cam);
		shader.loadModelMatrix({ 0,0,-5 });


		tex.bind();
		m.bind();

		shader.use();


		context.draw();
	}

	//context.shutdown();

	return 0;
}
 