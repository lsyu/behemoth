function conf:folders(data)
  local config = Folders.new("test")
  for k, v in pairs(data) do
    if k == 'mesh' then
      config:setMeshDir(v)
    elseif k == 'material' then
      config:setMaterialDir(v)
    elseif k == 'texture' then
      config:setTextureDir(v)
    elseif k == 'shader' then
      config:setShaderDir(v)
    end
  end
  return config
end
