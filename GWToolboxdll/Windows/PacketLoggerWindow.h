#pragma once

#include <GWCA/Utilities/Hook.h>

#include <ToolboxWindow.h>

class PacketLoggerWindow : public ToolboxWindow {
    PacketLoggerWindow() {};
    ~PacketLoggerWindow() { ClearMessageLog(); };
public:
    static PacketLoggerWindow& Instance() {
        static PacketLoggerWindow instance;
        return instance;
    }

    const char* Name() const override { return "Packet Logger"; }
    void Draw(IDirect3DDevice9* pDevice) override;

    void Initialize() override;
    void SaveSettings(CSimpleIni* ini) override;
    void LoadSettings(CSimpleIni* ini) override;
    void Update(float delta) override;
    static void OnMessagePacket(GW::HookStatus*, GW::Packet::StoC::PacketBase* packet);
    void Enable();
    void Disable();
    void AddMessageLog(const wchar_t* encoded);
    void SaveMessageLog();
    void ClearMessageLog();
    
private:
    std::unordered_map<std::wstring, std::wstring*> message_log;
    std::wstring* last_message_decoded = nullptr;
    uint32_t identifiers[512] = { 0 }; // Presume 512 is big enough for header size...
    GW::HookEntry hook_entry;

    struct ForTranslation {
        std::wstring in;
        std::wstring out;
    };
    std::vector<ForTranslation*> pending_translation;


    GW::HookEntry DisplayDialogue_Entry;
    GW::HookEntry MessageCore_Entry;
    GW::HookEntry MessageLocal_Entry;
    GW::HookEntry NpcGeneralStats_Entry;
};
