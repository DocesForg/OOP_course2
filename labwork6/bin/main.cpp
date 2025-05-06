#include "lib/parser.h"
#include <iostream>

int main(int, char**) {
    // Парсим файл config.omfl
    auto root = omfl::parse(std::filesystem::path("D:/Desktop/labwork6/example/config.omfl"));

    // Выводим секцию [common]
    const auto& common = *root.sections.at("common");
    std::cout << "[common]\n";
    std::cout << "name = \"" << common.values.at("name").AsString() << "\"\n";
    std::cout << "description = \"" << common.values.at("description").AsString() << "\"\n";
    std::cout << "version = " << common.values.at("version").AsInt() << "\n\n";

    // Выводим секцию [servers]
    const auto& servers = *root.sections.at("servers");

    // Выводим вложенную секцию [servers.first]
    const auto& first = *servers.sections.at("first");
    std::cout << "[servers.first]\n";
    std::cout << "enabled = " << (first.values.at("enabled").AsBool() ? "true" : "false") << "\n";
    std::cout << "ip = \"" << first.values.at("ip").AsString() << "\"\n";
    const auto& ports_first = first.values.at("ports").AsArray();
    std::cout << "ports = [ ";
    for (size_t i = 0; i < ports_first.size(); ++i) {
        std::cout << ports_first[i].AsInt();
        if (i != ports_first.size() - 1)
            std::cout << ", ";
    }
    std::cout << " ]\n\n";

    // Выводим вложенную секцию [servers.second]
    const auto& second = *servers.sections.at("second");
    std::cout << "[servers.second]\n";
    std::cout << "enabled = " << (second.values.at("enabled").AsBool() ? "true" : "false") << "\n";
    std::cout << "ip = \"" << second.values.at("ip").AsString() << "\"\n";
    const auto& ports_second = second.values.at("ports").AsArray();
    std::cout << "ports = [ ";
    for (size_t i = 0; i < ports_second.size(); ++i) {
        std::cout << ports_second[i].AsInt();
        if (i != ports_second.size() - 1)
            std::cout << ", ";
    }
    std::cout << " ]\n";

    return 0;
}