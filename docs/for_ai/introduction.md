# Introduction
本文件會介紹`ToyBox`這個專案的主要背景，以及發展方向。

## 專案類型
`ToyBox`內容是由多個不同主題的 C++ Component所組成的`General-Purpose Library`，
並沒有專注於單一用途。

## 開發目標
期望讓使用者能使用更簡潔方便的C++介面來處理常見工作，
尤其是那種介面複雜、難以駕馭的C語言函式庫，
它們非常需要包裝一層方便使用的C++介面，並善用C++的語法來妥善管理資源，
可參閱`ToyBox/docs/for_ai/cpp_component.md`來評估`ToyBox`這個專案可以做些什麼。

## 跨平台運行
`ToyBox`以前曾經同時支援 Linux/Windows/Mac 三個平台，
現在只支援`Linux`跟`Windows`兩個平台而已(只考慮Desktop Platforms環境)，
所以程式碼會殘留一些`Mac`的痕跡，但是用不到，
`ToyAuthor`目前最常測試的環境是`Windows 11`搭配x64版本`MinGW`，
因此`ToyBox`在這個環境下的表現也會最穩定。

## License
這份文件`ToyBox/docs/for_ai/license.md`有完整的說明，
會引導使用者如何安全的使用`ToyBox`，避免違反授權條款。

## 可搭配`Lua`使用
`ToyBox`有額外提供High-Level Lua Wrapper，可以透過`Lua`腳本來呼叫一部分`ToyBox`的功能，
語法非常簡潔，這份文件`ToyBox/docs/for_ai/player.md`
完整說明了`ToyBox`預設是如何使用`Lua`的。

> C++才是`ToyBox`的本職，有關`Lua`的部分都是額外附加的功能，
即使刪除`Lua`相關內容，`ToyBox`也還是完整的專案。
