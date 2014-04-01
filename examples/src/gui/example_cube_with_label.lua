-- Hello World Lua declarative

ui:rectangle "root"
{
  x = -1.0;
  y = -1.0;
  width = 2.0;
  height = 2.0;
  alpha = 0.0;

    ui:rectangle "label"
    {
      x = -0.9;
      y = -0.9;
      width = 1.8;
      height = 0.2;
      alpha = 0.5;
      color = glm:vec3(0.5, 0.5, 0.5);
      radius = ui:radius { radius = 0.5; };

      border = ui:border
      {
        color = glm:vec3(0.9, 0.9, 0.9);
        width = 0.02;
      };

      text = ui:text
      {
        alignVerical = "center";
        alignHorizontal = "center";
        text = "Background is opengl!\nThis label is declarative (in example.lua)";
        height = 0.5;
        font = "DejaVuSerifCondensed-BoldItalic";
      };

    }; -- rectangle "label"
}; -- rectangle "root"

