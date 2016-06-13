
local g1 = require 'glLua'
local g2 = require 'glfwLua'
local g3 = require 'glewLua'
local j = require 'JupiterLua'

if not g2.glfwInit() then
    print ("glfw error")
    g2.glfwTerminate()
end

--g2.glfwWindowHint(g2.GLFW_CONTEXT_VERSION_MAJOR, 3)
--g2.glfwWindowHint(g2.GLFW_CONTEXT_VERSION_MINOR, 3)
--g2.glfwWindowHint(g2.GLFW_OPENGL_PROFILE, g2.GLFW_OPENGL_CORE_PROFILE);
--g2.glfwWindowHint(g2.GLFW_OPENGL_FORWARD_COMPAT, g2.GLFW_OPENGL_COMPAT_PROFILE);

local window = g2.glfwCreateWindow(800, 480, "Дия - плеер игр на Lua для Юпитера", nil, nil)

g2.glfwMakeContextCurrent(window)

ok,res = pcall(function() j.startJupiter() end)
if ok then
    print('init jupiter success')
else
    error('init jupiter error: ' .. res)
end

local width = 800
local height = 480

g1.glViewport(0, 0, width, height)
g1.glEnable(g1.GL_TEXTURE_2D)
g1.glEnable(g1.GL_DEPTH_TEST)
g1.glEnable(g1.GL_BLEND)
g1.glBlendFunc(g1.GL_SRC_ALPHA, g1.GL_ONE_MINUS_SRC_ALPHA)

j.File.setBase('../../../samples/Box')

shader = j.FileShader(j.File('Resources/sprite.vs'), j.File('Resources/sprite.fs'))

bgImage   = j.PngImage('Resources/bg.png')
bg        = j.Transform()
bg:
    translate(0, 0, -1):
    setScaleF(0.022):
    addNode(j.Sprite(j.ImageTexture(bgImage), j.ImageShape(bgImage), shader))

rootNode = j.Node()

cameraTrans = j.Transform(0, 0, -20)
camera   = j.Camera(cameraTrans, j.Perspective(45.0, width * 1. / height * 1., 1.0, 1000.0))
camera:
    addNode(cameraTrans):
    addNode(bg)

rootNode:addNode(camera)

--addVisitor(j.PrintVisitor(game)):

game = j.Game()
game:
    setRootNode(rootNode):
    addVisitor(j.RenderVisitor()):
    setWidth(width):
    setHeight(height)


print('OpenGL Version:                  ' .. g1.glGetString(g1.GL_VERSION))
print('OpenGL Shading Language Version: ' .. g1.glGetString(g1.GL_SHADING_LANGUAGE_VERSION))
print('OpenGL Vendor:                   ' .. g1.glGetString(g1.GL_VENDOR))
print('OpenGL Renderer:                 ' .. g1.glGetString(g1.GL_RENDERER))

while g2.glfwWindowShouldClose(window) do
    g1.glClear(g1.GL_COLOR_BUFFER_BIT + g1.GL_DEPTH_BUFFER_BIT)
    g1.glClearColor(0.1, 0.3, 0.1, 1.)

    game:draw()

    g2.glfwSwapBuffers(window)
    g2.glfwPollEvents()
end

j.endJupiter()

g2.glfwDestroyWindow(window)
g2.glfwTerminate()

print('Good, Bye!!!')
