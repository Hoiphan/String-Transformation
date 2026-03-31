#include "app/App.hpp"

#include "Config.hpp"
#include "middlewares/JsonRequest.hpp"
#include "utils/Utils.hpp"

#include <algorithm>
#include <crow/app.h>
#include <crow/http_request.h>
#include <crow/http_response.h>
#include <crow/json.h>
#include <string>
#include <vector>

Utils::Result<> App::Init()
{
    SetupRoutes();
    m_App.port(Config::PORT).multithreaded();
    return Utils::Result<>();
}

void App::Run()
{
    m_App.run();
}

void App::SetupRoutes()
{
    CROW_LOG_INFO << "Setting up routes...";

    CROW_ROUTE(m_App, "/")([]() {
        auto page = crow::mustache::load("index.html");
        return page.render();
    });

    CROW_ROUTE(m_App, "/json")
        .CROW_MIDDLEWARES(m_App, JsonRequest)
        .methods("POST"_method)([](const crow::request& req) {
            auto reqJson = crow::json::load(req.body);

            if (!reqJson)
                return crow::response(crow::status::BAD_REQUEST, "Invalid JSON data");

            return crow::response(crow::status::OK, crow::json::wvalue(reqJson));
        });

    CROW_ROUTE(m_App, "/calculate")
        .CROW_MIDDLEWARES(m_App, JsonRequest)
        .methods("POST"_method)([](const crow::request& req) {
            auto reqJson = crow::json::load(req.body);
            if (!reqJson)
                return crow::response(crow::status::BAD_REQUEST, "Invalid JSON data");

            std::string source = reqJson["source"].s();
            std::string target = reqJson["target"].s();

            try
            {
                // Try to do the math
                auto calc_result = Utils::calculate_edit_distance(source, target);

                crow::json::wvalue::list actions_json;
                for (const auto& action : calc_result.actions)
                {
                    actions_json.push_back(action);
                }

                crow::json::wvalue res(
                    {{"actions_num", calc_result.actions_num}, {"actions", std::move(actions_json)}});

                return crow::response(crow::status::OK, res);
            }
            catch (const std::invalid_argument& e)
            {
                // If the math function throws an error, catch it here!
                return crow::response(crow::status::BAD_REQUEST, e.what());
            }
        });
}
