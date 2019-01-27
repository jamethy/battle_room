#include "rel_pixel.h"
#include "string_utils.h"

#include <cmath>
#include <string>

namespace BattleRoom {

// apply settings

    void RelPixel::applySettings(ResourceDescriptor settings) {

        std::vector<std::string> values = split(settings.getValue(), ',');
        if (values.size() == 2) {
            setRow(toRelPx(values[0]));
            setCol(toRelPx(values[1]));
        }

        ResourceDescriptor sub = settings.getSubResource("Col");
        if (isNotEmpty(sub.getValue())) {
            setCol(toRelPx(sub.getValue()));
        }

        sub = settings.getSubResource("Row");
        if (isNotEmpty(sub.getValue())) {
            setRow(toRelPx(sub.getValue()));
        }
    }

    ResourceDescriptor RelPixel::getSettings() const {
        ResourceDescriptor rd;
        std::vector<ResourceDescriptor> subs = {};

        subs.emplace_back("Col", std::to_string(getCol()));
        subs.emplace_back("Row", std::to_string(getRow()));

        rd.setSubResources(subs);
        return rd;
    }

// Constructors

    RelPixel::RelPixel() {}

    RelPixel::RelPixel(relpx row, relpx col)
            : m_row(row), m_col(col) {}

    int RelPixel::getRowInt(int viewHeight) const {
        return (int) std::round(m_row * viewHeight);
    }

    int RelPixel::getColInt(int viewWidth) const {
        return (int) std::round(m_col * viewWidth);
    }

// getters and setters

    void RelPixel::setRow(relpx row) {
        m_row = row;
    }

    void RelPixel::setCol(relpx col) {
        m_col = col;
    }

    relpx RelPixel::getRow() const {
        return m_row;
    }

    relpx RelPixel::getCol() const {
        return m_col;
    }

    relpx toRelPx(std::string s) {
        return stod(s);
    }

} // namespace BattleRoom
