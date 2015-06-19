/* -----------------------------------------------------------------
 * File:    GREventReceiver.h
 * Author:  Michael Gharbi <gharbi@mit.edu>
 * Created: 2015-06-19
 * -----------------------------------------------------------------
 * 
 * 
 * 
 * ---------------------------------------------------------------*/


#ifndef GREVENTHANDLER_H_MN0GITF1
#define GREVENTHANDLER_H_MN0GITF1

#include <irrlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


namespace gr{
class GREventReceiver : public IEventReceiver
{
public:
    // This is the one method that we have to implement
    virtual bool OnEvent(const SEvent& event)
    {
        // Remember whether each key is down or up
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

        return false;
    }

    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }
    
    GREventReceiver()
    {
        for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    }

private:
    // We use this array to store the current state of each key
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

} // namespace gr
#endif /* end of include guard: GREVENTHANDLER_H_MN0GITF1 */

