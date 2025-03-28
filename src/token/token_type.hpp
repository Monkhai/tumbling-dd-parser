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

    static inline const map<string, string> TWIST_STRINGS = {
        {"1", "half"},
        {"2", "full"},
        {"4", "double full"},
        {"6", "triple full"},
        {"8", "quad full"},
    };

    static inline const map<string, string> FLIP_STRINGS = {
        {"1", ""},
        {"2", "double"},
        {"3", "triple"},
        {"4", "quad"},
    };

    static inline const map<string, string> SHAPE_STRINGS = {
        {"o", "tuck"},
        {"<", "pike"},
        {"/", "straight"},
    };

    static inline const map<int, string> DIRECTION_STRINGS = {
        {0, "back"},
        {1, "front"},
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
