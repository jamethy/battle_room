#ifndef BATTLE_ROOM_VIEW_H
#define BATTLE_ROOM_VIEW_H

#include "common/unique_id.h"
#include "common/pixel.h"
#include "common/resource.h"
#include "application/inputs.h"
#include "views/view_interface.h"
#include "views/camera.h"
#include "views/view_position.h"

namespace BattleRoom {

    /**
     * \brief base class for a view - common impl
     */
    class View : public ViewInterface {

    public:

        // constructors
        View(ResourceDescriptor settings, int windowWidth, int windowHeight);

        View(const View &original);

        View &operator=(const View &original);

        ~View() override = default;

        // getters and setters
        void setLayer(int layer);

        // inherited
        Inputs handleInputs(Inputs inputs) override;

        void adjustForResize(int width, int height, int oldWidth, int oldHeight) override;

        RelPixel fromLocation(Vector3D point) override;

        Vector3D zeroPlaneIntersection(Pixel point) const override;

        Pixel getTopLeft() const override;

        Pixel getBottomRight() const override;

        int getLayer() const override;

        UniqueId getUniqueId() const override;

        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

        int getViewWidth();

        int getViewHeight();

    protected:

        UniqueCamera m_camera;

    private:

        /**
         * \brief Utility function used to recalculate camera FOV
         */
        void recalculateVerticalFov();

        UniqueId m_uniqueId;
        int m_layer = 0; //< higher numbers are rendered first (therefore then covered up)
        ViewPosition m_position;

    }; // View class
} // BattleRoom namespace
#endif // BATTLE_ROOM_VIEW_H
