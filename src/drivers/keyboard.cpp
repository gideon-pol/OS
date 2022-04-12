#include <drivers/keyboard.h>
#include <kernel/io.h>
#include <interface.h>
#include <kernel/interrupt.h>

KeyboardDriver keyboardDriver = KeyboardDriver();

void KeyboardDriver::Initialize(){
    InterruptManager::SetHandler(0x21, (void(*)())&KeyboardDriver::HandleInterrupt);
}

void KeyboardDriver::HandleInterrupt(){
    uint8_t scanCode = IO::In(0x60);

    Interface::Clear();
    KeyCode code = KeyCode::FromScanCode(scanCode);

    char d = code.ToChar();
    Interface::Print(&d, 0, 1);
}