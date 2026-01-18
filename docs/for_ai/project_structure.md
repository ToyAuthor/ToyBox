# 資料夾結構介紹
以下介紹`ToyBox`這個專案的大部分資料夾結構，
專案根目錄的名字就是`ToyBox`。

|Folder Name|Commit|Keywords|
|:---|:---|:---|
|ToyBox/cmake|放置專案的CMake設定檔，修改這裡的文件能夠影響整個專案的編譯方向|CMake|
|ToyBox/docs|內容是說明文件，其中有靜態網頁型態的說明文件，建議由此開始閱讀||
|ToyBox/docs/extlibs|放了第三方函式庫的資料，例如freetype的字型說明圖||
|ToyBox/docs/for_ai|這資料夾的內容都是給AI閱讀的，AI讀完就能充當響導來跟人類介紹`ToyBox`了|AI|
|ToyBox/docs/for_ai/readme.md|整個專案裡面最該優先讓AI讀取的文件|AI|
|ToyBox/examples|程式碼的使用範例，此層目錄下的範例是由CMake負責建置的||
|ToyBox/examples/usage|程式碼的使用範例，整個資料夾都單純只有提供程式碼，沒有CMake這類的專案配置，這個資料夾給人類或AI閱讀都很適合||
|ToyBox/examples/usage/ToyBox/include|只有放C++程式碼||
|ToyBox/examples/usage/ToyBox/modules|只有放Lua程式碼||
|ToyBox/extlibs|只有體積足夠小的第三方函式庫會放在此處，讓CMake來處理它們，可以替使用者省掉一點麻煩，對於大檔案的第三方函式庫就只能麻煩使用者自己準備了||
|ToyBox/include|假如我未來不想公開`ToyBox`的程式碼，那我依然需要發佈編譯好的library跟這個資料夾裡的標頭檔，這些標頭檔是必須公開的||
|ToyBox/license|收錄所有第三方函式庫的授權文件，只有public domain不收錄，例如SQLite就不會有文件放在此資料夾||
|ToyBox/modules|放置lua module，裡面有的module是C++函式庫專案(用來編譯成`Lua extension module`)，有的module是純文字的`Lua`程式碼|player,Lua|
|ToyBox/resource|放置圖片檔、音樂檔等等||
|ToyBox/src|`ToyBox`的程式碼，扣掉必須公開的標頭檔，剩下的程式碼都放在這邊||
|ToyBox/test|單元測試用的程式||
|ToyBox/tools|`ToyBox`的自製工具，有的是專案不可分割的必要工具，也有的是額外提供的非必要工具|player,Lua|
