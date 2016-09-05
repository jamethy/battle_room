#include "sdl_helper_functions.h"

namespace BattleRoom {

SDL_Rect rectFrom(RelPixel topLeft, RelPixel bottomRight, px viewWidth, px viewHeight) {

    SDL_Rect rect;
    rect.x = topLeft.getColInt(viewWidth);
    rect.y = topLeft.getRowInt(viewHeight);
    rect.w = bottomRight.getColInt(viewWidth) - rect.x;
    rect.h = bottomRight.getRowInt(viewHeight) - rect.y;

    return rect;
}

SDL_Rect rectFrom(Pixel topLeft, Pixel bottomRight) {

    SDL_Rect rect;
    rect.x = topLeft.getColInt();
    rect.y = topLeft.getRowInt();
    rect.w = bottomRight.getColInt() - rect.x;
    rect.h = bottomRight.getRowInt() - rect.y;

    return rect;
}

InputKey::Key sdlMouseButtonToInputKey(unsigned key, unsigned clicks) {
    if (key == (unsigned) SDL_BUTTON_LEFT && clicks == 1) {
        return InputKey::Key::LeftClick;
    }
    else if (key == (unsigned) SDL_BUTTON_LEFT && clicks == 2) {
        return InputKey::Key::DoubleClick;
    }
    else if (key == (unsigned) SDL_BUTTON_MIDDLE) {
        return InputKey::Key::MiddleClick;
    }
    else if (key == (unsigned) SDL_BUTTON_RIGHT) {
        return InputKey::Key::RightClick;
    }
    else if (key == (unsigned) SDL_BUTTON_X1) {
        return InputKey::Key::MouseExtra1;
    }
    else if (key == (unsigned) SDL_BUTTON_X2) {
        return InputKey::Key::MouseExtra1;
    }
    return InputKey::Key::MouseOnly;
}

InputKey::Key sdlKeyToInputKey(SDL_Keycode code) {

    switch (code) {
        case SDLK_RETURN:
            return InputKey::Key::Return;
        case SDLK_ESCAPE:
            return InputKey::Key::Escape;
        case SDLK_BACKSPACE:
            return InputKey::Key::Backspace;
        case SDLK_TAB:
            return InputKey::Key::Tab;
        case SDLK_SPACE:
            return InputKey::Key::Space;
        case SDLK_EXCLAIM:
            return InputKey::Key::Exclaim;
        case SDLK_QUOTEDBL:
            return InputKey::Key::Quotedbl;
        case SDLK_HASH:
            return InputKey::Key::Pound;
        case SDLK_PERCENT:
            return InputKey::Key::Percent;
        case SDLK_DOLLAR:
            return InputKey::Key::Dollar;
        case SDLK_AMPERSAND:
            return InputKey::Key::Ampersand;
        case SDLK_QUOTE:
            return InputKey::Key::Quote;
        case SDLK_LEFTPAREN:
            return InputKey::Key::Leftparen;
        case SDLK_RIGHTPAREN:
            return InputKey::Key::Rightparen;
        case SDLK_ASTERISK:
            return InputKey::Key::Asterisk;
        case SDLK_PLUS:
            return InputKey::Key::Plus;
        case SDLK_COMMA:
            return InputKey::Key::Comma;
        case SDLK_MINUS:
            return InputKey::Key::Minus;
        case SDLK_PERIOD:
            return InputKey::Key::Period;
        case SDLK_SLASH:
            return InputKey::Key::ForwardSlash;
        case SDLK_0:
            return InputKey::Key::Zero;
        case SDLK_1:
            return InputKey::Key::One;
        case SDLK_2:
            return InputKey::Key::Two;
        case SDLK_3:
            return InputKey::Key::Three;
        case SDLK_4:
            return InputKey::Key::Four;
        case SDLK_5:
            return InputKey::Key::Five;
        case SDLK_6:
            return InputKey::Key::Six;
        case SDLK_7:
            return InputKey::Key::Seven;
        case SDLK_8:
            return InputKey::Key::Eight;
        case SDLK_9:
            return InputKey::Key::Nine;
        case SDLK_COLON:
            return InputKey::Key::Colon;
        case SDLK_SEMICOLON:
            return InputKey::Key::Semicolon;
        case SDLK_LESS:
            return InputKey::Key::LessThan;
        case SDLK_EQUALS:
            return InputKey::Key::Equals;
        case SDLK_GREATER:
            return InputKey::Key::GreaterThan;
        case SDLK_QUESTION:
            return InputKey::Key::Question;
        case SDLK_AT:
            return InputKey::Key::At;
        case SDLK_LEFTBRACKET:
            return InputKey::Key::Leftbracket;
        case SDLK_BACKSLASH:
            return InputKey::Key::Backslash;
        case SDLK_RIGHTBRACKET:
            return InputKey::Key::Rightbracket;
        case SDLK_CARET:
            return InputKey::Key::Caret;
        case SDLK_UNDERSCORE:
            return InputKey::Key::Underscore;
        case SDLK_BACKQUOTE:
            return InputKey::Key::Backquote;
        case SDLK_a:
            return InputKey::Key::A;
        case SDLK_b:
            return InputKey::Key::B;
        case SDLK_c:
            return InputKey::Key::C;
        case SDLK_d:
            return InputKey::Key::D;
        case SDLK_e:
            return InputKey::Key::E;
        case SDLK_f:
            return InputKey::Key::F;
        case SDLK_g:
            return InputKey::Key::G;
        case SDLK_h:
            return InputKey::Key::H;
        case SDLK_i:
            return InputKey::Key::I;
        case SDLK_j:
            return InputKey::Key::J;
        case SDLK_k:
            return InputKey::Key::K;
        case SDLK_l:
            return InputKey::Key::L;
        case SDLK_m:
            return InputKey::Key::M;
        case SDLK_n:
            return InputKey::Key::N;
        case SDLK_o:
            return InputKey::Key::O;
        case SDLK_p:
            return InputKey::Key::P;
        case SDLK_q:
            return InputKey::Key::Q;
        case SDLK_r:
            return InputKey::Key::R;
        case SDLK_s:
            return InputKey::Key::S;
        case SDLK_t:
            return InputKey::Key::T;
        case SDLK_u:
            return InputKey::Key::U;
        case SDLK_v:
            return InputKey::Key::V;
        case SDLK_w:
            return InputKey::Key::W;
        case SDLK_x:
            return InputKey::Key::X;
        case SDLK_y:
            return InputKey::Key::Y;
        case SDLK_z:
            return InputKey::Key::Z;
    }

    return InputKey::Key::MouseOnly;
}

SDL_Color toSdlColor(Color color) {
    SDL_Color sdlcolor = {
        (Uint8)color.getRed(),
        (Uint8)color.getGreen(),
        (Uint8)color.getBlue(),
        (Uint8)color.getAlpha()
    };
    return sdlcolor;
}

/**
 * \brief Utility function to check if the rectangle on view needs to be drawn
 */
bool isInRelativeFrame(RelPixel topLeft, RelPixel topRight, RelPixel botRight, RelPixel botLeft) {

    // if corner in frame
    if ( topLeft.isInFrame() || topRight.isInFrame()
        || botRight.isInFrame() || botLeft.isInFrame() ) {
        return true;
    }

    // if frame corner in object
    relpx abc = topRight.getCol() - topLeft.getCol();
    relpx abr = topRight.getRow() - topLeft.getRow();
    relpx adc = botLeft.getCol() - topLeft.getCol();
    relpx adr = botLeft.getRow() - topLeft.getRow();

    std::vector<RelPixel> corners = {
        RelPixel(0,0),
        RelPixel(0,1),
        RelPixel(1,0),
        RelPixel(1,1)
    };

    for (RelPixel& corner : corners) {

        relpx amc = corner.getCol() - topLeft.getCol();
        relpx amr = corner.getRow() - topLeft.getRow();

        relpx amab = amc*abc + amr*abr;
        relpx abab = abc*abc + abr*abr;
        relpx amad = amc*adc + amr*adr;
        relpx adad = adc*adc + adr*adr;

        if (amab > 0 && amab < abab && amad > 0 && amad < adad) {
            return true;
        }
    }
    return false;
}


SdlDrawable getSdlDrawableFrom(Object& object, View& view) {

    SdlDrawable drawable;

    Animation& animation = object.getAnimation();
    const Frame& frame = animation.getFrame(object.getAnimationState());

    Vector3D objCenter = object.getLocation();
    Quaternion ornt = object.getOrientation();
    Vector3D xOffset = ornt.getRotated(Vector3D(frame.getWidth()/2.0, 0, 0));
    Vector3D yOffset = ornt.getRotated(Vector3D(0, frame.getHeight()/2.0, 0));

    RelPixel topLeftRel = view.fromLocation(objCenter.minus(xOffset).plus(yOffset));
    RelPixel topRightRel = view.fromLocation(objCenter.plus(xOffset).plus(yOffset));
    RelPixel botRightRel = view.fromLocation(objCenter.plus(xOffset).minus(yOffset));
    RelPixel botLeftRel = view.fromLocation(objCenter.minus(xOffset).minus(yOffset));

    if (isInRelativeFrame(topLeftRel,topRightRel,botRightRel,botLeftRel)) {

        // fix to get angle until I figure out the skewing issue
        // aka the camera must be facing straight down
        Vector3D drawn = Vector3D(
                botRightRel.getCol() - topLeftRel.getCol(),
                botRightRel.getRow() - topLeftRel.getRow(),
                0.0
                );
        Vector3D drawnUnit = drawn.getUnit();
        Vector3D world = Vector3D(
                frame.getWidth(),
                frame.getHeight(),
                0.0
                ).getUnit();

        double angle = std::atan2(
                world.x()*drawnUnit.y() - world.y()*drawnUnit.x(), 
                world.dot(drawnUnit)
                );

        // Get pixel coordinates of texture
        RelPixel center = view.camera().fromLocation(objCenter);
        RelPixel unrotatedDelta(
                drawn.x()*std::sin(-angle) + drawn.y()*std::cos(-angle),
                drawn.x()*std::cos(-angle) - drawn.y()*std::sin(-angle)
                );

        RelPixel drawTL(
                center.getRow() - unrotatedDelta.getRow()/2.0,
                center.getCol() - unrotatedDelta.getCol()/2.0
                );

        RelPixel drawBR(
                center.getRow() + unrotatedDelta.getRow()/2.0,
                center.getCol() + unrotatedDelta.getCol()/2.0
                );

        // Fill drawable
        drawable.isInFrame = true;
        drawable.viewLayer = view.getLayer();
        drawable.zPosition = objCenter.z();
        drawable.angle = angle;
        drawable.sourceRect = rectFrom(frame.getTopLeft(), frame.getBottomRight());
        drawable.destinationRect = rectFrom(drawTL, drawBR, 
                view.getBottomRight().getColInt() - view.getTopLeft().getColInt(), 
                view.getBottomRight().getRowInt() - view.getTopLeft().getRowInt()
                );
        
        drawable.imageFile = animation.getImageFile();
    } 

    return drawable;

} // end getSdlDrawableFrom

} // BattleRoom namespace

