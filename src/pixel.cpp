#include "pixel.h"
#include "string_utils.h"

#include <cmath>
#include <string>

namespace BattleRoom {

// apply settings

    void Pixel::applySettings(ResourceDescriptor settings) {

        std::vector<std::string> values = split(settings.getValue(), ',');
        if (values.size() == 2) {
            setRow(toPx(values[0]));
            setCol(toPx(values[1]));
        }

        ResourceDescriptor sub = settings.getSubResource("Col");
        if (isNotEmpty(sub.getValue())) {
            setCol(toPx(sub.getValue()));
        }

        sub = settings.getSubResource("Row");
        if (isNotEmpty(sub.getValue())) {
            setRow(toPx(sub.getValue()));
        }

    }

// constructors

    Pixel::Pixel() {}

    Pixel::Pixel(px row, px col)
            : m_row(row), m_col(col) {}

    int Pixel::getRowInt() const {
        return (int) std::round(m_row);
    }

    int Pixel::getColInt() const {
        return (int) std::round(m_col);
    }

    bool Pixel::isBetween(Pixel topLeft, Pixel bottomRight) {
        return (topLeft.getCol() < getCol() && topLeft.getRow() < getRow() &&
                bottomRight.getCol() > getCol() && bottomRight.getRow() > getRow());
    }

// getters and setters

    void Pixel::setRow(px row) {
        m_row = row;
    }

    void Pixel::setCol(px col) {
        m_col = col;
    }

    px Pixel::getRow() const {
        return m_row;
    }

    px Pixel::getCol() const {
        return m_col;
    }

    px toPx(std::string s) {
        return stod(s);
    }

} // namespace BattleRoom
