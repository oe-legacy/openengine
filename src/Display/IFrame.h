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

#include <Core/IModule.h>

namespace OpenEngine {
namespace Display {
    class ICanvas;
    
    using Core::IModule;
    
/**
 * Frame options.
 *
 * @enum FrameOption
 */
enum FrameOption {
    FRAME_NONE       = 0x00000000,
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
class IFrame : public virtual IModule {
public:
    /**
     * Frame destructor.
     */
    virtual ~IFrame() {};

    /**
     * Get frame width.
     *
     * @return Frame width
     */
    virtual unsigned int GetWidth() const = 0;

    /**
     * Get frame height.
     *
     * @return Frame height
     */
    virtual unsigned int GetHeight() const = 0;
    
    /**
     * Get frame depth.
     *
     * @return Frame depth
     */
    virtual unsigned int GetDepth() const = 0;

    /**
     * Set frame width.
     * Must be supported as long as the module initialization method
     * has not been invoked.
     * After initialization the behavior is up to the implementation.
     *
     * @param width Frame width
     */
    virtual void SetWidth(const unsigned int width) = 0;

    /**
     * Set frame height.
     * Must be supported as long as the module initialization method
     * has not been invoked.
     * After initialization the behavior is up to the implementation.
     *
     * @param height Frame height
     */
    virtual void SetHeight(const unsigned int height) = 0;
    
    /**
     * Set frame depth.
     * Must be supported as long as the module initialization method
     * has not been invoked.
     * After initialization the behavior is up to the implementation.
     *
     * @param depth Frame depth
     */
    virtual void SetDepth(const unsigned int depth) = 0;

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
     * Set the canvas that will be mapped onto this frame.
     *
     * @param canvas The canvas that will be mapped onto this frame.
     */
    virtual void SetCanvas(ICanvas* canvas) = 0;

    /**
     * Get the canvas that will be mapped onto this frame.
     *
     * @return The canvas that will be mapped onto this frame.
     */
    virtual ICanvas* GetCanvas() = 0;
};

} // NS Display
} // NS OpenEngine

#endif // _INTERFACE_FRAME_H_
