#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>

void LeftClick() {
    using namespace std::chrono_literals;
    INPUT Input = {0};
    // left down
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    ::SendInput(1, &Input, sizeof(INPUT));
    std::this_thread::sleep_for(50ms);
    // left up
    ::ZeroMemory(&Input, sizeof(INPUT));
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    ::SendInput(1, &Input, sizeof(INPUT));
}

void MiddleClick() {
    using namespace std::chrono_literals;
    INPUT Input = {0};
    // left down
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
    ::SendInput(1, &Input, sizeof(INPUT));
    std::this_thread::sleep_for(50ms);
    // left up
    ::ZeroMemory(&Input, sizeof(INPUT));
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
    ::SendInput(1, &Input, sizeof(INPUT));
}

void LeftUp() {
    using namespace std::chrono_literals;
    INPUT Input = {0};
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    ::SendInput(1, &Input, sizeof(INPUT));
    std::this_thread::sleep_for(50ms);
}

void LeftDown() {
    using namespace std::chrono_literals;
    INPUT Input = {0};
    // left down
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    ::SendInput(1, &Input, sizeof(INPUT));
    std::this_thread::sleep_for(50ms);
}

void MouseScroll(double RY) {
    using namespace std::chrono_literals;
    INPUT Input = {0};
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_WHEEL;
    Input.mi.mouseData = static_cast<int>(RY * 30);
    Input.mi.time = 0;
    SendInput(1, &Input, sizeof(Input));
    ::SendInput(1, &Input, sizeof(INPUT));
}

void pressTwoKeys() {
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    ip.ki.wVk = 0x11; // virtual-key code for the "a" key
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));

    // Press the "A" key
    ip.ki.wVk = 0x57; // virtual-key code for the "a" key
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));

    // Release the "A" key
    ip.ki.wVk = 0x57;
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));

    ip.ki.wVk = 0x11;
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));
}

std::vector<int> getColor(int x, int y) {
    using namespace std::chrono_literals;
    COLORREF color;
    HDC hDC;

    // Get the device context for the screen
    hDC = GetDC(NULL);
    if (hDC == NULL)
        return std::vector<int>{255, 255, 255};
    // Retrieve the color at that position
    color = GetPixel(hDC, x, y);
    if (color == CLR_INVALID)
        return std::vector<int>{255, 255, 255};

    // Release the device context again
    ReleaseDC(GetDesktopWindow(), hDC);

    //fmt::println("R {} G {} B {}; x {} y {}", GetRValue(color), GetGValue(color), GetBValue(color),x,y);
    return std::vector<int>{GetRValue(color), GetGValue(color), GetBValue(color)};
}


int main() {
    auto window = sf::RenderWindow(sf::VideoMode(200, 200), "yaoi was here");
    window.setFramerateLimit(240);
    auto event = sf::Event();
    int i = 0;
    int s = 0;
    const int y = 45;
    int replays = 0;
    bool init = true;
    std::string status = "none";

    while (window.isOpen()) {

        if (status == "ban") {
            if (init) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                LeftClick();
                std::this_thread::sleep_for(std::chrono::milliseconds(600));
                SetCursorPos(960, 412);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                LeftClick();
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                MouseScroll(-46);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                SetCursorPos(1200, 420);
                std::this_thread::sleep_for(std::chrono::milliseconds(600));
                SetCursorPos(960, 364);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                LeftClick();
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                init = false;
                MouseScroll(46);
                std::this_thread::sleep_for(std::chrono::milliseconds(600));
            }
            SetCursorPos(1420, 190 + i * y);
            std::this_thread::sleep_for(std::chrono::milliseconds(40));
            LeftClick();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            if (getColor(1420, 300 + i * y) == std::vector<int>{28, 23, 25}) {
                SetCursorPos(1420, 272 + i * y);
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                LeftClick();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                SetCursorPos(575, 180 + i * y);
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                MiddleClick();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                replays++;
            }
            SetCursorPos(1800, 400);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            LeftClick();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            s++;
            i++;
            if (i % 16 == 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(400));
                MouseScroll(-10);
                std::this_thread::sleep_for(std::chrono::milliseconds(400));
                i = 5;
            }
            if (s > 100) {
                status = "unban";
                s = 0;
                i = 0;
            }
        }

        if (status == "unban"){
            pressTwoKeys();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            SetCursorPos(608, 616);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            if(getColor(608,616)==std::vector<int>{102,204,255}){
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                LeftClick();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(800));
            i++;
            if(i>replays){
                window.close();
            }
        }

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    status = "ban";
                }
            }
        }
    }
}
