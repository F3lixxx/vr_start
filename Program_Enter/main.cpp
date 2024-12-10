#include <iostream>
#include <cstdlib>

void executeCommand(const std::string& command) {
    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "Command failed: " << command << std::endl;
    }
}

int main() {
    std::string ipAddress = "192.168.0.9";
    std::string devicePort = ":5555";
    std::string apkPath = "C:\\Users\\User\\Downloads\\Telegram_Desktop\\debug.apk";
    std::string packageName = "com.FiveCoders.bowowling";

    executeCommand("adb connect " + ipAddress + devicePort);

    executeCommand("adb install " + apkPath);

    executeCommand("adb shell am start -n " + packageName + " \\com.unity3d.player.UnityPlayerActivity");

    return 0;
}
