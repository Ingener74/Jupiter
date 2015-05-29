
local g1 = require 'glLua'
local g2 = require 'glfwLua'
local g3 = require 'glewLua'
local j = require 'JupiterLua'

if not g2.glfwInit() then
    print ("glfw error")
    g2.glfwTerminate()
end

g2.glfwWindowHint(g2.GLFW_CONTEXT_VERSION_MAJOR, 3)
g2.glfwWindowHint(g2.GLFW_CONTEXT_VERSION_MINOR, 3)
g2.glfwWindowHint(g2.GLFW_OPENGL_PROFILE, g2.GLFW_OPENGL_CORE_PROFILE);
g2.glfwWindowHint(g2.GLFW_OPENGL_COMPAT_PROFILE, g2.GLFW_OPENGL_FORWARD_COMPAT);

local window = g2.glfwCreateWindow(800, 480, "Дия - плеер игр на Lua для Юпитера", nil, nil)

g2.glfwMakeContextCurrent(window)

ok,res = pcall(function() j.startJupiter() end)
if ok then
    print('init jupiter success')
else
    error('init jupiter error: ' .. res)
end

g1.glViewport(0, 0, 800, 480)
g1.glEnable(g1.GL_TEXTURE_2D)
g1.glEnable(g1.GL_DEPTH_TEST)

j.File.setBase('../../samples/Box')

shader = j.FileShader(j.File('Resources/sprite.vs'), j.File('Resources/sprite.fs'))

bgImage   = j.PngImage('Resources/bg.png')
bgTexture = j.ImageTexture(bgImage)
bgShape   = j.ImageShape(bgImage)
bg        = j.Sprite()
bg:setProgram(shader):setTexture(bgTexture):setShape(bgShape)

rootNode = j.Node()
rootNode:addNode(bg)

camera   = j.Camera(45.0,   800.0, 480.0,   1.0, 1000.0,   0.0, 0.0, 100.0,   0.0, 0.0, 0.0,   0.0, 1.0, 0.0)
renderer = j.RenderVisitor(camera)

game = j.Game()
game:setRootNode(rootNode):addVisitor(renderer):setWidth(800.0):setHeight(480.0)

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