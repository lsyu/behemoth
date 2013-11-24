-- Hello World Lua declarative

ui:rectangle "root"
{
  x = -0.9,
  y = -0.6,
  width = 1.8,
  height = 1.2,
  texture = "test",

  radius = 0.1,
  radiusOfB = 0.5,
  radiusOfA = 1.0,
  radiusOfC = 1.0,

  border = {
    color = vec3(0.5, 0.5, 0.5),
    width = 0.2
  },

  ui:text
  {
--    alignVerical = ui:center,
--    alignHorizontal = ui:center,
    text = "Hello, world!",
    height = 0.8,
    font = "FreeSans"
  }
} -- rectangle "root"

