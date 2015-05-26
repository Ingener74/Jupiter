
local g1 = require 'glLua'
local g2 = require 'glfwLua'
local g3 = require 'glewLua'
local j = require 'LuaJupiter'

if not g2.glfwInit() then
    print ("glfw error")
    g2.glfwTerminate()
end

g2.glfwWindowHint(g2.GLFW_CONTEXT_VERSION_MAJOR, 3)
g2.glfwWindowHint(g2.GLFW_CONTEXT_VERSION_MINOR, 3)
g2.glfwWindowHint(g2.GLFW_OPENGL_PROFILE, g2.GLFW_OPENGL_CORE_PROFILE);
g2.glfwWindowHint(g2.GLFW_OPENGL_COMPAT_PROFILE, g2.GLFW_OPENGL_FORWARD_COMPAT);

local window = g2.glfwCreateWindow(800, 480, "Dia Lua Game Player", nil, nil)

ok,res = pcall(function() j.initJupiter() end)
if ok then
    print('init jupiter success')
else
    error('init jupiter error: ' .. res)
end

--[[
local glewError = g3.glewInit()
if glewError ~= g3.GLEW_OK then
    print('glew error: ' .. g3.glewGetErrorString(glewError))
end
]]--

g2.glfwMakeContextCurrent(window)

j.File.setBase('../../samples/Box')

vs1 = j.File('Resources/sprite.vs')
fs1 = j.File('Resources/sprite.fs')
--sh1 = j.FileShader(vs1, fs1)

im1 = j.PngImage('Resources/bg.png')

print('OpenGL Version: '                  .. g1.glGetString(g1.GL_VERSION))
print('OpenGL Shading Language Version: ' .. g1.glGetString(g1.GL_SHADING_LANGUAGE_VERSION))
print('OpenGL Vendor: '                   .. g1.glGetString(g1.GL_VENDOR))
print('OpenGL Renderer: '                 .. g1.glGetString(g1.GL_RENDERER))

while g2.glfwWindowShouldClose(window) do
    g1.glClear(g1.GL_COLOR_BUFFER_BIT | g1.GL_DEPTH_BUFFER_BIT)
    g1.glClearColor(0.1, 0.3, 0.1, 1.)

    -- draw();

    g2.glfwSwapBuffers(window)
    g2.glfwPollEvents()
end

g2.glfwDestroyWindow(window)
g2.glfwTerminate()

print('Good, Bye!!!')
