#include "battle_room/engine/animation/frame.h"

namespace Animation {


void Frame::setEndTime(seconds endTime) {
    m_endTime = endTime;
}

void Frame::setTopRow(px topRow) {
    m_topRow = topRow;
}

void Frame::setLeftCol(px leftCol) {
    m_leftCol = leftCol;
}

void Frame::setBottomRow(px bottomRow) {
    m_bottomRow = bottomRow;
}

void Frame::setRightCol(px rightCol) {
    m_rightCol = rightCol;
}

void Frame::setXScale(double xScale) {
    m_xScale = xScale;
}

void Frame::setYScale(double yScale) {
    m_yScale = yScale;
}

seconds Frame::getEndTime() {
    return m_endTime;
}

px Frame::getTopRow() {
    return m_topRow;
}

px Frame::getLeftCol() {
    return m_leftCol;
}

px Frame::getBottomRow() {
    return m_bottomRow;
}

px Frame::getRightCol() {
    return m_rightCol;
}

double Frame::getXScale() {
    return m_xScale;
}

double Frame::getYScale() {
    return m_yScale;
}

} // Animation namespace
