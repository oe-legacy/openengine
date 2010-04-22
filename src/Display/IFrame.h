// Frame interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _INTERFACE_FRAME_H_
#define _INTERFACE_FRAME_H_

#include <Display/ICanvas.h>
#include <Core/IModule.h>

namespace OpenEngine {
namespace Display {

    class StereoCamera;
    using Core::IModule;
    
/**
 * Frame options.
 *
 * @enum FrameOption
 */
enum FrameOption {
    FRAME_OPENGL     = 0x00000002,
    FRAME_NOBORDER   = 0x00000020,
    FRAME_FULLSCREEN = 0x80000000,
    FRAME_STEREO     = 0x00000100
};

/**
 * Frame module interface.
 *
 * A frame represents a top-level canvas with additional methods to
 * control features such as fullscreen mode and other video
 * attributes.
 *
 * @see ICanvas
 * @class IFrame IFrame.h Display/IFrame.h
 */
class IFrame : public virtual ICanvas, public virtual IModule {
public:
    /**
     * Frame destructor.
     */
    virtual ~IFrame() {};

    /**
     * Is this frame focused.
     *
     * @return True if in focus.
     */
    virtual bool IsFocused() const = 0;
    
    /**
     * Get frame options
     *
     * @return Frame options
     */
    virtual FrameOption GetOptions() const = 0;

    /**
     * Get frame option
     *
     * @return bool is the option set
     */
    virtual bool GetOption(const FrameOption option) const = 0;

    /**
     * Set frame options
     * Must be supported as long as the module initialization method
     * has not been invoked.
     * After initialization the behavior is up to the implementation.
     *
     * @return options Frame options
     */
    virtual void SetOptions(const FrameOption options) = 0;

    /**
     * Toggle frame options
     * Must be supported as long as the module initialization method
     * has not been invoked.
     * After initialization the behavior is up to the implementation.
     */
    virtual void ToggleOption(const FrameOption option) = 0;

    /**
     * Check if an option is set.
     *
     * @param o Frame option(s) to check
     * @return True if set
     */
    bool IsOptionSet(const FrameOption o) const {
        return (o & GetOptions()) == o;
    }

    /**
     * Get the stereocamera for use when stereo rendering is enabled.
     * The stereo camera is used to calculate the position of two
     * addition eye cameras based on the current viewing volume.
     *
     * @return The stereo camera.
     */
    virtual StereoCamera& GetStereoCamera() const = 0;
};

} // NS Display
} // NS OpenEngine

#endif // _INTERFACE_FRAME_H_
