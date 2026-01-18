# Lua Module介紹
這裡會介紹`ToyBox`所建立的Lua Module

## 前言
`ToyBox`建立了許多C++函式庫，然後又在這之上進一步包裝出`Lua extension module`，
可以使用`Lua`官方的直譯器來使用這些module，
也可以用`ToyBox`客製化的直譯器(`player`)來使用module，請參閱文件`ToyBox/docs/for_ai/player.md`的說明來了解`player`。

## Sample Code
Lua module的範例程式碼寫在這邊`ToyBox/examples/usage/ToyBox/modules`，
該資料夾裡面只有程式碼而已，
module名稱跟範例路徑是有關的，方便你尋找對應的範例，下面舉個例子：

當你想要查詢`toy.logger`這個module的使用方式時，去查閱`ToyBox/examples/usage/ToyBox/modules/toy/logger.lua`這個範例，
想要查詢`toy.math.bignum`這個module的使用方式時，去查閱`ToyBox/examples/usage/ToyBox/modules/toy/math/bignum.lua`這個範例，
由於介面上已經包裝的夠簡單了，不管人類還是AI都可以輕鬆閱讀這些範例。

## Lua Module清單
以下列出比較重要的module

### toy.logger
專門用來印出訊息，只能輸入UTF-8字串，
可取代Lua內建的print函式。

### toy.debug
包含了類似try-catch的機制，
可以協助除錯。

### toy.env
這module讓使用者可以查詢`ToyBox`製作的module們有何背景資訊。

### toy.root
這個module只有`player`才能使用，
用來提供`player`特有資訊，
非必要功能。
