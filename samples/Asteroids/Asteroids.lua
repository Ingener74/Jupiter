viewport = {
    x = 0;
    y = 0;
    width = 800;
    height = 600;
}

scenes = {
    {
        name = "Start",
        sprites = {
            {
                texture = "bg.png",
                x = 0,
                y = 0
            },
            {
                texture = "start_button.png",
                x = 0,
                y = 0
            }
        },
        game_objects = {
            bg1 = {
                name = "bg",
                
                bla = 123,
                
                controller = function(bg1)
                    print("background controller", bg1.name)
                end,
                onInput = function(bg1, x, y)
                    print("x = ", x, ", y = ", y)
                end,
                onUpdate = function(bg1, dt)
                    bg1.bla = bg1.bla + dt
                    print("update = ", dt, ", bla = ", bg1.bla)
                end
            }
        }
    },
    {
        name = "Main",
        sprites = {
        },
        game_objects = {
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

print("viewport ", viewport.x, " ", viewport.y, " ", viewport.width, " ", viewport.height, " ")
for i, n in pairs(scenes) do
    print(i, " -> ", n.name);
    for s, t in pairs(n.sprites) do
        print("\t", s, " -> ", t.texture)
    end
    for s1, g in pairs(n.game_objects) do
        print("\t", s1, " -> ", g.name)
        g:controller()        
        g:onInput(100, 123)
        if g.onUpdate ~= nil then
            g:onUpdate(0.1)
        end
    end
end




