-- Hello World Lua declarative

ui:rectangle "root"
{
  x = -0.9,
  y = -0.6,
  width = 1.8,
  height = 1.2,
--  color = vec3(0.0, 0.0, 1.0),
  texture = "test",

  radius = 0.1,
  radiusOfB = 0.5,
  radiusOfA = 1.0,
  radiusOfC = 1.0,

  border = {
    color = vec3(0.5, 0.5, 0.5),
    width = 0.2
  },

  ui:rectangle "parent1"
  {
    color = vec3(1.0, 0.0, 0.0),
    x = - 0.9,
    y =  0.4,
    width = 0.4,
    height = 0.4,

    radius = 1.0,
    border = {
      color = vec3(0.5, 0.5, 0.5),
      width = 0.2
    },
  }, -- rectangle "parent1"
} -- rectangle "root"

