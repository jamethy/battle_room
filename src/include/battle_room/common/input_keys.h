#ifndef INPUT_KEYS_H
#define INPUT_KEYS_H

namespace InputKey {

    enum Key {

        // Mouse input
        MouseOnly, LeftClick, DoubleClick, MiddleClick,
        RightClick, MouseExtra1, MouseExtra2,

        // Letter keys
        A, B, C, D, E, F, G, H, I,
        J, K, L, M, N, O, P, Q, R,
        S, T, U, V, W, X, Y, Z,

        // Numbers
        Zero, One, Two, Three, Four,
        Five, Six, Seven, Eight, Nine,

        // Number alternates
        Exclaim, At, Pound, Dollar, Percent,
        Caret, Ampersand, Asterisk, Leftparen, Rightparen,

        // Right keys
        Minus, Underscore,
        Equals, Plus,
        Leftbracket,
        Rightbracket,
        Semicolon, Colon,
        Quote, Quotedbl,
        Comma, LessThan,
        Period, GreaterThan,
        ForwardSlash, Question,

        // Misc keys
        Escape, Backquote, Tab,
        Backspace, Backslash, Return,
        Space
    };

    enum Motion {
        PressedDown,
        Released,
        Scroll,
        None
    };

} // InputKey namespace
#endif // INPUT_KEYS_H
