# Set Library Path
以下這些設計是因為`ToyAuthor`不使用CMake的find_package功能而造成的，
也就是不使用CMake來尋找library，而是由使用者來指定library路徑。

## 函式庫配置概念
在`ToyBox`內部的範例程式專案裡面，
寫CMake文件是不需要指示`ToyBox`的標頭檔與library的該去哪裡找的，
只需要提供函式庫名稱，例如`toy_file`，這樣CMake就能自己去找到並連結`toy_file.lib`了，
第三方函式庫就不能這樣了，必須指定標頭檔路徑、library路徑、library檔名，
如果你閱讀過`ToyBox/cmake/toy_SetThirdPartyLibraryPath.cmake`的內容，
肯定能明白如何設置library路徑。

## ToyBoxSDK
為了提供使用者一個方便的方式來處理第三方函式庫編譯，
`ToyAuthor`另外先將第三方函式庫編譯好，然後依照特定的資料夾結構來儲存，資料夾名稱是`ToyBoxSDK`，
你下載`ToyBoxSDK`之後，
在`ToyBox/cmake/toy_SetThirdPartyLibraryPath.cmake`上面
修改`TOY_SDK_INC`跟`TOY_SDK_LIB`這兩個路徑即可，
以下是範例：
```cmake
set(TOY_SDK_INC "d:/work/ToyBoxSDK/include")
set(TOY_SDK_LIB "d:/work/ToyBoxSDK/lib/msvc2015_x64_win32_release")
```
如果`ToyAuthor`準備的`ToyBoxSDK`無法滿足你，那你就必須自己親手去張羅這些函式庫了。

## 第三方函式庫的路徑設定
在`ToyBox/cmake/toy_SetThirdPartyLibraryPath.cmake`裡面，
會列出非常多的函式庫路徑，你可以個別修改路徑，
不影響整個專案的運作，修改後的路徑裡確實有正確的檔案就好。

### 內部攜帶的第三方函式庫
舉例，以下是`SQLite`函式庫的路徑：
```cmake
set(TOY_include_sqlite "${TOY_ROOT_SOURCE_DIR}/extlibs/sqlite")
set(TOY_library_sqlite "${TOY_ROOT_BINARY_DIR}/extlibs/sqlite")
set(TOY_libname_sqlite "sqlite3" )
```
`TOY_ROOT_SOURCE_DIR`是專案根目錄  
`TOY_ROOT_BINARY_DIR`則是CMake設定要放編譯產物的資料夾位置  
`TOY_include_sqlite`是SQLite標頭檔的資料夾位置  
`TOY_library_sqlite`是SQLite函式庫的資料夾位置  
`TOY_libname_sqlite`是SQLite函式庫的檔名  
因此SQLite這個第三方函式庫的程式碼是放在`ToyBox`內部的，
CMake會去負責處理，但是你希望指定成外部路徑也沒問題，如下所示：
```cmake
set(TOY_library_sqlite "d:/work/sqlite3/lib")
```

### 外部設置的第三方函式庫
舉例，以下是`FLTK`函式庫的路徑：
```cmake
set(TOY_include_fltk "${TOY_SDK_INC}")
set(TOY_library_fltk "${TOY_SDK_LIB}/FLTK")
set(TOY_libname_fltk "fltk")
```
有寫出`TOY_SDK`這個字眼的就是位在專案外部的路徑了，
你完全可以無視`TOY_SDK_INC`這樣的命名，
寫成以下這樣也完全可行：
```cmake
set(TOY_include_fltk "d:/work/FLTK/include")
```
只要給定的資料夾裡面真的有正確的檔案即可。
