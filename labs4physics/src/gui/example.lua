-- Hello World Lua declarative

ui:rectangle "root"
{
  x = -1.0;
  y = -1.0;
  width = 2.0;
  height = 2.0;
  texture = "test";

  ui:rectangle "modal"
  {
    x = -0.5;
    y = -0.5;
    width = 1.0;
    height = 1.0;
    radius = 0.1;

    color = ui:vec3(0.6, 0.6, 0.6);

    border = ui:border
    {
      color = ui:vec3(0.2, 0.2, 0.2);
      width = 0.02;
    };

    ui:rectangle "hideItem"
    {
      x = -0.9;
      y = -0.6;
      width = 1.8;
      height = 1.6;
      alpha = 0.0;

      text = ui:text
      {
        alignVerical = "center";
        alignHorizontal = "center";
        text = "'Hello world' from lua! :)\nMessageBox example...";
        height = 0.2;
        font = "DejaVuSans";
      };
    };

    ui:rectangle "button"
    {
      x = -0.9;
      y = -0.9;
      width = 1.8;
      height = 0.35;
      radius = 0.5;

      color = ui:vec3(0.4, 0.4, 0.4);

      border = ui:border
      {
        color = ui:vec3(0.2, 0.2, 0.2);
        width = 0.1;
      };

      text = ui:text
      {
        alignVerical = "center";
        alignHorizontal = "center";
        text = "Exit";
        height = 1;
        font = "DejaVuSans";
      };

      onPressed = function()
        print ("Pressed BUTTON")
        ui.button.border = ui:border
        {
          color = ui:vec3(0.9, 0.9, 0.9);
          width = 0.1;
        };
      end;

      onClick = function()
        print ("Clicked BUTTON!")
      end;

      onReleased = function()
        print ("Released BUTTON")
        ui.button.border = ui:border
        {
          color = ui:vec3(0.2, 0.2, 0.2);
          width = 0.1;
        };
      end;
      
    };
  };
}; -- rectangle "root"

