#include "Utils.hpp"

namespace Utils
{
    std::string GetEnv(std::string_view varName, std::string_view defaultValue)
    {
        const char* val = std::getenv(varName.data());
        return (val && val[0] != '\0') ? std::string(val) : std::string(defaultValue);
    }

    EditDistanceResult calculate_edit_distance(const std::string& source, const std::string& target)
    {
        if (source.length() > 1000 || target.length() > 1000)
        {
            throw std::invalid_argument("Source and target strings must be at most 1000 characters long");
        }
        int n = source.length();
        int m = target.length();

        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));

        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= m; j++)
            {
                if (i == 0)
                    dp[i][j] = j;
                else if (j == 0)
                    dp[i][j] = i;
                else if (source[i - 1] == target[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = 1 + std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }

        std::vector<std::string> actions;
        int i = n, j = m;
        while (i > 0 || j > 0)
        {
            if (i > 0 && j > 0 && source[i - 1] == target[j - 1])
            {
                i--;
                j--;
            }
            else if (j > 0 && (i == 0 || dp[i][j - 1] <= dp[i - 1][j] && dp[i][j - 1] <= dp[i - 1][j - 1]))
            {
                actions.push_back("Insert '" + std::string(1, target[j - 1]) + "'");
                j--;
            }
            else if (i > 0 && (j == 0 || dp[i - 1][j] <= dp[i][j - 1] && dp[i - 1][j] <= dp[i - 1][j - 1]))
            {
                actions.push_back("Delete '" + std::string(1, source[i - 1]) + "'");
                i--;
            }
            else
            {
                actions.push_back("Replace '" + std::string(1, source[i - 1]) + "' with '" +
                                  std::string(1, target[j - 1]) + "'");
                i--;
                j--;
            }
        }
        std::reverse(actions.begin(), actions.end());

        return {dp[n][m], actions};
    }

} // namespace Utils
