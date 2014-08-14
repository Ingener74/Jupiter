
aspect = 16 / 9
w = 100

viewport = {
    x = 0,
    y = 0,
    width = w,
    height = w / aspect,
}

resources_dir = "resources/"
imgs = resources_dir .. "images/"
shaders = resources_dir .. "shaders/"

background = {
    sprites = {
        background_sprite = {
            textures = {
                background_texture = {
                    file = imgs .. "bg.png",
                    tx1 = 0.0,
                    ty1 = 0.0,
                    tx2 = 1.0,
                    ty2 = 1.0
                }
            },
            x = 0,
            y = 0,
            z = 0,
            width = 100,
            height = 100
        }
    },
    onUpdate = function(background, dt)
        print("background on update")
    end
}

program = {
    vertex = shaders .. "vertex.shader",
    fragment = shaders .. "fragment.shader"
}

scenes = {
    Start = {
        game_objects = {
            background,
            start_button = {
                sprites = {
                    {
                        textures = {
                            {
                                file = imgs .. "start_button.png",
                                tx1 = 0.0,
                                ty1 = 0.0,
                                tx2 = 1.0,
                                ty2 = 1.0
                            }
                        },
                        x = 0,
                        y = 0,
                        z = 0,
                        width = 100,
                        height = 100
                    }
                },
                bla = 123,
                controller = function(bg)
                    print("background controller")
                end,
                onInput = function(bg, x, y)
                    bg.bla = bg.bla + 10;
                    print("x = " .. x .. ", y = " .. y .. ", bla = " .. bg.bla)
                end,
                onUpdate = function(bg, dt)
                    bg.bla = bg.bla + dt
                    print("update = " .. dt .. ", bla = " .. bg.bla)
                end
            }
        }
    },
    Main = {
        game_objects = {
            background,
            battleship = {
                sprites = {
                    -- one texture two spirites, different texture coords
                    body = {
                        textures = {
                            battleship_texture = {
                                file = imgs .. "battleship.png",
                                tx1 = 0.0,
                                ty1 = 0.0,
                                tx2 = 1.0,
                                ty2 = 1.0
                            },
                        },
                        x = 0,
                        y = 0,
                        z = 0,
                        width = 100,
                        height = 100
                    },
                    fire = {
                        textures = {
                            fire = {
                                file = imgs .. "bullet.png",
                                tx1 = 0.0,
                                ty1 = 0.0,
                                tx2 = 1.0,
                                ty2 = 1.0
                            }
                        },
                        x = 0,
                        y = 0,
                        z = 0,
                        width = 100,
                        height = 100
                    }
                },
                onInput = function(battleship, x, y)
                    if x > 100 and x < 300 then
                        print("battleship pressed " .. x .. " " .. y)
                    end
                end,
                onUpdate = function(battleship, dt)
                    print("update battleship = " .. dt)
                end
            }
        }
    },
    Win = {
        game_objects = {
            background,
        }
    },
    Fail = {
        game_objects = {
            background,
        }
    },
    current_scene = Start
}

dofile(getGameLocation() .. "/resources/scripts/ext.lua")

print("viewport " .. viewport.x .. " " .. viewport.y .. " " .. viewport.width .. " " .. viewport.height)

for i1, n in pairs(scenes) do
    print("scene ", i1)
    if n.game_objects ~= nil then
    
        createScene(i1)
        
        for i2, g in pairs(n.game_objects) do
            print("|--> game object " .. i2)
            for i3, s in pairs(g.sprites) do
                print("|    |--> sprite      " .. i3)
                for i4, t in pairs(s.textures) do
                    print("|    |    |--> texture      " .. i4 .. " -- " .. t.file)
                end
            end
            if g.onUpdate ~= nil then
                g:onUpdate(0.31415)
            end
            if g.onInput ~= nil then
                g:onInput(100, 200)
            end
        end
    end
end
