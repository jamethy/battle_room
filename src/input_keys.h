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

        // Numbers row
        Zero, One, Two, Three, Four,
        Five, Six, Seven, Eight, Nine,
        RightParen, Exclaim, At, Pound, Dollar, Percent,
        Caret, Ampersand, Asterisk, LeftParen,

        // Right keys
        Minus, Underscore,
        Equals, Plus,
        LeftBracket, RightBracket,
        LeftCurlyBracket, RightCurlyBracket,
        Semicolon, Colon,
        Quote, DoubleQuote,
        Comma, LessThan,
        Period, GreaterThan,
        ForwardSlash, Question,

        // Misc keys
        Escape, Backquote, Tilde, Tab,
        Backspace, Backslash, Pipe, Return,
        Space, Left, Up, Down, Right,

        Home, End, PageUp, PageDown, Insert, Delete, Divide, Multiply, Subtract, Add, Decimal,

        // Function Keys
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12
    };

    enum Motion {
        PressedDown,
        Released,
        Scroll,
        None
    };

    enum Modifier {
        Plain,
        Shift,
        Ctrl,
        Alt,
    };

} // InputKey namespace
#endif // INPUT_KEYS_H
