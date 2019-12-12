#import "Config.h"
#import "hidtrackerimpl_osx.h"
#include <CoreFoundation/CoreFoundation.h>
#include <Cocoa/Cocoa.h>

HIDTrackerImplOSX::HIDTrackerImplOSX()
    :mMachPortRef(0), mKeyboardEventSrc(0)
{

}

HIDTrackerImplOSX::~HIDTrackerImplOSX()
{

}


bool HIDTrackerImplOSX::isPossible()
{
    if (AXIsProcessTrustedWithOptions != NULL)
    {
        // 10.9 and later
        const void * keys[] = { kAXTrustedCheckOptionPrompt };
        const void * values[] = { kCFBooleanTrue };

        CFDictionaryRef options = CFDictionaryCreate(
                                      kCFAllocatorDefault,
                                      keys,
                                      values,
                                      sizeof(keys) / sizeof(*keys),
                                      &kCFCopyStringDictionaryKeyCallBacks,
                                      &kCFTypeDictionaryValueCallBacks);

        return AXIsProcessTrustedWithOptions(options);
    }
    else
        return AXAPIEnabled() != 0;
}

time_t LastKeyboardActivityTime = 0;
time_t LastMouseActivityTime = 0;

CGEventRef eventTapFunction(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon)
{
    if (type != NX_KEYUP && type != NX_OMOUSEDOWN && type != NX_OMOUSEUP && type != NX_OMOUSEDRAGGED &&
            type != NX_LMOUSEUP && type != NX_LMOUSEDOWN && type != NX_RMOUSEUP && type != NX_RMOUSEDOWN &&
            type != NX_MOUSEMOVED && type != NX_LMOUSEDRAGGED && type != NX_RMOUSEDRAGGED)
        return event;

    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    NSEvent* sysEvent = [NSEvent eventWithCGEvent:event];
    if (type == NX_KEYUP && [sysEvent type] == NSKeyUp)
        LastKeyboardActivityTime = time(NULL);
    else
        LastMouseActivityTime = time(NULL);

    [pool release];
    return event;
}

bool HIDTrackerImplOSX::start()
{
    LastKeyboardActivityTime = LastMouseActivityTime = time(NULL);
    CGEventMask keyboardMask = CGEventMaskBit(kCGEventKeyUp);
    CGEventMask mouseMask = CGEventMaskBit(kCGEventMouseMoved) | CGEventMaskBit(kCGEventLeftMouseDown) |
                            CGEventMaskBit(kCGEventRightMouseDown);

    CGEventMask mask = keyboardMask + mouseMask;// + mouseMask;//CGEventMaskBit(kCGEventKeyDown) | CGEventMaskBit(kCGEventMouseMoved);

    // Try to create keyboard-only hook. It will fail if Assistive Devices are not set.
    mMachPortRef =  CGEventTapCreate(
                        kCGAnnotatedSessionEventTap,
                        kCGTailAppendEventTap, // kCGHeadInsertEventTap
                        kCGEventTapOptionListenOnly,
                        keyboardMask,
                        (CGEventTapCallBack)eventTapFunction,
                        0 );
    if (!mMachPortRef)
        return false;
    else
        CFRelease(mMachPortRef);

    mMachPortRef = CGEventTapCreate(
                       kCGAnnotatedSessionEventTap,
                       kCGTailAppendEventTap, // kCGHeadInsertEventTap
                       kCGEventTapOptionListenOnly,
                       mask,
                       (CGEventTapCallBack)eventTapFunction,
                       0 );
    if (!mMachPortRef)
        return false;

    mKeyboardEventSrc = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, mMachPortRef, 0);
    if ( !mKeyboardEventSrc )
    {
        CFRelease(mMachPortRef); mMachPortRef = 0;
        return false;
    }

    CFRunLoopRef runLoop = CFRunLoopGetCurrent();
    if ( !runLoop )
    {
        CFRelease(mMachPortRef); mMachPortRef = 0;
        return false;
    }

    CFRunLoopAddSource(runLoop,  mKeyboardEventSrc, kCFRunLoopDefaultMode);
    return true;
}

void HIDTrackerImplOSX::stop()
{
    if (mKeyboardEventSrc && mMachPortRef)
        CFRunLoopRemoveSource(CFRunLoopGetCurrent(), mKeyboardEventSrc, kCFRunLoopDefaultMode);
    if (mKeyboardEventSrc)
        CFRelease(mKeyboardEventSrc);
    if (mMachPortRef)
        CFRelease(mMachPortRef);

    mKeyboardEventSrc = NULL;
    mMachPortRef = NULL;
}

bool HIDTrackerImplOSX::isUserActive()
{
    if (!LastKeyboardActivityTime && !LastMouseActivityTime)
    {
        LastKeyboardActivityTime = LastMouseActivityTime = time(NULL);
        return true;
    }

    time_t current = time(NULL);
    if (current - LastKeyboardActivityTime <= mInterval)
        return true;

    if (current - LastMouseActivityTime <= mInterval)
        return true;

    return false;
}

void HIDTrackerImplOSX::resetUserActive()
{
    LastKeyboardActivityTime = 0;
    LastMouseActivityTime = 0;
}
