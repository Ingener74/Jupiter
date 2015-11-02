using System;

namespace Ananke
{
	public class MainClass: MonoGLo
	{
		public static Game game;

		public static Game init()
		{
			JupiterCSHARP.startJupiter ();

			var width = 800;
			var height = 480;

			glViewport (0, 0, width, height);
			glEnable (GL_TEXTURE_2D);
			glEnable (GL_DEPTH_TEST);
			glEnable (GL_BLEND);
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			File.setBase("../../../samples/Box");

			var shader = new FileShader(new File("Resources/sprite.vs"), new File("Resources/sprite.fs"));

			var bgImage   = new PngImage("Resources/bg.png");
			var bg        = new Transform();
			bg.translate(0, 0, -1);
			bg.setScaleF(0.02f);
			bg.addNode(new Sprite(new ImageTexture(bgImage), new ImageShape(bgImage), shader));

			var rootNode = new Node();

			var cameraTrans = new Transform(0, 0, -20);
			var camera = new Camera(cameraTrans, new Perspective(45.0f, width * 1.0f / height * 1.0f, 1.0f, 1000.0f));
			camera.addNode(cameraTrans);
			camera.addNode(bg);

			rootNode.addNode(camera);

			var game = new Game();
			game.setRootNode(rootNode);
			game.addVisitor(new RenderVisitor());
			game.setWidth(width);
			game.setHeight(height);

			return game;
		}

		public static void display()
		{
			glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor (0.1f, 0.3f, 0.1f, 1.0f);

			game.draw ();

			glutSwapBuffers ();
		}

		public static void reshape(int w, int h)
		{
			glViewport(0, 0, w, h);
		}

		public static void Main (string[] args)
		{
			if (args.Length == 0)
			{
				args=new string [1];
				args[0]="Material.exe";
			}

			int argc=args.Length;
			glutInit(ref argc, args);	
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
			glutInitWindowSize(800, 480);       
			glutCreateWindow("Ananke - C# game player");
			game = init();
			glutDisplayFunc(new GlutDisplayFuncCallback(display));
			glutReshapeFunc(new GlutReshapeFuncCallback(reshape));	 
			glutMainLoop();

			JupiterCSHARP.endJupiter ();
		}
	}
}

