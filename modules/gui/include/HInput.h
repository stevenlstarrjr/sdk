#pragma once

#include <cstdint>

namespace Ht {

// Based on generic key codes, mapping to XKB/Qt standards
enum class HKey : uint32_t {
    Unknown = 0,
    Escape = 0x01000000,
    Tab,
    Backtab,
    Backspace,
    Return,
    Enter,
    Insert,
    Delete,
    Pause,
    Print,
    SysReq,
    Clear,
    Home,
    End,
    Left,
    Up,
    Right,
    Down,
    PageUp,
    PageDown,
    Shift,
    Control,
    Meta,
    Alt,
    CapsLock,
    NumLock,
    ScrollLock,
    
    // ASCII 
    Space = 0x20,
    A = 0x41,
    B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    
    F1 = 0x01000030,
    F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12
};

enum class HModifier : uint32_t {
    NoModifier = 0x00,
    ShiftModifier = 0x02000000,
    ControlModifier = 0x04000000,
    AltModifier = 0x08000000,
    MetaModifier = 0x10000000,
    KeypadModifier = 0x20000000
};

inline HModifier operator|(HModifier a, HModifier b) {
    return static_cast<HModifier>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

inline HModifier operator&(HModifier a, HModifier b) {
    return static_cast<HModifier>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}

struct HKeyEvent {
    HKey key;
    HModifier modifiers;
    std::string text; // UTF-8 text if available
    bool pressed;
    bool isAutoRepeat;
    uint32_t nativeScanCode;
    uint32_t nativeVirtualKey;
    bool accepted = false;
    
    void accept() { accepted = true; }
    void ignore() { accepted = false; }
};

} // namespace Ht
