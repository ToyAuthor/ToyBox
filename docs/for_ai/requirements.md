# Requirements
本文件描述專案所需要的環境條件以及工具版本，也是`ToyAuthor`真正測試過的。

## 作業系統
只支援`Windows`跟`Linux`兩個作業系統而已

### Windows
至少必須是`Windows 7`，可以是x86版本。

### Linux
只有試過x64架構的`Ubuntu`，不確定最低版本，應該2015年之後發表的`Ubuntu`都能支援，
實際測試過的是`Ubuntu 24.04 LTS`。

## 程式語言
以C++11為最低需求

## 編譯器
有支援C++11的編譯器才能使用，
實際測試過的編譯器是GCC 13.3.0、TDM-GCC 10.3.0、Visual Studio 2015、Visual Studio 2022。

## 自動化建構系統
只使用CMake來建置專案，至少要3.15版(`Windows 7`尚支援此版本)，但是實際上有可能更低版本也行。

## OpenGL
最低需求是4.5版

## 第三方函式庫
請參閱`ToyBox/extlibs/readme.md`這份文件，上面有列出所有第三方函式庫的版本以及license，
有的函式庫因為體積小，已經內建在`ToyBox`裡面，程式碼放置在`ToyBox/extlibs`這個資料夾，CMake會替你編譯好，
有的函式庫因為體積大，不會夾帶在`ToyBox`裡面，你需要自己下載函式庫、build函式庫，
然後修改`ToyBox/cmake/toy_SetThirdPartyLibraryPath.cmake`來讓`ToyBox`知道你將檔案放在何處。
