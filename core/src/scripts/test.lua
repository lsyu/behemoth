-- Hello World Lua declarative

ui:rectangle "root"
{
  x = -0.5;
  y = -0.5;
  width = 1.0;
  height = 1.0;
  color = ui:vec3(0.0, 1.0, 1.0);

  ui:rectangle "a11"
  {
    x = -0.5;
    y = -1.0;
    width = 1.0;
    height = 2.0;
    texture = "test";

    radius = 0.2;

    border = ui:border 
    {
      color = ui:vec3(0.5, 0.5, 0.5);
      width = 0.02;
    };

    onClick = function()
      print ("hello world from lua declarative!")
      print ("x      = " .. ui.a11.x)
      print ("y      = " .. ui.a11.y)
      print ("width  = " .. ui.a11.width)
      print ("height = " .. ui.a11.height)
    end;

    ui:text
    {
      alignVerical = "center";
      alignHorizontal = "center";
      text = "Hello, world!\nThis subline does not contain delimiters! :)";
      height = 0.2;
      font = "DejaVuSans";
    };

  };
};

print (ui.root)

-- ui:rectangle "root"
-- {
--   x = -1.0;
--   y = -1.0;
--   width = 2.0;
--   height = 2.0;
--   texture = "test";

--   onClick = function()
--     print ("hello world from lua declarative!")
--   end;

--   ui:rectangle "modal"
--   {
--     x = -0.5;
--     y = -0.5;
--     width = 1.0;
--     height = 1.0;
--     radius = 0.1;

--     color = vec3(0.6, 0.6, 0.6);

--     border = {
--       color = vec3(0.2, 0.2, 0.2);
--       width = 0.02;
--     };

--       onClick = function()
--         print ("Clicked MODAL!")
--       end;

--     ui:rectangle "hideItem"
--     {
--       x = -0.9;
--       y = -0.6;
--       width = 1.8;
--       height = 1.6;
--       alpha = 0.0;

--       ui:text
--       {
--         alignVerical = ui.center;
--         alignHorizontal = ui.center;
--         text = "Hello, world!\nThis subline does not contain delimiters! :)";
--         height = 0.2;
--         font = "DejaVuSans";
--       };

--       onClick = function()
--         print ("Clicked HIDEITEM!")
--       end;
--     };

--     ui:rectangle "button"
--     {
--       x = -0.9;
--       y = -0.9;
--       width = 1.8;
--       height = 0.35;
--       radius = 0.5;

--       color = vec3(0.4, 0.4, 0.4);

--       border = {
--         color = vec3(0.2, 0.2, 0.2);
--         width = 0.1;
--       };

--       ui:text
--       {
--         alignVerical = ui.center;
--         alignHorizontal = ui.center;
--         text = "Exit";
--         height = 1;
--         font = "DejaVuSans";
--       };

--       onClick = function()
--         print ("Clicked BUTTON!")
--       end;

      
--     };
--   };
-- }; -- rectangle "root"

