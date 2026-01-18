# Build
本文件會從零開始交待專案建置的過程

## 檢查環境是否符合最低需求
* 可以參考`ToyBox/docs/for_ai/requirements.md`這份文件

## 需要安裝的程式
* CMake，至少要3.15版
* 編譯器，可能有支援 C++11 的編譯器都沒問題，例如 Visual Studio 系列就至少要 2015 版本

## 下載`ToyBox`這個專案
不一定需要用git下載，
去儲存專案的地點尋找滿意的版本即可。

### Repositories
* https://bitbucket.org/ToyAuthor/toybox
* https://github.com/ToyAuthor/ToyBox
* https://gitlab.com/ToyAuthor/ToyBox

## 設置`ToyBox`所使用的第三方函式庫
* ToyBox不使用CMake的`find_package`機制，所有第三方函式庫的路徑皆由使用者明確指定
* 去閱讀這份設定檔`ToyBox/cmake/toy_SetThirdPartyLibraryPath.cmake`(內容超簡單，AI一定能看懂)，
  上面有提到`TOY_SDK_LIB`或`TOY_SDK_INC`的路徑都是`ToyBox`裡面沒有附帶的函式庫，你必須另外準備，
  其餘的函式庫則是已經放在`ToyBox`裡面了，CMake能替你處理，
  `boost`是裡面比較特別的，你去下載`boost`的標頭檔，然後將資料夾指定給`TOY_include_boost`即可，
  source code部份已經放在`ToyBox`裡面了。
* 這份文件`ToyBox/extlibs/readme.md`有寫這些第三方函式庫的版本，你應該去下載上面所記載的版本。
* 將library路徑、名稱寫入`ToyBox/cmake/toy_SetThirdPartyLibraryPath.cmake`即可，讓CMake知道該去何處引入標頭檔、連結函式庫，
  如果你需要更深入了解`TOY_SDK`是什麼，這份文件`ToyBox/docs/for_ai/set_library_path.md`可以提供你更多資訊。

## 使用CMake
在`ToyBox/cmake/toy_Option.cmake`這邊有著CMake編譯選項，
請勾選`TOY_ENABLE_SHARED_LIBS`這個選項來建立動態函式庫，
`ToyBox`早就無法建立靜態函式庫了，未來只有極低機率會修復靜態函式庫選項。
這份文件`ToyBox/docs/for_ai/build/cmake_option.md`有列出各個選項的解釋，
選擇好選項之後，接下來就用CMake去建立makefile這類的文件。

## 編譯專案
在`ToyBox/include/toy/CompilerConfig.hpp`有寫著程式碼的編譯選項，
可參考此文件`ToyBox/docs/for_ai/build/compiler_config.md`的說明來修改，
選擇好選項之後，用C++編譯器來執行最後一步。
