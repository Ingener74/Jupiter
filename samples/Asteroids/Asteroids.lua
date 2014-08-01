viewport = {
    x = 0;
    y = 0;
    width = 800;
    height = 600;
}

background_sprite = {
    texture = "bg.png",
    x = 0,
    y = 0
}

scenes = {
    {
        name = "Start",
        sprites = {
            background_sprite
        },
        game_objects = {
            start_button = {
                name = "start button",
                sprites = {
                    {
                        texture = "start_button.png",
                        x = 0,
                        y = 0
                    }
                },
                
                bla = 123,
                controller = function(bg)
                    print("background controller", bg.name)
                end,
                onInput = function(bg, x, y)
                    bg.bla = bg.bla + 10;
                    print("x = ", x, ", y = ", y, ", bla = ", bg.bla)
                end,
                onUpdate = function(bg, dt)
                    bg.bla = bg.bla + dt
                    print("update = ", dt, ", bla = ", bg.bla)
                end
            }
        }
    },
    {
        name = "Main",
        sprites = {
            background_sprite
        },
        game_objects = {
            battleship = {
                name = "Battle ship",
                
                sprites = {
                    -- one texture two spirites, different texture coords
                    body = {
                        texture = "battleship.png",
                        x = 0,
                        y = 0,
                    },
                    fire = {
                        texture = "battleship.png",
                        x = 0,
                        y = 0,
                    }
                },
                onInput = function(battleship, x, y)
                    if x > 100 and x < 300 then
                        print("battleship pressed")
                    end
                end,
                onUpdate = function(battleship, dt)
                    print("update battleship = ", dt)
                end
            }
        }
    },
    {
        name = "Win",
        sprites = {
        },
        game_objects = {
        }
    },
    {
        name = "Fail",
        sprites = {
        },
        game_objects = {
        }
    }
}

local old_print = print
print = function(...)
  new_print(...);
end

-- TODO getGameLocation() function return Asteroids containg directory
dofile("../samples/Asteroids/ext.lua")

--[[
print("viewport ", viewport.x, " ", viewport.y, " ", viewport.width, " ", viewport.height, " ")
for i, n in pairs(scenes) do
    print(i, " -> ", n.name);
    for s, t in pairs(n.sprites) do
        print("\t", s, " -> ", t.texture)
    end
    for s1, g in pairs(n.game_objects) do
        print("\t", s1, " -> ", g.name)
        if g.controller ~= nil then
            g:controller()
        end
        if g.onInput ~= nil then
            g:onInput(100, 123)
        end
        if g.onUpdate ~= nil then
            g:onUpdate(0.1)
        end
    end
end
--]]