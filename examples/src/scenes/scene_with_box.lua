speed = 0.01;
flag = 1

bgm:node "root"
{
    entity = "box.mesh";
    position = glm:vec3(0.5, 0.0, 0.0);

    onUpdate = function()
      speed = speed + flag * 0.01;
      if speed > 2 then
        flag = -1;
      elseif speed < -2 then
        flag = 1;
      end
      bgm.root.obj:rotate(speed, glm:vec3(0.0, 0.0, 1.0).obj);
    end;
}
