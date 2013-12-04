-- Hello World Lua declarative

ui:rectangle "root"
{
  x = -1.0,
  y = -1.0,
  width = 2.0,
  height = 2.0,
  texture = "test",

  ui:rectangle "modal"
  {
    x = -0.5,
    y = -0.5,
    width = 1.0,
    height = 1.0,
    radius = 0.1,

    color = vec3(0.6, 0.6, 0.6),

    border = {
      color = vec3(0.2, 0.2, 0.2),
      width = 0.02
    },

    ui:rectangle "hideItem"
    {
      x = -0.9,
      y = -0.6,
      width = 1.8,
      height = 1.6,
      alpha = 0.0,

      ui:text
      {
        alignVerical = ui.center,
        alignHorizontal = ui.center,
        text = "Hello, world!\nThis subline does not contain delimiters! :)",
        height = 0.2,
        font = "DejaVuSans"
      }
    },

    ui:rectangle "button"
    {
      x = -0.9,
      y = -0.9,
      width = 1.8,
      height = 0.3,
      radius = 0.5,

      color = vec3(0.4, 0.4, 0.4),

      border = {
        color = vec3(0.2, 0.2, 0.2),
        width = 0.1
      },

      ui:text
      {
        alignVerical = ui.center,
        alignHorizontal = ui.center,
        text = "Button 1 (Exit)",
        height = 1,
        font = "DejaVuSans"
      }
    }
  }
} -- rectangle "root"

