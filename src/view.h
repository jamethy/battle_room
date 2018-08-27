#ifndef VIEW_H
#define VIEW_H

#include "unique_id.h"
#include "pixel.h"
#include "resource.h"
#include "inputs.h"
#include "view_interface.h"
#include "camera.h"
#include "view_position.h"

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
        virtual ~View() {}

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
#endif // VIEW_H
