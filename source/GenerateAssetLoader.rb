def quote s
	"\"#{s}\""
end

template = File.read("source/AssetLoaderTemplate.txt")

result = template.sub('%% ASSETS %%', Dir.glob("assets/**/*.png").collect do |path|
	asset_name = File.basename(path, '.png')
	"assets.set(#{quote asset_name}, loadImage(#{quote path}, screen));"
end.join("\n"))

File.write("source/AssetLoader.hpp", result)