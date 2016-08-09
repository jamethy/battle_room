#ifndef FRAME_H
#define FRAME_H

namespace Animation {

typedef double seconds;

class Frame {

public:

    void setEndTime(seconds endTime);

    void setTopRow(px topRow);
    void setLeftCol(px leftCol);
    void setBottomRow(px bottomRow);
    void setRightCol(px rightCol);

    void setXScale(double xScale);
    void setYScale(double yScale);

    seconds getEndTime();

    px getTopRow();
    px getLeftCol();
    px getBottomRow();
    px getRightCol();

    double getXScale();
    double getYScale();


private:
    
    seconds m_endTime;

    px m_topRow;
    px m_leftCol;
    px m_bottomRow;
    px m_rightCol;

    double m_xScale; // meters per pixel
    double m_yScale; // meters per pixel
    
}; // Frame class
} // Animation namespace
#endif // FRAME_H
