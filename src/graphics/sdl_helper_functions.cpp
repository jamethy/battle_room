#include "sdl_helper_functions.h"
#include "sdl_drawable_text.h"
#include "sdl_drawable_image.h"

#include <cmath>

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

unsigned getWindowIdFrom(SDL_Event& event) {

    unsigned windowID = (unsigned)-1;
    switch (event.type) {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            windowID = event.key.windowID;
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            windowID = event.button.windowID;
            break;
        case SDL_MOUSEWHEEL:
            windowID = event.wheel.windowID;
            break;
        case SDL_MOUSEMOTION:
            windowID = event.motion.windowID;
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_ENTER
                    || event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED
                    || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                windowID = event.window.windowID;
            }
            break;

    }
    return windowID;
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
 * \brief Utility function that uses a version of the separate axis theroem simplified for the
 * situation to check if the polygon input overlaps with the view (0-1,0-1)
 */
bool isInRelativeFrame(RelPixel topLeft, RelPixel topRight, RelPixel botRight, RelPixel botLeft) {

    // Calculate the normals of the input polygon - no need to normalize
    RelPixel normalA(topLeft.getRow() - topRight.getRow(), topLeft.getCol() - topRight.getCol());
    RelPixel normalB(botRight.getRow() - topRight.getRow(), botRight.getCol() - topRight.getCol());


    // Because the SAT does not check for one polygon completely within the other, do a quick check 
    // If the polygon is completely in the view, the top left pixel is too
    if (topLeft.getCol() >= 0 && topLeft.getCol() <= 1 && topLeft.getRow() >= 0 && topLeft.getRow() <= 1) {
        return true;
    }

    // if the view is completely in the polygon, (0,0) is inside too // (0<AM⋅AB<AB⋅AB)∧(0<AM⋅AD<AD⋅AD
    // AM = vector between (0,0) and topRight, AB = normalB, and AD = normalA
    relpx AMdotAB = -topRight.getRow()*normalB.getRow() - topRight.getCol()*normalB.getCol();
    relpx ABdotAB = normalB.getRow()*normalB.getRow() + normalB.getCol()*normalB.getCol();
    relpx AMdotAD = -topRight.getRow()*normalA.getRow() - topRight.getCol()*normalA.getCol();
    relpx ADdotAD = normalA.getRow()*normalA.getRow() + normalA.getCol()*normalA.getCol();
    if ( 0 <= AMdotAB && AMdotAB <= ABdotAB && 0 <= AMdotAD && AMdotAD <= ADdotAD ) {
        return true;
    }


    // Simplified checking normals of view ((0,1) and (1,0))

    relpx maxCol = -1, minCol = 2, maxRow = -1, minRow = 1;
    for ( const RelPixel& p : {topLeft, topRight, botRight, botLeft} ) {
        minRow = std::min(minRow,p.getRow());
        maxRow = std::max(maxRow,p.getRow());
        minCol = std::min(minCol,p.getCol());
        maxCol = std::max(maxCol,p.getCol());
    }

    if (0 > maxCol || minCol > 1) {
        return false;
    }
    if (0 > maxRow || minRow > 1) {
        return false;
    }

    // Simplified checking normals of polygon (normalA and normalB)

    relpx maxViewA = -99999, minViewA = 99999, maxViewB = -999999, minViewB = 99999;
    for (const RelPixel& p : {RelPixel(0,0), RelPixel(0,1), RelPixel(1,0), RelPixel(1,1)} ) {
        relpx pA = p.getRow()*normalA.getRow() + p.getCol()*normalA.getCol();
        relpx pB = p.getRow()*normalB.getRow() + p.getCol()*normalB.getCol();
        
        minViewA = std::min(minViewA,pA);
        maxViewA = std::max(maxViewA,pA);
        minViewB = std::min(minViewB,pB);
        maxViewB = std::max(maxViewB,pB);
    }

    relpx maxPolyA = -99999, minPolyA = 99999, maxPolyB = -999999, minPolyB = 99999;
    for (const RelPixel& p : {topLeft, topRight, botRight, botLeft} ) {
        relpx pA = p.getRow()*normalA.getRow() + p.getCol()*normalA.getCol();
        relpx pB = p.getRow()*normalB.getRow() + p.getCol()*normalB.getCol();

        minPolyA = std::min(minPolyA,pA);
        maxPolyA = std::max(maxPolyA,pA);
        minPolyB = std::min(minPolyB,pB);
        maxPolyB = std::max(maxPolyB,pB);
    }

    if (minViewA > maxPolyA || minPolyA > maxPolyA) {
        return false;
    }

    if (minViewB > maxPolyB || minPolyB > maxPolyB) {
        return false;
    }

    maxViewA = -99999, minViewA = 99999, maxViewB = -999999, minViewB = 99999;
    for (const RelPixel& p : {RelPixel(0,0), RelPixel(0,1), RelPixel(1,0), RelPixel(1,1)} ) {
        relpx pA = -p.getRow()*normalA.getRow() - p.getCol()*normalA.getCol();
        relpx pB = -p.getRow()*normalB.getRow() - p.getCol()*normalB.getCol();
        
        minViewA = std::min(minViewA,pA);
        maxViewA = std::max(maxViewA,pA);
        minViewB = std::min(minViewB,pB);
        maxViewB = std::max(maxViewB,pB);
    }

    maxPolyA = -99999, minPolyA = 99999, maxPolyB = -999999, minPolyB = 99999;
    for (const RelPixel& p : {topLeft, topRight, botRight, botLeft} ) {
        relpx pA = -p.getRow()*normalA.getRow() - p.getCol()*normalA.getCol();
        relpx pB = -p.getRow()*normalB.getRow() - p.getCol()*normalB.getCol();

        minPolyA = std::min(minPolyA,pA);
        maxPolyA = std::max(maxPolyA,pA);
        minPolyB = std::min(minPolyB,pB);
        maxPolyB = std::max(maxPolyB,pB);
    }

    if (minViewA > maxPolyA || minPolyA > maxPolyA) {
        return false;
    }

    if (minViewB > maxPolyB || minPolyB > maxPolyB) {
        return false;
    }

    return true;
}

