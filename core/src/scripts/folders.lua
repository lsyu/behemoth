function conf:folders(data)
  local config = Folders.new()
  for k, v in pairs(data) do
    config:addResource(k, v)
  end
  return config
end
