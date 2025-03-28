#pragma once

#include <string>
#include <map>

class TokenType
{
public:
    static constexpr const char *END_OF_FILE = "EOF";
    static constexpr const char *ILLEGAL = "ILLEGAL";

    // special skills
    static constexpr const char *RO = "(";
    static constexpr const char *FLIC = "f";
    static constexpr const char *WHIP = "^";

    // flips
    static constexpr const char *SOMERSAULT = "-";

    // shapes
    static constexpr const char *TUCK = "o";
    static constexpr const char *PIKE = "<";
    static constexpr const char *STRAIGHT = "/";

    // helpers
    static constexpr const char *DIRECTION_INDICATOR = ".";

    static constexpr const char *TRANSITION_SKILLS[] = {
        RO,
        FLIC,
        WHIP,
    };

    static inline const map<string, string> SKILL_STRINGS = {
        {"(", "RO"},
        {"f", "flic"},
        {"^", "whip"},
        {"o", "tuck"},
        {"<", "pike"},
        {"/", "straight"},
    };

    static bool isShape(const char &ch)
    {
        return ch == *TUCK || ch == *PIKE || ch == *STRAIGHT;
    }

    static bool isTransitionSkill(const char &ch)
    {
        for (const auto &skill : TRANSITION_SKILLS)
        {
            if (ch == *skill)
            {
                return true;
            }
        }
        return false;
    }

    static bool isTransitionSkill(string token)
    {
        for (const auto &skill : TRANSITION_SKILLS)
        {
            if (token == skill)
            {
                return true;
            }
        }
        return false;
    }

    static bool isIllegal(const char &ch)
    {
        vector<char> legalChars = {
            *RO,
            *FLIC,
            *WHIP,
            *SOMERSAULT,
            *TUCK,
            *PIKE,
            *STRAIGHT,
            *DIRECTION_INDICATOR,
        };

        if (isdigit(ch))
        {
            if (ch == '0')
            {
                return true;
            }
            return false;
        }
        for (const auto &legalChar : legalChars)
        {
            if (ch == legalChar)
            {
                return false;
            }
        }
        return true;
    }
};
