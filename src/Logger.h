//
// Created by james on 1/12/19.
//

#ifndef PROJECT_DEATHBLADE_LOGGER_H
#define PROJECT_DEATHBLADE_LOGGER_H

#include <string>
#include <iostream>
#include <string>
#include <initializer_list>

namespace BattleRoom {

    template<typename T>
    void printStuff(T t) {
        std::cout << t << std::endl;
    }

    template<typename T, typename... Args>
    void printStuff(T t, Args... args) {
        std::cout << t;
        printStuff(args...);
    }

    long getTimeStamp();

    template<typename T, typename... Args>
    void print(const std::string &levelLabel, T t, Args... args) {
        printStuff("[", getTimeStamp(), "][", levelLabel, "]: ", t, args...);
    }


    class Log {
    public:

        typedef enum {
            DEBUG,
            INFO,
            WARN,
            ERROR,
            FATAL, // exits program?
            NONE
        } Level;

        static Level getLevel();

        static void setLevel(Level level);

        template<typename T, typename... Args>
        static void debug(T t, Args... args) {
            if (m_level <= DEBUG) {
                print("DEBUG", t, args...);
            }
        }

        template<typename T, typename... Args>
        static void info(T t, Args... args) {
            if (m_level <= INFO) {
                print("INFO", t, args...);
            }
        }

        template<typename T, typename... Args>
        static void warn(T t, Args... args) {
            if (m_level <= WARN) {
                print("WARN", t, args...);
            }
        }

        template<typename T, typename... Args>
        static void error(T t, Args... args) {
            if (m_level <= ERROR) {
                print("ERROR", t, args...);
            }
        }

        template<typename T, typename... Args>
        static void fatal(T t, Args... args) {
            if (m_level <= FATAL) {
                print("FATAL", t, args...);
            }
        }

    private:

        static Level m_level;

    }; // Logger class
} // BattleRoom namespace
#endif //PROJECT_DEATHBLADE_LOGGER_H