/**
 * \brief Fills the fields of SdlDrawable common to all drawables
 * \param out drawable NonNull pointer reference of drawable to fill
 * \param objCenter Location of object in 3D space
 * \param orientation Orientation vector of object
 * \param objWidth Width of object in space
 * \param objHeight Height of object in space:w
 */
void fillBaseDrawable( SdlDrawable* drawable, View& view, 
        Vector3D objCenter, Quaternion orientation, meters objWidth, meters objHeight) {

    Vector3D xOffset = orientation.getRotated(Vector3D(objWidth/2.0, 0, 0));
    Vector3D yOffset = orientation.getRotated(Vector3D(0, objHeight/2.0, 0));

    RelPixel topLeftRel = view.fromLocation(objCenter.minus(xOffset).plus(yOffset));
    RelPixel topRightRel = view.fromLocation(objCenter.plus(xOffset).plus(yOffset));
    RelPixel botRightRel = view.fromLocation(objCenter.plus(xOffset).minus(yOffset));
    RelPixel botLeftRel = view.fromLocation(objCenter.minus(xOffset).minus(yOffset));

    if (isInRelativeFrame(topLeftRel,topRightRel,botRightRel,botLeftRel)) {

        // fix to get angle until I figure out the skewing issue
        // aka the camera must be facing straight down

        px viewHeight = view.getBottomRight().getRowInt() - view.getTopLeft().getRowInt();
        px viewWidth = view.getBottomRight().getColInt() - view.getTopLeft().getColInt();
        Pixel topLeft(topLeftRel.getRow()*viewHeight, topLeftRel.getCol()*viewWidth);
        Pixel botRight(botRightRel.getRow()*viewHeight, botRightRel.getCol()*viewWidth);

        Vector3D drawn = Vector3D(
                botRight.getCol() - topLeft.getCol(),
                botRight.getRow() - topLeft.getRow(),
                0.0
                );
        Vector3D drawnUnit = drawn.getUnit();
        Vector3D world = Vector3D( objWidth, objHeight, 0.0).getUnit();

        double angle = std::atan2(
                world.x()*drawnUnit.y() - world.y()*drawnUnit.x(), 
                world.dot(drawnUnit)
                );

        // Get pixel coordinates of texture
        RelPixel centerRel = view.fromLocation(objCenter);
        Pixel center(centerRel.getRow()*viewHeight, centerRel.getCol()*viewWidth);
        Pixel unrotatedDelta(
                drawn.x()*std::sin(-angle) + drawn.y()*std::cos(-angle),
                drawn.x()*std::cos(-angle) - drawn.y()*std::sin(-angle)
                );

        Pixel drawTL(
                center.getRow() - unrotatedDelta.getRow()/2.0,
                center.getCol() - unrotatedDelta.getCol()/2.0
                );

        Pixel drawBR(
                center.getRow() + unrotatedDelta.getRow()/2.0,
                center.getCol() + unrotatedDelta.getCol()/2.0
                );


        // Fill SdlDrawable
        drawable->setIsInFrame(true);
        drawable->setViewLayer(view.getLayer());
        drawable->setZPosition(objCenter.z());
        drawable->setAngle(angle);
        drawable->setDestinationRect(rectFrom(drawTL, drawBR));
    }
}

UniqueDrawable getSdlDrawableFrom(const DrawableText& text, View& view) {

    SdlDrawableText* drawable = new SdlDrawableText();

    // Fill base SdlDrawable
    fillBaseDrawable( drawable, view, text.getLocation(), text.getOrientation(), 
            text.getWidth(), text.getHeight()
    );

    // Fill SdlDrawableImage
    drawable->setColor(toSdlColor(text.getColor()));
    drawable->setFont(text.getFont());
    drawable->setFontSize( 150 ); // TODO calculate font size
    drawable->setText(text.getText());

    return UniqueDrawable(drawable);
}



UniqueDrawable getSdlDrawableFrom(const DrawableObject& object, View& view) {

    SdlDrawableImage* drawable = new SdlDrawableImage();

    Animation& animation = object.getAnimation();
    const Frame& frame = animation.getFrame(object.getAnimationState());

    // Fill base SdlDrawable
    fillBaseDrawable( drawable, view, object.getLocation(), object.getOrientation(),
            frame.getWidth(), frame.getHeight()
    );

    // Fill SdlDrawableImage
    drawable->setSourceRect(rectFrom(frame.getTopLeft(), frame.getBottomRight()));
    drawable->setImageFile(animation.getImageFile());

    return UniqueDrawable(drawable);

} // end getSdlDrawableFrom

} // BattleRoom namespace

