
class Clip {
private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;

    std::ratio m_scaleX;
    std::ratio m_scaleY;
        
};


class AnimationInfoNeeded {
private:
    DoublePoint a_pos;
    double a_rot;
    std::string a_animation;
        Frame
            Clip
    double a_animation_time;

};

class IntersectionInfoNeeded {
private:
    DoublePoint a_pos;
    double a_rot;
    std::string a_animation;
        Frame
            Boundary
    double a_animation_time;

};


class Boudary {

public:
    double getRadius();


}

class Frame {

private:
    Clip m_clip;
    Time endtime;
    Boundary m_intersection;

public:
    const Clip& getClip();
    const Boundary& getBoundary();
    double getEndTime();
};


class Animation {

private:
    std::vector<Frame> m_frames;
    std::string m_nextAnimation;
    std::string m_spriteFile;

public:
    double getEndTime();
    std::string getNextAnimation();
    const Frame& getFrame(const double time);
};

class AnimationService {

private:
    std::vector<Animation> m_animations;

    AnimationService& getSingleton();

public:
    static void addAnimation(const Animation animation);
    static const Animation& getAnimation(const std::string& name);
};
