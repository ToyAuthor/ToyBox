# `player`
本文件講解`player`是什麼東西

## `player`是直譯器
`player`是一個`Lua`直譯器，與`Lua`官方的直譯器不同，
`player`是專門為`ToyBox`客製化的`Lua`直譯器。

## Lua Module
以`ToyBox`建立的C++ library為基底，
在這之上進一步包裝出`Lua extension module`供`player`使用，
這些module是`player`的動力來源。
module介面會比C++介面簡單易用，程式碼會很簡潔，
但是也犧牲了C++介面原有的靈活度。

在`ToyBox/docs/for_ai/lua_modules.md`有更多介紹。

## `player`與`Lua`官方直譯器的差別
`player`與`Lua`官方的直譯器差異並不大，只是`player`內建宣告了一些非必要的全域變數，
並在執行時需要讀取設定檔(官方直譯器不需要設定檔)，
都是為了使用便利而增加的改造，
使用`Lua`官方的直譯器也一樣能夠執行`ToyBox`所建立的`Lua extension module`。

## 未來規劃
未來會把`player`跟所有需要的module、動態函式庫都打包放一起發佈出來，會是個portable的軟體工具，
讓使用者只需要學習`Lua`語法就能使用這個工具，
不用親自去編譯C++的函式庫、程式。

## 如何開始使用`player`？
總共三個步驟

### Step 1: 取得`player`
目前尚未備妥程式的載點，
所以目前只能編譯`ToyBox`這個專案，`CMake`會幫忙建立`player`與那些`Lua extension module`，
未來會直接提供`Linux`與`Windows`版本的`player`程式給使用者下載。

### Step 2: 設置`player`所需要的設定檔
設定檔的使用方式寫在`ToyBox/docs/for_ai/player/config.md`，
使用`--help`這樣的指令也可以學到一些。

### Step 3: 學習使用`player`
首先要學習`Lua`這個語言，
然後去`ToyBox/examples/usage/ToyBox/modules`這個資料夾學習那些`Lua module`的用法。
