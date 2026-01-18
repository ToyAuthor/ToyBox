# `player`的設定檔
本文件要解釋`player`的config相關議題

## 介紹
設定檔的名字會是`default-config.lua`，
放置到跟`player`程式同一個目錄下，`player`執行時，預設就會去找`default-config.lua`來讀取了，
然後按照`default-config.lua`的指示來執行程式。

## 範例
以下是設定檔的內容示範，同樣也是使用`Lua`的語法：
```lua
-- Set a path for searching your image file, font file, etc.
search_path = "d:/resource"

-- Set the main script of your project.
script = "main.lua"

-- Set a path for searching main script of project.
main_path = "d:/examples/HelloWorld"
```
範例的內容就是要求`palyer`去`d:/examples/HelloWorld`這個資料夾裡面找名為`main.lua`的腳本檔，
就像C語言總是從名為`main`的函式開始執行一樣，
`palyer`也總是從指定的腳本檔開始執行。
