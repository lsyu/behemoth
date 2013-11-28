ui.center = "center"
ui.top = "top"
ui.bottom = "bottom"
ui.left = "left"
ui.right = "right"

function ui:text(data)
  local r = Text.new()
  for k, v in pairs(data) do
    if k == "font" then
      r:setName(v)
    elseif k == "height" then
      r:setHeight(v)
    elseif k == "text" then
      r:setText(v)
    elseif k == "alignVerical" then
      r:setAlignVertical(v)
    elseif k == "alignHorizontal" then
      r:setAlignHorizontal(v)
    end
  end
  return r
end
