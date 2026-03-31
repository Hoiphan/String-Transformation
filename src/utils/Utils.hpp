#pragma once

#include <crow/common.h>
#include <expected>
#include <string>
#include <string_view>

namespace Utils
{
    struct ErrorData
    {
        crow::status statusCode;
        std::string message;
    };

    template<typename T = void>
    using Result = std::expected<T, ErrorData>;
    using Error = std::unexpected<ErrorData>;

    std::string GetEnv(std::string_view varName, std::string_view defaultValue);
    struct EditDistanceResult
    {
        int actions_num;
        std::vector<std::string> actions;
    };

    EditDistanceResult calculate_edit_distance(const std::string& source, const std::string& target);
} // namespace Utils
