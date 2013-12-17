function ui:rectangle(id)
  return function(data)
    local r = Rectangle.new(id)
    local ret = {}

    for k, v in pairs(data) do
      if k == "x" then
        r:setX(v)
      elseif k == "y" then
        r:setY(v)
      elseif k == "width" then
        r:setWidth(v)
      elseif k == "height" then
        r:setHeight(v)
      elseif k == "color" then
        r:setColor(v)
      elseif k == "texture" then
        r:setTexture(v) -- READ ONLY!!!
      elseif k == "radius" then
        r:setRadius(v)
      elseif k == "radiusOfA" then
        r:setRadiusOfA(v)
      elseif k == "radiusOfB" then
        r:setRadiusOfB(v)
      elseif k == "radiusOfC" then
        r:setRadiusOfC(v)
      elseif k == "radiusOfD" then
        r:setRadiusOfD(v)
      elseif k == "alpha" then
        r:setAlpha(v)
      elseif k == "border" then
        r:setBorderWidth(v.width) -- READ ONLY!!! TODO: MAKE WRITE
        r:setBorderColor(v.color) -- READ ONLY!!! TODO: MAKE WRITE
      elseif k == "onClick" then
        ret.onClick = v
      else
        r:addChild(v.obj)
      end
    end

    r:sync()
    ret.obj = r

    local mt = {}
    mt.__index = function(self, key)
      if key == "x" then
        return self.obj:getX()
      elseif key == "y" then
        return self.obj:getY()
      elseif key == "width" then
        return self.obj:getWidth()
      elseif key == "height" then
        return self.obj:getHeight()
      else
        return rawget(self, key)
      end
    end
    mt.__newindex = function(self, key, value)
      if key == "x" then
        self.obj:setX(value)
      elseif key == "y" then
        self.obj:setY(value)
      elseif key == "width" then
        self.obj:setWidth(value)
      elseif key == "height" then
        self.obj:setHeight(value)
      end
    end
    setmetatable(ret, mt)
    ui[id] = ret
    return ret
  end
end
