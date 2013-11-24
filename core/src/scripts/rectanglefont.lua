-- function ui:text()
  function ui:text(data)
    local r = Text.new()
    for k, v in pairs(data) do
      if k == "font" then
        r:setName(v)
      elseif k == "height" then
        r:setHeight(v)
      elseif k == "text" then
        r:setText(v)
      end
    end
    return r
  end
-- end
