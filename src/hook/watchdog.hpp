#include "dictionary.h"

namespace Watchdog {

  namespace Handler {

    void Keypress()
    {
      while (true) {
        Sleep(100);
        if ((GetAsyncKeyState(VK_CONTROL) & GetAsyncKeyState(VK_F5)) && Config::Setting::enable_refresh == false) {
          Config::Setting::enable_refresh = true;
          logger::info("refresh");
        }
        if ((GetAsyncKeyState(VK_CONTROL) & GetAsyncKeyState(VK_F3)) && Config::Setting::enable_translation == true) {
          Config::Setting::enable_translation = false;
          logger::info("translation switched off");
          //MessageBoxA(nullptr, "translation switched off", "dfint hook info", MB_ICONWARNING);
        }
        if ((GetAsyncKeyState(VK_CONTROL) & GetAsyncKeyState(VK_F4)) && Config::Setting::enable_translation == false) {
          Config::Setting::enable_translation = true;
          logger::info("translation switched on");
          //MessageBoxA(nullptr, "translation switched on", "dfint hook info", MB_ICONWARNING);
        }
        if ((GetAsyncKeyState(VK_CONTROL) & GetAsyncKeyState(VK_F2))) {
          logger::info("reload dictionary");
          Dictionary::GetSingleton()->Clear();
          Dictionary::GetSingleton()->LoadCsv("./dfint_data/dfint_dictionary.csv","./dfint_data/kr_regex.txt");
          //MessageBoxA(nullptr, "dictionary reloaded", "dfint hook info", MB_ICONWARNING);
        }
      }
    }

  }

  void WatchKeyboard()
  {
    CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Watchdog::Handler::Keypress), nullptr, 0,
                 nullptr);
  }

}