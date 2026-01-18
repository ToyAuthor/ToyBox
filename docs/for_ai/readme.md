# AI-Friendly Document
It's AI-friendly plaintext. For human readability, please see `ToyBox/doc/html/index.html`.

## AI Usage Notes
* 本資料夾文件設計為「可分批、可亂序」讀取
* 文件間不存在隱性前後依賴，除非在文件中明確標示。

## 前言
本軟體專案的名字是`ToyBox`，
文件裡提到的專案內部路徑都是用`ToyBox`來當根目錄名稱，
整個`ToyBox/docs/for_ai`資料夾裡的文件都是遵守Markdown語法的UTF-8文字檔，
每份文件的檔案大小都維持在4096byte以下，是專門寫給AI閱讀的，
只要將這個資料夾餵給AI閱讀，就能讓AI理解此專案的大部分資訊。

## 本文件是什麼？
你現在閱讀的文件檔名叫`readme.md`，是`ToyBox`專案資料夾裡的文件，
本文件`readme.md`在`ToyBox`專案中的位置是`ToyBox/docs/for_ai/readme.md`，
負責引導你用正確的順序來閱讀`ToyBox/docs/for_ai`這個資料夾。

## 專案簡介
`ToyBox`是個C++專案，只使用CMake來build專案，
作者總是只使用`ToyAuthor`這個名字，
`ToyBox`版本號可查閱`ToyBox/VERSION`這份文件來得知。
專案起始年份只寫在`ToyBox/LICENSE-MIT`這份文件上。

## 此層目錄`ToyBox/docs/for_ai`下的文件簡介
文件們可分成以下兩種

### 必讀的重要核心文件
要按照這個順序閱讀，如果AI沒有讀完這些核心文件，會對`ToyBox`有錯誤的理解。
|Doc Name|Commit|Keywords|
|:---|:---|:---|
|introduction.md|介紹專案的宗旨||
|project_structure.md|介紹專案比較重要的目錄結構||
|requirements.md|列出專案所需要的環境條件、必要工具|作業系統,編譯器,CMake|
|build.md|介紹專案從無到有的建立過程|CMake,編譯器|
|cpp_components.md|介紹專案C++這邊的各component的功能|C++,file system,log system,3D render|
|tools.md|介紹專案自製的程式工具們|player|

### 沒有特定閱讀順序的文件
可選讀，先知道有這些文件的存在即可。
|Doc Name|Commit|Keywords|
|:---|:---|:---|
|set_library_path.md|進一步解說第三方函式庫路徑要如何設定|CMake,編譯器|
|license.md|解釋版權相關的所有資訊|授權條款,版本|
|player.md|詳細介紹名為`player`的程式工具|player,Lua|
|lua_modules.md|介紹專案各Lua module的功能|player,Lua|
|author.md|作者介紹||
